import pandas as pd

instancia = "TCC-Instancia-2018-1"

# Leitura do arquivo Excel
df = pd.read_excel("data/og-horarios/"+instancia+".xls")

# Lista de dias da semana
dias_semana = ["SEG", "TER", "QUA", "QUI", "SEX", "SAB"]

# Dicionários de horários por período
horarios = {
    "Manhã": ["07:30 - 08:19", "08:20 - 09:09", "09:20 - 10:09", "10:10 - 10:59", "11:00 - 11:49", "11:50 - 12:39"],
    "Tarde": ["13:30 - 14:19", "14:20 - 15:09", "15:20 - 16:09", "16:10 - 16:59", "17:00 - 17:49", "17:50 - 18:39"],
    "Noite": ["18:50 - 19:39", "19:40 - 20:29", "20:40 - 21:29", "21:30 - 22:19"]
}

# Obtenção de professores e turmas únicos
professores = df["PROFESSOR PRINCIPAL"].unique().tolist()
turmas = df["TURMA"].unique().tolist()

# Dicionários de horários dos professores e turmas
horarios_professores = {professor: {dia: [""] * 16 for dia in dias_semana} for professor in professores}
horarios_turmas = {turma: {dia: [""] * 16 for dia in dias_semana} for turma in turmas}

# Preenchimento dos horários dos professores e turmas
for _, row in df.iterrows():
    professor = row["PROFESSOR PRINCIPAL"]
    turma = row["TURMA"]
    horario = row["HORÁRIOS"]
    dia = horario.split(" ")[0]
    intervalo = horario.split(" ")[1][1:-1]  # Remover colchetes
    inicio, fim = intervalo.split("~")
    inicio_horario = next((i for i, h in enumerate(horarios.values()) if inicio in h), -1)
    fim_horario = next((i for i, h in enumerate(horarios.values()) if fim in h), -1)
    if inicio_horario != -1 and fim_horario != -1:
        horarios_professores[professor][dia][inicio_horario] = row["COMPONENTE CURRICULAR"]
        horarios_turmas[turma][dia][inicio_horario] = row["COMPONENTE CURRICULAR"]

# Gerar arquivo .tex
with open("data/og-output-latex/"+instancia+"/horarios.tex", "w") as f:
    f.write(r"\documentclass{article}" + "\n")
    f.write(r"\usepackage[a4paper, landscape, margin=0.12cm]{geometry}" + "\n")
    f.write(r"\usepackage{array}" + "\n")
    f.write(r"\begin{document}" + "\n")
    f.write(r"\pagenumbering{gobble}" + "\n")
    f.write(r"\newcolumntype{P}[1]{ >{\vbox to 5ex\bgroup\vfill\centering} p{#1} <{\egroup}}" + "\n")
    f.write(r"\newcolumntype{C}[1]{ >{\vbox to 14.5ex\bgroup\vfill\centering} p{#1} <{\egroup}}" + "\n")
    f.write(r"\begin{tabular}{| C{0.78cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} |}" + "\n")
    f.write(r" \hline" + "\n")
    f.write(r" \multicolumn{17}{|P{20.52cm}|}{ \bfseries EDGAR PEREIRA DOS SANTOS } \tabularnewline \hline" + "\n")
    f.write(r"\bfseries Dia  & \bfseries 07:30 \\ - \\ 08:20 & \bfseries 08:20 \\ - \\ 09:10 & \bfseries 09:20 \\ - \\ 10:10 & \bfseries 10:10 \\ - \\ 11:00 & \bfseries 11:00 \\ - \\ 11:50 & \bfseries 11:50 \\ - \\ 12:40 & \bfseries 13:30 \\ - \\ 14:20 & \bfseries 14:20 \\ - \\ 15:10 & \bfseries 15:20 \\ - \\ 16:10 & \bfseries 16:10 \\ - \\ 17:00 & \bfseries 17:00 \\ - \\ 17:50 & \bfseries 17:50 \\ - \\ 18:40 & \bfseries 18:50 \\ - \\ 19:40 & \bfseries 19:40 \\ - \\ 20:30 & \bfseries 20:40 \\ - \\ 21:30 & \bfseries 21:30 \\ - \\ 22:20 \tabularnewline \hline" + "\n")
    for dia in dias_semana:
        f.write(r"\bfseries " + dia + r" &")
        for horario in horarios.values():
            if "EDGAR PEREIRA DOS SANTOS" in horarios_professores and dia in horarios_professores["EDGAR PEREIRA DOS SANTOS"] and horario in horarios_professores["EDGAR PEREIRA DOS SANTOS"][dia]:
                disciplina_professor = horarios_professores["EDGAR PEREIRA DOS SANTOS"][dia][horario]
            else:
                disciplina_professor = ""
            if "02CDC20I.3IESP" in horarios_turmas and dia in horarios_turmas["02CDC20I.3IESP"] and horario in horarios_turmas["02CDC20I.3IESP"][dia]:
                disciplina_turma = horarios_turmas["02CDC20I.3IESP"][dia][horario]
            else:
                disciplina_turma = ""
            f.write(r" \tiny " + disciplina_professor + r" \\ - \\ " + disciplina_turma + r" &")
        f.write(r" \tabularnewline \hline" + "\n")
    f.write(r"\end{tabular}" + "\n")
    f.write(r"\newpage" + "\n")
    f.write(r"\end{document}" + "\n")
