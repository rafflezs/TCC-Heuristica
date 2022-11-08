#ifndef _SOLUCAO_HPP
#define _SOLUCAO_HPP

#include "instancia.hpp"
#include <algorithm>
class Solucao{

private:
    Instancia *m_instancia{nullptr};

public:
    Solucao(std::string t_instancia);

    void popular_solucao(std::vector <Disciplina*> disciplinas_ordenadas);
    void exibir_solucao();
    bool tem_choque(Disciplina* t_disciplina);

    Professor* encontrar_prof_relacionado(Disciplina* t_disciplina);
    Turma* encontrar_turma_relacionada(Disciplina* t_disciplina);
    Curso* encontrar_curso_relacionado(Turma* t_turma);

    Instancia get_instancia();
    void debug_vector_disciplina_addr();

};

#endif // !_SOLUCAO_HPP