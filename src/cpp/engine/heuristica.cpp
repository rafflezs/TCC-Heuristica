#include "heuristica.hpp"

Heuristica::Heuristica(std::default_random_engine &t_rng, const std::string &t_instancia_nome, const int qtd_turmas_heuristica, const int qtd_rept_busca_local, const int &t_peso_janela, const int &t_peso_sexto)
{
    this->m_rng = t_rng;
    this->m_instancia_nome = t_instancia_nome;
    this->m_qtd_turmas_heuristica = qtd_turmas_heuristica;
    this->m_qtd_rept_busca_local = qtd_rept_busca_local;
    this->m_peso_janela = t_peso_janela;
    this->m_peso_sexto = t_peso_sexto;

    for (int i = 0; i < 10; i++)
    {
        this->m_solucoes.push_back(new Solucao(m_rng, m_instancia_nome, i));
    }
    std::cout << "Gerando solucoes em C++" << std::endl;
}

Heuristica::~Heuristica()
{
    std::cout << "De-instanciando objeto Heuristica" << std::endl;
    for (int i = 0; i < m_solucoes.size(); i++)
    {
        delete m_solucoes[i];
        m_solucoes[i] = nullptr;
    }

    m_solucoes.clear();
}

void Heuristica::inicializar(std::chrono::_V2::steady_clock::time_point *m_tempo_inicial)
{
    this->m_tempo_inicial = m_tempo_inicial;
    heuristica_construtiva(0);

    std::cout << "Salvando melhor solucao em C++" << std::endl;
    get_melhor_solucao();
}

std::vector<Disciplina *> Heuristica::ordenar_disciplinas(const int &rand_metodo, Solucao *solucao)
{

    std::vector<Disciplina *> t_disciplinas_ordenadas = (*solucao).get_instancia()->get_lista_disciplinas();

    switch (rand_metodo)
    {

    // Caso 1: Ordenar disciplinas por maior CH-MIN (tamanho)
    case 1:
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_ch_min() > rhs->get_ch_min(); });
        break;

    // Caso 2: Ordenar disciplinas por Menor Split (tamanho)
    case 2:
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return lhs->get_split() < rhs->get_split(); });
        break;

    // Caso 3: Ordenar disciplina por prioriedade de CH-MIN e Split combinadas (tamanho)
    case 3:
        std::sort(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), [](Disciplina *lhs, Disciplina *rhs)
                  { return (lhs->get_ch_min() > rhs->get_ch_min()) && (lhs->get_split() < rhs->get_split()); });
        break;

    case 4:
        std::shuffle(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), m_rng);
        break;

    // Caso base: ordenação por ordem de leitura da instância
    default:
        std::shuffle(t_disciplinas_ordenadas.begin(), t_disciplinas_ordenadas.end(), m_rng);
        break;
    }

    return t_disciplinas_ordenadas;
}

void Heuristica::heuristica_construtiva(int t_iteracao)
{

    for (int index_sol = 0; index_sol < m_solucoes.size(); index_sol++)
    {
        std::cout << "Construtiva para a solucao " << index_sol << " em C++" << std::endl;

        auto disciplinas_ordenadas = ordenar_disciplinas(index_sol, m_solucoes[index_sol]);
        std::cout << "1" << std::endl;

        bool deu_certo = m_solucoes[index_sol]->popular_solucao(disciplinas_ordenadas);
        std::cout << "2" << std::endl;

        avaliar_solucao(m_solucoes[index_sol]);
        std::cout << "3" << std::endl;

        // Salvando parametros da solucao em csv para futura analise
        std::cout << "Salvando analise" << std::endl;

        output.salvar_analise("data/output/", m_solucoes[index_sol], t_iteracao, 0, "CONSTRUTIVA", {}, index_sol, *m_tempo_inicial);

        std::cout << "Busca local ";

        if (m_qtd_turmas_heuristica == 0)
        {
            std::cout << "DINAMICA" << std::endl;

            m_solucoes[index_sol] = fix_and_optimize_dinamico(new Solucao(*m_solucoes[index_sol]));
        }
        else
        {
            std::cout << "ESTATICA" << std::endl;

            m_solucoes[index_sol] = fix_and_optimize_estatico(new Solucao(*m_solucoes[index_sol]));
        }
    }
}

