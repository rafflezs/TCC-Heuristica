#!/bin/bash

ulimit -v 8000000  # Setar limite para execucao

# Fase de compilacao
if [ -f "./test/exe" ]; then
    echo "Compilando codigo fonte (/src/cpp*)..."
    if g++ ./test/main.cpp ./src/cpp/engine/*.cpp ./src/cpp/helpers/*.cpp -o ./test/exe -lm; then
        echo "Codigo compilado corretamente!"
    else
        echo "Falha na compilacao"
        exit 1
    fi
    echo "Prosseguindo com script..."
    echo ""
    echo ""
fi

# Limpando pasta output/
rm -r data/output/*

# Lista de parametros
INSTANCIAS_LIST=("TCC-Instancia-2018-1" "TCC-Instancia-2018-2" "TCC-Instancia-2019-1" "TCC-Instancia-2019-2") # "TCC-Instancia-2022-1")
REPTS_LIST=(1 2 5 10)
QTD_TURMAS_LIST=(0 1 2 1000)
PESOS_JANELA_LIST=(1 2 5)
PESOS_SEXTO_LIST=(1 2 5)
TAM_POPULACAO=50

# #
# # Main drive: loop principal de parametros
# #

# Variavel the progresso para saber quanto falta pra acabar.
total=$((${#INSTANCIAS_LIST[@]} * ${#REPTS_LIST[@]} * ${#QTD_TURMAS_LIST[@]} * ${#PESOS_JANELA_LIST[@]} * ${#PESOS_SEXTO_LIST[@]}))
progresso_atual=0
erros=0

# Cria arquivo para acompanhar exec_time
echo "ITERACAO;INSTANCIA_NOME;TAM_POPULACAO;QTD_TURMAS_HEURISTICA;QTD_REPT_HEURISTICA;PESO_JANELA;PESO_SEXTO;TEMPO_EXEC;ID_SOLUCAO;JANELA_SOLUCAO;SEXTO_HORARIO_SOLUCAO;VALOR_SOLUCAO" >> "data/bash-time.csv"

for instancia_value in "${INSTANCIAS_LIST[@]}"; do
    output_dir="data/output/$instancia_value"
    mkdir -p "$output_dir"
    echo "Instancia: $instancia_value"

    for qtd_turma_value in "${QTD_TURMAS_LIST[@]}"; do
        for qtd_rept_value in "${REPTS_LIST[@]}"; do
            for peso_janela_value in "${PESOS_JANELA_LIST[@]}"; do
                for peso_sexto_value in "${PESOS_SEXTO_LIST[@]}"; do

                    # Cria subpasta da nova execucao
                    subfolder_name="qtdTurmas${qtd_turma_value}-REPTS_LIST${qtd_rept_value}-Jan${peso_janela_value}-Sex${peso_sexto_value}"
                    subfolder_path="$output_dir/$subfolder_name"
                    mkdir -p "$subfolder_path"

                    echo "qtd turmas heuristica: $qtd_turma_value"
                    echo "qtd repet heuristica: $qtd_rept_value"
                    echo "peso janela: $peso_janela_value"
                    echo "peso sexto: $peso_sexto_value"
                    echo ""

                    # Checa se houve runtime error
                    if { time -p (./test/exe "$instancia_value" "$TAM_POPULACAO" "$qtd_turma_value" "$qtd_rept_value" "$peso_janela_value" "$peso_sexto_value") ; } 2> >(grep real | awk '{print $2}' > "data/output/time.txt") > /dev/null ; then
                        echo "Tempo de execucao: $exec_time segundos."
                        echo ""

                        # Read values from pequena_trollagem.txt
                        IFS=';' read -r best_id best_window_value best_sixth_grade_value solution_value < "data/pequena_trollagem.txt"

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
                        echo "Iteracao completa: passo $progresso_atual de $total."
                        echo "----------------------------------------------"
                        echo ""

                        exec_time=$(cat "data/output/time.txt")
                        echo "$progresso_atual;$instancia_value;$TAM_POPULACAO;$qtd_turma_value;$qtd_rept_value;$peso_janela_value;$peso_sexto_value;$exec_time;$best_id;$best_window_value;$best_sixth_grade_value;$solution_value" >> "data/bash-time.csv"
                    else
                        ((progresso_atual++))
                        echo "Falha na execucao: passo $progresso_atual de $total."
                        echo "Erros encontrados: $erros"
                        ((erros++))

                        exec_time=$(cat "data/output/time.txt")
                        echo "$progresso_atual;$instancia_value;$TAM_POPULACAO;$qtd_turma_value;$qtd_rept_value;$peso_janela_value;$peso_sexto_value;RUNTIME_ERROR;RUNTIME_ERROR;RUNTIME_ERROR;RUNTIME_ERROR" >> "data/bash-time.csv"
                    fi
                done
            done
        done
    done
done

mv "data/bash-time.csv" "data/output/"
echo ""
echo "Programa encerrado com $erros! Resultados salvos em /data/output/"
