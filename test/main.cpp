#include "../src/cpp/classes/curso.hpp"
#include "../src/cpp/public/public_includes.hpp"

int main() {
  // Curso c = Curso();

  std::ifstream fin;
  fin.open("data\\csv\\2018-1\\Cursos.csv");
  std::vector<std::string> row;
  std::string line, word, temp;

  while (fin >> temp) {
    std::cout << temp << std::endl;
    std::cout << "ç~``´´^ããíí" << std::endl;
  }

  return 0;
}