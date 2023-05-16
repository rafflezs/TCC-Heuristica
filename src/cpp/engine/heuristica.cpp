#include "heuristica.hpp"

Heuristica::Heuristica(const std::string &t_instancia_nome, const int &t_tam_pop, const float &t_peso_janela, const int &t_peso_sexto)
{
    this->m_instancia_nome = t_instancia_nome;
    this->m_tamanho_populacao = t_tam_pop;
    this->m_peso_janela = t_peso_janela;
    this->m_peso_sexto = t_peso_sexto;

    for (int i = 0; i < m_tamanho_populacao; i++)
    {
        this->m_solucoes.push_back(new Solucao(m_instancia_nome, i));
    }
}

void Heuristica::inicializar()
{
    GravarArquivo ga = GravarArquivo("data/output/");

    heuristica_construtiva();
    avaliar_solucoes(m_peso_janela, m_peso_sexto);
    for (auto sol : m_solucoes)
    {
        // TERMINAR ESSA PORRA
        ga.salvar_analise("./data/output/", sol, true);
    }

    pos_processamento(); // salvar_analise dentro ou fora do pos_processamento?
                         // Fora implica em gerar toda a heuristica de busca local para a solucao e depois avaliar resultado final
                         // Dentro implica em acompanhar a evolução da solucao ao longo das diferentes geracoes da heuristica busca local
                         // Por enquanto fora
    avaliar_solucoes(m_peso_janela, m_peso_sexto);

    for (auto sol : m_solucoes)
    {
        // Ver com o painho se esses dados são suficientes pra analise (clica na porra da funcao loiro burro)
        ga.salvar_analise("./data/output/", sol, false);
    }

    // salvando solucao em arquivo .tex
    auto melhor_solucao = get_melhor_solucao();
    std::cout << "A solução ID " << melhor_solucao->get_id_solucao() 
              << " com o valor na função objetivo de "
              << melhor_solucao->get_valor_avaliacao()
              << " pontos." << std::endl;
    ga.salvar_saidas(melhor_solucao);
}

std::vector<Disciplina *> Heuristica::ordenar_disciplinas(const int &rand_metodo, Solucao *solucao)
{

    std::vector<Disciplina *> t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
    std::random_device rd;
    std::mt19937 g(rd());

    switch (rand_metodo)
    {

    // Caso 1: Ordenar disciplinas por maior CH-MIN (tamanho)
    case 1:
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_ch_min() > rhs->get_ch_min(); });
        break;

    // Caso 2: Ordenar disciplinas por Menor Split (tamanho)
    case 2:
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_split() < rhs->get_split(); });
        break;

    // Caso 3: Ordenar disciplina por prioriedade de CH-MIN e Split combinadas (tamanho)
    case 3:
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return (lhs->get_ch_min() > rhs->get_ch_min()) && (lhs->get_split() < rhs->get_split()); });
        break;

    case 4:
        std::shuffle(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), g);
        break;

    // Caso base: ordenação por ordem de leitura da instância
    default:
        t_disciplinas_ordenadas;
        break;
    }

    return t_disciplinas_ordenadas;
}

void Heuristica::ordenar_disciplinas(const int &rand_metodo, std::vector<Disciplina *> *t_disciplina)
{

    std::random_device rd;
    std::mt19937 g(rd());

    switch (rand_metodo)
    {

    // Caso 1: Ordenar disciplinas por maior CH-MIN (tamanho)
    case 1:
        std::sort(t_disciplina->begin(), t_disciplina->end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_ch_min() > rhs->get_ch_min(); });
        break;

    // Caso 2: Ordenar disciplinas por Menor Split (tamanho)
    case 2:
        std::sort(t_disciplina->begin(), t_disciplina->end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_split() < rhs->get_split(); });
        break;

    // Caso 3: Ordenar disciplina por prioriedade de CH-MIN e Split combinadas (tamanho)
    case 3:
        std::sort(t_disciplina->begin(), t_disciplina->end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return (lhs->get_ch_min() > rhs->get_ch_min()) && (lhs->get_split() < rhs->get_split()); });
        break;

    case 4:
        std::shuffle(t_disciplina->begin(), t_disciplina->end(), g);
        break;

    // Caso base: ordenação por ordem de leitura da instância
    default:
        t_disciplina;
        break;
    }
}

