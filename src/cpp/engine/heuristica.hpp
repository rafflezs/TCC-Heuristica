#ifndef _HEURISTICA_HPP
#define _HEURISTICA_HPP

#include "solucao.hpp"

class Heuristica {

// ! TODO: Implementar Herística Construtiva da Solução -> Inserir Inicio
    // ! Verificar ordenação utilizada na Heurística Construtiva


// TODO: Implementar leitura da Solução
// TODO: Implementar exclusão da Solução
// TODO: Implementar inserção da Solução

private:
    std::vector<Solucao*> solucoes{};

public:
    Heuristica(std::string t_instancia_pipe, int tam_populacao);
    
    std::vector<Disciplina*> ordernar_disciplinas(const int &rand_metodo, Solucao* solucao);
    void heuristica_construtiva();
    
    void exibir_solucoes();
    void debug_heuristica();

};

#endif //!_HEURISTICA_HPP