#include "heuristica.hpp"

Heuristica::Heuristica(std::default_random_engine &t_rng, const std::string &t_instancia_nome, const int &t_tam_pop, const int qtd_turmas_heuristica, const int qtd_rept_busca_local, const float &t_peso_janela, const float &t_peso_sexto)
{
    this->m_rng = t_rng;
    this->m_instancia_nome = t_instancia_nome;
    this->m_tamanho_populacao = t_tam_pop;
    this->m_qtd_turmas_heuristica = qtd_turmas_heuristica;
    this->m_qtd_rept_busca_local = qtd_rept_busca_local;
    this->m_peso_janela = t_peso_janela;
    this->m_peso_sexto = t_peso_sexto;

    for (int i = 0; i < m_tamanho_populacao; i++)
    {
        this->m_solucoes.push_back(new Solucao(m_rng, m_instancia_nome, i));
    }
}

void Heuristica::inicializar(std::chrono::_V2::steady_clock::time_point *m_tempo_inicial)
{
    this->m_tempo_inicial = m_tempo_inicial;
    // Heuristica inicial para preencher solucoes vazias
    heuristica_construtiva(0);
    ordenar_solucoes();
    // exibir_solucoes();

    // Heuristica: fix-and-optimize
    std::map<int, Solucao *> solucoes_map{};
    if (m_qtd_turmas_heuristica == 0)
    {
        solucoes_map = pos_processamento_dinamico();
    }
    else
    {
        solucoes_map = pos_processamento_estatico();
    }
    ordenar_solucoes();
    for (auto sol_final : m_solucoes)
    {
        output.salvar_analise("data/output/", sol_final, 0, 0, "FINAL", 0, *m_tempo_inicial);
    }
    exibir_solucoes();

    // salvando solucao em arquivo .tex
    auto melhor_solucao = get_melhor_solucao();
    if (melhor_solucao == nullptr)
    {
        std::cout << "Nenhuma soluço encontrada. Encerrando com erro 02" << std::endl;
        return;
    }
    else
    {
        std::cout << "\n\n\n\n\n\n\n\n\n\n\nMAIS MELHOR SOLUCAO\n\n"
                  << std::endl;
        std::cout << "A solução ID " << melhor_solucao->get_id_solucao() << " com o valor na função objetivo de " << melhor_solucao->get_valor_solucao() << " pontos." << std::endl;
        melhor_solucao->exibir_solucao();
    }
}

std::vector<Disciplina *> Heuristica::ordenar_disciplinas(const int &rand_metodo, Solucao *solucao)
{

    std::vector<Disciplina *> t_disciplinas_ordenadas = (*solucao).get_instancia()->get_lista_disciplinas();

    switch (rand_metodo)
    {

    // Caso 1: Ordenar disciplinas por maior CH-MIN (tamanho)
    case 1:
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_ch_min() > rhs->get_ch_min(); });
        break;

    // Caso 2: Ordenar disciplinas por Menor Split (tamanho)
    case 2:
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_split() < rhs->get_split(); });
        break;

    // Caso 3: Ordenar disciplina por prioriedade de CH-MIN e Split combinadas (tamanho)
    case 3:
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return (lhs->get_ch_min() > rhs->get_ch_min()) && (lhs->get_split() < rhs->get_split()); });
        break;

    case 4:
        std::shuffle(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), m_rng);
        break;

    // Caso base: ordenação por ordem de leitura da instância
    default:
        std::shuffle(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), m_rng);
        break;
    }

    return t_disciplinas_ordenadas;
}

void Heuristica::heuristica_construtiva(int t_iteracao)
{
    GravarArquivo ga = GravarArquivo();

    for (auto it : this->m_solucoes)
    {
        int rand_switch = 1 + (rand() % 4);
        auto disciplinas_ordenadas = ordenar_disciplinas(rand_switch, it);
        bool deu_certo = it->popular_solucao(disciplinas_ordenadas);
        avaliar_solucao(it, deu_certo);

        // Salvando parametros da solucao em csv para futura analise
        output.salvar_analise("data/output/", it, t_iteracao, 0, "CONSTRUTIVA", rand_switch, *m_tempo_inicial);
    }
}

void Heuristica::exibir_solucoes()
{
    for (auto solucao : m_solucoes)
    {
        std::cout << "Solucao " << solucao->get_id_solucao() << " | Avaliada em: " << solucao->get_valor_solucao() << std::endl;
        solucao->exibir_solucao();
    }
    std::cout << "Solucoes Exibidas: void return (no problems found)" << std::endl;
}

void Heuristica::debug_heuristica()
{
    /* ---------------DEBUG BLOCK---------------------
    ** ! VERIFICAR COPIA DE PRT ADDR !
    */
    std::cout << REDB "\n\nDEBUG - ENDERECOS DISCIPLINAS\n" NC << std::endl;
    for (auto it : this->m_solucoes)
    {
        it->debug_vector_disciplina_addr();
    }
}

