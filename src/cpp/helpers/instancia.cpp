#include "instancia.hpp"

Instancia::Instancia(const std::string ano_instancia)
{
    std::cout << "Gerando instancia do periodo: " + ano_instancia << std::endl;
    this->m_lista_cursos = instanciar_curso(ano_instancia);
    this->m_lista_turmas = instanciar_turma(ano_instancia);
    this->m_lista_professores = instanciar_professor(ano_instancia);
    this->m_lista_disciplinas = instanciar_disciplina(ano_instancia);
}

const std::vector<std::string> Instancia::parse_coluna(const std::string entrada, const char operador)
{
    std::string buffer{""};
    std::vector<std::string> t_string;

    for (auto temp : entrada)
    {
        if (temp != operador)
        {
            buffer += temp;
        }
        else
        {
            if (temp == operador && buffer != "")
            {
                t_string.push_back(buffer);
                buffer = "";
            }
        }
    }
    if (buffer != "")
        t_string.push_back(buffer);
    return t_string;
}

const std::array<std::array<int, 16>, 6> Instancia::preencher_disponibilidade(const std::vector<std::string> dias)
{

    std::array<std::array<int, 16>, 6> t_disponibilidade;

    std::vector<std::string> inicio;
    std::vector<std::string> fim;

    for (int dia = 0; dia < dias.size(); dia++)
    {
        inicio = parse_coluna(dias[dia], ',');
        if (inicio[0] == "0")
        {
            inicio[0] = "17";
        }
        else
        {
            for (auto n : inicio)
            {
                if (n.length() > 2)
                {
                    std::vector<std::string> temp;
                    std::string tempWord;
                    temp = parse_coluna(n, '-');
                    int start, end;
                    start = stoi(temp[0]);
                    end = stoi(temp[1]);
                    for (int i = start; i <= end; i++)
                    {
                        tempWord = std::to_string(i);
                        fim.push_back(tempWord);
                    }
                }
                else
                {
                    fim.push_back(n);
                }
            }
            for (int i = 0; i < 16; i++)
            {
                t_disponibilidade[dia][i] = 0;
            }
        }
        for (auto n : fim)
        {
            t_disponibilidade[dia][std::stoi(n) - 1] = -1;
        }
    }

    return t_disponibilidade;
}

const std::list<Professor> Instancia::instanciar_professor(const std::string &ano_instancia)
{
    std::ifstream file("D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Professores.csv");
    std::string line;
    std::vector<std::string> colunas;
    getline(file, line, '\n');
    std::list<Professor> t_professores;
    int index = 1;
    while (file.good())
    {
        getline(file, line, '\n');
        colunas = parse_coluna(line, ';');
        t_professores.push_back(Professor(colunas[0],
                                            index,
                                            colunas[1],
                                            {},
                                            preencher_disponibilidade(
                                                {colunas[3], colunas[4], colunas[5], colunas[6], colunas[7], colunas[8]}
                                            )
                                        )
                                    );
    }

    return t_professores;
}

const std::list<Curso> Instancia::instanciar_curso(const std::string &ano_instancia)
{
    std::ifstream file("D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Cursos.csv");
    std::string line;
    std::vector<std::string> colunas;
    getline(file, line, '\n');
    std::list<Curso> t_cursos;
    int index = 1;
    while (file.good())
    {
        getline(file, line, '\n');
        colunas = parse_coluna(line, ';');
        t_cursos.push_back(Curso(colunas[0],
                                index,
                                colunas[1],
                                colunas[2],
                                {},
                                preencher_disponibilidade(
                                    {colunas[3], colunas[4], colunas[5], colunas[6], colunas[7], colunas[8]}
                                )
                            )
                        );
    }

    return t_cursos;
}

const std::list<Turma> Instancia::instanciar_turma(const std::string &ano_instancia)
{
    std::ifstream file("D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Turmas.csv");
    std::string line;
    std::vector<std::string> colunas;
    getline(file, line, '\n');
    std::list<Turma> t_turmas;
    int index = 1;
    while (file.good())
    {
        getline(file, line, '\n');
        colunas = parse_coluna(line, ';');
        t_turmas.push_back(Turma(colunas[0],
                                index,
                                colunas[2],
                                colunas[3],
                                {},
                                preencher_disponibilidade(
                                    {colunas[5], colunas[6], colunas[7], colunas[8], colunas[9], colunas[10]}
                                )
                            )
                        );
    }

    return t_turmas;
}

const std::list<Disciplina> Instancia::instanciar_disciplina(const std::string &ano_instancia)
{
    std::ifstream file("D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Disciplinas.csv");
    std::string line;
    std::vector<std::string> colunas;
    getline(file, line, '\n');
    std::list<Disciplina> t_disciplinas;
    int index = 1;
    while (file.good())
    {
        getline(file, line, '\n');
        colunas = parse_coluna(line, ';');
        t_disciplinas.push_back(Disciplina(colunas[0], 
                                            colunas[1], 
                                            index, 
                                            colunas[2],
                                            colunas[5],
                                            std::stoi(colunas[6]),
                                            std::stoi(colunas[7]),
                                            std::stoi(colunas[8]),
                                            preencher_disponibilidade(
                                                {colunas[9],colunas[10], colunas[11], colunas[12], colunas[13], colunas[14]}
                                            )
                                        )
                                    );
    }

    t_disciplinas;
}
