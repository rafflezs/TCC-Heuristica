#ifndef _SOLUCAO_HPP
#define _SOLUCAO_HPP

#include "instancia.hpp"
#include <algorithm>
#include <random>
#include <set>
class Solucao
{

private:
    Instancia *m_instancia{nullptr};
    int m_id{0};
    bool m_factivel{false};
    float m_valor_avaliado{0.0};
    float m_valor_janelas{0.0};
    float m_valor_sextos_horarios{0.0};
    std::string m_instancia_nome{"NULL"};

public:
    Solucao(std::string t_instancia, int t_id);

    bool popular_solucao(std::vector<Disciplina *> disciplinas_ordenadas);
    bool verificar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma, int *t_dias);
    void alocar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split);
    bool eh_horario_disponivel(Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split);
    bool eh_horario_disponivel(Professor *t_professor, int t_dia_escolhido, int t_horario_inicial, int t_split);
    void exibir_solucao();
    // void trocar_disciplina(int ponto_de_corte, Disciplina* t_disicplina);

    Professor *encontrar_prof_relacionado(Disciplina *t_disciplina);
    Turma *encontrar_turma_relacionada(Disciplina *t_disciplina);
    Curso *encontrar_curso_relacionado(Turma *t_turma);

    Instancia get_instancia();
    void debug_vector_disciplina_addr();

    bool get_factivel();
    void set_factivel(bool const &t_factivel);

    float get_valor_avaliacao();
    void set_valor_avaliacao(float const &t_valor_avaliacao);

    float get_janela();
    void set_janela(float const &t_janela);

    float get_sexto_horario();
    void set_sexto_horario(float const &t_sexto_horario);

    void set_id_solucao(const int &t_id);
    int get_id_solucao();

    void set_instancia_nome(std::string t_instancia_nome);
    std::string get_instancia_nome();


    Solucao *shallow_copy();
};

#endif // !_SOLUCAO_HPP