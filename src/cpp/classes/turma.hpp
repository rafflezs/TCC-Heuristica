#ifndef _TURMA_HPP
#define _TURMA_HPP

#include "disciplina.hpp"
#include "curso.hpp"

class Turma
{
private:
  std::string m_id;
  int m_index;
  std::string m_nome;
  std::string m_periodo;
  std::string m_curso_str;
  int m_primeiro_horario_turno;
  int m_ultimo_horario_turno;
  std::vector<Disciplina *> m_disciplinas;
  std::array<std::array<int, 16>, 6> m_disponibilidade;
  Curso *m_curso;

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

  void set_time_slot(int t_dia, int t_horario, int t_valor)
  {
    this->m_disponibilidade[t_dia][t_horario] = t_valor;
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

  std::string get_curso_str()
  {
    return this->m_curso_str;
  }

  void set_curso_str(std::string t_curso_str)
  {
    this->m_curso_str = t_curso_str;
  }

  Curso *get_curso()
  {
    return this->m_curso;
  }

  void set_curso(Curso *t_curso)
  {
    this->m_curso = t_curso;
  }

  Turma(){};

  // Turma nao esta inicializando Curso corretamente
  Turma(
      const std::string t_id,
      const int t_index,
      const std::string t_nome,
      std::string t_periodo,
      std::string t_curso_str,
      const std::vector<Disciplina *> t_disciplinas,
      const std::array<std::array<int, 16>, 6> t_disponibilidade,
      const int t_primeiro_horario_turno,
      const int t_ultimo_horario_turno,
      Curso *t_curso) : m_id(t_id),
                        m_nome(t_nome),
                        m_index(t_index),
                        m_periodo(t_periodo),
                        m_curso_str(t_curso_str),
                        m_disciplinas(t_disciplinas),
                        m_disponibilidade(t_disponibilidade),
                        m_primeiro_horario_turno(t_primeiro_horario_turno),
                        m_ultimo_horario_turno(t_ultimo_horario_turno),
                        m_curso(t_curso){};

  Turma(Turma &other, Curso *curso, std::vector<Disciplina *> shallow_disc)

  {
    m_id = other.get_id();
    m_index = other.get_index();
    m_nome = other.get_nome();
    m_periodo = other.get_periodo();
    m_curso_str = other.get_curso_str();
    m_primeiro_horario_turno = other.get_primeiro_horario_turno();
    m_ultimo_horario_turno = other.get_ultimo_horario_turno();
    m_curso = other.get_curso();
    m_disponibilidade = other.get_disponibilidade();
    m_disciplinas = shallow_disc;
  }

  int get_qtd_sextos()
  {
    int qtd_sextos_turma = 0;
    for (int dia = 0; dia < 6; dia++)
    {
      if (m_disponibilidade[dia][5] > 0)
        qtd_sextos_turma++;
      if (m_disponibilidade[dia][11] > 0)
        qtd_sextos_turma++;
    }
    return qtd_sextos_turma;
  }

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
              << ", Curso: " << this->get_curso()
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
    std::cout << "Id: " << this->get_id() << "| Nome: " << this->get_nome() << " | pointer " << this << std::endl;

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

  void print_output()
  {
    std::cout << "\\begin{table}[htbp]\n";
    std::cout << "\\centering\n";
    std::cout << "\\caption{Horário da Turma}\n";
    std::cout << "\\begin{tabular}{|l|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|}\\hline\n";
    std::cout << " & \\multicolumn{15}{|c|}{Horário} \\\\ \\cline{2-16}\n";
    std::cout << "Dia & H1 & H2 & H3 & H4 & H5 & H6 & H7 & H8 & H9 & H10 & H11 & H12 & H13 & H14 & H15 & H16 \\\\ \\hline\n";
    std::array<std::array<int, 16>, 6> f_dispo = this->get_disponibilidade();
    for (int i = 0; i < f_dispo.size(); i++)
    {
      switch (i)
      {
      case 0:
        std::cout << "\\multirow{2}{*}{SEG} & ";
        break;
      case 1:
        std::cout << "\\multirow{2}{*}{TER} & ";
        break;
      case 2:
        std::cout << "\\multirow{2}{*}{QUA} & ";
        break;
      case 3:
        std::cout << "\\multirow{2}{*}{QUI} & ";
        break;
      case 4:
        std::cout << "\\multirow{2}{*}{SEX} & ";
        break;
      case 5:
        std::cout << "\\multirow{2}{*}{SAB} & ";
        break;
      default:
        break;
      }
      for (int j = 0; j < f_dispo[i].size(); j++)
      {
        if (j == f_dispo[i].size() - 1)
        {
          std::cout << f_dispo[i][j] << " \\\\ \\cline{2-16}\n";
        }
        else
        {
          std::cout << f_dispo[i][j] << " & ";
        }
      }
    }
    std::cout << "\\end{tabular}\n";
    std::cout << "\\end{table}\n";
  }

  void destruir_turma()
  {
    for (int i = 0; i < m_disciplinas.size(); i++)
    {
      delete m_disciplinas[i];
    }
    delete m_curso;
  }
};

#endif // !_TURMA_HPP