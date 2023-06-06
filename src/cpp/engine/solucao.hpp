#ifndef _SOLUCAO_HPP
#define _SOLUCAO_HPP

#include "instancia.hpp"
#include <algorithm>
#include <random>
#include <set>
class Solucao
{

private:
    std::default_random_engine m_rng;
    Instancia *m_instancia{nullptr};
    int m_id{0};
    bool m_factivel{false};
    float m_valor_solucao{0.0};
    float m_peso_janelas{0.0};
    float m_peso_sexto{0.0};
    int m_qtd_sexto{0};
    int m_qtd_janelas{0};
    std::string m_instancia_nome{"NULL"};

public:
    Solucao(std::default_random_engine &t_rng, std::string t_instancia, int t_id);
    Solucao(Solucao &other);

    bool popular_solucao(std::vector<Disciplina *> t_disciplinas_ordenadas);
    bool verificar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma, int *t_dias);
    void alocar_horario(Disciplina *t_disciplina, Professor *t_professor, Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split);
    bool eh_horario_disponivel(Turma *t_turma, int t_dia_escolhido, int t_horario_inicial, int t_split);
    bool eh_horario_disponivel(Professor *t_professor, int t_dia_escolhido, int t_horario_inicial, int t_split);
    void exibir_solucao();
    // void trocar_disciplina(int ponto_de_corte, Disciplina* t_disicplina);

    Professor *encontrar_prof_relacionado(Disciplina *t_disciplina);
    Turma *encontrar_turma_relacionada(Disciplina *t_disciplina);
    Curso *encontrar_curso_relacionado(Turma *t_turma);
    std::vector<Turma *> encontrar_turmas_relacionadas(Curso *curso);

    Instancia *get_instancia();
    void debug_vector_disciplina_addr();

    bool get_factivel();
    void set_factivel(bool const &t_factivel);

    float get_valor_solucao();
    void set_valor_solucao(float const &t_valor_solucao);

    float get_peso_janela();
    void set_peso_janela(float const &t_peos_janela);

    float get_peso_sexto();
    void set_peso_sexto(float const &t_peso_sexto);

    int get_qtd_janela();
    void set_qtd_janela(int const &t_janela);

    int get_qtd_sexto_horario();
    void set_qtd_sexto_horario(int const &t_sexto_horario);

    void set_id_solucao(const int &t_id);
    int get_id_solucao();

    void set_instancia_nome(std::string t_instancia_nome);
    std::string get_instancia_nome();

    std::default_random_engine get_rng();
    void set_rng(std::default_random_engine t_rng);

    void destruir_horario(std::vector<Turma *> t_turmas);
    void destruir_horario(std::vector<Disciplina *> t_disciplinas);
    void busca_local(std::vector<Turma *> t_turmas);
};

#endif // !_SOLUCAO_HPP