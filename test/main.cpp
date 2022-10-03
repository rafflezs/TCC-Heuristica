#include "../src/cpp/helpers/instancia.hpp"

int main()
{
    Instancia inst = Instancia("2018");

    for (std::list<Turma>::iterator i = inst.m_lista_turmas.begin(); 
        i != inst.m_lista_turmas.end(); ++i){
        (i)->print();
    };

    return 0;
}

