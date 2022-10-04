#include "instancia.hpp"

Instancia::Instancia(const std::string ano_instancia)
{
    std::cout << "Gerando instancia do periodo: " + ano_instancia << std::endl;
    // this->m_lista_disciplinas = instanciar_disciplina(ano_instancia);
    // this->m_lista_turmas = instanciar_turma(ano_instancia);
    this->m_lista_professores = instanciar_professor(ano_instancia);
    // this->m_lista_cursos = instanciar_curso(ano_instancia);
}

const std::vector<std::string> Instancia::parse_coluna(const std::string &entrada, const char &operador)
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
            if ((temp == operador || temp == '\0') && buffer != "")
            {
                t_string.push_back(buffer);
                buffer = "";
            } else 
            {
                t_string.push_back(buffer);
            }
        }
    }
    if (buffer != "")
    {
        t_string.push_back(buffer);
    }
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
            std::cout << "inicio[0] == 0" << std::endl;
            inicio[0] = "17";
        }
        else
        {
            std::cout << "else {}" << std::endl;
            for (auto n : inicio)
            {
                if (n.length() > 2)
                {
                    std::vector<std::string> temp = parse_coluna(n, '-');
                    for (int i = std::stoi(temp[0])-1; i < std::stoi(temp[1])-1; i++)
                    {
                        std::string tempWord = std::to_string(i);
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
            std::cout << dia << " " << std::stoi(n) - 1 << std::endl;
            std::cout << t_disponibilidade[dia][std::stoi(n) - 1] << std::endl;
        }
    }
    return t_disponibilidade;
}

const std::list<Professor> Instancia::instanciar_professor(const std::string &ano_instancia)
{
    std::ifstream file;
    file.open("D:\\Programacao\\TCC\\data\\csv\\2018-1\\Professores.csv");
    std::string line;
    std::getline(file, line, '\n');
    std::list<Professor> t_professores;
    int index = 1;
    while (!file.eof())
    {
        std::vector<std::string> colunas;
        std::getline(file, line, '\n');
        colunas = parse_coluna(line, ';');
        std::vector<std::string> colunas_horarios;
        colunas_horarios.push_back(colunas[3]);
        colunas_horarios.push_back(colunas[4]);
        colunas_horarios.push_back(colunas[5]);
        colunas_horarios.push_back(colunas[6]);
        colunas_horarios.push_back(colunas[7]);
        colunas_horarios.push_back(colunas[8]);
        std::array<std::array<int,16>,6> t_disponibilidade = preencher_disponibilidade(colunas_horarios);
        Professor p = Professor(
            colunas[0],
            index,
            colunas[1],
            {},
            {}
        );
        std::cout << p.get_nome() << std::endl;
        t_professores.push_back(p);
        index++;
    }
    file.close();
        std::cout << "Fechando" << std::endl;

    return t_professores;
}

const std::list<Curso> Instancia::instanciar_curso(const std::string &ano_instancia)
{
    std::ifstream file("D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Cursos.csv");
    std::string line;
    std::vector<std::string> colunas;
    std::getline(file, line, '\n');
    std::list<Curso> t_cursos;
    int index = 1;
    while (file.good())
    {
        std::array<std::array<int,6>,16> t_disponibilidade {};
        std::getline(file, line, '\n');
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
    file.close();
    return t_cursos;
}

const std::list<Turma> Instancia::instanciar_turma(const std::string &ano_instancia)
{
    std::ifstream file("D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Turmas.csv");
    std::string line;
    std::vector<std::string> colunas;
    std::getline(file, line, '\n');
    std::list<Turma> t_turmas;
    int index = 1;
    while (file.good())
    {
        std::array<std::array<int,6>,16> t_disponibilidade {};
        std::getline(file, line, '\n');
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
    file.close();
    return t_turmas;
}

const std::list<Disciplina> Instancia::instanciar_disciplina(const std::string &ano_instancia)
{
    std::ifstream file("D:\\Programacao\\TCC\\data\\csv\\" + ano_instancia + "\\Disciplinas.csv");
    std::string line;
    std::vector<std::string> colunas;
    std::getline(file, line, '\n');
    std::list<Disciplina> t_disciplinas;
    int index = 1;
    while (file.good())
    {
        std::array<std::array<int,6>,16> t_disponibilidade {};
        std::getline(file, line, '\n');
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
