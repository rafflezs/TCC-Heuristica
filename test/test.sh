#!/bin/bash

ulimit -v 16000000  # Setar limite para execução

# Fase de compilação
echo "Compilando código fonte (/src/cpp*)..."
if g++ -O3 ./test/main.cpp ./src/cpp/engine/*.cpp ./src/cpp/helpers/*.cpp -o ./test/exe -lm; then
    echo "Código compilado corretamente!"
else
    echo "Falha na compilação"
    exit 1
fi
echo "Prosseguindo com script..."
echo ""
echo ""

if [ -d "data/output" ];
then
    echo "Limpando data/output"
    rm -r data/output
fi

# Lista de parâmetros
ITERACOES=10
INSTANCIAS_LIST=("TCC-Instancia-2018-1" "TCC-Instancia-2018-2" "TCC-Instancia-2019-1" ) #"TCC-Instancia-2019-2" "TCC-Instancia-2022-1")
TURMAS=(0 1 2 1000)
REPETICOES=(1 2 5 10)
JANELAS=(1 2 5)
SEXTOS=(1 2 5)

# #
# # Main drive: loop principal de parâmetros
# #

# Variável de progresso para saber quanto falta para acabar.
total=$((${#INSTANCIAS_LIST[@]} * ${#REPETICOES[@]} * ${#TURMAS[@]} * ${#JANELAS[@]} * ${#SEXTOS[@]} * 5))
progresso_atual=0
erros=0

for ((i = 1; i <= $ITERACOES; i++)); do

    output_dir_iteration="data/output/Iteracao-${i}"
    mkdir -p "$output_dir_iteration"
    
    # Cria arquivo para acompanhar exec_time
    echo "ITERACAO;INSTANCIA_NOME;ITERACOES;QTD_TURMAS_HEURISTICA;QTD_REPT_HEURISTICA;PESO_JANELA;PESO_SEXTO;TEMPO_EXEC;ID_SOLUCAO;JANELA_SOLUCAO;SEXTO_HORARIO_SOLUCAO;VALOR_SOLUCAO" >> "data/bash-time.csv"

    for instancia_value in "${INSTANCIAS_LIST[@]}"; do
        output_dir="$output_dir_iteration/$instancia_value"
        mkdir -p "$output_dir"
        echo "Instancia: $instancia_value"

        for qtd_turma_value in "${TURMAS[@]}"; do
            for qtd_rept_value in "${REPETICOES[@]}"; do
                for peso_janela_value in "${JANELAS[@]}"; do
                    for peso_sexto_value in "${SEXTOS[@]}"; do

                        ((progresso_atual++))

                        # Cria subpasta da nova execução
                        subfolder_name="ID${i}-TURMAS${qtd_turma_value}-REPETICOES${qtd_rept_value}-JAN${peso_janela_value}-SEX${peso_sexto_value}"
                        subfolder_path="$output_dir/$subfolder_name"
                        mkdir -p "$subfolder_path"

                        echo "qtd turmas heuristica: $qtd_turma_value"
                        echo "qtd repet heuristica: $qtd_rept_value"
                        echo "peso janela: $peso_janela_value"
                        echo "peso sexto: $peso_sexto_value"
                        echo ""

                        # Checa se houve runtime error
                        if { time -p (./test/exe "$instancia_value" "$qtd_turma_value" "$qtd_rept_value" "$peso_janela_value" "$peso_sexto_value" >> "$subfolder_path"/debug.txt ) ; } 2> >(grep real | awk '{print $2}' > "data/output/time.txt") > /dev/null ; then
                            echo "Tempo de execução: $exec_time segundos."
                            echo ""

                            # Read values from pequena_trollagem.txt
                            IFS=';' read -r best_id best_window_value best_sixth_grade_value solution_value < "data/output/pequena_trollagem.txt"

                            # Move arquivos para subpasta criada
                            echo "Movendo arquivos."
                            if [ -f "data/output/debug-out.txt" ]; then
                                mv "data/output/debug-out.txt" "$subfolder_path/"
                            fi
                            if [ -f "data/output/analise.csv" ]; then
                                mv "data/output/analise.csv" "$subfolder_path/"
                            fi

                            # Executa o compilador LaTeX
                            echo "Compilando LaTeX"
                            if [ -f "data/output/professor.tex" ]; then
                                mv "data/output/professor.tex" "$subfolder_path/"
                                (cd "$subfolder_path" && pdflatex -halt-on-error -interaction=batchmode -output-directory . professor.tex > /dev/null)
                            fi
                            if [ -f "data/output/turma.tex" ]; then
                                mv "data/output/turma.tex" "$subfolder_path/"
                                (cd "$subfolder_path" && pdflatex -halt-on-error -interaction=batchmode -output-directory . turma.tex > /dev/null)
                            fi
                            echo "Iteração completa: passo $progresso_atual de $total."
                            echo "----------------------------------------------"
                            echo ""

                            rm "$subfolder_path"/turma.tex
                            rm "$subfolder_path"/professor.tex
                            rm "$subfolder_path"/turma.aux
                            rm "$subfolder_path"/professor.aux
                            rm "$subfolder_path"/turma.log
                            rm "$subfolder_path"/professor.log

                            exec_time=$(cat "data/output/time.txt")
                            echo "$progresso_atual;$instancia_value;$ITERACOES;$qtd_turma_value;$qtd_rept_value;$peso_janela_value;$peso_sexto_value;$exec_time;$best_id;$best_window_value;$best_sixth_grade_value;$solution_value" >> "data/output/bash-time.csv"
                        else
                            echo "Falha na execução: passo $progresso_atual de $total."
                            echo "Erros encontrados: $erros"
                            ((erros++))

                            exec_time=$(cat "data/output/time.txt")
                            echo "$progresso_atual;$instancia_value;$ITERACOES;$qtd_turma_value;$qtd_rept_value;$peso_janela_value;$peso_sexto_value;RUNTIME_ERROR;RUNTIME_ERROR;RUNTIME_ERROR;RUNTIME_ERROR" >> "data/output/bash-time.csv"
                            rm -f "data/output/pequena_trollagem.txt"

                            echo "ID ${progresso_atual}" >> data/output/erros.txt
                        fi
                    done
                done
            done
        done
    done
done

echo ""
echo "Programa encerrado com $erros! Resultados salvos em /data/output/"