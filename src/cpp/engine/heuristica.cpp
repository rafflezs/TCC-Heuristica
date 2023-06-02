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
    exibir_solucoes();

    // Heuristica: fix-and-optimize
    pos_processamento();
    exibir_solucoes();

    // salvando solucao em arquivo .tex
    auto melhor_solucao = get_melhor_solucao();
    if (melhor_solucao == nullptr)
    {
        std::cout << "Nenhuma soluço encontrada. Encerrando com erro 02" << std::endl;
    }
    else
    {
        std::cout << "A solução ID " << melhor_solucao->get_id_solucao() << " com o valor na função objetivo de " << melhor_solucao->get_valor_solucao() << " pontos." << std::endl;
        std::cout << "\n\n\n\n\n\n\n\n\n\n\nMAIS MELHOR SOLUCAO\n\n"
                  << std::endl;
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
        ga.salvar_analise("data/output/", it, t_iteracao, 0, "CONSTRUTIVA", rand_switch, *m_tempo_inicial);
    }

    ordenar_solucoes();
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

void Heuristica::pos_processamento()
{
    GravarArquivo ga = GravarArquivo();

    for (int i = 0; i < m_solucoes.size(); i++) // Iterar pela populacao de solucoes
    {
        int iteracao_solucao = 1; // Identificador da evolucao da solucao ao longo das iteracoes
        int count = 0;            // Valor de escape da heuristica

        auto nova_solucao = new Solucao(*m_solucoes[i]);

        for (auto curso : nova_solucao->get_instancia()->get_lista_cursos())
        {
            auto turmas = nova_solucao->encontrar_turmas_relacionadas(curso);

            int qtd_turmas = m_qtd_turmas_heuristica;
            if (qtd_turmas == 0)
            {
                qtd_turmas = 1;
            }
            for (; qtd_turmas <= m_qtd_turmas_heuristica; qtd_turmas++)
            {
                int turma_total = turmas.size();
                std::vector<Turma *> turmas_selecionadas;

                for (int j = 0; j < qtd_turmas; j++)
                {
                    int index = (count + j) % turma_total;
                    turmas_selecionadas.push_back(turmas[index]);
                }

                // !! TESTAR ESSA PORRA
                for (int rept = 0; rept < m_qtd_rept_busca_local; rept++) // implementar rept como parametro da Heuristica para facilmente alterar depois
                {
                    iteracao_solucao++;
                    busca_local(turmas_selecionadas, nova_solucao);
                    ga.salvar_analise("data/output/", nova_solucao, iteracao_solucao, qtd_turmas, curso->get_nome(), 4, *m_tempo_inicial);

                    if (nova_solucao->get_valor_solucao() < nova_solucao->get_valor_solucao())
                    {
                        std::cout << "Antiga solucao: " << nova_solucao->get_valor_solucao() << " substituida pela nova solucao: " << nova_solucao->get_valor_solucao() << std::endl;
                        delete m_solucoes[i];
                        m_solucoes[i] = nova_solucao;
                        count = 0;
                        break;
                    }
                }
                if (count)
                {
                    delete nova_solucao;
                    count++;
                }
            }
        }
    }

    for (auto sol_final : m_solucoes)
    {
        ga.salvar_analise("data/output/", sol_final, 0, 0, "FINAL", 0, *m_tempo_inicial);
    }
}

// Alterar tipo da funcao e parametros
void Heuristica::busca_local(std::vector<Turma *> t_turmas, Solucao *t_solucao)
{

    std::vector<Disciplina *> disciplinas_turmas{};
    std::vector<Professor *> professores_relacionados{};
    for (Turma *turma : t_turmas)
    {
        std::vector<Disciplina *> temp_disciplinas = turma->get_disciplinas();
        disciplinas_turmas.insert(disciplinas_turmas.end(), temp_disciplinas.begin(), temp_disciplinas.end());
    }

    t_solucao->destruir_horario(t_turmas);
    t_solucao->destruir_horario(disciplinas_turmas);

    bool deu_certo = t_solucao->popular_solucao(disciplinas_turmas);
    avaliar_solucao(t_solucao, deu_certo);
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
    ga.salvar_saidas("data/output/", *melhor_solucao);

    return *melhor_solucao;
}