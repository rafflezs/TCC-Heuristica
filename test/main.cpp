#include "../src/cpp/classes/curso.hpp"
#include "../src/cpp/public/public_includes.hpp"

int main() {

  std::array<std::array<int,16>,6> a {};


  Turma t1 = Turma("T1", 1, "Turma 1", "Tarde", {nullptr}, {});
  Turma t2 = Turma("T2", 2, "Turma 2", "Tarde", {nullptr}, {});
  Curso c = Curso("st1", 0, "st2", "st3", {&t1, &t2}, a);
  
  c.print();

  return 0;
}