void Heuristica::ordenar_solucoes()
{
    std::sort(m_solucoes.begin(), m_solucoes.end(), [](Solucao *s1, Solucao *s2)
              { return s1->get_valor_solucao() < s2->get_valor_solucao(); });
}

void Heuristica::avaliar_solucao(Solucao *t_solucao, bool t_factibilidade)
{
    int sexto_horario = calcular_sexto_horario_turma(t_solucao);
    int janela_prof = calcular_janela_professor(t_solucao);

    t_solucao->set_qtd_sexto_horario(sexto_horario);
    t_solucao->set_qtd_janela(janela_prof);
    t_solucao->set_peso_sexto(m_peso_sexto);
    t_solucao->set_peso_janela(m_peso_janela);
    t_solucao->set_factivel(t_factibilidade);
    if (t_factibilidade == true)
    {
        t_solucao->set_valor_solucao((m_peso_sexto * sexto_horario) + (m_peso_janela * janela_prof));
    }
    else
    {
        // t_solucao->set_valor_avaliacao(std::numeric_limits<float>::max());
        t_solucao->set_valor_solucao(999999);
    }
}

int Heuristica::calcular_janela_professor(Solucao *t_solucao)
{

    int janela = 0;

    auto profs = t_solucao->get_instancia()->get_lista_professores();
    for (auto p : profs)
    {
        std::array<std::array<int, 16>, 6> f_dispo = p->get_disponibilidade();

        for (int dia = 0; dia < 6; dia++)
        {

            int primeiro_slot = 0;
            int ultimo_slot = 0;

            // Manhã
            for (int slot = 0; slot < 6; slot++)
            {
                if (f_dispo[dia][slot] > 0)
                {
                    primeiro_slot = slot;
                    break;
                }
            }
            for (int slot = 5; slot >= 0; slot--)
            {
                if (f_dispo[dia][slot] > 0)
                {
                    ultimo_slot = slot;
                    break;
                }
            }

            for (int slot = primeiro_slot + 1; slot < ultimo_slot; slot++)
            {
                if (f_dispo[dia][slot] == 0)
                {
                    janela += 1;
                }
            }

            primeiro_slot = 0;
            ultimo_slot = 0;

            // Tarde
            for (int slot = 6; slot < 12; slot++)
            {
                if (f_dispo[dia][slot] > 0)
                {
                    primeiro_slot = slot;
                    break;
                }
            }
            for (int slot = 11; slot >= 6; slot--)
            {
                if (f_dispo[dia][slot] > 0)
                {
                    ultimo_slot = slot;
                    break;
                }
            }

            for (int slot = primeiro_slot + 1; slot < ultimo_slot; slot++)
            {
                if (f_dispo[dia][slot] <= 0)
                {
                    janela += 1;
                }
            }

            primeiro_slot = 0;
            ultimo_slot = 0;

            // Noite
            for (int slot = 12; slot < 16; slot++)
            {
                if (f_dispo[dia][slot] > 0)
                {
                    primeiro_slot = slot;
                    break;
                }
            }
            for (int slot = 15; slot >= 12; slot--)
            {
                if (f_dispo[dia][slot] > 0)
                {
                    ultimo_slot = slot;
                    break;
                }
            }

            for (int slot = primeiro_slot + 1; slot < ultimo_slot; slot++)
            {
                if (f_dispo[dia][slot] <= 0)
                {
                    janela += 1;
                }
            }
        }

        // std::cout << "\033[0m";

        // if (janela > 0)
        // {
        //     p->print_solucao();
        // }
    }

    return janela;
}

int Heuristica::calcular_sexto_horario_turma(Solucao *t_solucao)
{

    int sexto_horario = 0;

    auto turmas = t_solucao->get_instancia()->get_lista_turmas();
    for (auto t : turmas)
    {
        std::array<std::array<int, 16>, 6> f_dispo = t->get_disponibilidade();

        for (int i = 0; i < f_dispo.size(); i++)
        {
            if (f_dispo[i][5 || 11] > 0)
            {
                sexto_horario += 1;
            }
        }
    }

    return sexto_horario;
}

Solucao *Heuristica::get_solucao(int index)
{
    return this->m_solucoes[index];
}

std::vector<Solucao *> Heuristica::get_lista_solucoes()
{
    return this->m_solucoes;
}

