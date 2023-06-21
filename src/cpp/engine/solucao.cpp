#include "solucao.hpp"

Solucao::Solucao(std::default_random_engine &t_rng, std::string t_instancia, int t_id)
{
    this->m_rng = t_rng;
    m_instancia = new Instancia(t_instancia);
    m_id = t_id;
    this->m_instancia_nome = t_instancia;
}

bool Solucao::popular_solucao(std::vector<Disciplina *> t_disciplinas_ordenadas)
{
    int iteracoes = 0;
    int iteracoes_limite = t_disciplinas_ordenadas.size();

    while (!t_disciplinas_ordenadas.empty())
    {
        if (iteracoes >
            (iteracoes_limite * iteracoes_limite))
        {
            return false;
        }

        auto professor_relacionado = encontrar_prof_relacionado(t_disciplinas_ordenadas.back());
        auto turma_relacionada = encontrar_turma_relacionada(t_disciplinas_ordenadas.back());

        bool verificado = verificar_horario(t_disciplinas_ordenadas.back(), professor_relacionado, turma_relacionada);
        if (verificado == true)
        {
            t_disciplinas_ordenadas.pop_back();
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
    {
        return true;
    }

    std::vector<int> splits{};
    int tam_total_disciplina = t_disciplina->get_ch_presencial();
    int horas_por_split = tam_total_disciplina / t_disciplina->get_split();

    for (int i = 0; i < t_disciplina->get_split() - 1; i++)
        splits.push_back(horas_por_split);
    splits.push_back(tam_total_disciplina - horas_por_split * (t_disciplina->get_split() - 1));

    int dias[6] = {0, 1, 2, 3, 4, 5};
    std::shuffle(dias, dias + 5, this->m_rng);

    for (int split = 0; split < splits.size(); split++)
    {
        for (auto dia : dias)
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
    for (auto professor : m_instancia->get_lista_professores())
    {
        for (auto disciplina : professor->get_disciplinas())
        {
            if (t_disciplina->get_id() == disciplina->get_id())
            {
                return professor;
            }
        }
    }

    exit(3);
}

Turma *Solucao::encontrar_turma_relacionada(Disciplina *t_disciplina)
{
    for (auto turma : m_instancia->get_lista_turmas())
    {
        for (auto disciplina : turma->get_disciplinas())
        {
            if (t_disciplina->get_id() == disciplina->get_id())
            {
                return turma;
            }
        }
    }

    exit(3);
}

std::vector<Turma *> Solucao::encontrar_turmas_relacionadas(Curso *curso)
{

    std::vector<Turma *> turmas_relacionadas{};

    auto turmas_str_id = curso->get_turmas();

    for (auto turma_id : turmas_str_id)
    {
        for (auto turma : get_instancia()->get_lista_turmas())
        {
            if (turma_id == turma->get_id())
            {
                turmas_relacionadas.push_back(turma);
                break;
            }
        }
    }

    return turmas_relacionadas;
}

void Solucao::exibir_solucao()
{
    for (auto it : m_instancia->get_lista_professores())
    {
        it->print_solucao();
    }

    for (auto it : m_instancia->get_lista_turmas())
    {
        it->print_solucao();
    }
}

Instancia *Solucao::get_instancia()
{
    return m_instancia;
}

// ! DEBUG FUNCTION
// ! Retorna o endereco da lista de disciplinas da Instancia
// ! e o endereço de suas disciplinas componentes.

void Solucao::debug_vector_disciplina_addr()
{
    auto t_disciplinas_debug = m_instancia->get_lista_disciplinas();
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

float Solucao::get_valor_solucao()
{
    return this->m_valor_solucao;
}

void Solucao::set_valor_solucao(float const &t_valor_avaliacao)
{
    this->m_valor_solucao = t_valor_avaliacao;
}

float Solucao::get_peso_janela()
{
    return this->m_peso_janelas;
}

void Solucao::set_peso_janela(float const &t_janela)
{
    this->m_peso_janelas = t_janela;
}

int Solucao::get_qtd_janela()
{
    return this->m_qtd_janelas;
}
void Solucao::set_qtd_janela(int const &t_janela)
{
    this->m_qtd_janelas = t_janela;
}

int Solucao::get_qtd_sexto_horario()
{
    return this->m_qtd_sexto;
}
void Solucao::set_qtd_sexto_horario(int const &t_sexto_horario)
{
    this->m_qtd_sexto = t_sexto_horario;
}

float Solucao::get_peso_sexto()
{
    return this->m_peso_sexto;
}

void Solucao::set_peso_sexto(float const &t_sexto_horario)
{
    this->m_peso_sexto = t_sexto_horario;
}

void Solucao::set_id_solucao(const int &t_id)
{
    this->m_id = t_id;
}

void Solucao::set_instancia_nome(std::string t_instancia)
{
    this->m_instancia_nome = t_instancia;
}

std::string Solucao::get_instancia_nome()
{
    return this->m_instancia_nome;
}

std::default_random_engine Solucao::get_rng()
{
    return this->m_rng;
}
void Solucao::set_rng(std::default_random_engine t_rng)
{
    this->m_rng = t_rng;
}

void Solucao::destruir_horario(std::vector<Turma *> t_turmas)
{
    for (auto turma : t_turmas)
    {
        auto disponibilidade = turma->get_disponibilidade();
        for (int dia = 0; dia < disponibilidade.size(); dia++)
        {
            for (int horario = 0; horario < disponibilidade[dia].size(); horario++)
            {
                if (disponibilidade[dia][horario] > 0)
                {
                    disponibilidade[dia][horario] = 0;
                }
            }
        }
        turma->set_disponibilidade(disponibilidade);
    }
}

void Solucao::destruir_horario(std::vector<Disciplina *> t_disciplinas)
{
    for (auto disciplina : t_disciplinas)
    {
        auto professor = encontrar_prof_relacionado(disciplina);
        auto disponibilidade = professor->get_disponibilidade();
        for (int dia = 0; dia < disponibilidade.size(); dia++)
        {
            for (int horario = 0; horario < disponibilidade[dia].size(); horario++)
            {
                if (disponibilidade[dia][horario] > 0)
                {
                    disponibilidade[dia][horario] = 0;
                }
            }
        }
        professor->set_disponibilidade(disponibilidade);
    }
}

void Solucao::busca_local(std::vector<int> t_turmas)
{

    std::vector<Disciplina *> disciplinas_turmas{};
    std::vector<Turma *> turmas{};
    std::vector<Professor *> professores_relacionados{};
    for (auto turma : t_turmas)
    {
        turmas.push_back(this->get_instancia()->get_lista_turmas()[turma]);
        std::vector<Disciplina *> temp_disciplinas = this->get_instancia()->get_lista_turmas()[turma]->get_disciplinas();
        disciplinas_turmas.insert(disciplinas_turmas.end(), temp_disciplinas.begin(), temp_disciplinas.end());
    }

    this->destruir_horario(turmas);
    this->destruir_horario(disciplinas_turmas);

    std::shuffle(disciplinas_turmas.begin(), disciplinas_turmas.end(), m_rng);

    if (this->popular_solucao(disciplinas_turmas)) //  Se popular_solucao() for true, set_factivel também é true
        this->set_factivel(true);
    else
        this->set_factivel(false);
}

Solucao::Solucao(Solucao &other)
{
    m_rng = other.get_rng();
    m_instancia = other.get_instancia();
    m_id = other.get_id_solucao();
    m_factivel = other.get_factivel();
    m_valor_solucao = other.get_valor_solucao();
    m_peso_janelas = other.get_peso_janela();
    m_peso_sexto = other.get_peso_sexto();
    m_qtd_janelas = other.get_qtd_janela();
    m_qtd_sexto = other.get_qtd_sexto_horario();
    m_instancia_nome = other.get_instancia_nome();
}

void Solucao::desalocar_atributos_solucao()
{
    m_instancia->destruir_atributos_instancia();
    delete m_instancia;
}
