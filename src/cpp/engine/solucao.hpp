#ifndef _SOLUCAO_HPP
#define _SOLUCAO_HPP

#include "instancia.hpp"
#include <algorithm>
class Solucao
{

private:
    Instancia *m_instancia{nullptr};
    int m_id{0};
    bool m_factivel{false};
public:
    Solucao(std::string t_instancia, int t_id);

    bool popular_solucao(std::vector<Disciplina *> disciplinas_ordenadas);
    bool verificar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma);
    void alocar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split);
    bool tem_choque(Disciplina *t_disciplina, Professor *t_professor, int t_dia_escolhido, int t_horario_inicial, int t_split);
    bool tem_choque(Disciplina *t_disciplina, Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split);
    void exibir_solucao();

    Professor *encontrar_prof_relacionado(Disciplina *t_disciplina);
    Turma *encontrar_turma_relacionada(Disciplina *t_disciplina);
    Curso *encontrar_curso_relacionado(Turma *t_turma);

    Instancia get_instancia();
    void debug_vector_disciplina_addr();

    bool get_factivel();
    void set_factivel(bool const& t_factivel);

    int get_id_solucao();
};

#endif // !_SOLUCAO_HPP