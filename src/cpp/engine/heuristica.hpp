#ifndef _HEURISTICA_HPP
#define _HEURISTICA_HPP

#include "../helpers/gravar-arquivo.hpp"
#include <set>
#include <ctime>
#include <limits>

class Heuristica
{

private:
    std::default_random_engine m_rng;
    std::vector<Solucao *> m_solucoes{};
    std::string m_instancia_nome{"NULL"};
    int m_qtd_turmas_heuristica{1};
    int m_qtd_rept_busca_local{1};
    int m_peso_janela{0};
    int m_peso_sexto{0};
    std::chrono::_V2::steady_clock::time_point *m_tempo_inicial;
    GravarArquivo output{};

    std::vector<Disciplina *> ordenar_disciplinas(const int &rand_metodo, Solucao *solucao);
    void ordenar_disciplinas(const int &rand_metodo, std::vector<Disciplina *> *t_disciplina);

    void heuristica_construtiva(int t_iteracao);
    Solucao *fix_and_optimize_estatico(Solucao *t_solucao);
    Solucao *fix_and_optimize_dinamico(Solucao *t_solucao);

    void exibir_solucoes();
    void debug_heuristica();

    // Função Objetivo
    void ordenar_solucoes();

    void avaliar_solucao(Solucao *t_solucao);
    int calcular_janela_professor(Solucao *t_solucao);
    int calcular_sexto_horario_turma(Solucao *t_solucao);

    void get_melhor_solucao();

    void exibir_turma_e_sexto(Instancia *t_instancia, std::vector<int> t_index_turmas);
    void exibir_professor_e_janela(Instancia *t_instancia, int t_professor);
    void exibir_melhoria(Solucao *solucao_antiga, Solucao *solucao_melhorada, std::vector<int> t_turmas_index);

public:
    Heuristica(std::default_random_engine &t_rng, const std::string &t_instancia_nome, const int qtd_turmas_heuristica, const int qtd_rept_busca_local, const int &t_peso_janela, const int &t_peso_sexto);
    ~Heuristica();
    Solucao *get_solucao(int index);
    std::vector<Solucao *> get_lista_solucoes();
    void inicializar(std::chrono::_V2::steady_clock::time_point *m_tempo_inicial);
};

#endif //!_HEURISTICA_HPP