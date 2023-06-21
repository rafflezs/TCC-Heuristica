#include "../engine/solucao.hpp"
#include "../public/since-template.hpp"

class GravarArquivo
{

private:
public:
    GravarArquivo();

    void salvar_analise(const std::string &path, Solucao *t_solucao, int t_iteracao, int qtd_turmas_heuristica, std::string curso, std::vector<int> t_turmas_selecionadas, int t_case_construtiva, std::chrono::_V2::steady_clock::time_point t_tempo_inicial_solucao);
    void salvar_saidas(const std::string &path, Solucao *t_solucao);

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

    void pequena_trollagem(std::string t_path, Solucao *t_solucao);

    std::string obter_nome_dia_semana(int dia);
    std::string obter_nome_horario(int dia);
};