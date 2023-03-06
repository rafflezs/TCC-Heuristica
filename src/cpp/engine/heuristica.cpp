#include "heuristica.hpp"

Heuristica::Heuristica(std::string t_instancia_pipe, int tam_populacao)
{
    // this->solucoes.push_back(new Solucao(t_instancia_pipe, 0));
    for (int i = 1; i <= tam_populacao; i++)
    {
        std::cout << CYN "Gerando Instancia " << t_instancia_pipe << " nº: " << i + 1 << NC << std::endl;
        this->m_solucoes.push_back(new Solucao(t_instancia_pipe, i));
    }
    std::cout << "-------Encerrada geração de populações-------\n"
              << std::endl;


    std::cout << "-------Avaliando Soluções-------\n"
              << std::endl;

    for (int i = 1; i <= tam_populacao; i++)
    {
        std::cout << CYN "Gerando Instancia " << t_instancia_pipe << " nº: " << i + 1 << NC << std::endl;
        avaliar_solucao(m_solucoes[i]);
    }

}

std::vector<Disciplina *> Heuristica::ordernar_disciplinas(const int &rand_metodo, Solucao *solucao)
{

    std::vector<Disciplina *> t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
    std::random_device rd;
    std::mt19937 g(rd());

    switch (rand_metodo)
    {

    // Caso 1: Ordenar disciplinas por maior CH-MIN (tamanho)
    case 1:
        printf("\n------Caso %d - Maior CH-MIN------", rand_metodo);
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_ch_min() > rhs->get_ch_min(); });
        break;

    // Caso 2: Ordenar disciplinas por Menor Split (tamanho)
    case 2:
        printf("\n------Caso %d - Menor Split------", rand_metodo);
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_split() < rhs->get_split(); });
        break;

    // Caso 3: Ordenar disciplina por prioriedade de CH-MIN e Split combinadas (tamanho)
    case 3:
        printf("\n------Caso %d - Prioriedade CH-MIN e Split Combinados------", rand_metodo);
        t_disciplinas_ordenadas = (*solucao).get_instancia().m_lista_disciplinas;
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return (lhs->get_ch_min() > rhs->get_ch_min()) && (lhs->get_split() < rhs->get_split()); });
        break;

    // // TODO Caso 4: Ordenar disciplina por professor com mais disciplinas
    // case 4:
    //     printf("\n------Caso %d\n", rand_metodo);
    //     break;

    // // TODO Caso 5: Ordenar disciplina por Curso
    // case 5:
    //     printf("\n------Caso %d\n", rand_metodo);
    //     break;

    // TODO Caso 6: Random Sort
    case 6:
        printf("\n------Caso %d\n", rand_metodo);
        std::shuffle(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), g);
        break;

    // Caso base: ordenação por ordem de leitura da instância
    default:
        printf("\n------Caso %d - Ordem de Leitura\n", rand_metodo);
        t_disciplinas_ordenadas;
        break;
    }

    return t_disciplinas_ordenadas;
}

void Heuristica::heuristica_construtiva()
{
    for (auto it : this->m_solucoes)
    {
        // TODO : Alterar o teto do rand baseado na quantidade de parametros do ordernar_disciplinas()
        bool deu_certo = it->popular_solucao(ordernar_disciplinas(rand() % 4, it));
        if (deu_certo == true)
        {
            it->set_factivel(true);
            std::cout << "Solucao " << it->get_id_solucao() << " encontrada" << std::endl;
            // it->exibir_solucao();
        }
        else
        {
            it->set_factivel(false);
            std::cout << "Solucao " << it->get_id_solucao() << " infactivel" << std::endl;
            // it->exibir_solucao();
        }
    }
}

void Heuristica::exibir_solucoes()
{
    for (auto it = this->m_solucoes.begin(); it != this->m_solucoes.end(); it++)
    {
        if ((*it)->get_factivel() == true)
            (*it)->exibir_solucao();
    }
}

void Heuristica::debug_heuristica()
{
    /* ---------------DEBUG BLOCK---------------------
    ** ! VERIFICAR COPIA DE PRT ADDR !
    */
    std::cout << REDB "\n\nDEBUG - ENDERECOS DISCIPLINAS\n" NC << std::endl;
    for (auto it : this->m_solucoes)
    {
        it->debug_vector_disciplina_addr();
    }
}

float Heuristica::avaliar_solucao(Solucao* m_solucao){
    return 0.0;
}

Solucao* Heuristica::get_solucao(int index){
        return this->m_solucoes[index];
}

// void Heuristica::mutar(Solucao *solucao, int taxa_mutacao)
// {
//     std::mt19937 engine(time(NULL));
//     std::uniform_real_distribution<double> dist(0, 1);

//     for (int i = 0; i < solucao->get_instancia().m_lista_disciplinas.size(); i++)
//     {
//         if (dist(engine) < taxa_mutacao)
//         {
//             int disciplina_idx = i;
//             int nova_posicao = rand() % solucao->get_instancia().m_lista_disciplinas.size();

//             auto disciplina = solucao->get_instancia().m_lista_disciplinas[disciplina_idx];
//             solucao->get_instancia().m_lista_disciplinas.erase(solucao->get_instancia().m_lista_disciplinas.begin() + disciplina_idx);
//             solucao->get_instancia().m_lista_disciplinas.insert(solucao->get_instancia().m_lista_disciplinas.begin() + nova_posicao, disciplina);
//         }
//     }
// }

// void Heuristica::cruzar(Solucao *solucao1, Solucao *solucao2)
// {

//     std::uniform_int_distribution<int> dist(0, solucao1->get_instancia().m_lista_disciplinas.size() - 1);
//     std::mt19937 engine(time(nullptr));

//     int ponto_corte = dist(engine);

//     Solucao filho1 = *solucao1;
//     Solucao filho2 = *solucao2;

//     for (int i = ponto_corte; i < filho1.get_instancia().m_lista_disciplinas.size(); ++i)
//     {
//         Disciplina disciplina_solucao2 = *filho2.get_instancia().m_lista_disciplinas[i];
//         filho1.trocar_disciplina(i, disciplina_solucao2);
//         filho2.trocar_disciplina(i, *filho1.get_instancia().m_lista_disciplinas[i]);
//     }

//     solucoes.push_back(new Solucao(filho1));
//     solucoes.push_back(new Solucao(filho2));
// }
