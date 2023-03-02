#ifndef _FUNC_OBJ_HPP
#define _FUNC_OBJ_HPP

class FuncaoObjetivo{

private:
    float m_valor{0.0};
public:

    float avaliar_solucao();
    float avaliar_janela();
    float avaliar_sexto_horario();
    // float avaliar;

};

#endif //!_FUNC_OBJ_HPP