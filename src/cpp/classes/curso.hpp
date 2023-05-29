#ifndef _CURSO_HPP
#define _CURSO_HPP

#include "../public/public_includes.hpp"

class Curso
{
private:
  std::string m_id{"NULL"};
  int m_index{0};
  std::string m_nome{"NULL"};
  std::string m_titulo_formacao{"NULL"};
  std::vector<int> m_turmas_index{};
  std::vector<std::string> m_turmas{};
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

  std::string get_titulo_formacao()
  {
    return this->m_titulo_formacao;
  }

  void set_titulo_formacao(std::string m_titulo_formacao)
  {
    this->m_titulo_formacao = m_titulo_formacao;
  }

  std::vector<int> get_turmas_index()
  {
    return this->m_turmas_index;
  }

  void set_turmas_index(std::vector<int> t_turmas_index)
  {
    this->m_turmas_index = t_turmas_index;
  }

  std::vector<std::string> get_turmas()
  {
    return this->m_turmas;
  }

  void set_turmas(std::vector<std::string> t_turmas)
  {
    this->m_turmas = t_turmas;
  }

  std::array<std::array<int, 16>, 6> get_disponibilidade()
  {
    return this->m_disponibilidade;
  }

  void set_disponibilidade(std::array<std::array<int, 16>, 6> t_disponibilidade)
  {
    this->m_disponibilidade = t_disponibilidade;
  }

  Curso(){};

  Curso(const std::string &t_id,
        const int t_index,
        const std::string &t_nome,
        std::string t_titulo_formacao,
        const std::vector<int> t_turmas_index,
        const std::vector<std::string> t_turmas,
        const std::array<std::array<int, 16>, 6> t_disponibilidade) :

                                                                      m_id(t_id),
                                                                      m_nome(t_nome),
                                                                      m_index(t_index),
                                                                      m_titulo_formacao(t_titulo_formacao),
                                                                      m_turmas_index(t_turmas_index),
                                                                      m_turmas(t_turmas),
                                                                      m_disponibilidade(t_disponibilidade){};

  Curso(Curso &other)
      : m_id(other.get_id()),
        m_index(other.get_index()),
        m_nome(other.get_nome()),
        m_titulo_formacao(other.get_titulo_formacao()),
        m_turmas_index(other.get_turmas_index()),
        m_turmas(other.get_turmas()),
        m_disponibilidade(other.get_disponibilidade()){};
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
              << ", Tipo: " << this->get_titulo_formacao() << std::endl;

    std::cout << "vector<int Turmas>" << std::endl;
    for (auto t_turma : this->get_turmas_index())
    {
      std::cout << t_turma << std::endl;
    }

    std::cout << "vector<str Turmas>" << std::endl;
    for (auto t_turma : this->get_turmas())
    {
      std::cout << t_turma << std::endl;
    }

    std::cout << "array<disponibilidade>" << std::endl;
    std::array<std::array<int, 16>, 6> f_dispo = this->get_disponibilidade();

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
    for (int i = 0; i < f_dispo.size(); i++)
    {
      for (int j = 0; j < f_dispo[i].size(); j++)
      {
        std::cout << std::setw(5) << f_dispo[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
};

#endif // !_CURSO_HPP