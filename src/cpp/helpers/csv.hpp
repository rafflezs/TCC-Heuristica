#ifndef _CSV_HPP
#define _CSV_HPP

#include "../public/public_includes.hpp"

class CSVReader
{
private:
public:
    const std::vector<std::string> parse_coluna(const std::string &entrada, const char &operador);
    const std::array<std::array<int, 16>, 6> preencher_disponibilidade(const std::vector<std::string> dias);
    std::vector<std::vector<std::string>> ler_colunas(std::ifstream *file, const char &separador);
};
#endif