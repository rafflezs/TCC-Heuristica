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
    salvar_solucao_turmas(path, t_solucao);
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

    Instancia *instancia = t_solucao->get_instancia();

    arquivo << "\\documentclass{article}" << std::endl;
    arquivo << "\\usepackage[a4paper, landscape, margin=0.12cm]{geometry}" << std::endl;
    arquivo << "\\usepackage{array}" << std::endl;
    arquivo << "\\begin{document}" << std::endl
            << std::endl;
    arquivo << "\\pagenumbering{gobble}" << std::endl
            << std::endl;

    arquivo << "\\newcolumntype{P}[1]{ >{\\vbox to 5ex\\bgroup\\vfill\\centering} p{#1} <{\\egroup}}" << std::endl;
    arquivo << "\\newcolumntype{C}[1]{ >{\\vbox to 14.5ex\\bgroup\\vfill\\centering} p{#1} <{\\egroup}}" << std::endl
            << std::endl;

    for (auto professor : instancia->get_lista_professores())
    {
        arquivo << "\\begin{tabular}{| C{0.78cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} |}" << std::endl;
        arquivo << " \\hline" << std::endl;
        arquivo << " \\multicolumn{17}{|P{20.52cm}|}{ \\bfseries " << professor->get_nome() << " } \\tabularnewline \\hline" << std::endl;
        arquivo << "\\bfseries Dia  & \\bfseries 07:30 \\\\ - \\\\ 08:20 & \\bfseries 08:20 \\\\ - \\\\ 09:10 & \\bfseries 09:20 \\\\ - \\\\ 10:10 & \\bfseries 10:10 \\\\ - \\\\ 11:00 & \\bfseries 11:00 \\\\ - \\\\ 11:50 & \\bfseries 11:50 \\\\ - \\\\ 12:40 & \\bfseries 13:30 \\\\ - \\\\ 14:20 & \\bfseries 14:20 \\\\ - \\\\ 15:10 & \\bfseries 15:20 \\\\ - \\\\ 16:10 & \\bfseries 16:10 \\\\ - \\\\ 17:00 & \\bfseries 17:00 \\\\ - \\\\ 17:50 & \\bfseries 17:50 \\\\ - \\\\ 18:40 & \\bfseries 18:50 \\\\ - \\\\ 19:40 & \\bfseries 19:40 \\\\ - \\\\ 20:30 & \\bfseries 20:40 \\\\ - \\\\ 21:30 & \\bfseries 21:30 \\\\ - \\\\ 22:20 \\tabularnewline \\hline" << std::endl;

        std::array<std::array<int, 16UL>, 6UL> agenda = professor->get_disponibilidade();
        for (int dia = 0; dia < agenda.size(); dia++)
        {
            arquivo << "\\bfseries ";
            arquivo << obter_nome_dia_semana(dia);

            for (int horario = 0; horario < agenda[dia].size(); horario++)
            {
                arquivo << " & ";
                if (agenda[dia][horario] > 0)
                {
                    auto disciplina = instancia->get_lista_disciplinas()[agenda[dia][horario]];
                    arquivo << "\\tiny " << disciplina->get_nome() << " \\\\ - \\\\ " << t_solucao->encontrar_turma_relacionada(disciplina)->get_nome();
                }
                else
                {
                    arquivo << "\\tiny";
                }
            }
            arquivo << " \\tabularnewline \\hline" << std::endl;
        }
        arquivo << std::endl;
        arquivo << "\\end{tabular}" << std::endl;
        if (professor != instancia->get_lista_professores().back())
            arquivo << "\\newpage" << std::endl;
    }

    arquivo << "\\end{document}" << std::endl;

    arquivo.close();
}

void GravarArquivo::salvar_solucao_turmas(const std::string &path, Solucao *t_solucao)
{
    std::ofstream arquivo(path + "turma.tex");

    if (!arquivo.is_open())
    {
        std::cerr << "Falha ao carregar o arquivo! Encerrando programa com erro: 08" << std::endl;
        return;
    }

    Instancia *instancia = t_solucao->get_instancia();

    arquivo << "\\documentclass{article}" << std::endl;
    arquivo << "\\usepackage[a4paper, landscape, margin=0.12cm]{geometry}" << std::endl;
    arquivo << "\\usepackage{array}" << std::endl;
    arquivo << "\\begin{document}" << std::endl
            << std::endl;

    arquivo << "\\newcolumntype{P}[1]{ >{\\vbox to 5ex\\bgroup\\vfill\\centering} p{#1} <{\\egroup}}" << std::endl;
    arquivo << "\\newcolumntype{C}[1]{ >{\\vbox to 14.5ex\\bgroup\\vfill\\centering} p{#1} <{\\egroup}}" << std::endl
            << std::endl;

    for (auto turma : instancia->get_lista_turmas())
    {
        arquivo << "\\begin{tabular}{| C{0.78cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} |}" << std::endl;
        arquivo << " \\hline" << std::endl;
        arquivo << " \\multicolumn{17}{|P{20.52cm}|}{ \\bfseries " << turma->get_nome() << " } \\tabularnewline \\hline" << std::endl;
        arquivo << "\\bfseries Dia  & \\bfseries 07:30 \\\\ - \\\\ 08:20 & \\bfseries 08:20 \\\\ - \\\\ 09:10 & \\bfseries 09:20 \\\\ - \\\\ 10:10 & \\bfseries 10:10 \\\\ - \\\\ 11:00 & \\bfseries 11:00 \\\\ - \\\\ 11:50 & \\bfseries 11:50 \\\\ - \\\\ 12:40 & \\bfseries 13:30 \\\\ - \\\\ 14:20 & \\bfseries 14:20 \\\\ - \\\\ 15:10 & \\bfseries 15:20 \\\\ - \\\\ 16:10 & \\bfseries 16:10 \\\\ - \\\\ 17:00 & \\bfseries 17:00 \\\\ - \\\\ 17:50 & \\bfseries 17:50 \\\\ - \\\\ 18:40 & \\bfseries 18:50 \\\\ - \\\\ 19:40 & \\bfseries 19:40 \\\\ - \\\\ 20:30 & \\bfseries 20:40 \\\\ - \\\\ 21:30 & \\bfseries 21:30 \\\\ - \\\\ 22:20 \\tabularnewline \\hline" << std::endl;

        std::array<std::array<int, 16UL>, 6UL> agenda = turma->get_disponibilidade();
        for (int dia = 0; dia < agenda.size(); dia++)
        {
            arquivo << "\\bfseries ";
            arquivo << obter_nome_dia_semana(dia);

            for (int horario = 0; horario < agenda[dia].size(); horario++)
            {
                arquivo << " & ";
                if (agenda[dia][horario] > 0)
                {
                    auto disciplina = instancia->get_lista_disciplinas()[agenda[dia][horario]];
                    arquivo << "\\tiny " << disciplina->get_nome() << " \\\\ - \\\\ " << t_solucao->encontrar_prof_relacionado(disciplina)->get_nome();
                }
                else
                {
                    arquivo << "\\tiny";
                }
            }
            arquivo << " \\tabularnewline \\hline" << std::endl;
        }
        arquivo << std::endl;
        arquivo << "\\end{tabular}" << std::endl;
        if (turma != instancia->get_lista_turmas().back())
            arquivo << "\\newpage" << std::endl;
    }

    arquivo << "\\end{document}" << std::endl;

    arquivo.close();
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