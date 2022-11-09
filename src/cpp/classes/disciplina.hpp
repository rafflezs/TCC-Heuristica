#ifndef _DISCIPLINA_HPP
#define _DISCIPLINA_HPP

#include "../public/public_includes.hpp"

class Disciplina
{
private:
  std::string m_id{"NULL"};
  std::string m_cod_diario{"NULL"};
  int m_index{NULL};
  std::string m_nome{"NULL"};
  std::string m_periodo{"NULL"};
  std::array<std::array<int, 16>, 6> m_disponibilidade{};
  int m_qtd_alunos{0};
  int m_ch_ead{0};
  int m_ch_presencial{0};
  int m_split{1};
  int m_ch_min{0};
public:

  std::string get_id()
  {
    return this->m_id;
  }

  void set_id(std::string t_id)
  {
    this->m_id = t_id;
  }

  int get_index()
  {
    return this->m_index;
  }

  void set_index(int t_index)
  {
    this->m_index = t_index;
  }

  std::string get_nome()
  {
    return this->m_nome;
  }

  void set_nome(std::string t_nome)
  {
    this->m_nome = t_nome;
  }

  std::string get_periodo()
  {
    return this->m_periodo;
  }

  void set_periodo(std::string t_periodo)
  {
    this->m_periodo = t_periodo;
  }

  std::array<std::array<int, 16>, 6> get_disponibilidade()
  {
    return this->m_disponibilidade;
  }

  void set_disponibilidade(std::array<std::array<int, 16>, 6> t_disponibilidade)
  {
    this->m_disponibilidade = t_disponibilidade;
  }

  int get_qtd_alunos()
  {
    return this->m_qtd_alunos;
  }

  void set_qtd_alunos(int t_qtd_alunos)
  {
    this->m_qtd_alunos = t_qtd_alunos;
  }

  int get_ch_ead()
  {
    return this->m_ch_ead;
  }

  void set_ch_ead(int t_ch_ead)
  {
    this->m_ch_ead = t_ch_ead;
  }

  int get_ch_presencial()
  {
    return this->m_ch_presencial;
  }

  void set_ch_presencial(int t_ch_presencial)
  {
    this->m_ch_presencial = t_ch_presencial;
  }

    int get_ch_min()
  {
    return this->m_ch_min;
  }

  void set_ch_min(int t_ch_min)
  {
    this->m_ch_min = t_ch_min;
  }

    int get_split()
  {
    return this->m_split;
  }

  void set_split(int t_split)
  {
    this->m_split = t_split;
  }

  Disciplina(){};

  Disciplina(
    const std::string t_id,
    const std::string t_cod_diario,
    const int t_index,
    const std::string t_nome,
    std::string t_periodo,
    const int t_qtd_alunos,
    const int t_ch_presencial,
    const int t_ch_ead,
    const int t_ch_min,
    const int t_split,
    const std::array<std::array<int, 16>, 6> t_disponibilidade
  ) : 
    m_id(t_id),
    m_cod_diario(t_cod_diario), 
    m_nome(t_nome), 
    m_index(t_index),
    m_periodo(t_periodo), 
    m_qtd_alunos(t_qtd_alunos),
    m_ch_presencial(t_ch_presencial),
    m_ch_ead(t_ch_ead), 
    m_ch_min(t_ch_min),
    m_split(t_split),
    m_disponibilidade(t_disponibilidade){};

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
    << ", Periodo: " << this->get_periodo() 
    << ", # ALUNOS: " << this->get_qtd_alunos() 
    << ", CH Presencial: " << this->get_ch_presencial() 
    << ", CH EAD: " << this->get_ch_ead() << std::endl
    << ", MIN: " << this->get_ch_min() << std::endl
    << ",SPLIT: " << this->get_split() << std::endl;

    std::cout << "array<disponibilidade>" << std::endl;
    std::cout << std::setw(5) << "H1 " << " "
              << std::setw(5) << "H2 " << " "
              << std::setw(5) << "H3 " << " "
              << std::setw(5) << "H4 " << " "
              << std::setw(5) << "H5 " << " "
              << std::setw(5) << "H6 " << " "
              << std::setw(5) << "H7 " << " "
              << std::setw(5) << "H8 " << " "
              << std::setw(5) << "H9 " << " "
              << std::setw(5) << "H10 " << " "
              << std::setw(5) << "H11 " << " "
              << std::setw(5) << "H12 " << " "
              << std::setw(5) << "H13 " << " "
              << std::setw(5) << "H14 " << " "
              << std::setw(5) << "H15 " << " "
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
};

#endif // !_DISCIPLINA_HPP