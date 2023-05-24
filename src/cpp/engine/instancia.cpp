#include "instancia.hpp"

Instancia::Instancia(const std::string ano_instancia)
{
    // std::cout << "Gerando instancia do periodo: " + ano_instancia << std::endl;
    this->m_ano_instancia = ano_instancia;

    this->m_lista_disciplinas = instanciar_disciplina(ano_instancia);
    // std::cout << "Gerou lista de disciplinas" << std::endl;

    this->m_lista_turmas = instanciar_turma(ano_instancia);
    // std::cout << "Gerou lista de turmas" << std::endl;

    this->m_lista_professores = instanciar_professor(ano_instancia);
    // std::cout << "Gerou lista de professores" << std::endl;

    this->m_lista_cursos = instanciar_curso(ano_instancia);
    // std::cout << "Gerou lista de cursos" << std::endl;

    relacionar_turmas_cursos();
}

const std::vector<Professor *> Instancia::instanciar_professor(const std::string &ano_instancia)
{
    std::vector<Professor *> t_professores;
    std::ifstream file{"data/csv/" + ano_instancia + "/Professores.csv"}; // WSL
    // std::ifstream file{"/home/rafflezs/Programacao/TCC/data/csv/" + ano_instancia + "/Professores.csv"}; // Unix
    // std::ifstream file{"D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Professores.csv"}; // Windows
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++)
    {
        if (index > 0)
        {
            t_professores.push_back(new Professor(
                (*row)[0],
                index,
                (*row)[1],
                buscar_disciplinas(m_csv.parse_coluna((*row)[2], ',')),
                m_csv.preencher_disponibilidade({(*row)[3], (*row)[4], (*row)[5], (*row)[6], (*row)[7], (*row)[8]})));
        }
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
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++)
    {
        if (index > 0)
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
        }
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
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++)
    {
        if (index > 0)
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
        }
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
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++)
    {
        if (index > 0)
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
        }
        index++;
    }

    file.close();

    return t_disciplinas;
}

std::vector<Disciplina *> Instancia::buscar_disciplinas(const std::vector<std::string> &nome_disciplinas)
{

    std::vector<Disciplina *> t_disc{nullptr};

    for (auto parse_disciplina : nome_disciplinas)
    {
        for (auto it : m_lista_disciplinas)
        {
            if (parse_disciplina == it->get_id())
            {
                // std::cout << "Disciplina: " << it->get_nome() << " | Endereço -> " << &it << " | ";
                t_disc.push_back(it);
                continue;
            }
        }
    }

    // std::cout << "\n" << std::endl;

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
                // std::cout << "Turma: " << it->get_nome() << " | Endereço -> " << &it << " | ";
                turmas_index.push_back(it->get_index());
                continue;
            }
        }
    }

    // std::cout << "\n" << std::endl;

    return turmas_index;
}

void Instancia::relacionar_turmas_cursos()
{
    std::unordered_map<std::string, Curso *> cursos_map;

    for (Curso *curso : m_lista_cursos)
    {
        cursos_map[curso->get_id()] = curso;
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