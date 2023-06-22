#include "instancia.hpp"

Instancia::Instancia(const std::string ano_instancia)
{
    this->m_ano_instancia = ano_instancia;

    this->m_lista_disciplinas = instanciar_disciplina(ano_instancia);

    this->m_lista_turmas = instanciar_turma(ano_instancia);

    this->m_lista_professores = instanciar_professor(ano_instancia);

    this->m_lista_cursos = instanciar_curso(ano_instancia);

    relacionar_turmas_cursos();
}

Instancia::Instancia(Instancia &other)
{

    m_csv = other.m_csv;
    m_ano_instancia = other.m_ano_instancia;

    // Perform deep copy for the vector of Turma pointers
    for (Turma *turma : other.m_lista_turmas)
    {
        std::vector<Disciplina *> copy_disc;
        for (Disciplina *disciplina : turma->get_disciplinas())
        {
            // Find the cloned Disciplina in the new Instancia's m_lista_disciplinas
            for (Disciplina *shallow_disc_list : m_lista_disciplinas)
            {
                if (shallow_disc_list->get_id() == disciplina->get_id())
                {
                    copy_disc.push_back(shallow_disc_list);
                    break;
                }
            }
        }
        m_lista_turmas.push_back(new Turma(*turma, turma->get_curso(), copy_disc));
    }

    // Perform deep copy for the vector of Professor pointers
    for (Professor *professor : other.m_lista_professores)
    {
        std::vector<Disciplina *> copy_disc;
        for (Disciplina *disciplina : professor->get_disciplinas())
        {
            // Find the cloned Disciplina in the new Instancia's m_lista_disciplinas
            for (Disciplina *shallow_disc_list : m_lista_disciplinas)
            {
                if (shallow_disc_list->get_id() == disciplina->get_id())
                {
                    copy_disc.push_back(shallow_disc_list);
                    break;
                }
            }
        }
        m_lista_professores.push_back(new Professor(*professor, copy_disc));
    }
}

Instancia::~Instancia()
{
    // Deallocate the dynamically allocated Turma objects
    for (Turma *turma : m_lista_turmas)
    {
        delete turma;
    }

    // Deallocate the dynamically allocated Professor objects
    for (Professor *professor : m_lista_professores)
    {
        delete professor;
    }

    // Deallocate the dynamically allocated Disciplina objects
    for (Disciplina *disciplina : m_lista_disciplinas)
    {
        delete disciplina;
    }

    // Deallocate the dynamically allocated Curso objects
    for (Curso *curso : m_lista_cursos)
    {
        delete curso;
    }
}

const std::vector<Professor *> Instancia::instanciar_professor(const std::string &ano_instancia)
{
    std::vector<Professor *> t_professores;
    std::ifstream file{"data/csv/" + ano_instancia + "/Professores.csv"}; // WSL
    // std::ifstream file{"/home/rafflezs/Programacao/TCC/data/csv/" + ano_instancia + "/Professores.csv"}; // Unix
    // std::ifstream file{"D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Professores.csv"}; // Windows
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    std::vector<std::vector<std::string>>::iterator row = csv.begin();
    row++;
    for (; row != csv.end(); row++)
    {
        t_professores.push_back(new Professor(
            (*row)[0],
            index,
            (*row)[1],
            buscar_disciplinas(m_csv.parse_coluna((*row)[2], ',')),
            m_csv.preencher_disponibilidade({(*row)[3], (*row)[4], (*row)[5], (*row)[6], (*row)[7], (*row)[8]})));

        index++;
    }

    file.close();

    return t_professores;
}

const std::vector<Curso *> Instancia::instanciar_curso(const std::string &ano_instancia)
{
    std::vector<Curso *> t_cursos;
    std::ifstream file{"data/csv/" + ano_instancia + "/Cursos.csv"}; // WSL
    // std::ifstream file{"/home/rafflezs/Programacao/TCC/data/csv/" + ano_instancia + "/Cursos.csv"}; // Unix
    // std::ifstream file{"D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Cursos.csv"}; // Windows
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    std::vector<std::vector<std::string>>::iterator row = csv.begin();
    row++;
    for (; row != csv.end(); row++)
    {

        t_cursos.push_back(
            new Curso(
                (*row)[0],
                index,
                (*row)[1],
                (*row)[2],
                buscar_turmas_index(m_csv.parse_coluna((*row)[3], ',')),
                m_csv.parse_coluna((*row)[3], ','),
                m_csv.preencher_disponibilidade({(*row)[4], (*row)[5], (*row)[6], (*row)[7], (*row)[8], (*row)[9]})));

        index++;
    }

    file.close();

    return t_cursos;
}

