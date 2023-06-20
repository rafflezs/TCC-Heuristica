#!/bin/bash

# Change directory to data/og-horarios

# Iterate over subdirectories
for folder in data/og-sol/*; do
    echo "$folder"
    if ls "$folder"/*.tex >/dev/null 2>&1; then
        rm -f "$folder"/*.tex
    fi
    if ls "$folder"/*.pdf >/dev/null 2>&1; then
        rm -f "$folder"/*.pdf
    fi
    # rm "$folder/*.tex"
    python3 src/automation/og-sol-generator.py --instancia="$folder"
    for file in $(find "$folder" -name "*.tex"); do
        echo "$file"
        pdflatex -halt-on-error -output-directory $folder $file
    done
    if ls "$folder"/*.log >/dev/null 2>&1; then
        rm -f "$folder"/*.log
    fi
    if ls "$folder"/*.aux >/dev/null 2>&1; then
        rm -f "$folder"/*.aux
    fi
    echo ""
done
