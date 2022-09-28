#ifndef _TURMA_HPP
#define _TURMA_HPP

#include "disciplina.hpp"

class Turma {
  private:
    std::string m_id{"NULL"};
    int m_index{NULL};
    std::string m_nome{"NULL"};
    std::string m_periodo{"NULL"};
    std::list<Disciplina *> m_disciplinas{nullptr};
    std::array<std::array<int, 16>, 6> m_disponibilidade{};

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

  std::string get_periodo()
  {
    return this->m_periodo;
  }

  void set_periodo(std::string t_periodo)
  {
    this->m_periodo = t_periodo;
  }

  std::list<Disciplina*> get_disciplinas()
  {
    return this->m_disciplinas;
  }

  void set_disciplinas(std::list<Disciplina*> t_disciplinas)
  {
    this->m_disciplinas = t_disciplinas;
  }

  std::array<std::array<int, 16>, 6> get_disponibilidade()
  {
    return this->m_disponibilidade;
  }

  void set_disponibilidade(std::array<std::array<int, 16>, 6> t_disponibilidade)
  {
    this->m_disponibilidade = t_disponibilidade;
  }

  Turma(){};

  Turma(const std::string t_id,
        const int t_index,
        const std::string t_nome,
        std::string t_periodo,
        const std::list<Disciplina *> t_disciplinas,
        const std::array<std::array<int, 16>, 6> t_disponibilidade) : m_id(t_id), m_nome(t_nome), m_index(t_index),
                                                                      m_periodo(t_periodo), m_disciplinas(t_disciplinas),
                                                                      m_disponibilidade(t_disponibilidade){};

  void print()
  {
    std::cout << "Index: " << this->get_index() << ", ID: " << this->get_id() << ", Nome: " << this->get_nome()
              << ", Periodo: " << this->get_periodo() << std::endl;

    std::cout << "list<Disciplinas>" << std::endl;
    for (auto t_turma : this->get_disciplinas())
    {
      std::cout << t_turma << std::endl;
    }

    std::cout << "array<disponibilidade>" << std::endl;
    std::array<std::array<int, 16>, 6> f_dispo = this->get_disponibilidade();
    for (int i = 0; i < f_dispo.size(); i++)
    {
      for (int j = 0; j < f_dispo[i].size(); j++)
      {
        std::cout << f_dispo[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

};

#endif // !_TURMA_HPP