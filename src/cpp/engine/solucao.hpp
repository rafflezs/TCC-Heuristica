#ifndef _SOLUCAO_HPP
#define _SOLUCAO_HPP

#include "instancia.hpp"

class Solucao{

private:
    Instancia *m_instancia{nullptr};

public:
    Solucao(std::string t_instancia, std::vector<Disciplina*> disciplinas_ordenadas);
    Solucao(std::string t_instancia);

    void exibir_solucao();

    Instancia get_instancia();

    void debug_vector_disciplina_addr();

};

#endif // !_SOLUCAO_HPP