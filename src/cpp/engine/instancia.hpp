#ifndef _INSTANCIA_HPP
#define _INSTANCIA_HPP

#include "../classes/curso.hpp"
#include "../classes/professor.hpp"
#include "../classes/disciplina.hpp"
#include "../helpers/csv.hpp"

class Instancia
{
private:

    CSVReader m_csv = CSVReader();

public:
    Instancia(const std::string ano_instancia);

    std::vector<Turma*> m_lista_turmas;
    std::vector<Professor*> m_lista_professores;
    std::vector<Disciplina*> m_lista_disciplinas;
    std::vector<Curso*> m_lista_cursos;

    const std::vector<Professor*> instanciar_professor(const std::string &ano_instancia);
    const std::vector<Curso*> instanciar_curso(const std::string &ano_instancia);
    const std::vector<Turma*> instanciar_turma(const std::string &ano_instancia);
    const std::vector<Disciplina*> instanciar_disciplina(const std::string &ano_instancia);

    std::vector <Disciplina*> buscar_disciplinas(const std::vector<std::string> nome_disciplinas);
    std::vector <Turma*> buscar_turmas(const std::vector<std::string> nome_turmas);

    void print_instancia();
};

#endif //!_INSTNACIA_HPP