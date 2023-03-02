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

        t_solucao;

        arquivo << "\\begin{table}[htbp]" << std::endl;
        arquivo << "\\centering" << std::endl;
        arquivo << "\\caption{Solução}" << std::endl;
        arquivo << "\\begin{tabular}{|l|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|}" << std::endl;
        arquivo << "\\hline" << std::endl;
        arquivo << "\\multicolumn{1}{|c|}{\\textbf{}} & \\multicolumn{15}{|c|}{\\textbf{Horário da Turma}} \\\\" << std::endl;
        arquivo << "\\cline{2-16}" << std::endl;
        arquivo << "\\multicolumn{1}{|c|}{\\textbf{}} & \\textbf{H1} & \\textbf{H2} & \\textbf{H3} & \\textbf{H4} & \\textbf{H5} & \\textbf{H6} & \\textbf{H7} & \\textbf{H8} & \\textbf{H9} & \\textbf{H10} & \\textbf{H11} & \\textbf{H12} & \\textbf{H13} & \\textbf{H14} & \\textbf{H15} & \\textbf{H16} \\\\" << std::endl;
        arquivo << "\\hline" << std::endl;

        for (Professor p : t_solucao->m_instancia->professor)
        {
            std::array<std::array<int, 16>, 6> f_dispo = this->get_disponibilidade();
            arquivo << p.get_nome() << std::endl;

            for (int i = 0; i < p.get_disponibilidade().size(); i++)
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
                for (int j = 0; j < p.get_disponibilidade()[i].size(); j++)
                {
                    arquivo << f_dispo[i][j];
                    if (j < f_dispo[i].size() - 1)
                    {
                        arquivo << " & ";
                    }
                }
                arquivo << " \\\\ \\hline" << std::endl;
            }

            arquivo << "\\end{tabular}" << std::endl;
            arquivo << "\\end{table}" << std::endl;
        }
    };
};