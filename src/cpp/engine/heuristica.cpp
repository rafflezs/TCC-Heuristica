#include "heuristica.hpp"

Heuristica::Heuristica(std::default_random_engine &t_rng, const std::string &t_instancia_nome, const int &t_tam_pop, const float &t_peso_janela, const int &t_peso_sexto, std::chrono::time_point<std::chrono::steady_clock> *t_tempo_inicial)
{
    this->m_rng = t_rng;
    this->m_instancia_nome = t_instancia_nome;
    this->m_tamanho_populacao = t_tam_pop;
    this->m_peso_janela = t_peso_janela;
    this->m_peso_sexto = t_peso_sexto;
    this->m_tempo_inicial = t_tempo_inicial;

    for (int i = 0; i < m_tamanho_populacao; i++)
    {
        this->m_solucoes.push_back(new Solucao(m_rng, m_instancia_nome, i));
    }
}

void Heuristica::inicializar()
{
    // Heuristica inicial para preencher solucoes vazias
    heuristica_construtiva(0);

    // Heuristica: fix-and-optimize
    pos_processamento();

    // salvando solucao em arquivo .tex
    auto melhor_solucao = get_melhor_solucao();
    std::cout << "A solução ID " << melhor_solucao->get_id_solucao()
              << " com o valor na função objetivo de "
              << melhor_solucao->get_valor_avaliacao()
              << " pontos." << std::endl;
}

std::vector<Disciplina *> Heuristica::ordenar_disciplinas(const int &rand_metodo, Solucao *solucao)
{

    std::vector<Disciplina *> t_disciplinas_ordenadas = (*solucao).get_instancia().get_lista_disciplinas();

    switch (rand_metodo)
    {

    // Caso 1: Ordenar disciplinas por maior CH-MIN (tamanho)
    case 1:
        t_disciplinas_ordenadas = (*solucao).get_instancia().get_lista_disciplinas();
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_ch_min() > rhs->get_ch_min(); });
        break;

    // Caso 2: Ordenar disciplinas por Menor Split (tamanho)
    case 2:
        t_disciplinas_ordenadas = (*solucao).get_instancia().get_lista_disciplinas();
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_split() < rhs->get_split(); });
        break;

    // Caso 3: Ordenar disciplina por prioriedade de CH-MIN e Split combinadas (tamanho)
    case 3:
        t_disciplinas_ordenadas = (*solucao).get_instancia().get_lista_disciplinas();
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
    GravarArquivo ga = GravarArquivo("./data/output/analise.csv");

    for (auto it : this->m_solucoes)
    {
        int rand_switch = 1 + (rand() % 4);
        auto disciplinas_ordenadas = ordenar_disciplinas(rand_switch, it);
        bool deu_certo = it->popular_solucao(disciplinas_ordenadas);
        avaliar_solucao(it, deu_certo);

        // Salvando parametros da solucao em csv para futura analise
        ga.salvar_analise(it, t_iteracao, rand_switch, (std::chrono::steady_clock::now() - *m_tempo_inicial));
    }

    ordenar_solucoes();
}

void Heuristica::exibir_solucoes()
{
    for (auto it = this->m_solucoes.begin(); it != this->m_solucoes.end(); it++)
    {
        std::cout << "Solucao " << (*it)->get_id_solucao() << " | Avaliada em: " << (*it)->get_valor_avaliacao() << std::endl;
        (*it)->exibir_solucao();
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
              { return s1->get_valor_avaliacao() > s2->get_valor_avaliacao(); });
}

void Heuristica::avaliar_solucao(Solucao *t_solucao, bool t_factibilidade)
{
    float sexto_horario = calcular_sexto_horario_turma(t_solucao);
    float janela_prof = calcular_janela_professor(t_solucao);

    t_solucao->set_sexto_horario(sexto_horario);
    t_solucao->set_janela(janela_prof);
    t_solucao->set_factivel(t_factibilidade);
    if (t_factibilidade == true)
    {
        t_solucao->set_valor_avaliacao((m_peso_sexto * sexto_horario) + (m_peso_janela * janela_prof));
    }
    else
    {
        // t_solucao->set_valor_avaliacao(std::numeric_limits<float>::max());
        t_solucao->set_valor_avaliacao(999999999999);
    }
}

int Heuristica::calcular_janela_professor(Solucao *t_solucao)
{

    int janela = 0;

    auto profs = t_solucao->get_instancia().get_lista_professores();
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

        if (janela > 0)
        {
            p->print_solucao();
        }
    }

    return janela;
}

