#ifndef _SORT_DISC_HPP
#define _SORT_DISC_HPP

#include "../public/public_includes.hpp"
#include "../classes/disciplina.hpp"

class SortDisciplina
{

private:
std::vector<Disciplina*> m_disciplina{};

public:


int compararDisciplinas(Disciplina* lhs, Disciplina* rhs)
{
    return lhs->get_ch_presencial() < rhs->get_ch_presencial();
}

// std::sort(m_disciplina.begin(), m_disciplina.end(), compararDisciplinas);

};

#endif