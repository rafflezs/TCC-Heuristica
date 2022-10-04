#ifndef _INSTANCIA_HPP
#define _INSTANCIA_HPP

#include "../classes/curso.hpp"
#include "../classes/professor.hpp"
#include "../classes/disciplina.hpp"

class Instancia
{
private:

public:
    std::list<Turma> m_lista_turmas;
    std::list<Professor> m_lista_professores;
    std::list<Disciplina> m_lista_disciplinas;
    std::list<Curso> m_lista_cursos;
    Instancia(const std::string ano_instancia);
    const std::vector<std::string> parse_coluna(const std::string &entrada, const char &operador);
    const std::array<std::array<int, 16>, 6> preencher_disponibilidade(const std::vector <std::string> dias);
    const std::list<Professor> instanciar_professor(const std::string &ano_instancia);
    const std::list<Curso> instanciar_curso(const std::string &ano_instancia);
    const std::list<Turma> instanciar_turma(const std::string &ano_instancia);
    const std::list<Disciplina> instanciar_disciplina(const std::string &ano_instancia);
};

#endif //!_INSTNACIA_HPP