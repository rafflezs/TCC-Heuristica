#include "solucao.hpp"

Solucao::Solucao(std::default_random_engine &t_rng, std::string t_instancia, int t_id)
{
    this->m_rng = t_rng;
    m_instancia = new Instancia(t_instancia);
    m_id = t_id;
    this->m_instancia_nome = t_instancia;
}

bool Solucao::popular_solucao(std::vector<Disciplina *> disciplinas_ordenadas)
{
    int iteracoes = 0;
    int iterations_limit = disciplinas_ordenadas.size();

    while (!disciplinas_ordenadas.empty())
    {
        if (iteracoes >
            (iterations_limit * iterations_limit))
        {
            return false;
        }

        auto professor_relacionado = encontrar_prof_relacionado(disciplinas_ordenadas.back());
        auto turma_relacionada = encontrar_turma_relacionada(disciplinas_ordenadas.back());

        int dias[6] = {0, 1, 2, 3, 4, 5};
        auto verificar_rd_dias = std::rand() % 2;

        if (verificar_rd_dias == 1)
        {
            std::shuffle(dias, dias + 6, this->m_rng);
        }

        bool verificado = verificar_horario(disciplinas_ordenadas.back(), professor_relacionado, turma_relacionada, dias);
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

bool Solucao::verificar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma, int *t_dias)
{

    if (t_disciplina->get_ch_presencial() == 0)
    {
        return true;
    }

    std::vector<int> splits{};
    int tam_total_disciplina = t_disciplina->get_ch_presencial();
    int horas_por_split = tam_total_disciplina / t_disciplina->get_split();

    for (int i = 0; i < t_disciplina->get_split() - 1; i++)
        splits.push_back(horas_por_split);
    splits.push_back(tam_total_disciplina - horas_por_split * (t_disciplina->get_split() - 1));


    for (int split = 0; split < splits.size(); split++)
    {
        for (int dia = 0; dia < 6; dia++)
        {
            for (int horario = t_turma->get_primeiro_horario_turno(); horario <= t_turma->get_ultimo_horario_turno(); horario++)
            {
                if (eh_horario_disponivel(t_turma, dia, horario, splits[split]) && eh_horario_disponivel(t_professor, dia, horario, splits[split]))
                {
                    alocar_horario(t_disciplina, t_professor, t_turma, dia, horario, splits[split]);
                    split++;
                    break;
                }
            }
            if (split == splits.size())
                break;
        }
    }

    return true;
}

void Solucao::alocar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split)
{
    int split_professor = t_split;
    auto horario = t_professor->get_disponibilidade();
    for (int j = t_horario_inicial; j < horario[t_dia_escolhido].size(); j++)
    {
        if (split_professor == 0)
            break;
        horario[t_dia_escolhido][j] = t_disciplina->get_index();
        split_professor--;
    }
    t_professor->set_disponibilidade(horario);

    // t_professor->print_solucao();

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
    // t_turma->print_solucao();

}

bool Solucao::eh_horario_disponivel(Professor *t_professor, int t_dia_escolhido, int t_horario_inicial, int t_split)
{

    int alocado = 0;

    for (int i = t_horario_inicial; i < t_horario_inicial + t_split; i++)
        if (t_professor->get_disponibilidade()[t_dia_escolhido][i] == 0)
            alocado++;
        else
            continue;

    if (t_split == alocado)
        return true;

    return false;
}

bool Solucao::eh_horario_disponivel(Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split)
{

    int alocado = 0;

    for (int i = t_horario_inicial; i < t_horario_inicial + t_split; i++)
        if (t_turma->get_disponibilidade()[t_dia_escolhido][i] == 0)
            alocado++;
        else
            continue;

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
                return it;
            }
        }
    }

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
                return it;
            }
        }
    }

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
                return it;
            }
        }
    }

    return (new Curso{});
}

void Solucao::exibir_solucao()
{
    for (auto it : m_instancia->m_lista_professores)
    {
        it->print_solucao();
    }

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

void Solucao::set_id_solucao(const int &t_id)
{
    this->m_id = t_id;
}

void Solucao::set_instancia_nome(std::string t_instancia)
{
    this->m_instancia_nome = t_instancia;
}

Solucao *Solucao::shallow_copy()
{
    Solucao *sol = new Solucao(this->m_rng, this->m_instancia_nome, this->m_id);

    sol->set_instancia_nome(this->m_instancia_nome);
    sol->set_id_solucao(this->m_id);
    sol->set_factivel(this->m_factivel);
    sol->set_valor_avaliacao(this->m_valor_avaliado);
    sol->set_janela(this->m_valor_janelas);
    sol->set_sexto_horario(this->m_valor_sextos_horarios);
    return sol;
}