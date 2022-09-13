#ifndef _CURSO_HPP
#define _CURSO_HPP

#include "../public/public_includes.hpp"

class Curso{
  private:

  public:
    std::string m_id;
    std::string m_nome;
    std::string m_turmas;

    Curso(const std::string& t_id, const std::string& t_nome, const std::string& t_turma);
    std::string toString();
};

#endif // !_CURSO_HPP