#include "solucao.hpp"

Solucao::Solucao(std::string t_instancia, std::vector<Disciplina *> disciplinas_ordenadas)
{
    m_instancia = new Instancia(t_instancia);
    std::cout << "Gerada Instancia da Solução Populada."<< std::endl;

    if (disciplinas_ordenadas.size() > 0) 
    {
        
    }
}

Solucao::Solucao(std::string t_instancia)
{
    m_instancia = new Instancia(t_instancia);
    std::cout << "Gerada Instancia da Solução Zero."<< std::endl;
}

void Solucao::exibir_solucao()
{
    // Exibir agenda dos professores
    std::cout << RED "\n\nAgenda dos professores\n\n" NC;
    for (auto it : m_instancia->m_lista_professores)
    {
        it->print_solucao();
    }
    

    // Exibir agenda das turmas
    std::cout << RED "\n\nAgenda das Turmas\n\n" NC;
    for (auto it : m_instancia->m_lista_turmas)
    {
        it->print_solucao();
    }
}

Instancia Solucao::get_instancia() 
{
    return *m_instancia;
}

// ! DEBUG FUNCTION
// ! Retorna o endereco da lista de disciplinas da Instancia
// ! e o endereço de suas disciplinas componentes.

void Solucao::debug_vector_disciplina_addr()
{
    auto t_disciplinas_debug = m_instancia->m_lista_disciplinas;
    std::cout << "Endereco Lista Raiz -> " << &t_disciplinas_debug << std::endl;

    for (auto it : t_disciplinas_debug)
    {
        std::cout << "Disciplina " << it->get_nome() << ";" << it << std::endl;
    }
    std::cout << std::endl;
}
