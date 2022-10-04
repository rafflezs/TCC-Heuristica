#include "csv.hpp"

const std::vector<std::string> CSVReader::parse_coluna(const std::string &entrada, const char &operador)
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
            if ((temp == operador || temp == ' ') && buffer != "")
            {
                t_string.push_back(buffer);
                buffer = "";
            }
            else
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

const std::array<std::array<int, 16>, 6> CSVReader::preencher_disponibilidade(const std::vector<std::string> dias)
{
    std::array<std::array<int, 16>, 6> t_disponibilidade{};

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
                    std::vector<std::string> temp = parse_coluna(n, '-');
                    for (int i = std::stoi(temp[0]); i < std::stoi(temp[1]); i++)
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
            t_disponibilidade[dia][std::stoi(n)] = -1;
        }
    }

    return t_disponibilidade;
}

std::vector<std::vector<std::string>> CSVReader::ler_colunas(std::ifstream *file, const char &separador)
{
    std::vector<std::vector<std::string>> csvRows;

    for (std::string line; std::getline(*file, line);)
    {
        std::istringstream ss(std::move(line));
        std::vector<std::string> row;
        if (!csvRows.empty())
        {
            // We expect each row to be as big as the first row
            row.reserve(csvRows.front().size());
        }
        // std::getline can split on other characters, here we use ','
        for (std::string value; std::getline(ss, value, separador);)
        {
            row.push_back(std::move(value));
        }
        csvRows.push_back(std::move(row));
    }

    return csvRows;
}