const std::vector<Turma *> Instancia::instanciar_turma(const std::string &ano_instancia)
{
    std::vector<Turma *> t_turmas;
    std::ifstream file{"data/csv/" + ano_instancia + "/Turmas.csv"}; // WSL
    // std::ifstream file{"/home/rafflezs/Programacao/TCC/data/csv/" + ano_instancia + "/Turmas.csv"}; // Unix
    // std::ifstream file{"D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Turmas.csv"}; // Windows
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    std::vector<std::vector<std::string>>::iterator row = csv.begin();
    row++;
    for (; row != csv.end(); row++)
    {

        int int_primeiro_horario = 0;
        int int_ultimo_horario = 5;

        if ((*row)[3] == "Tarde")
        {

            int_primeiro_horario = 6;
            int_ultimo_horario = 11;
        }
        else if ((*row)[3] == "Noite")
        {

            int_primeiro_horario = 12;
            int_ultimo_horario = 15;
        }

        t_turmas.push_back(new Turma(
            (*row)[0],
            index,
            (*row)[2],
            (*row)[3],
            (*row)[1],
            buscar_disciplinas(m_csv.parse_coluna((*row)[4], ',')),
            m_csv.preencher_disponibilidade({(*row)[5], (*row)[6], (*row)[7], (*row)[8], (*row)[9], (*row)[10]}),
            int_primeiro_horario,
            int_ultimo_horario,
            nullptr));

        index++;
    }

    file.close();

    return t_turmas;
}

const std::vector<Disciplina *> Instancia::instanciar_disciplina(const std::string &ano_instancia)
{
    std::vector<Disciplina *> t_disciplinas;
    std::ifstream file{"data/csv/" + ano_instancia + "/Disciplinas.csv"}; // WSL
    // std::ifstream file{"/home/rafflezs/Programacao/TCC/data/csv/" + ano_instancia + "/Disciplinas.csv"}; // Unix
    // std::ifstream file{"D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Disciplinas.csv"}; // Windows
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    std::vector<std::vector<std::string>>::iterator row = csv.begin();
    row++;
    for (; row != csv.end(); row++)
    {
        t_disciplinas.push_back(new Disciplina(
            (*row)[0],
            (*row)[1],
            index,
            (*row)[2],
            (*row)[5],
            std::stoi((*row)[6]),
            std::stoi((*row)[7]),
            std::stoi((*row)[8]),
            std::stoi((*row)[9]),
            std::stoi((*row)[10]),
            m_csv.preencher_disponibilidade({(*row)[11], (*row)[12], (*row)[13], (*row)[14], (*row)[15], (*row)[16]})));

        index++;
    }

    file.close();

    return t_disciplinas;
}

std::vector<Disciplina *> Instancia::buscar_disciplinas(const std::vector<std::string> &nome_disciplinas)
{

    std::vector<Disciplina *> t_disc{};

    for (auto parse_disciplina : nome_disciplinas)
    {
        for (auto it : m_lista_disciplinas)
        {
            if (parse_disciplina == it->get_id())
            {
                t_disc.push_back(it);
                continue;
            }
        }
    }

    return t_disc;
}

std::vector<int> Instancia::buscar_turmas_index(const std::vector<std::string> &t_turmas)
{

    std::vector<int> turmas_index{};

    for (auto turma_str_id : t_turmas)
    {
        for (auto it : m_lista_turmas)
        {
            if (turma_str_id == it->get_id())
            {
                turmas_index.push_back(it->get_index());
                continue;
            }
        }
    }

    return turmas_index;
}

