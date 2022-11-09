#include "solucao.hpp"

Solucao::Solucao(std::string t_instancia, int t_id)
{
    m_instancia = new Instancia(t_instancia);
    m_id = t_id;
    std::cout << "Gerada Instancia da Solução Populada." << std::endl;
}

bool Solucao::popular_solucao(std::vector<Disciplina *> disciplinas_ordenadas)
{
    int iteracoes = 0;

    while (disciplinas_ordenadas.size() != 0)
    {
        if (iteracoes >
            (disciplinas_ordenadas.size() * disciplinas_ordenadas.size()))
        {
            printf("População encerrada por excesso de iterações\n");
            return false;
        }

        auto disciplina = disciplinas_ordenadas[disciplinas_ordenadas.size() - 1];

        std::cout << disciplina->get_nome() << " | " << disciplina->get_nome() << std::endl;
        auto professor_relacionado = encontrar_prof_relacionado(disciplina);
        auto turma_relacionada = encontrar_turma_relacionada(disciplina);
        std::cout << std::endl;

        bool verificado = verificar_horario(disciplina, professor_relacionado, turma_relacionada);
        if (verificado == true)
        {
            disciplinas_ordenadas.pop_back();
            iteracoes++;
        }
        else
            iteracoes++;
    }
    return true;
}

bool Solucao::verificar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma)
{
    if (t_disciplina->get_ch_presencial() == 0)
        return true;

    std::vector<int> splits{};
    if (t_disciplina->get_ch_presencial() % t_disciplina->get_split() == 0)
        for (int i = 0; i < t_disciplina->get_split(); i++)
            splits.push_back(t_disciplina->get_ch_min());
    else
    {
        int tam_total_disciplina = t_disciplina->get_ch_presencial();
        for (int i = 0; i < t_disciplina->get_split(); i++)
            splits.push_back(t_disciplina->get_ch_min());
        splits.back() = splits.back() + (t_disciplina->get_ch_presencial() % t_disciplina->get_split());
    }

    for (auto split : splits)
    {
        for (int dia = 0; dia < 6; dia++)
        {
            for (int horario = 0; horario < (16 - t_disciplina->get_ch_min()); horario++)
            {
                if (!tem_choque(t_disciplina, t_professor, dia, horario, split) && !tem_choque(t_disciplina, t_turma, dia, horario, split))
                {
                    alocar_horario(t_disciplina, t_professor, t_turma, dia, horario, split);
                }
            }
        }
    }

    return false;
}

void Solucao::alocar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split)
{
    auto horario = t_professor->get_disponibilidade();
    for (int j = t_horario_inicial; j < horario[t_dia_escolhido].size(); j++)
    {
        if (t_split == 0)
            break;
        horario[t_dia_escolhido][j] = t_disciplina->get_id_nominal();
        t_split--;
    }
    t_professor->set_disponibilidade(horario);

    horario = t_turma->get_disponibilidade();
    for (int j = t_horario_inicial; j < horario[t_dia_escolhido].size(); j++)
    {
        if (t_split == 0)
            break;
        horario[t_dia_escolhido][j] = t_disciplina->get_id_nominal();
        t_split--;
    }
    t_turma->set_disponibilidade(horario);
}

bool Solucao::tem_choque(Disciplina *t_disciplina, Professor *t_professor, int t_dia_escolhido, int t_horario_inicial, int t_split)
{
    auto horario = t_professor->get_disponibilidade();
    int consecutivo = 0;
    for (int j = t_horario_inicial; j < horario[t_dia_escolhido].size(); j++)
    {
        if (horario[t_dia_escolhido][j] != 0)
            consecutivo++;
        if (consecutivo == t_split)
            return false;
    }

    return true;
}

bool Solucao::tem_choque(Disciplina *t_disciplina, Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split)
{
    auto horario = t_turma->get_disponibilidade();
    int consecutivo = 0;
    for (int j = t_horario_inicial; j < horario[t_dia_escolhido].size(); j++)
    {
        if (horario[t_dia_escolhido][j] != 0)
            consecutivo++;
        if (consecutivo == t_split)
            return false;
    }

    return true;
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

int Solucao::get_id_solucao()
{
    return this->m_id;
}
