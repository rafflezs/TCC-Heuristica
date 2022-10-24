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
    case 1:
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        break;

    default:
        t_disciplinas_ordenadas;
        break;
    }

    return t_disciplinas_ordenadas;
}

void Heuristica::heuristica_construtiva()
{
    for (auto it: this->solucoes)
    {
        it->popular_solucao(ordernar_disciplinas(0, it));
        debug_heuristica(ordernar_disciplinas(0, it), it);
    }
}

void Heuristica::exibir_solucoes()
{
    for (auto it = this->solucoes.begin(); it != this->solucoes.end(); it++)
    {
        (*it)->exibir_solucao();
    }
}

void Heuristica::debug_heuristica(const std::vector<Disciplina *> &disciplinas_ordenadas, Solucao* sol)
{
    /* ---------------DEBUG BLOCK---------------------
    ** ! VERIFICAR COPIA DE PRT ADDR !
    */
    (*sol).debug_vector_disciplina_addr();
    std::cout << "\n\n"
              << std::endl;
    std::cout << "Endereco Lista t_disciplinas_ordenadas -> " << &disciplinas_ordenadas << std::endl;
    for (auto it : disciplinas_ordenadas)
    {
        std::cout << "Disciplina " << it->get_nome() << ";" << it << std::endl;
    }
    std::cout << std::endl;
}