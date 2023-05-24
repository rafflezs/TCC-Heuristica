#ifndef _INSTANCIA_HPP
#define _INSTANCIA_HPP

#include "../classes/turma.hpp"
#include "../classes/professor.hpp"
#include "../classes/disciplina.hpp"
#include "../helpers/csv.hpp"

class Instancia
{
private:
    CSVReader m_csv = CSVReader();
    std::vector<Turma *> m_lista_turmas;
    std::vector<Professor *> m_lista_professores;
    std::vector<Disciplina *> m_lista_disciplinas;
    std::vector<Curso *> m_lista_cursos;
    std::string m_ano_instancia{"NULL"};

public:
    Instancia(std::string ano_instancia);

    const std::vector<Professor *> instanciar_professor(const std::string &ano_instancia);
    const std::vector<Curso *> instanciar_curso(const std::string &ano_instancia);
    const std::vector<Turma *> instanciar_turma(const std::string &ano_instancia);
    const std::vector<Disciplina *> instanciar_disciplina(const std::string &ano_instancia);

    std::vector<Disciplina *> buscar_disciplinas(const std::vector<std::string> &nome_disciplinas);
    std::vector<int> buscar_turmas_index(const std::vector<std::string> &nome_turmas);
    void relacionar_turmas_cursos();

    std::vector<Turma *> get_lista_turmas();
    std::vector<Professor *> get_lista_professores();
    std::vector<Disciplina *> get_lista_disciplinas();
    std::vector<Curso *> get_lista_cursos();
    std::string get_ano_instancia();

    void set_lista_turmas(const std::vector <Turma*> t_input);
    void set_lista_professores(const std::vector <Professor*> t_input);
    void set_lista_disciplinas(const std::vector <Disciplina*> t_input);
    void set_lista_cursos(const std::vector <Curso*> t_input);
    void set_ano_instancia(const std::string &t_input);

    void print_instancia();

    Instancia *shallow_copy();

};

#endif //!_INSTNACIA_HPP