void Instancia::relacionar_turmas_cursos()
{
    std::unordered_map<std::string, Curso *> cursos_map;

    for (Curso *curso : m_lista_cursos)
    {
        cursos_map[curso->get_nome()] = curso;
    }

    for (Turma *turma : m_lista_turmas)
    {
        const std::string &curso_str = turma->get_curso_str();
        auto it = cursos_map.find(curso_str);
        if (it != cursos_map.end())
        {
            turma->set_curso(it->second);
        }
        else
        {
            turma->set_curso(nullptr);
        }
    }
}

Turma *Instancia::get_turma_por_id(int turma_index)
{
    Turma *m_turma = m_lista_turmas.at(turma_index);
    return m_turma;
}

std::vector<Turma *> Instancia::get_lista_turmas()
{
    return this->m_lista_turmas;
}
std::vector<Professor *> Instancia::get_lista_professores()
{
    return this->m_lista_professores;
}
std::vector<Disciplina *> Instancia::get_lista_disciplinas()
{
    return this->m_lista_disciplinas;
}
std::vector<Curso *> Instancia::get_lista_cursos()
{
    return this->m_lista_cursos;
}
std::string Instancia::get_ano_instancia()
{
    return this->m_ano_instancia;
}

void Instancia::set_lista_turmas(const std::vector<Turma *> t_input)
{
    this->m_lista_turmas = t_input;
}
void Instancia::set_lista_professores(const std::vector<Professor *> t_input)
{
    this->m_lista_professores = t_input;
}
void Instancia::set_lista_disciplinas(const std::vector<Disciplina *> t_input)
{
    this->m_lista_disciplinas = t_input;
}
void Instancia::set_lista_cursos(const std::vector<Curso *> t_input)
{
    this->m_lista_cursos = t_input;
}
void Instancia::set_ano_instancia(const std::string &t_input)
{
    this->m_ano_instancia = t_input;
}

void Instancia::print_instancia()
{
    std::cout << "\n\n--------Lista de Disciplinas--------\n";
    for (auto it = m_lista_disciplinas.begin(); it < m_lista_disciplinas.end(); it++)
    {
        (*it)->print();
    }

    std::cout << "\n\n--------Lista de Cursos--------\n";
    for (auto it = m_lista_cursos.begin(); it < m_lista_cursos.end(); it++)
    {
        (*it)->print();
    }

    std::cout << "\n\n--------Lista de Professores--------\n";
    for (auto it = m_lista_professores.begin(); it < m_lista_professores.end(); it++)
    {
        (*it)->print();
    }

    std::cout << "\n\n--------Lista de Turmas--------\n";
    for (auto it = m_lista_turmas.begin(); it < m_lista_turmas.end(); it++)
    {
        (*it)->print();
    }
}

Instancia *Instancia::shallow_copy()
{
    Instancia *inst = new Instancia(this->m_ano_instancia);
    inst->m_csv = m_csv;
    for (auto turma : m_lista_turmas)
    {
        inst->m_lista_turmas.push_back(turma);
    }
    for (auto prof : m_lista_professores)
    {
        inst->m_lista_professores.push_back(prof);
    }
    for (auto disc : m_lista_disciplinas)
    {
        inst->m_lista_disciplinas.push_back(disc);
    }
    for (auto curso : m_lista_cursos)
    {
        inst->m_lista_cursos.push_back(curso);
    }
    return inst;
}

void Instancia::destruir_atributos_instancia()
{
    // Desalocar cursos
    for (int i = 0; i < m_lista_cursos.size(); i++)
    {
        delete m_lista_cursos[i];
    }

    // Desalocar turmas
    for (int i = 0; i < m_lista_turmas.size(); i++)
    {
        m_lista_turmas[i]->destruir_turma();
        delete m_lista_turmas[i];
    }

    // Desalocar professores
    for (int i = 0; i < m_lista_professores.size(); i++)
    {
        m_lista_professores[i]->destruir_professor();
        delete m_lista_professores[i];
    }

    // Desalocar disciplinas
    for (int i = 0; i < m_lista_disciplinas.size(); i++)
    {
        delete m_lista_disciplinas[i];
    }
}