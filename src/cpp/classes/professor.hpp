#ifndef _PROFESSOR_HPP
#define _PROFESSOR_HPP

#include <string>

#include "disciplina.hpp"

class Professor
{
private:
  std::string m_id{"NULL"};
  int m_index{NULL};
  std::string m_nome{"NULL"};
  std::vector<Disciplina *> m_disciplinas{nullptr};
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

  void set_disponibilidade(std::array<std::array<int, 16>, 6> t_disponibilidade)
  {
    this->m_disponibilidade = t_disponibilidade;
  }

  void set_disponibilidade(int t_dia, int t_horario, int t_valor)
  {
    this->m_disponibilidade[t_dia][t_horario] = t_valor;
  }

  std::array<std::array<int, 16>, 6> get_disponibilidade()
  {
    return this->m_disponibilidade;
  }

  std::vector<Disciplina *> get_disciplinas()
  {
    return this->m_disciplinas;
  }

  void set_disciplinas(std::vector<Disciplina *> t_disciplinas)
  {
    this->m_disciplinas = t_disciplinas;
  }

  Professor(){};

  Professor(
      const std::string t_id,
      const int t_index,
      const std::string t_nome,
      const std::vector<Disciplina *> t_disciplinas,
      const std::array<std::array<int, 16>, 6> t_disponibilidade) : m_id(t_id),
                                                                    m_nome(t_nome),
                                                                    m_index(t_index),
                                                                    m_disciplinas(t_disciplinas),
                                                                    m_disponibilidade(t_disponibilidade){};

  Professor(const Professor &other)
      : m_id(other.m_id),
        m_index(other.m_index),
        m_nome(other.m_nome),
        m_disponibilidade(other.m_disponibilidade)
  {
    // Perform deep copy for the vector of Disciplina pointers
    for (Disciplina *disciplina : other.m_disciplinas)
    {
      m_disciplinas.push_back(new Disciplina(*disciplina));
    }
  }

  void print()
  {
    std::cout << "Index: " << this->get_index()
              << ", ID: " << this->get_id()
              << ", Nome: " << this->get_nome() << std::endl;

    std::cout << "vector<Disciplinas>" << std::endl;
    for (auto t_turma : this->get_disciplinas())
    {
      std::cout << t_turma << std::endl;
    }

    std::cout << "array<disponibilidade>" << std::endl;
    std::cout << std::setw(5) << "H1 "
              << " "
              << std::setw(5) << "H2 "
              << " "
              << std::setw(5) << "H3 "
              << " "
              << std::setw(5) << "H4 "
              << " "
              << std::setw(5) << "H5 "
              << " "
              << std::setw(5) << "H6 "
              << " "
              << std::setw(5) << "H7 "
              << " "
              << std::setw(5) << "H8 "
              << " "
              << std::setw(5) << "H9 "
              << " "
              << std::setw(5) << "H10 "
              << " "
              << std::setw(5) << "H11 "
              << " "
              << std::setw(5) << "H12 "
              << " "
              << std::setw(5) << "H13 "
              << " "
              << std::setw(5) << "H14 "
              << " "
              << std::setw(5) << "H15 "
              << " "
              << std::setw(5) << "H16 " << std::endl;
    std::array<std::array<int, 16>, 6> f_dispo = this->get_disponibilidade();
    for (int i = 0; i < f_dispo.size(); i++)
    {
      for (int j = 0; j < f_dispo[i].size(); j++)
      {
        std::cout << std::setw(5) << f_dispo[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  void print_solucao()
  {
    std::cout << "Nome: " << this->get_nome() << std::endl;

    std::cout << "Horario do Professor" << std::endl;
    std::cout << std::setw(5) << "   "
              << " "
              << std::setw(5) << "H1 "
              << " "
              << std::setw(5) << "H2 "
              << " "
              << std::setw(5) << "H3 "
              << " "
              << std::setw(5) << "H4 "
              << " "
              << std::setw(5) << "H5 "
              << " "
              << std::setw(5) << "H6 "
              << " "
              << std::setw(5) << "H7 "
              << " "
              << std::setw(5) << "H8 "
              << " "
              << std::setw(5) << "H9 "
              << " "
              << std::setw(5) << "H10 "
              << " "
              << std::setw(5) << "H11 "
              << " "
              << std::setw(5) << "H12 "
              << " "
              << std::setw(5) << "H13 "
              << " "
              << std::setw(5) << "H14 "
              << " "
              << std::setw(5) << "H15 "
              << " "
              << std::setw(5) << "H16 " << std::endl;
    std::array<std::array<int, 16>, 6> f_dispo = this->get_disponibilidade();
    for (int i = 0; i < f_dispo.size(); i++)
    {
      switch (i)
      {
      case 0:
        std::cout << std::setw(5) << "SEG "
                  << " ";
        break;
      case 1:
        std::cout << std::setw(5) << "TER "
                  << " ";
        break;
      case 2:
        std::cout << std::setw(5) << "QUA "
                  << " ";
        break;
      case 3:
        std::cout << std::setw(5) << "QUI "
                  << " ";
        break;
      case 4:
        std::cout << std::setw(5) << "SEX "
                  << " ";
        break;
      case 5:
        std::cout << std::setw(5) << "SAB "
                  << " ";
        break;
      default:
        break;
      }
      for (int j = 0; j < f_dispo[i].size(); j++)
      {
        std::cout << std::setw(5) << f_dispo[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
};

#endif