std::map<int, Solucao *> Heuristica::pos_processamento_estatico()
{
    std::map<int, Solucao *> solucoes_map;
    GravarArquivo ga = GravarArquivo();

    for (auto solucao : m_solucoes) // Iterar pela populacao de solucoes
    {
        // int num_turmas = turmas.size();
        Solucao *temp_solucao = new Solucao(*solucao);

        bool houve_melhoria = true;

        while (houve_melhoria)
        {
            houve_melhoria = false;
            for (auto curso : temp_solucao->get_instancia()->get_lista_cursos())

            {
                std::vector<Turma *> turmas_curso{};

                for (auto turma_index : curso->get_turmas_index())
                    turmas_curso.push_back(temp_solucao->get_instancia()->get_turma_por_id(turma_index));

                for (int nbl = 0; nbl < turmas_curso.size() + 1 - std::min(m_qtd_turmas_heuristica, int(turmas_curso.size())); nbl++)
                {
                    Solucao *nova_solucao = new Solucao(*temp_solucao);

                    std::vector<Turma *> turmas_iteracao;
                    for (int i = 0; i < std::min(m_qtd_turmas_heuristica, int(turmas_curso.size())); i++)
                    {
                        turmas_iteracao.push_back(solucao->get_instancia()->get_turma_por_id(turmas_curso[i + nbl]->get_index()));
                        std::cout << turmas_iteracao.back()->get_nome() << ", ";
                    }
                    std::cout << std::endl;

                    nova_solucao->busca_local(turmas_iteracao);
                    avaliar_solucao(nova_solucao, nova_solucao->get_factivel());

                    if (nova_solucao->get_valor_solucao() < temp_solucao->get_valor_solucao())
                    {
                        std::cout << "Houve melhoria. Reiniciando loop." << std::endl;
                        solucoes_map.insert(std::make_pair(nova_solucao->get_id_solucao(), nova_solucao));
                        temp_solucao = nova_solucao;
                        houve_melhoria = true;
                    }
                    else
                    {
                        std::cout << "Não houve melhoria. Indo para a proxima turma sem incrementar a qtd_turmas" << std::endl;
                        delete nova_solucao;
                    }
                }
            }
        }
    }
    return solucoes_map;
}

std::map<int, Solucao *> Heuristica::pos_processamento_dinamico()
{
    std::map<int, Solucao *> solucoes_map;
    GravarArquivo ga = GravarArquivo();

    for (auto solucao : m_solucoes) // Iterar pela populacao de solucoes
    {
        // int num_turmas = turmas.size();
        Solucao *temp_solucao = new Solucao(*solucao);

        std::vector<int> qtd_turmas_iteracoes{1, 2, 10};
        for (auto n : qtd_turmas_iteracoes)
        {
            for (auto curso : temp_solucao->get_instancia()->get_lista_cursos())
            {

                std::vector<Turma *> turmas_curso{};

                for (auto turma_index : curso->get_turmas_index())
                    turmas_curso.push_back(temp_solucao->get_instancia()->get_turma_por_id(turma_index));

                for (int nbl = 0; nbl < turmas_curso.size() + 1 - std::min(n, int(turmas_curso.size())); nbl++)
                {
                    Solucao *nova_solucao = new Solucao(*temp_solucao);

                    std::vector<Turma *> turmas_iteracao;
                    for (int i = 0; i < std::min(n, int(turmas_curso.size())); i++)
                    {
                        turmas_iteracao.push_back(solucao->get_instancia()->get_turma_por_id(turmas_curso[i + nbl]->get_index()));
                        std::cout << turmas_iteracao.back()->get_nome() << ", ";
                    }
                    std::cout << std::endl;

                    nova_solucao->busca_local(turmas_iteracao);
                    avaliar_solucao(nova_solucao, nova_solucao->get_factivel());

                    if (nova_solucao->get_valor_solucao() < temp_solucao->get_valor_solucao())
                    {
                        std::cout << "Houve melhoria. Reiniciando loop." << std::endl;
                        solucoes_map.insert(std::make_pair(nova_solucao->get_id_solucao(), nova_solucao));
                        temp_solucao = nova_solucao;
                    }
                    else
                    {
                        std::cout << "Não houve melhoria. Indo para a proxima turma sem incrementar a qtd_turmas" << std::endl;
                        delete nova_solucao;
                    }
                }
            }
        }
    }
    return solucoes_map;
}

void Heuristica::fix_n_opt()
{
}

Solucao *Heuristica::get_melhor_solucao()
{
    if (m_solucoes.empty())
    {
        return nullptr;
    }

    auto compareSolucao = [](Solucao *solucao1, Solucao *solucao2)
    {
        return solucao1->get_valor_solucao() < solucao2->get_valor_solucao();
    };

    auto melhor_solucao = std::min_element(m_solucoes.begin(), m_solucoes.end(), compareSolucao);
    GravarArquivo ga = GravarArquivo();
    output.salvar_saidas("data/output/", *melhor_solucao);

    return *melhor_solucao;
}