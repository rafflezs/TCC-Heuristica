#include "heuristica.hpp"

Heuristica::Heuristica(std::string t_instancia_pipe, int tam_populacao)
{
    solucoes.push_back(new Solucao(t_instancia_pipe));
    for (int i = 0; i < tam_populacao; i++)
    {
        std::cout << CYN "Gerando Instancia " << t_instancia_pipe << " nº: " << i+1 << NC << std::endl;
        solucoes.push_back(new Solucao(t_instancia_pipe, {}));
    }
}

void Heuristica::exibir_solucoes()
{
    for (auto it = solucoes.begin(); it != solucoes.end(); it++)
    {
        (*it)->exibir_solucao();
    }
}

const std::vector<Disciplina*> Heuristica::ordernar_disciplinas(const int &rand_metodo)
{
    std::vector<Disciplina*> t_disciplinas_ordenadas = solucoes[0]->get_instancia().m_lista_disciplinas;
    
    solucoes[0]->debug_vector_disciplina_addr();
    
    std::cout << "\n\n"  << std::endl;

    std::cout << "Endereco Lista t_disciplinas_ordenadas -> " << &t_disciplinas_ordenadas << std::endl;

    for (auto it : t_disciplinas_ordenadas)
    {
        std::cout << "Disciplina " << it->get_nome() << ";" << it << std::endl;
    }
    std::cout << std::endl;

    return t_disciplinas_ordenadas;
}