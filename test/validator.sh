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

# Lista de parâmetros
# INSTANCIAS_LIST=("TCC-Instancia-2018-1" "TCC-Instancia-2018-2" "TCC-Instancia-2019-1" "TCC-Instancia-2019-2" "TCC-Instancia-2022-1")
INSTANCIAS_LIST=("TCC-Instancia-2018-2" "TCC-Instancia-2019-1" "TCC-Instancia-2019-2" "TCC-Instancia-2022-1")
REPTS_LIST=(1 2 5 10)
QTD_TURMAS_LIST=(0 1 2 1000)
PESOS_JANELA_LIST=(1 2 5)
PESOS_SEXTO_LIST=(1 2 5)
TAM_POPULACAO=10

# #
# # Main drive: loop principal de parâmetros
# #

# Variável de progresso para saber quanto falta para acabar.
total=$((${#INSTANCIAS_LIST[@]} * ${#REPTS_LIST[@]} * ${#QTD_TURMAS_LIST[@]} * ${#PESOS_JANELA_LIST[@]} * ${#PESOS_SEXTO_LIST[@]} * 5))
progresso_atual=0
erros=0

for ((i = 1; i <= 3; i++)); do

    output_dir_iteration="data/output/Execucao${i}"
    mkdir -p "$output_dir_iteration"
    
    # Cria arquivo para acompanhar exec_time
    echo "ITERACAO;INSTANCIA_NOME;TAM_POPULACAO;QTD_TURMAS_HEURISTICA;QTD_REPT_HEURISTICA;PESO_JANELA;PESO_SEXTO;TEMPO_EXEC;ID_SOLUCAO;JANELA;VALOR_JANELA_SOLUCAO;SEXTO;SEXTO_HORARIO_SOLUCAO;SEXTO+JANELA;VALOR_SOLUCAO" >> "data/bash-time.csv"

    for instancia_value in "${INSTANCIAS_LIST[@]}"; do
        output_dir="$output_dir_iteration/$instancia_value"
        mkdir -p "$output_dir"
        echo "Instancia: $instancia_value"

        for qtd_turma_value in "${QTD_TURMAS_LIST[@]}"; do
            for qtd_rept_value in "${REPTS_LIST[@]}"; do
                for peso_janela_value in "${PESOS_JANELA_LIST[@]}"; do
                    for peso_sexto_value in "${PESOS_SEXTO_LIST[@]}"; do

                        # Cria subpasta da nova execução
                        subfolder_name="qtdTurmas${qtd_turma_value}-REPTS_LIST${qtd_rept_value}-Jan${peso_janela_value}-Sex${peso_sexto_value}"
                        subfolder_path="$output_dir/$subfolder_name"
                        mkdir -p "$subfolder_path"

                        echo "qtd turmas heuristica: $qtd_turma_value"
                        echo "qtd repet heuristica: $qtd_rept_value"
                        echo "peso janela: $peso_janela_value"
                        echo "peso sexto: $peso_sexto_value"
                        echo ""

                        # Checa se houve runtime error
                        if { time ./test/exe $instancia_value $TAM_POPULACAO $qtd_turma_value $qtd_rept_value $peso_janela_value $peso_sexto_value > "$subfolder_path"/debug.txt ; } > "data/output/time.txt" ; then
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

                            ((progresso_atual++))
                            echo "Iteração completa: passo $progresso_atual de $total."
                            echo "----------------------------------------------"
                            echo ""

                            exec_time=$(cat "data/output/time.txt")
                            echo "$progresso_atual;$instancia_value;$TAM_POPULACAO;$qtd_turma_value;$qtd_rept_value;$peso_janela_value;$peso_sexto_value;$exec_time;$best_id;$best_window_value;$best_sixth_grade_value;$solution_value" >> "data/bash-time.csv"
                        else
                            ((progresso_atual++))
                            echo "Falha na execução: passo $progresso_atual de $total."
                            ((erros++))
                            echo "Erros encontrados: $erros"

                            exec_time=$(cat "data/output/time.txt")
                            echo "$progresso_atual;$instancia_value;$TAM_POPULACAO;$qtd_turma_value;$qtd_rept_value;$peso_janela_value;$peso_sexto_value;RUNTIME_ERROR;RUNTIME_ERROR;RUNTIME_ERROR;RUNTIME_ERROR" >> "data/bash-time.csv"
                            rm -f "data/output/pequena_trollagem.txt"
                        fi
                    done
                done
            done
        done
    done

    mv "data/output/bash-time.csv" "$output_dir_iteration/"
done

echo ""
echo "Programa encerrado com $erros! Resultados salvos em /data/output/"
