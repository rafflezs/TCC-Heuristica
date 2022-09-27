#include "../src/cpp/classes/curso.hpp"
#include "../src/cpp/public/public_includes.hpp"

int main() {

  std::array<std::array<int,16>,6> a {};
  Curso c = Curso("st1", 0, "st2", "st3", {nullptr}, a);

  std::cout << c.toString() << std::endl;

  return 0;
}