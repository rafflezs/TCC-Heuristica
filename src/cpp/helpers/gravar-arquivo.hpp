#include "../engine/solucao.hpp"
#include "../public/since-template.hpp"

class GravarArquivo
{

private:
    std::string m_instancia{""};
    std::string m_param_janela{"1"};
    std::string m_param_sexto{"1"};

public:
    GravarArquivo(){};

    void salvar_analise(const std::string &path, Solucao *t_solucao, int t_iteracao, int t_case_construtiva, std::chrono::_V2::steady_clock::time_point t_tempo_inicial_solucao)
    {
        std::string file_w_path{path + "analise.csv"};
        std::ofstream arquivo(file_w_path, std::ios::app);

        if (!arquivo.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo " << file_w_path << std::endl;
            return;
        }

        arquivo.seekp(0, std::ios::end);
        if (arquivo.tellp() == 0)
        {
            arquivo << "SOL_ID;[PESOS];JANELAS;SEXTOS_HORARIOS;VALOR_FINAL;ITERACAO;DISC_ORDER_SWITCH;TEMPO_SOLUCAO\n";
        }

        arquivo << t_solucao->get_id_solucao() << ";["
                << this->m_param_janela << ","
                << this->m_param_sexto << "];"
                << t_solucao->get_janela() << ";"
                << t_solucao->get_sexto_horario() << ";"
                << t_solucao->get_valor_avaliacao() << ";"
                << t_iteracao << ";"
                << t_case_construtiva << ";"
                << since(t_tempo_inicial_solucao).count() << "\n";
    }

    void salvar_saidas(const std::string &path, Solucao *t_solucao)
    {
        // salvar_solucao_turmas(path, t_solucao);
        salvar_horario_professores(path, t_solucao);
    }

    /*
    @brief Salva o horario de todos os professores da solução selecionada
    ------ em formato de tabela LaTeX.
    @param string path, Solucao* t_solucao
    */
    void salvar_horario_professores(const std::string &path, Solucao *t_solucao);

    /*
    @brief Salva o horario de todos as turmas da solução selecionada
    ------ em formato de tabela LaTeX.
    @param string path, Solucao* t_solucao
    */
    void salvar_solucao_turmas(const std::string &path, Solucao *t_solucao);

    std::string obter_nome_dia_semana(int dia);
    std::string obter_nome_horario(int dia);
};