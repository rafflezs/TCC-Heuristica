#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class LeitorCSV
{

private:
    std::string m_linha;
    std::vector<int> m_valor;

public:
    std::string operator[](std::size_t index) const
    {
        return std::string(&m_linha[m_valor[index] + 1], m_valor[index + 1] - (m_valor[index] + 1));
    }
    std::size_t size() const
    {
        return m_valor.size() - 1;
    }
    void ler_proxima_linha(std::istream &str)
    {
        std::getline(str, m_linha);

        m_valor.clear();
        m_valor.emplace_back(-1);
        std::string::size_type pos = 0;
        while ((pos = m_linha.find(';', pos)) != std::string::npos)
        {
            m_valor.emplace_back(pos);
            ++pos;
        }

        // Busca por separadores ao final da última coluna (sem dados sucedentes)
        pos = m_linha.size();
        m_valor.emplace_back(pos);
    }
};

std::istream &operator>>(std::istream &str, LeitorCSV &arquivo)
{
    arquivo.ler_proxima_linha(str);
    return str;
}