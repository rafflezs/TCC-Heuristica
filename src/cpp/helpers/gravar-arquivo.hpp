#include "../engine/solucao.hpp"
#include <chrono>

class GravarArquivo
{

private:
    std::string m_output_path{"./data/output/"}; // salva os arquivos de saida por padrao na pasta data/output dentro deste repo
    std::string m_instancia{""};
    std::string m_param_janela{"1"};
    std::string m_param_sexto{"1"};

public:
    GravarArquivo(const std::string &path)
    {
        this->m_output_path = path;
    }

    void salvar_analise(Solucao *t_solucao, int t_iteracao, int t_case_construtiva, std::chrono::duration<double> t_tempo_solucao)
    {
        std::string file_w_path{m_output_path};
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
                << std::to_string(t_tempo_solucao.count()) << "\n";
    }

    void salvar_saidas(Solucao *t_solucao)
    {
        salvar_solucao_prof(t_solucao);
        salvar_solucao_turmas(t_solucao);
    }

    void salvar_solucao_prof(Solucao *t_solucao)
    {
        std::string file_w_path{m_output_path};
        std::ofstream arquivo(file_w_path, std::ios::app);

        if (!arquivo.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo " << file_w_path << std::endl;
            return;
        }

        arquivo << "\\documentclass{article}" << std::endl;
        arquivo << "\\usepackage[a4paper, landscape, margin=1in]{geometry}" << std::endl;
        arquivo << "\\usepackage{tabularx}" << std::endl
                << std::endl;

        arquivo << "\\setlength{\\extrarowheight}{40pt}" << std::endl
                << std::endl;
        arquivo << "\\begin{document}" << std::endl;

        auto profs = t_solucao->get_instancia().m_lista_professores;

        for (auto p : profs)
        {
            arquivo << "\\centering" << std::endl;
            arquivo << "\\begin{tabularx}{\\textwidth} { | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X |}" << std::endl;
            arquivo << "\\hline" << std::endl;
            arquivo << "\\multicolumn{17}{|c|}{\\textbf{" << p->get_nome() << "}} \\\\" << std::endl;
            arquivo << "\\cline{1-17}" << std::endl;
            arquivo << "\\multicolumn{1}{|c|}{\\textbf{}} & \\textbf{07:30 - 08:20} & \\textbf{08:20 - 09:10} & \\textbf{09:20 - 10:10} & \\textbf{10:10 - 11:00} & \\textbf{11:00 - 11:50} & \\textbf{11:50 - 12:40} & \\textbf{13:30 - 14:20} & \\textbf{14:20 - 15:10} & \\textbf{15:20 - 16:10} & \\textbf{16:10 - 17:00} & \\textbf{17:00 - 17:50} & \\textbf{17:50 - 18:40} & \\textbf{18:50 - 19:40} & \\textbf{19:40 - 20:30} & \\textbf{20:40 - 21:30} & \\textbf{21:30 - 22:20} \\\\" << std::endl;
            arquivo << "\\hline" << std::endl;

            std::array<std::array<int, 16>, 6> f_dispo = p->get_disponibilidade();

            for (int i = 0; i < f_dispo.size(); i++)
            {
                switch (i)
                {
                case 0:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{SEG}} & ";
                    break;
                case 1:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{TER}} & ";
                    break;
                case 2:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{QUA}} & ";
                    break;
                case 3:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{QUI}} & ";
                    break;
                case 4:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{SEX}} & ";
                    break;
                case 5:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{SAB}} & ";
                    break;
                default:
                    break;
                }
                for (int j = 0; j < p->get_disponibilidade()[i].size(); j++)
                {
                    if (f_dispo[i][j] > 0)
                    {
                        arquivo << f_dispo[i][j];
                    }
                    else
                    {
                        arquivo << " ";
                    }

                    if (j < f_dispo[i].size() - 1)
                    {
                        arquivo << " & ";
                    }
                }
                arquivo << " \\\\ \\hline" << std::endl;
            }

            arquivo << "\\end{tabularx}" << std::endl;
            arquivo << "Instituto Federal de Educação, Ciência e Tecnologia Goiano - Campus Rio Verde, Rod. Sul Goiana, Km 01, Cx. P. 66, Rio Verde / Goiás" << std::endl;
            arquivo << "\\newpage" << std::endl
                    << std::endl;
        }

        arquivo << "\\end{document}" << std::endl;
    };

    void salvar_solucao_turmas(Solucao *t_solucao)
    {
        std::string file_w_path{m_output_path};
        std::ofstream arquivo(file_w_path, std::ios::app);

        if (!arquivo.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo " << file_w_path << std::endl;
            return;
        }

        arquivo << "\\documentclass{article}" << std::endl;
        arquivo << "\\usepackage[a4paper, landscape, margin=1in]{geometry}" << std::endl;
        arquivo << "\\usepackage{tabularx}" << std::endl
                << std::endl;

        arquivo << "\\setlength{\\extrarowheight}{40pt}" << std::endl
                << std::endl;
        arquivo << "\\begin{document}" << std::endl;

        auto profs = t_solucao->get_instancia().m_lista_turmas;

        for (auto p : profs)
        {
            arquivo << "\\centering" << std::endl;
            arquivo << "\\begin{tabularx}{\\textwidth} { | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X | > {\\centering\\arraybackslash} X |}" << std::endl;
            arquivo << "\\hline" << std::endl;
            arquivo << "\\multicolumn{17}{|c|}{\\textbf{" << p->get_nome() << "}} \\\\" << std::endl;
            arquivo << "\\cline{1-17}" << std::endl;
            arquivo << "\\multicolumn{1}{|c|}{\\textbf{}} & \\textbf{07:30 - 08:20} & \\textbf{08:20 - 09:10} & \\textbf{09:20 - 10:10} & \\textbf{10:10 - 11:00} & \\textbf{11:00 - 11:50} & \\textbf{11:50 - 12:40} & \\textbf{13:30 - 14:20} & \\textbf{14:20 - 15:10} & \\textbf{15:20 - 16:10} & \\textbf{16:10 - 17:00} & \\textbf{17:00 - 17:50} & \\textbf{17:50 - 18:40} & \\textbf{18:50 - 19:40} & \\textbf{19:40 - 20:30} & \\textbf{20:40 - 21:30} & \\textbf{21:30 - 22:20} \\\\" << std::endl;
            arquivo << "\\hline" << std::endl;

            std::array<std::array<int, 16>, 6> f_dispo = p->get_disponibilidade();

            for (int i = 0; i < f_dispo.size(); i++)
            {
                switch (i)
                {
                case 0:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{SEG}} & ";
                    break;
                case 1:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{TER}} & ";
                    break;
                case 2:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{QUA}} & ";
                    break;
                case 3:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{QUI}} & ";
                    break;
                case 4:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{SEX}} & ";
                    break;
                case 5:
                    arquivo << "\\multicolumn{1}{|c|}{\\textbf{SAB}} & ";
                    break;
                default:
                    break;
                }
                for (int j = 0; j < p->get_disponibilidade()[i].size(); j++)
                {
                    if (f_dispo[i][j] > 0)
                    {
                        arquivo << f_dispo[i][j];
                    }
                    else
                    {
                        arquivo << " ";
                    }

                    if (j < f_dispo[i].size() - 1)
                    {
                        arquivo << " & ";
                    }
                }
                arquivo << " \\\\ \\hline" << std::endl;
            }

            arquivo << "\\end{tabularx}" << std::endl;
            arquivo << "Instituto Federal de Educação, Ciência e Tecnologia Goiano - Campus Rio Verde, Rod. Sul Goiana, Km 01, Cx. P. 66, Rio Verde / Goiás" << std::endl;
            arquivo << "\\newpage" << std::endl
                    << std::endl;
        }

        arquivo << "\\end{document}" << std::endl;
    };
};