void Heuristica::exibir_solucoes()
{
    for (auto solucao : m_solucoes)
    {
        std::cout << "Solucao " << solucao->get_id_solucao() << " | Avaliada em: " << solucao->get_valor_solucao() << std::endl;
        solucao->exibir_solucao();
    }
    std::cout << "Solucoes Exibidas: void return (no problems found)" << std::endl;
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

void Heuristica::ordenar_solucoes()
{
    std::sort(m_solucoes.begin(), m_solucoes.end(), [](Solucao *s1, Solucao *s2)
              { return s1->get_valor_solucao() < s2->get_valor_solucao(); });
}

void Heuristica::avaliar_solucao(Solucao *t_solucao)
{
    t_solucao->set_qtd_sexto_horario(calcular_sexto_horario_turma(t_solucao));
    t_solucao->set_qtd_janela(calcular_janela_professor(t_solucao));

    if (t_solucao->get_factivel() == true)
        t_solucao->set_valor_solucao((m_peso_sexto * t_solucao->get_qtd_sexto_horario()) + (m_peso_janela * t_solucao->get_qtd_janela()));
    else
        t_solucao->set_valor_solucao(999999);
}

int Heuristica::calcular_janela_professor(Solucao *t_solucao)
{
    int janela = 0;

    for (auto professor : t_solucao->get_instancia()->get_lista_professores())
    {
        janela += professor->get_qtd_janelas_horario();
    }

    return janela;
}

int Heuristica::calcular_sexto_horario_turma(Solucao *t_solucao)
{

    int sexto_horario = 0;

    for (auto turma : t_solucao->get_instancia()->get_lista_turmas())
    {
        sexto_horario += turma->get_qtd_sextos();
    }

    return sexto_horario;
}

Solucao *Heuristica::get_solucao(int index)
{
    return this->m_solucoes[index];
}

std::vector<Solucao *> Heuristica::get_lista_solucoes()
{
    return this->m_solucoes;
}

Solucao *Heuristica::fix_and_optimize_estatico(Solucao *t_solucao)
{

    int iteracao_solucao = 0;
    Solucao *solucao_retorno = new Solucao(*t_solucao); // atribui solucao original

    for (auto curso : t_solucao->get_instancia()->get_lista_cursos())
    {
        bool houve_melhoria = true;
        while (houve_melhoria)
        {
            houve_melhoria = false;
            std::vector<int> index_turmas_curso{};

            for (auto turma_index : curso->get_turmas_index())
                index_turmas_curso.push_back(t_solucao->get_instancia()->get_lista_turmas().at(turma_index)->get_index());

            for (int nbl = 0; nbl < index_turmas_curso.size() + 1 - std::min(m_qtd_turmas_heuristica, int(index_turmas_curso.size())); nbl++)
            {
                Solucao nova_solucao = Solucao(*t_solucao);

                std::vector<int> turmas_iteracao;
                for (int i = 0; i < std::min(m_qtd_turmas_heuristica, int(index_turmas_curso.size())); i++)
                    turmas_iteracao.push_back(nova_solucao.get_instancia()->get_lista_turmas()[index_turmas_curso[i + nbl]]->get_index());

                int count = 0;
                for (; count < m_qtd_rept_busca_local; count++)
                {
                    nova_solucao.busca_local(turmas_iteracao);
                    avaliar_solucao(&nova_solucao);
                    if (nova_solucao.get_valor_solucao() < solucao_retorno->get_valor_solucao())
                    {
                        delete solucao_retorno;
                        solucao_retorno = new Solucao(nova_solucao);
                        output.salvar_analise("data/output/", &nova_solucao, iteracao_solucao, turmas_iteracao.size(), curso->get_nome(), turmas_iteracao, 4, *m_tempo_inicial);
                        houve_melhoria = true;
                        break;
                    }
                }
            }
        }
    }
    return solucao_retorno;
}

Solucao *Heuristica::fix_and_optimize_dinamico(Solucao *t_solucao)
{
    int iteracao_solucao = 0;
    std::vector<int> qtd_iteracoes{1, 2, 100};

    Solucao *solucao_retorno = new Solucao(*t_solucao); // atribui solucao original

    for (auto n : qtd_iteracoes)
    {
        for (auto curso : t_solucao->get_instancia()->get_lista_cursos())
        {
            bool houve_melhoria = true;
            while (houve_melhoria)
            {
                houve_melhoria = false;

                // Seleciona as turmas Todas as turmas do Curso
                std::vector<int> index_turmas_curso{};
                for (auto turma_index : curso->get_turmas_index())
                    index_turmas_curso.push_back(t_solucao->get_instancia()->get_lista_turmas().at(turma_index)->get_index());

                // Processamento dinamico de turmas
                for (int nbl = 0; nbl < index_turmas_curso.size() + 1 - std::min(m_qtd_turmas_heuristica, int(index_turmas_curso.size())); nbl++)
                {
                    Solucao nova_solucao = Solucao(*t_solucao);

                    std::vector<int> turmas_iteracao;
                    for (int i = 0; i < std::min(m_qtd_turmas_heuristica, int(index_turmas_curso.size())); i++)
                        turmas_iteracao.push_back(nova_solucao.get_instancia()->get_lista_turmas()[index_turmas_curso[i + nbl]]->get_index());

                    int count = 0;
                    for (; count < m_qtd_rept_busca_local; count++)
                    {

                        nova_solucao.busca_local(turmas_iteracao);
                        avaliar_solucao(&nova_solucao);

                        if (nova_solucao.get_valor_solucao() < solucao_retorno->get_valor_solucao())
                        {

                            std::cout << "Solucao antiga" << std::endl;
                            // exibir_turma_e_sexto(t_solucao->get_instancia(), turmas_iteracao);

                            std::cout << "Solucao nova" << std::endl;
                            // exibir_turma_e_sexto(nova_solucao.get_instancia(), turmas_iteracao);

                            delete solucao_retorno;
                            solucao_retorno = new Solucao(nova_solucao);
                            output.salvar_analise("data/output/", &nova_solucao, iteracao_solucao, turmas_iteracao.size(), curso->get_nome(), turmas_iteracao, 4, *m_tempo_inicial);
                            houve_melhoria = true;

                            break;
                        }
                    }
                }
            }
        }
    }
    return solucao_retorno;
}

void Heuristica::get_melhor_solucao()
{
    if (m_solucoes.empty())
    {
        std::cout << "Nenhuma soluçao encontrada. Encerrando com erro 02" << std::endl;
        exit(2);
    }

    Solucao melhor_solucao = Solucao(*m_solucoes[0]);

    if (m_solucoes.size() > 1)
    {
        for (int i = 1; i < m_solucoes.size(); i++)
        {
            if (m_solucoes[i]->get_valor_solucao() < melhor_solucao.get_valor_solucao())
            {
                melhor_solucao = *m_solucoes[i];
            }
        }
    }

    std::cout << "\n\n\n\nMAIS MELHOR SOLUCAO\n"
              << std::endl;
    std::cout << "A solução ID " << melhor_solucao.get_id_solucao() << " com o valor na função objetivo de " << melhor_solucao.get_valor_solucao() << " pontos." << std::endl;
    melhor_solucao.exibir_solucao();
    output.salvar_analise("data/output/", &melhor_solucao, 0, 0, "MELHOR_SOLUCAO", {}, 0, *m_tempo_inicial);
    output.salvar_saidas("data/output/", &melhor_solucao);
    output.pequena_trollagem("data/output/pequena_trollagem.txt", &melhor_solucao);

}

void Heuristica::exibir_turma_e_sexto(Instancia *t_instancia, std::vector<int> t_index_turmas)
{
    for (auto turma_index : t_index_turmas)
    {
        t_instancia->get_lista_turmas()[turma_index]->print_solucao();
        std::cout << "Sextos Horarios: " << t_instancia->get_lista_turmas()[turma_index]->get_qtd_sextos() << std::endl;
    }
    getchar();
}

void Heuristica::exibir_professor_e_janela(Instancia *t_instancia, int t_professor_index)
{

    t_instancia->get_lista_professores()[t_professor_index]->print_solucao();
    std::cout << "Janelas: " << t_instancia->get_lista_professores()[t_professor_index]->get_qtd_janelas_horario() << std::endl;

    getchar();
}

void Heuristica::exibir_melhoria(Solucao *solucao_antiga, Solucao *solucao_melhorada, std::vector<int> t_turmas_index)
{

    std::cout << "Solucao antiga" << std::endl;
    for (auto turma_index : t_turmas_index)
    {
        solucao_antiga->get_instancia()->get_lista_turmas()[turma_index]->print_solucao();
        std::cout << "Sextos Horarios: " << solucao_antiga->get_instancia()->get_lista_turmas()[turma_index]->get_qtd_sextos() << std::endl;
        for (auto disciplina : solucao_antiga->get_instancia()->get_lista_turmas()[turma_index]->get_disciplinas())
        {
            auto professor = solucao_antiga->encontrar_prof_relacionado(disciplina);
            professor->print_solucao();
            std::cout << "Janelas: " << professor->get_qtd_janelas_horario() << std::endl;
            getchar();
            delete professor;
        }
        getchar();
    }

    std::cout << "Solucao Melhorada" << std::endl;
    for (auto turma_index : t_turmas_index)
    {
        solucao_melhorada->get_instancia()->get_lista_turmas()[turma_index]->print_solucao();
        std::cout << "Sextos Horarios: " << solucao_melhorada->get_instancia()->get_lista_turmas()[turma_index]->get_qtd_sextos() << std::endl;
        for (auto disciplina : solucao_melhorada->get_instancia()->get_lista_turmas()[turma_index]->get_disciplinas())
        {
            auto professor = solucao_melhorada->encontrar_prof_relacionado(disciplina);
            professor->print_solucao();
            std::cout << "Janelas: " << professor->get_qtd_janelas_horario() << std::endl;
            getchar();
            delete professor;
        }
        getchar();
    }
}