#include "heuristica.hpp"

Heuristica::Heuristica(std::string t_instancia_pipe, int tam_populacao)
{
    this->solucoes.push_back(new Solucao(t_instancia_pipe));
    for (int i = 0; i < tam_populacao; i++)
    {
        std::cout << CYN "Gerando Instancia " << t_instancia_pipe << " nº: " << i + 1 << NC << std::endl;
        this->solucoes.push_back(new Solucao(t_instancia_pipe));
    }
}

std::vector<Disciplina *> Heuristica::ordernar_disciplinas(const int &rand_metodo, Solucao *solucao)
{

    std::vector<Disciplina *> t_disciplinas_ordenadas{};

    switch (rand_metodo)
    {

    case 0:
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        break;

    case 1:
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_ch_presencial() < rhs->get_ch_presencial(); });
        break;

    case 2:

        break;

    default:
        t_disciplinas_ordenadas;
        break;
    }

    return t_disciplinas_ordenadas;
}

void Heuristica::heuristica_construtiva()
{
    for (auto it : this->solucoes)
    {
        it->popular_solucao(ordernar_disciplinas(0, it));
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