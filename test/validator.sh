#!/bin/bash

if [ ! -f "./test/exe" ]; then
    echo "Compiling source code..."
    g++ ./test/main.cpp ./src/cpp/engine/*.cpp ./src/cpp/helpers/*.cpp -o ./test/exe -lm
    echo "Compilation completed."
fi

rm -r data/output/*

instancias=("TCC-Instancia-2018-1" "TCC-Instancia-2018-2" "TCC-Instancia-2019-1" "TCC-Instancia-2019-2" "TCC-Instancia-2022-1")
repts=(1 2 5 10)
qtd_turmas=(0 1 2 1000)
pesos_janela=(1 2 5)
pesos_sexto=(1 2 5)

for instancia in "${instancias[@]}"; do
    output_folder="data/output/$instancia"
    mkdir -p "$output_folder"
    echo "Instancia: $instancia"
    
    for qtd_turmas_value in "${qtd_turmas[@]}"; do
        for qtd_rept_value in "${repts[@]}"; do
            for peso_janela_value in "${pesos_janela[@]}"; do
                for peso_sexto_value in "${pesos_sexto[@]}"; do
                    subfolder_name="tamPop100-qtdTurmas${qtd_turmas_value}-Repts${qtd_rept_value}-Jan${peso_janela_value}-Sex${peso_sexto_value}"
                    subfolder_path="$output_folder/$subfolder_name"
                    
                    echo "Running iteration: $subfolder_name"
                    NOME_INSTANCIA="$instancia"
                    TAM_POPULACAO=100
                    QTD_TURMAS_HEURISTICA="$qtd_turmas_value"
                    QTD_REPT_HEURISTICA="$qtd_rept_value"
                    PESO_JANELA="$peso_janela_value"
                    PESO_SEXTO="$peso_sexto_value"
                    
                    echo "instancia: $NOME_INSTANCIA"
                    echo "qtd turmas heuristica: $QTD_TURMAS_HEURISTICA"
                    echo "qtd repet heuristica: $QTD_REPT_HEURISTICA"
                    echo "peso janela: $PESO_JANELA"
                    echo "peso sexto: $PESO_SEXTO"
                    
                    time ./test/exe "$NOME_INSTANCIA" "$TAM_POPULACAO" "$QTD_TURMAS_HEURISTICA" "$QTD_REPT_HEURISTICA" "$PESO_JANELA" "$PESO_SEXTO" >> data/output/debug-out.txt
                    
                    # Create the subfolder within the output folder
                    mkdir -p "$subfolder_path"
                    
                    # Move files to the subfolder if they exist
                    if [ -f "data/output/debug-out.txt" ]; then
                        mv "data/output/debug-out.txt" "$subfolder_path/"
                    fi
                    if [ -f "data/output/analise.csv" ]; then
                        mv "data/output/analise.csv" "$subfolder_path/"
                    fi
                    if [ -f "data/output/professor.tex" ]; then
                        mv "data/output/professor.tex" "$subfolder_path/"
                        (cd "$subfolder_path" && pdflatex -halt-on-error -output-directory . professor.tex)
                    fi
                    if [ -f "data/output/turma.tex" ]; then
                        mv "data/output/turma.tex" "$subfolder_path/"
                        (cd "$subfolder_path" && pdflatex -halt-on-error -output-directory . turma.tex)
                    fi
                done
            done
        done
    done
done
