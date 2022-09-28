#include "../src/cpp/classes/curso.hpp"
#include "../src/cpp/classes/professor.hpp"
#include "../src/cpp/public/csvReader.hpp"

int main()
{
    std::ifstream file("data/csv/2018-1/Cursos.csv");

    LeitorCSV row;
    while(file >> row)
    {
        std::cout << row[0] << std::endl;
    }
}