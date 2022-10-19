#include "instancia.hpp"

Instancia::Instancia(const std::string ano_instancia)
{
    std::cout << "Gerando instancia do periodo: " + ano_instancia << std::endl;

    this->m_lista_disciplinas = instanciar_disciplina(ano_instancia);
    std::cout << "Gerou lista de disciplinas" << std::endl;
    
    // this->m_lista_turmas = instanciar_turma(ano_instancia);
    // std::cout << "Gerou lista de turmas" << std::endl;

    // this->m_lista_professores = instanciar_professor(ano_instancia);
    // std::cout << "Gerou lista de professores" << std::endl;

    // this->m_lista_cursos = instanciar_curso(ano_instancia);
    // std::cout << "Gerou lista de cursos" << std::endl;

}

const std::vector<Professor> Instancia::instanciar_professor(const std::string &ano_instancia)
{
    std::vector<Professor> t_professores;
    std::ifstream file{"/home/rafflezs/TCC/data/csv/" + ano_instancia + "/Professores.csv"};    // WSL
    // std::ifstream file{"/home/rafflezs/Programacao/TCC/data/csv/" + ano_instancia + "/Professores.csv"}; // Windows
    // std::ifstream file{"D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Professores.csv"}; // Unix
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++)
    {
        if (index > 0)
        {
            t_professores.push_back(
                Professor(
                    (*row)[0],
                    index,
                    (*row)[1],
                    {},
                    m_csv.preencher_disponibilidade({(*row)[3], (*row)[4], (*row)[5], (*row)[6], (*row)[7], (*row)[8]})));
        }
        index++;
    }

    return t_professores;
}

const std::vector<Curso> Instancia::instanciar_curso(const std::string &ano_instancia)
{
    std::vector<Curso> t_cursos;
    std::ifstream file{"/home/rafflezs/TCC/data/csv/" + ano_instancia + "/Cursos.csv"};    // WSL
    // std::ifstream file{"/home/rafflezs/Programacao/TCC/data/csv/" + ano_instancia + "/Cursos.csv"}; // Windows
    // std::ifstream file{"D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Cursos.csv"}; // Unix
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++)
    {
        if (index > 0)
        {
            t_cursos.push_back(
                Curso(
                    (*row)[0],
                    index,
                    (*row)[1],
                    (*row)[2],
                    {},
                    m_csv.preencher_disponibilidade({(*row)[4], (*row)[5], (*row)[6], (*row)[7], (*row)[8], (*row)[9]})));
        }
        index++;
    }

    return t_cursos;
}

const std::vector<Turma> Instancia::instanciar_turma(const std::string &ano_instancia)
{
    std::vector<Turma> t_turmas;
    std::ifstream file{"/home/rafflezs/TCC/data/csv/" + ano_instancia + "/Turmas.csv"};    // WSL
    // std::ifstream file{"/home/rafflezs/Programacao/TCC/data/csv/" + ano_instancia + "/Turmas.csv"}; // Windows
    // std::ifstream file{"D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Turmas.csv"}; // Unix
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++)
    {
        if (index > 0)
        {
            t_turmas.push_back(
                Turma(
                    (*row)[0],
                    index,
                    (*row)[2],
                    (*row)[3],
                    {},
                    m_csv.preencher_disponibilidade({(*row)[5], (*row)[6], (*row)[7], (*row)[8], (*row)[9], (*row)[10]})));
        }
        index++;
    }

    return t_turmas;
}

const std::vector<Disciplina> Instancia::instanciar_disciplina(const std::string &ano_instancia)
{
    std::vector<Disciplina> t_disciplinas;
    std::ifstream file{"/home/rafflezs/TCC/data/csv/" + ano_instancia + "/Disciplinas.csv"};    // WSL
    // std::ifstream file{"/home/rafflezs/Programacao/TCC/data/csv/" + ano_instancia + "/Disciplinas.csv"}; // Windows
    // std::ifstream file{"D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Disciplinas.csv"}; // Unix
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++)
    {
        if (index > 0)
        {
            std::cout << "row[0]" << (*row)[0] << std::endl;
            Disciplina t_disciplina = Disciplina(
                (*row)[0],
                (*row)[1],
                index,
                (*row)[2],
                (*row)[5],
                std::stoi((*row)[6]),
                std::stoi((*row)[7]),
                std::stoi((*row)[8]),
                m_csv.preencher_disponibilidade({(*row)[9], (*row)[10], (*row)[11], (*row)[12], (*row)[13], (*row)[14]}));

            t_disciplina.print();
            t_disciplinas.push_back(t_disciplina);
        }
        index++;
    }

    return t_disciplinas;
}
