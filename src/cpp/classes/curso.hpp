#ifndef _CURSO_HPP
#define _CURSO_HPP

#include "turma.hpp"

class Curso
{
private:
  std::string m_id;
  int m_index;
  std::string m_nome;
  std::string m_titulo_formacao;
  std::list<Turma *> m_turmas;
  std::array <std::array<int,16>,6> m_disponibilidade;

public:
  std::string get_id()
  {
    return this->m_id;
  }

  void set_id(std::string m_id)
  {
    this->m_id = m_id;
  }

  int get_index()
  {
    return this->m_index;
  }

  void set_index(int m_index)
  {
    this->m_index = m_index;
  }

  std::string get_nome()
  {
    return this->m_nome;
  }

  void set_nome(std::string m_nome)
  {
    this->m_nome = m_nome;
  }

  std::string get_titulo_formacao()
  {
    return this->m_titulo_formacao;
  }

  void set_titulo_formacao(std::string m_titulo_formacao)
  {
    this->m_titulo_formacao = m_titulo_formacao;
  }

  std::list<Turma *> get_turmas()
  {
    return this->m_turmas;
  }

  void set_turmas(std::list<Turma *> m_turmas)
  {
    this->m_turmas = m_turmas;
  }

  std::array <std::array<int,16>,6> get_disponibilidade(){
    return this->m_disponibilidade;
  }

  void set_disponibilidade(std::array <std::array<int,16>,6> t_disponibilidade){
    this->m_disponibilidade = t_disponibilidade;
  }

  Curso(const std::string t_id, 
        const int m_index,
        const std::string t_nome, 
        std::string m_titulo_formacao,
        const std::list<Turma*> t_turmas, 
        const std::array <std::array<int,16>,6> m_disponibilidade) : 
  m_id(t_id), m_nome(t_nome), m_turmas(t_turmas) {};
  std::string toString();
};

#endif // !_CURSO_HPP