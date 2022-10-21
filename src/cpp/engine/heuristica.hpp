#ifndef _HEURISTICA_HPP
#define _HEURISTICA_HPP

#include "solucao.hpp"

class Heuristica {

// ! TODO: Implementar Inicialização da Solução -> Solução Zero
// ! TODO: Implementar Herística Construtiva da Solução -> Inserir Inicio
    // ! Verificar ordenação utilizada na Heurística Construtiva
// ! TODO: Implementar Impressão da Solução


// Instancia - Computação
// Instancia (hard) - Biologias e Biotecnologia

// TODO: Implementar leitura da Solução
// TODO: Implementar exclusão da Solução
// TODO: Implementar inserção da Solução

private:
    std::list<Solucao*> solucoes;

public:
    std::vector<Disciplina> ordernar_disciplinas();
    void exibir_solucoes();


};

#endif //!_HEURISTICA_HPP