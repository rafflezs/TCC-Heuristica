#include "../engine/solucao.hpp"

class GravarArquivo
{

private:
public:
    void salvar_solucao_prof(const std::string &nome_arquivo, Solucao *t_solucao)
    {
        std::ofstream arquivo(nome_arquivo);

        if (!arquivo.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo " << nome_arquivo << std::endl;
            return;
        }

        arquivo << "\\documentclass{article}" << std::endl;
        arquivo << "\\usepackage[utf8]{inputenc}" << std::endl;
        arquivo << "\\usepackage{lscape}" << std::endl;

        arquivo << "\\begin{document}" << std::endl;


        auto profs = t_solucao->get_instancia().m_lista_professores;

        for (auto p : profs)
        {
            arquivo << "\\begin{landscape}" << std::endl;
            arquivo << "\\begin{table}[htbp]" << std::endl;
            arquivo << "\\centering" << std::endl;
            arquivo << "\\begin{tabular}{|l|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|}" << std::endl;
            arquivo << "\\hline" << std::endl;
            arquivo << "\\multicolumn{17}{|c|}{\\textbf{" << p->get_nome() << "}} \\\\" << std::endl;
            arquivo << "\\cline{1-17}" << std::endl;
            arquivo << "\\multicolumn{1}{|c|}{\\textbf{}} & \\textbf{H1} & \\textbf{H2} & \\textbf{H3} & \\textbf{H4} & \\textbf{H5} & \\textbf{H6} & \\textbf{H7} & \\textbf{H8} & \\textbf{H9} & \\textbf{H10} & \\textbf{H11} & \\textbf{H12} & \\textbf{H13} & \\textbf{H14} & \\textbf{H15} & \\textbf{H16} \\\\" << std::endl;
            arquivo << "\\hline" << std::endl;

            std::array<std::array<int, 16>, 6> f_dispo = p->get_disponibilidade();

            for (int i = 0; i < p->get_disponibilidade().size(); i++)
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

            arquivo << "\\end{tabular}" << std::endl;
            arquivo << "\\end{table}" << std::endl;
            arquivo << "\\end{landscape}" << std::endl;

            arquivo << "\\newpage" << std::endl;
        }

        arquivo << "\\end{document}" << std::endl;
    };
};