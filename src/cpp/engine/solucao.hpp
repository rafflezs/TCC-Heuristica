#ifndef _SOLUCAO_HPP
#define _SOLUCAO_HPP

#include "instancia.hpp"

class Solucao{

private:
    Instancia m_instancia{nullptr};

public:
    Solucao();

    void gerar_solucao(); // Caso não receba disciplinas, gerar solucao zero
    void gerar_solucao(std::vector<Disciplina*> disciplinas_ordenadas);

};

#endif // !_SOLUCAO_HPP