#include "../src/cpp/engine/instancia.hpp"

int main()
{
    Instancia inst = Instancia("2018-1");
    for (auto it = inst.m_lista_turmas.begin(); it < inst.m_lista_turmas.end(); it++)
    {
        (*it).print();
    }
    
    return 0;
}
