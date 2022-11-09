#include "heuristica.hpp"

Heuristica::Heuristica(std::string t_instancia_pipe, int tam_populacao)
{
    this->solucoes.push_back(new Solucao(t_instancia_pipe, 0));
    for (int i = 1; i <= tam_populacao; i++)
    {
        std::cout << CYN "Gerando Instancia " << t_instancia_pipe << " nº: " << i + 1 << NC << std::endl;
        this->solucoes.push_back(new Solucao(t_instancia_pipe, i));
    }
}

std::vector<Disciplina *> Heuristica::ordernar_disciplinas(const int &rand_metodo, Solucao *solucao)
{

    std::vector<Disciplina *> t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;

    switch (rand_metodo)
    {

    // Caso 1: Ordenar disciplinas por maior CH-MIN (tamanho)
    case 1:
        printf("Caso %d - Maior CH-MIN\n", rand_metodo);
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_ch_min() > rhs->get_ch_min(); });
        break;

    // Caso 2: Ordenar disciplinas por Menor Split (tamanho)
    case 2:
        printf("Caso %d - Menor Split\n", rand_metodo);
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_split() < rhs->get_split(); });
        break;

    // Caso 3: Ordenar disciplina por prioriedade de CH-MIN e Split combinadas (tamanho)
    case 3:
        printf("Caso %d - Prioriedade CH-MIN e Split Combinados\n", rand_metodo);
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return (lhs->get_ch_min() > rhs->get_ch_min()) && (lhs->get_split() <  rhs->get_split()); });
        break;

    // // TODO Caso 4: Ordenar disciplina por professor com mais disciplinas
    // case 4:
    //     printf("Caso %d\n", rand_metodo);
    //     break;

    // // TODO Caso 5: Ordenar disciplina por Curso
    // case 5:
    //     printf("Caso %d\n", rand_metodo);
    //     break;

    // // TODO Caso 6: Random Sort
    // case 6:
    //     printf("Caso %d\n", rand_metodo);
    //     break;

    // Caso base: ordenação por ordem de leitura da instância
    default:
        printf("Caso %d - Ordem de Leitura\n", rand_metodo);
        t_disciplinas_ordenadas;
        break;
    }

    return t_disciplinas_ordenadas;
}

void Heuristica::heuristica_construtiva()
{
    for (auto it : this->solucoes)
    {
        // TODO : Alterar o teto do rand baseado na quantidade de parametros do ordernar_disciplinas()
        if (it->popular_solucao(ordernar_disciplinas(rand() % 4, it)) == true)
            it->exibir_solucao();
        else
            std::cout << "Solucao " << it->get_id_solucao() << " infactivel" << std::endl;
    }
}

void Heuristica::exibir_solucoes()
{
    for (auto it = this->solucoes.begin(); it != this->solucoes.end(); it++)
    {
        (*it)->exibir_solucao();
    }
}

void Heuristica::debug_heuristica()
{
    /* ---------------DEBUG BLOCK---------------------
    ** ! VERIFICAR COPIA DE PRT ADDR !
    */
    std::cout << REDB "\n\nDEBUG - ENDERECOS DISCIPLINAS\n" NC << std::endl;
    for (auto it : this->solucoes)
    {
        it->debug_vector_disciplina_addr();
    }
}