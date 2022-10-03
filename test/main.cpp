#include "../src/cpp/classes/curso.hpp"
#include "../src/cpp/classes/professor.hpp"

const std::vector<std::string> col_parser(const std::string &entrada, const char &operador);

int main()
{
    std::ifstream file("D:\\Programacao\\TCC\\data\\csv\\2018-1\\Cursos.csv");
    std::string line;
    std::vector <std::string> colunas;
    getline(file, line, '\n');
    while (file.good())
    {
        getline(file, line, '\n');
        std:: cout << line << std::endl;
        colunas = col_parser(line, ';');
        std:: cout << colunas[0] << std::endl;
        
    }
}

const std::vector<std::string> col_parser(const std::string &entrada, const char &operador)
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