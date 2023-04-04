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
    while (!disciplinas_ordenadas.empty())
    {
        std::cout << "Iteracao " << iteracoes << " | Disciplina " << disciplinas_ordenadas.back()->get_index() << " - " << disciplinas_ordenadas.back()->get_nome() << std::endl;
        if (iteracoes >
            (iterations_limit * iterations_limit))
        {
            printf("População encerrada por excesso de iterações\n");
            return false;
        }

        // std::cout << disciplina->get_nome() << " | " << disciplina->get_nome() << std::endl;
        auto professor_relacionado = encontrar_prof_relacionado(disciplinas_ordenadas.back());
        auto turma_relacionada = encontrar_turma_relacionada(disciplinas_ordenadas.back());
        // std::cout << std::endl;

        int dias[6] = {0,1,2,3,4,5};
        auto verificar_rd_dias = std::rand() % 2;

        if ( verificar_rd_dias == 1)
        {
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(dias, dias + 6, g);
        }

        bool verificado = verificar_horario(disciplinas_ordenadas.back(), professor_relacionado, turma_relacionada, dias);
        if (verificado == true)
        {
            disciplinas_ordenadas.pop_back();
            iteracoes++;
            std::cout << "Disciplina alocada\n"
                      << std::endl;
        }
        else
            iteracoes++;
    }

    return true;
}

bool Solucao::verificar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma, int* t_dias)
{
    std::cout << "Alocando disciplina " << t_disciplina->get_nome() << "(" << t_disciplina->get_index() << ")"
              << " para o professor " << t_professor->get_nome() << " e turma " << t_turma->get_nome() << std::endl;

    if (t_disciplina->get_ch_presencial() == 0)
    {
        std::cout << "Disciplina com CH Nula " << std::endl;
        return true;
    }

    std::vector<int> splits{};
    int tam_total_disciplina = t_disciplina->get_ch_presencial();
    int horas_por_split = tam_total_disciplina / t_disciplina->get_split();

    for (int i = 0; i < t_disciplina->get_split() - 1; i++)
        splits.push_back(horas_por_split);
    splits.push_back(tam_total_disciplina - horas_por_split * (t_disciplina->get_split() - 1));

    std::cout << "Split Size= " << splits.size() << std::endl;

    for (int split = 0; split < splits.size(); split++)
    {
        std::cout << "Split [i] = " << splits[split] << std::endl;
        //int random_day = rand() % 6;
        //for (int d = 0; d < 6; d++)
        for (int dia = 0; dia < 6; dia++)
        {
            //dia = (d + random_day) % 6;
            std::cout << "Verificando possibilidade no dia " << dia << std::endl;
            for (int horario = t_turma->get_primeiro_horario_turno(); horario <= t_turma->get_ultimo_horario_turno(); horario++)
            {
                std::cout << "Verificando possibilidade do horario " << horario << " ate o horario " << t_turma->get_ultimo_horario_turno() << std::endl;
                if (eh_horario_disponivel(t_turma, dia, horario, splits[split]) && eh_horario_disponivel(t_professor, dia, horario, splits[split]))
                {
                    alocar_horario(t_disciplina, t_professor, t_turma, dia, horario, splits[split]);
                    split++;
                    std::cout << "Alocação bem-sucedida. Split: " << split << std::endl;
                    break;
                }
            }
            if (split == splits.size())
                break;
        }
    }

    std::cout << std::endl;
    return true;
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

    t_professor->print_solucao();

    int split_aluno = t_split;
    horario = t_turma->get_disponibilidade();
    for (int j = t_horario_inicial; j < horario[t_dia_escolhido].size(); j++)
    {
        if (split_aluno == 0)
            break;
        horario[t_dia_escolhido][j] = t_disciplina->get_index();
        split_aluno--;
    }
    t_turma->set_disponibilidade(horario);
    t_turma->print_solucao();

    std::cout << std::endl;
}

bool Solucao::eh_horario_disponivel(Professor *t_professor, int t_dia_escolhido, int t_horario_inicial, int t_split)
{
    // if (t_horario_inicial + t_split > (t_turma->get_primeiro_horario_turno() % 16))
    // {
    // }

    int alocado = 0;

    for (int i = t_horario_inicial; i < t_horario_inicial + t_split; i++)
        if (t_professor->get_disponibilidade()[t_dia_escolhido][i] == 0)
            alocado++;
        else
            std::cout << "(Professor) Horario " << i << " do dia " << t_dia_escolhido << " indisponivel" << std::endl;

    if (t_split == alocado)
        return true;

    return false;
}

bool Solucao::eh_horario_disponivel(Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split)
{
    // if (t_horario_inicial + t_split > (t_turma->get_primeiro_horario_turno() % 16))
    // {
    // }

    int alocado = 0;

    for (int i = t_horario_inicial; i < t_horario_inicial + t_split; i++)
        if (t_turma->get_disponibilidade()[t_dia_escolhido][i] == 0)
            alocado++;
        else
            std::cout << "(Turma) Horario " << i << " do dia " << t_dia_escolhido << " indisponivel" << std::endl;

    if (t_split == alocado)
        return true;

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

// void Solucao::trocar_disciplina(int ponto_de_corte, Disciplina* t_disicplina)
// {
    // std::srand(std::time(nullptr));
    // int disciplina1_index = std::rand() % disciplinas_ordenadas.size();
    // int disciplina2_index = std::rand() % disciplinas_ordenadas.size();
    // std::swap(disciplinas_ordenadas[disciplina1_index], disciplinas_ordenadas[disciplina2_index]);
// }

int Solucao::get_id_solucao()
{
    return this->m_id;
}

bool Solucao::get_factivel()
{
    return this->m_factivel;
}

void Solucao::set_factivel(bool const &t_factivel)
{
    this->m_factivel = t_factivel;
}

float Solucao::get_valor_avaliacao()
{
    return this->m_valor_avaliado;
}

void Solucao::set_valor_avaliacao(float const &t_valor_avaliacao)
{
    this->m_valor_avaliado = t_valor_avaliacao;
}

float Solucao::get_janela()
{
    return this->m_valor_janelas;
}

void Solucao::set_janela(float const &t_janela)
{
    this->m_valor_janelas = t_janela;
}

float Solucao::get_sexto_horario()
{
    return this->m_valor_sextos_horarios;
}

void Solucao::set_sexto_horario(float const &t_sexto_horario)
{
    this->m_valor_sextos_horarios = t_sexto_horario;
}