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
    int iterations_limit = disciplinas_ordenadas.size();

    std::cout << "\n\nPopulando solução " << this->get_id_solucao() << std::endl;
    while (disciplinas_ordenadas.size() != 0)
    {
        if (iteracoes >
            (iterations_limit * iterations_limit))
        {
            printf("População encerrada por excesso de iterações\n");
            return false;
        }

        auto disciplina = disciplinas_ordenadas[disciplinas_ordenadas.size() - 1];

        // std::cout << disciplina->get_nome() << " | " << disciplina->get_nome() << std::endl;
        auto professor_relacionado = encontrar_prof_relacionado(disciplina);
        auto turma_relacionada = encontrar_turma_relacionada(disciplina);
        // std::cout << std::endl;

        bool verificado = verificar_horario(disciplina, professor_relacionado, turma_relacionada);
        if (verificado == true)
        {
            disciplinas_ordenadas.pop_back();
            iteracoes++;
            std::cout << "Disciplina alocada\n" << std::endl;
        }
        else
            iteracoes++;
    }

    if (disciplinas_ordenadas.empty())
        return true;
    return false;
}

bool Solucao::verificar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma)
{
    std::cout << "Alocando disciplina " << t_disciplina->get_nome() << "(" << t_disciplina->get_index   () << ")" << " para o professor " << t_professor->get_nome() << " e turma " << t_turma->get_nome() << std::endl;


    if (t_disciplina->get_ch_presencial() == 0)
    {
        std::cout << "Disciplina com CH Nula " << std::endl;
        return true;
    }


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

    std::cout << "A disciplina possui  CH-Presencial " << t_disciplina->get_ch_presencial() << " e " << t_disciplina->get_split() << " sendo eles: {";
    for (auto split : splits) std::cout << split << ", ";
    std::cout << "}" << std::endl;


    // ! Problema ta aqui o fila duma puta
    // ! é so dar um jeito de terminar o loop onde ele deve terminar

    for (auto split : splits)
    {
        for (int dia = 0; dia < 6; dia++)
        {
            for (int horario = 0; horario < (16 - t_disciplina->get_ch_min()); horario++)
            {
                if (tem_choque(t_disciplina, t_professor, dia, horario, split) == false && tem_choque(t_disciplina, t_turma, dia, horario, split) == false)
                {
                    std::cout << "Não houve choque para o professor " << t_professor->get_nome() << " e turma " << t_turma->get_nome() << ". Alocando horário" << std::endl;
                    alocar_horario(t_disciplina, t_professor, t_turma, dia, horario, split);
                    break;
                }
                break;
            }
            break;
        }
    }

    return false;
}

void Solucao::alocar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split)
{
    int split_professor = t_split;
    std::cout << "ID da Disciplina: " << t_disciplina->get_index() << std::endl;
    auto horario = t_professor->get_disponibilidade();
    for (int j = t_horario_inicial; j < horario[t_dia_escolhido].size(); j++)
    {
        if (split_professor == 0)
            break;
        horario[t_dia_escolhido][j] = t_disciplina->get_index();
        split_professor--;
    }
    t_professor->set_disponibilidade(horario);

    int split_aluno = t_split;
    horario = t_turma->get_disponibilidade();
    for (int j = t_horario_inicial; j < horario[t_dia_escolhido].size(); j++)
    {
        if (split_aluno== 0)
            break;
        horario[t_dia_escolhido][j] = t_disciplina->get_index();
        split_aluno--;
    }
    t_turma->set_disponibilidade(horario);
}

bool Solucao::tem_choque(Disciplina *t_disciplina, Professor *t_professor, int t_dia_escolhido, int t_horario_inicial, int t_split)
{
    auto horario = t_professor->get_disponibilidade();
    int consecutivo = 0;
    for (int j = t_horario_inicial; j < horario[t_dia_escolhido].size(); j++)
    {
        if (consecutivo == t_split) break;
        if (horario[t_dia_escolhido][j] == 0)
        {
            std::cout << "Dia " << t_dia_escolhido+1 << " horario " << j+1 << " disponível" << " -> " << horario[t_dia_escolhido][j] << std::endl;
            consecutivo++;
        }
    }

    if (consecutivo == t_split)
    {
        std::cout << "Choque não encontrado. Dia x Horario-Inicial: " << t_dia_escolhido+1 << " x " << t_horario_inicial+1 << ". Consecutivo " << consecutivo << " == Split " << t_split << std::endl;
        return false;
    }

    std::cout << "Houve choque para a disciplina " << t_disciplina->get_index() << " - " << t_disciplina->get_nome() << std::endl;
    t_professor->print_solucao();
    return true;
}

bool Solucao::tem_choque(Disciplina *t_disciplina, Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split)
{
    auto horario = t_turma->get_disponibilidade();
    int consecutivo = 0;
    for (int j = t_horario_inicial; j < horario[t_dia_escolhido].size(); j++)
    {
        if (consecutivo == t_split) break;
        if (horario[t_dia_escolhido][j] == 0)
        {
            std::cout << "Dia " << t_dia_escolhido+1 << " horario " << j+1 << " disponível" << " -> " << horario[t_dia_escolhido][j] << std::endl;
            consecutivo++;
        }
    }

    if (consecutivo == t_split)
    {
        std::cout << "Choque não encontrado. Dia x Horario-Inicial: " << t_dia_escolhido+1 << " x " << t_horario_inicial+1 << ". Consecutivo " << consecutivo << " == Split " << t_split << std::endl;
        return false;
    }

    std::cout << "Houve choque para a disciplina " << t_disciplina->get_index() << " - " << t_disciplina->get_nome() << std::endl;
    t_turma->print_solucao();
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
                // std::cout << "Professor encontrado: " << it->get_id() << " | " << it->get_nome() << std::endl;
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
                // std::cout << "Turma encontrado: " << it->get_id() << " | " << it->get_nome() << std::endl;
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
