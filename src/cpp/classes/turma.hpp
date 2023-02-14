#ifndef _TURMA_HPP
#define _TURMA_HPP

#include "disciplina.hpp"

class Turma
{
private:
  std::string m_id{"NULL"};
  int m_index{NULL};
  std::string m_nome{"NULL"};
  std::string m_periodo{"NULL"};
  int m_primeiro_horario_turno{-1};
  int m_ultimo_horario_turno{-1};
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

  std::string get_periodo()
  {
    return this->m_periodo;
  }

  void set_periodo(std::string t_periodo)
  {
    this->m_periodo = t_periodo;
  }

  std::vector<Disciplina *> get_disciplinas()
  {
    return this->m_disciplinas;
  }

  void set_disciplinas(std::vector<Disciplina *> t_disciplinas)
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

  int get_primeiro_horario_turno()
  {
    return this->m_primeiro_horario_turno;
  }

  void set_primeiro_horario_turno(int t_primeiro_horario_turno)
  {
    this->m_primeiro_horario_turno = t_primeiro_horario_turno;
  }

  int get_ultimo_horario_turno()
  {
    return this->m_ultimo_horario_turno;
  }

  void set_ultimo_horario_turno(int t_ultimo_horario_turno)
  {
    this->m_ultimo_horario_turno = t_ultimo_horario_turno;
  }

  Turma(){};

  Turma(
      const std::string t_id,
      const int t_index,
      const std::string t_nome,
      std::string t_periodo,
      const std::vector<Disciplina *> t_disciplinas,
      const std::array<std::array<int, 16>, 6> t_disponibilidade,
      const int t_primeiro_horario_turno,
      const int t_ultimo_horario_turno) : m_id(t_id),
                                          m_nome(t_nome),
                                          m_index(t_index),
                                          m_periodo(t_periodo),
                                          m_disciplinas(t_disciplinas),
                                          m_disponibilidade(t_disponibilidade),
                                          m_primeiro_horario_turno(t_primeiro_horario_turno),
                                          m_ultimo_horario_turno(t_ultimo_horario_turno){};

  /*
  ** Função para print da Classe
  ** @param NULL
  ** @return void
  */
  void print()
  {
    std::cout << "Index: " << this->get_index()
              << ", ID: " << this->get_id()
              << ", Nome: " << this->get_nome()
              << ", Periodo: " << this->get_periodo() << std::endl;

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

    std::cout << "Horario da Turma: " << std::endl;
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

#endif // !_TURMA_HPP