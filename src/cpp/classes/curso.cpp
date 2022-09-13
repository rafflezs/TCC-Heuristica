#include "curso.hpp"

Curso::Curso(const std::string& t_id, const std::string& t_nome, const std::string& t_turmas){
  this->m_id = t_id;
  this->m_nome = t_nome;
  this->m_turmas = t_turmas;
}

std::ostream& operator<<(std::ostream &strm, const Curso &t_curso) {
  return strm << "Curso(" << t_curso.m_id << " " << t_curso.m_nome << " " << t_curso.m_turmas << ")";
}