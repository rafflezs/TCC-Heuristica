#include "../src/cpp/engine/instancia.hpp"

int main()
{
    Instancia inst = Instancia("2018-1");
    for (std::list<Professor>::iterator i = inst.m_lista_professores.begin();
        i != inst.m_lista_professores.end(); ++i){
        (i)->print();
    };

    return 0;
}
