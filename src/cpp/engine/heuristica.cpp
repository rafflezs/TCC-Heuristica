#include "heuristica.hpp"

Heuristica::Heuristica(std::string t_instancia_pipe, int tam_populacao)
{

    this->m_instancia = t_instancia_pipe;
    this->m_tamanho_populacao = tam_populacao;


    // this->solucoes.push_back(new Solucao(t_instancia_pipe, 0));
    for (int i = 1; i <= tam_populacao; i++)
    {
        std::cout << CYN "Gerando Instancia " << t_instancia_pipe << " nº: " << i << NC << std::endl;
        this->m_solucoes.push_back(new Solucao(t_instancia_pipe, i));
    }
    std::cout << "-------Encerrada geração de populações-------\n"
              << std::endl;
}

std::vector<Disciplina *> Heuristica::ordernar_disciplinas(const int &rand_metodo, Solucao *solucao)
{

    std::vector<Disciplina *> t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
    std::random_device rd;
    std::mt19937 g(rd());

    switch (rand_metodo)
    {

    // Caso 1: Ordenar disciplinas por maior CH-MIN (tamanho)
    case 1:
        printf("\n------Caso %d - Maior CH-MIN------", rand_metodo);
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_ch_min() > rhs->get_ch_min(); });
        break;

    // Caso 2: Ordenar disciplinas por Menor Split (tamanho)
    case 2:
        printf("\n------Caso %d - Menor Split------", rand_metodo);
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_split() < rhs->get_split(); });
        break;

    // Caso 3: Ordenar disciplina por prioriedade de CH-MIN e Split combinadas (tamanho)
    case 3:
        printf("\n------Caso %d - Prioriedade CH-MIN e Split Combinados------", rand_metodo);
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return (lhs->get_ch_min() > rhs->get_ch_min()) && (lhs->get_split() < rhs->get_split()); });
        break;

    // // TODO Caso 4: Ordenar disciplina por professor com mais disciplinas
    // case 4:
    //     printf("\n------Caso %d\n", rand_metodo);
    //     break;

    // // TODO Caso 5: Ordenar disciplina por Curso com mais Turmas
    // case 5:
    //     printf("\n------Caso %d\n", rand_metodo);
    //     break;

    // // TODO Caso 5: Ordenar disciplina por Curso com mais Disciplinas
    // case 6:
    //     printf("\n------Caso %d\n", rand_metodo);
    //     break;

    // TODO Caso 6: Random Sort
    case 7:
        printf("\n------Caso %d\n", rand_metodo);
        std::shuffle(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), g);
        break;

    // Caso base: ordenação por ordem de leitura da instância
    default:
        printf("\n------Caso %d - Ordem de Leitura\n", rand_metodo);
        t_disciplinas_ordenadas;
        break;
    }

    return t_disciplinas_ordenadas;
}

void Heuristica::heuristica_construtiva()
{
    for (auto it : this->m_solucoes)
    {
        // TODO : Alterar o teto do rand baseado na quantidade de parametros do ordernar_disciplinas()
        bool deu_certo = it->popular_solucao(ordernar_disciplinas(rand() % 4, it));
        if (deu_certo == true)
        {
            it->set_factivel(true);
            std::cout << "Solucao " << it->get_id_solucao() << " encontrada" << std::endl;
            // it->exibir_solucao();
        }
        else
        {
            it->set_factivel(false);
            std::cout << "Solucao " << it->get_id_solucao() << " infactivel" << std::endl;
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
    // std::cout << "-------Avaliando Soluções-------\n" << std::endl;

    for (int i = 1; i < m_solucoes.size(); i++)
    {
        // std::cout << CYN "Avaliando solucao nº: " << i << NC << std::endl;
        m_solucoes[i]->set_valor_avaliacao(avaliar_solucao(m_solucoes[i], peso_janela, peso_sexto_horario));
        // std::cout << "Avaliacao da Solucao " << i << ": " << m_solucoes[i]->get_valor_avaliacao() << std::endl;
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
    t_solucao->set_valor_avaliacao((peso_sexto_horario * sexto_horario) + (peso_janela * janela_prof));

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

        std::cout << "\033[0m";

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

Heuristica* Heuristica::shallow_copy() const {
    Heuristica* newHeuristica = new Heuristica(*this);
    for (Solucao* s : newHeuristica->m_solucoes) {
        s = s->shallow_copy();
    }
    return newHeuristica;
}

void Heuristica::busca_local()
{

    // DESALOCAR AS TURMAS DE UMA SOLUCAO E VERIFICAR A VARIACAO DA QUALIDADE
    // IMPORTANTE: USAR SHALLOW_COPY EM CASA DE REVERTER A SOLUCAO (QUALIDADE PIOR)

    // PENSAR EM UMA MANEIRA DE CHAMAR ESSA FUNCAO OU ORGANIZAR ELA
}