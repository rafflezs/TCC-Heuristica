#include "solucao.hpp"

Solucao::Solucao(std::string t_instancia)
{
    m_instancia = new Instancia(t_instancia);
    std::cout << "Gerada Instancia da Solução Populada." << std::endl;
}

void Solucao::popular_solucao(std::vector<Disciplina *> disciplinas_ordenadas)
{
    int iteracoes = 0;
    while (disciplinas_ordenadas.size() != 0)
    {
        auto disciplina = disciplinas_ordenadas[disciplinas_ordenadas.size() - 1];
        std::cout << disciplina->get_nome() << " | " << disciplina->get_nome() << std::endl;
        auto professor_relacionado = encontrar_prof_relacionado(disciplina);
        auto turma_relacionada = encontrar_turma_relacionada(disciplina);
        std::cout << std::endl;
        if (iteracoes >
            (disciplinas_ordenadas.size() * disciplinas_ordenadas.size()))
        {
            printf("População encerrada por excesso de iterações\n");
            break;
        }

        disciplinas_ordenadas.pop_back();
    }
    std::cout << std::endl;
}

bool Solucao::tem_choque(Disciplina *t_disciplina)
{
    return false;
}

Professor *Solucao::encontrar_prof_relacionado(Disciplina *t_disciplina)
{
    for (auto it : m_instancia->m_lista_professores)
    {
        for (auto d : it->get_disciplinas())
        {
            if (t_disciplina == d)
            {
                std::cout << "Professor encontrado: " << it->get_id() << " | " << it->get_nome() << std::endl;
                return it;
            }
        }
    }

    std::cout << "Turma não encontrado" << std::endl;
    return (new Professor{});
}

Turma *Solucao::encontrar_turma_relacionada(Disciplina *t_disciplina)
{
    for (auto it : m_instancia->m_lista_turmas)
    {
        for (auto d : it->get_disciplinas())
        {
            if (t_disciplina == d)
            {
                std::cout << "Turma encontrado: " << it->get_id() << " | " << it->get_nome() << std::endl;
                return it;
            }
        }
    }

    std::cout << "Turma não encontrado" << std::endl;
    return (new Turma{});
}

Curso *Solucao::encontrar_curso_relacionado(Turma *t_turma)
{
    for (auto it : m_instancia->m_lista_cursos)
    {
        for (auto t : it->get_turmas())
        {
            if (t_turma == t)
            {
                std::cout << "Curso encontrado: " << it->get_id() << " | " << it->get_nome() << std::endl;
                return it;
            }
        }
    }

    std::cout << "Turma não encontrado" << std::endl;
    return (new Curso{});
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
    std::cout << "Endereco Lista Raiz;" << &t_disciplinas_debug << std::endl;

    for (auto it : t_disciplinas_debug)
    {
        std::cout << it->get_nome() << ";" << it << std::endl;
    }
    std::cout << std::endl;
}
