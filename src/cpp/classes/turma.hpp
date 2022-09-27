#ifndef _TURMA_HPP
#define _TURMA_HPP

#include "disciplina.hpp"

class Turma {
  private:
    std::string _id;
    std::string _periodo;
    std::list <Disciplina*> m_disciplinas;
    
  public:
};

#endif // !_TURMA_HPP