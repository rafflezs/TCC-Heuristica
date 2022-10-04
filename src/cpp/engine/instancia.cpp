#include "instancia.hpp"

Instancia::Instancia(const std::string ano_instancia)
{
    std::cout << "Gerando instancia do periodo: " + ano_instancia << std::endl;
    this->m_lista_disciplinas = instanciar_disciplina(ano_instancia);
    this->m_lista_turmas = instanciar_turma(ano_instancia);
    this->m_lista_professores = instanciar_professor(ano_instancia);
    this->m_lista_cursos = instanciar_curso(ano_instancia);
}

const std::list<Professor> Instancia::instanciar_professor(const std::string &ano_instancia)
{
    std::list<Professor> t_professores;
    std::ifstream file {"/home/rafflezs/Programacao/TCC/data/csv/"+ano_instancia+"/Professores.csv"};
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++) {
        if (index != 0) {
            t_professores.push_back(
                Professor(
                    (*row)[0],
                    index,
                    (*row)[1],
                    {},
                    m_csv.preencher_disponibilidade({(*row)[3], (*row)[4] ,(*row)[5], (*row)[6], (*row)[7], (*row)[8]})
                )
            );
        }
        index++;
    }


    return t_professores;
}

const std::list<Curso> Instancia::instanciar_curso(const std::string &ano_instancia)
{
    std::list<Curso> t_cursos;
    std::ifstream file {"/home/rafflezs/Programacao/TCC/data/csv/"+ano_instancia+"/Cursos.csv"};
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++) {
        if (index != 0) {
            t_cursos.push_back(
                Curso(
                    (*row)[0],
                    index,
                    (*row)[1],
                    (*row)[2],
                    {},
                    m_csv.preencher_disponibilidade({(*row)[4], (*row)[5] ,(*row)[6], (*row)[7], (*row)[8], (*row)[9]})
                )
            );
        }
        index++;
    }

    return t_cursos;
}

const std::list<Turma> Instancia::instanciar_turma(const std::string &ano_instancia)
{
    std::list<Turma> t_turmas;
    std::ifstream file {"/home/rafflezs/Programacao/TCC/data/csv/"+ano_instancia+"/Turmas.csv"};
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++) {
        if (index != 0) {
            t_turmas.push_back(
                Turma(
                    (*row)[0],
                    index,
                    (*row)[2],
                    (*row)[3],
                    {},
                    m_csv.preencher_disponibilidade({(*row)[5], (*row)[6] ,(*row)[7], (*row)[8], (*row)[9], (*row)[10]})
                )
            );
        }
        index++;
    }

    return t_turmas;
}

const std::list<Disciplina> Instancia::instanciar_disciplina(const std::string &ano_instancia)
{
    std::list<Disciplina> t_disciplinas;
    std::ifstream file {"/home/rafflezs/Programacao/TCC/data/csv/"+ano_instancia+"/Disciplinas.csv"};
    std::vector<std::vector<std::string>> csv = m_csv.ler_colunas(&file, ';');

    int index = 0;
    for (std::vector<std::vector<std::string>>::iterator row = csv.begin(); row != csv.end(); row++) {
        if (index != 0) {
            t_disciplinas.push_back(
                Disciplina(
                    (*row)[0],
                    (*row)[1],
                    index,
                    (*row)[2],
                    (*row)[5],
                    std::stoi((*row)[6]),
                    std::stoi((*row)[7]),
                    std::stoi((*row)[8]),
                    m_csv.preencher_disponibilidade({(*row)[9], (*row)[10] ,(*row)[11], (*row)[12], (*row)[13], (*row)[14]})
                )
            );
        }
        index++;
    }

    return t_disciplinas;
}