void Heuristica::heuristica_construtiva()
{
    for (auto it : this->m_solucoes)
    {
        // TODO : Alterar o teto do rand baseado na quantidade de parametros do ordenar_disciplinas()
        // bool deu_certo = it->popular_solucao(ordenar_disciplinas(rand() % 4, it));
        bool deu_certo = it->popular_solucao(ordenar_disciplinas(7, it));
        if (deu_certo == true)
        {
            it->set_factivel(true);
            // it->exibir_solucao();
        }
        else
        {
            it->set_factivel(false);
            // it->exibir_solucao();
        }
    }
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

void Heuristica::avaliar_solucoes(const float &peso_janela, const float &peso_sexto_horario)
{

    for (int i = 1; i < m_solucoes.size(); i++)
    {
        m_solucoes[i]->set_valor_avaliacao(avaliar_solucao(m_solucoes[i], peso_janela, peso_sexto_horario));
    }

    std::sort(m_solucoes.begin(), m_solucoes.end(), [](Solucao *s1, Solucao *s2)
              { return s1->get_valor_avaliacao() > s2->get_valor_avaliacao(); });
}

float Heuristica::avaliar_solucao(Solucao *t_solucao, const float &peso_janela, const float &peso_sexto_horario)
{
    // atribuir pesos fora das funções
    // retonar QUANTIDADE de sextos e janelas
    float sexto_horario = calcular_sexto_horario_turma(t_solucao);
    float janela_prof = calcular_janela_professor(t_solucao);

    t_solucao->set_sexto_horario(sexto_horario);
    t_solucao->set_janela(janela_prof);
    if (t_solucao->get_factivel())
    {
        t_solucao->set_valor_avaliacao((peso_sexto_horario * sexto_horario) + (peso_janela * janela_prof));
    }
    else
    {
        t_solucao->set_valor_avaliacao(std::numeric_limits<float>::max());
    }

    return t_solucao->get_valor_avaliacao();
}

float Heuristica::calcular_janela_professor(Solucao *t_solucao)
{

    float janela = 0.0;

    auto profs = t_solucao->get_instancia().m_lista_professores;
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
                    janela += 0.05;
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
                    janela += 0.05;
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
                    janela += 0.05;
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

float Heuristica::calcular_sexto_horario_turma(Solucao *t_solucao)
{

    float sexto_horario = 0.0;

    auto turmas = t_solucao->get_instancia().m_lista_turmas;
    for (auto t : turmas)
    {
        std::array<std::array<int, 16>, 6> f_dispo = t->get_disponibilidade();

        for (int i = 0; i < f_dispo.size(); i++)
        {
            if (f_dispo[i][5 || 11] > 0)
            {
                sexto_horario += 0.5;
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
    const int iteracao_max = 10; // Maximum number of iterations
    const int tempo_max = 10;    // Maximum time in seconds

    for (auto it : this->m_solucoes)
    {
        Instancia *shallow_instancia = it->get_instancia().shallow_copy();
        std::set<int> turmas_selecionadas{};

        // Tempo inicial 0
        std::chrono::time_point<std::chrono::steady_clock> chrono_inicial = std::chrono::steady_clock::now();

        // Gera um conjunto reduzido de turmas a serem detruidas
        int qtd_turmas_selecionadas = rand() % (*shallow_instancia).m_lista_turmas.size() + 1;
        for (int i = 0; i < qtd_turmas_selecionadas; i++)
            turmas_selecionadas.insert(rand() % qtd_turmas_selecionadas);

        int iteracao = 0;
        bool houve_melhoria = true;
        while (houve_melhoria && iteracao < iteracao_max)
        {
            auto nova_solucao = busca_local(turmas_selecionadas, *it);

            if (nova_solucao->get_factivel() && (nova_solucao->get_valor_avaliacao() > it->get_valor_avaliacao()))
            {
                it = nova_solucao;
                houve_melhoria = true;
            }
            else
            {
                houve_melhoria = false;
            }

            iteracao++;

            std::chrono::time_point<std::chrono::steady_clock> chrono_atual = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_sec = chrono_atual - chrono_inicial;
            if (elapsed_sec.count() > tempo_max)
                break;
        }
    }
}

Solucao *Heuristica::busca_local(std::set<int> t_turmas_selecionadas, Solucao t_solucao)
{

    auto nova_solucao = t_solucao.shallow_copy();
    auto nova_instancia = t_solucao.get_instancia().shallow_copy();

    for (auto turma_index : t_turmas_selecionadas)
    {
        std::set<int> disciplinas_turma_set = encontrar_disciplinas_turma(nova_instancia->m_lista_turmas[turma_index]);
        std::vector<Disciplina *> disciplinas_turma{};
        std::vector<Professor> professores_turma = encontrar_professores_turma(disciplinas_turma_set, nova_instancia, nova_solucao);

        // set <int> disciplina TO vector<Disciplina> reordenado
        for (auto disc_set : disciplinas_turma_set)
        {
            disciplinas_turma.push_back(nova_instancia->m_lista_disciplinas[disc_set]);
        }

        // std::shuffle(disciplinas_turma->begin(), disciplinas_turma->end(), g);

        // ordenar_disciplinas(rand() % 4, &disciplinas_turma);
        ordenar_disciplinas(7, &disciplinas_turma);

        bool deu_certo = nova_solucao->popular_solucao(disciplinas_turma);
        if (deu_certo == true)
        {
            nova_solucao->set_factivel(true);
        }
        else
        {
            nova_solucao->set_factivel(false);
        }
    }

    return nova_solucao;
}

std::set<int> Heuristica::encontrar_disciplinas_turma(Turma *t_turma)
{

    std::set<int> disciplinas_turma{};
    auto f_dispo = t_turma->get_disponibilidade();

    for (int dia = 0; dia < f_dispo.size(); dia++)
    {
        for (int horario = 0; horario < f_dispo[dia].size(); horario++)
        {
            if (f_dispo[dia][horario] > 0)
            {
                disciplinas_turma.insert(f_dispo[dia][horario]);
                f_dispo[dia][horario] = 0;
            }
        }
    }

    t_turma->set_disponibilidade(f_dispo);
    return disciplinas_turma;
}

std::vector<Professor> Heuristica::encontrar_professores_turma(std::set<int> disciplinas_turma, Instancia *temp_instancia, Solucao *temp_solucao)
{
    std::vector<Professor> professores_turma{};
    for (auto disciplina_index : disciplinas_turma)
    {
        professores_turma.push_back(*(temp_solucao->encontrar_prof_relacionado(temp_instancia->m_lista_disciplinas[disciplina_index])));
    }

    for (auto temp_prof : professores_turma)
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

    return *std::min_element(m_solucoes.begin(), m_solucoes.end(), compareSolucao);
}
