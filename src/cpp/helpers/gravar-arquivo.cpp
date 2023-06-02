#include "gravar-arquivo.hpp"

GravarArquivo::GravarArquivo()
{
}

void GravarArquivo::salvar_analise(const std::string &path, Solucao *t_solucao, int t_iteracao, int qtd_turmas_heuristica, std::string curso, int t_case_construtiva, std::chrono::_V2::steady_clock::time_point t_tempo_inicial_solucao)
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
        arquivo << "SOL_ID;PESO_SEXTO;PESO_JANELA;QTD_JANELAS;SEXTOS_HORARIOS;VALOR_JANELA;VALOR_SEXTO;ITERACAO;QTD_TURMAS_HEURISTICA;CURSO;DISC_ORDER_SWITCH;TEMPO_SOLUCAO;VALOR_SOLUCAO\n";
    }

    arquivo << t_solucao->get_id_solucao() << ";"
            << t_solucao->get_peso_janela() << ";"
            << t_solucao->get_peso_sexto() << ";"
            << t_solucao->get_qtd_janela() << ";"
            << t_solucao->get_qtd_sexto_horario() << ";"
            << (t_solucao->get_qtd_janela() * t_solucao->get_peso_janela()) << ";"
            << (t_solucao->get_qtd_sexto_horario() * t_solucao->get_peso_sexto()) << ";"
            << t_iteracao << ";"
            << qtd_turmas_heuristica << ";"
            << curso << ";"
            << t_case_construtiva << ";"
            << since(t_tempo_inicial_solucao).count() << ";"
            << t_solucao->get_valor_solucao() << "\n";
}

void GravarArquivo::salvar_saidas(const std::string &path, Solucao *t_solucao)
{
    // salvar_solucao_turmas(path, t_solucao);
    salvar_horario_professores(path, t_solucao);
}

void GravarArquivo::salvar_horario_professores(const std::string &path, Solucao *t_solucao)
{
    std::ofstream arquivo(path + "professor.tex");

    if (!arquivo.is_open())
    {
        std::cerr << "Falha ao carregar o arquivo! Encerrando programa com erro: 08" << std::endl;
        return;
    }

    return;
};

void GravarArquivo::salvar_solucao_turmas(const std::string &path, Solucao *t_solucao)
{
    std::ofstream arquivo(path + "turma.tex");

    if (!arquivo.is_open())
    {
        std::cerr << "Falha ao carregar o arquivo! Encerrando programa com erro: 08" << std::endl;
        return;
    }

    return;
};

std::string GravarArquivo::obter_nome_dia_semana(int dia)
{
    std::string nome_dia{""};

    switch (dia)
    {
    case 0:
        nome_dia = "SEG";
        break;
    case 1:
        nome_dia = "TER";
        break;
    case 2:
        nome_dia = "QUA";
        break;
    case 3:
        nome_dia = "QUI";
        break;
    case 4:
        nome_dia = "SEX";
        break;
    case 5:
        nome_dia = "SAB";
        break;
    }

    return nome_dia;
};

std::string GravarArquivo::obter_nome_horario(int dia)
{
    std::string nome_dia{""};

    switch (dia)
    {
    case 0:
        nome_dia = "7:30-8:20";
        break;
    case 1:
        nome_dia = "8:20-9:10";
        break;
    case 2:
        nome_dia = "9:20-10:10";
        break;
    case 3:
        nome_dia = "10:10-11:00";
        break;
    case 4:
        nome_dia = "11:00-11:50";
        break;
    case 5:
        nome_dia = "11:50-12:40";
        break;
    case 6:
        nome_dia = "13:30-14:20";
        break;
    case 7:
        nome_dia = "14:20-15:10";
        break;
    case 8:
        nome_dia = "15:20-16:10";
        break;
    case 9:
        nome_dia = "16:10-17:00";
        break;
    case 10:
        nome_dia = "17:00-17:50";
        break;
    case 11:
        nome_dia = "17:50-18:40";
        break;
    case 12:
        nome_dia = "18:50-19:40";
        break;
    case 13:
        nome_dia = "19:40-20:30";
        break;
    case 14:
        nome_dia = "20:40-21:30";
        break;
    case 15:
        nome_dia = "21:30-22:20";
        break;
    }

    return nome_dia;
};