int Heuristica::calcular_sexto_horario_turma(Solucao *t_solucao)
{

    int sexto_horario = 0;

    auto turmas = t_solucao->get_instancia().get_lista_turmas();
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

Heuristica *Heuristica::shallow_copy() const
{
    Heuristica *newHeuristica = new Heuristica(*this);
    for (Solucao *s : newHeuristica->m_solucoes)
    {
        s = s->shallow_copy();
    }
    return newHeuristica;
}

void Heuristica::pos_processamento()
{
    GravarArquivo ga = GravarArquivo("./data/output/analise.csv");

    for (int i = 0; i < m_solucoes.size(); i++)
    {
        auto nova_solucao = m_solucoes[i]->shallow_copy();

        int iteracao_solucao = 1;
        int count = 0;

        auto turmas = nova_solucao->get_instancia().get_lista_turmas();
        std::sort(turmas.begin(), turmas.end(), [](Turma *turma1, Turma *turma2)
                  { return turma1->get_curso() < turma2->get_curso(); });

        int max_turmas_por_curso = 0;
        for (Curso *curso : nova_solucao->get_instancia().get_lista_cursos())
        {
            auto turmas_size = curso->get_turmas_index().size();
            if (turmas_size > max_turmas_por_curso)
            {
                max_turmas_por_curso = turmas_size;
            }
        }

        while (count < nova_solucao->get_instancia().get_lista_turmas().size())
        {
            if (nova_solucao->get_valor_avaliacao() < m_solucoes[i]->get_valor_avaliacao())
            {
                m_solucoes[i] = nova_solucao;
                count = 0;
            }

            int n = iteracao_solucao % max_turmas_por_curso;
            if (n == 0)
            {
                n = max_turmas_por_curso;
            }

            std::vector<Turma *> turmas_selecionadas;
            for (Turma *turma : turmas)
            {
                if (turma->get_curso()->get_turmas_index().size() >= n)
                {
                    turmas_selecionadas.push_back(turma);
                    if (turmas_selecionadas.size() == n)
                    {
                        break;
                    }
                }
            }

            // Perform operations with the selected Turmas
            // Call the function to destroy their schedules
            busca_local(turmas_selecionadas, nova_solucao);

            iteracao_solucao++;
            count++;

            ga.salvar_analise(nova_solucao, iteracao_solucao, 4, (std::chrono::steady_clock::now() - *m_tempo_inicial));
        }
    }
}

// Alterar tipo da funcao e parametros
void Heuristica::busca_local(std::vector<Turma *> t_turmas, Solucao *t_solucao)
{
    std::vector<Disciplina *> disciplinas_turma{};
    for (Turma *turma : t_turmas)
    {
        // Destroy the schedule of the Turma
        disciplinas_turma = encontrar_disciplinas_turma(turma);
        std::vector<Professor> professores_turma = encontrar_professores_turma(disciplinas_turma, t_solucao);
    }
    bool deu_certo = t_solucao->popular_solucao(disciplinas_turma);
    avaliar_solucao(t_solucao, deu_certo);
}

std::vector<Disciplina *> Heuristica::encontrar_disciplinas_turma(Turma *t_turma)
{
    std::vector<Disciplina *> disciplinas_turma{};
    auto f_dispo = t_turma->get_disponibilidade();

    for (int dia = 0; dia < f_dispo.size(); dia++)
    {
        for (int horario = 0; horario < f_dispo[dia].size(); horario++)
        {
            if (f_dispo[dia][horario] > 0)
            {
                disciplinas_turma.push_back(t_turma->get_disciplinas()[f_dispo[dia][horario]]);
                f_dispo[dia][horario] = 0;
            }
        }
    }

    t_turma->set_disponibilidade(f_dispo);

    // Remove duplicate Disciplinas
    std::sort(disciplinas_turma.begin(), disciplinas_turma.end());
    disciplinas_turma.erase(std::unique(disciplinas_turma.begin(), disciplinas_turma.end()), disciplinas_turma.end());

    return disciplinas_turma;
}

std::vector<Professor> Heuristica::encontrar_professores_turma(std::vector<Disciplina *> disciplinas_turma, Solucao *temp_solucao)
{
    std::vector<Professor> professores_turma{};

    for (auto disciplina_ptr : disciplinas_turma)
    {
        professores_turma.push_back(*(temp_solucao->encontrar_prof_relacionado(disciplina_ptr)));
    }

    for (auto &temp_prof : professores_turma)
    {
        auto f_dispo = temp_prof.get_disponibilidade();

        for (int dia = 0; dia < f_dispo.size(); dia++)
        {
            for (int horario = 0; horario < f_dispo[dia].size(); horario++)
            {
                if (f_dispo[dia][horario] > 0)
                {
                    f_dispo[dia][horario] = 0;
                }
            }
        }

        temp_prof.set_disponibilidade(f_dispo);
    }

    return professores_turma;
}

Solucao *Heuristica::get_melhor_solucao()
{
    if (m_solucoes.empty())
    {
        return nullptr;
    }

    auto compareSolucao = [](Solucao *solucao1, Solucao *solucao2)
    {
        return solucao1->get_valor_avaliacao() < solucao2->get_valor_avaliacao();
    };

    auto melhor_solucao = std::min_element(m_solucoes.begin(), m_solucoes.end(), compareSolucao);
    GravarArquivo ga = GravarArquivo("./data/output/horarios.tex");
    ga.salvar_saidas(*melhor_solucao);

    return *melhor_solucao;
}
