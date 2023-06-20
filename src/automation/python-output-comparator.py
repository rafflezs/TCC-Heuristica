import pandas as pd
import re

instancia = "TCC-Instancia-2019-2"

# Leitura do arquivo Excel
df = pd.read_excel("data/og-horarios/"+instancia+"/"+instancia+".xls")

# Lista de dias da semana
dias_semana = ["SEG", "TER", "QUA", "QUI", "SEX", "SAB"]
dias_semana_num = {"SEG": 0, "TER" : 1, "QUA" : 2, "QUI" : 3, "SEX" : 4, "SAB" : 5}

# Dicionários de horários por período
horarios_periodo = {
    "Manhã": ["07:30~08:19", "08:20~09:09", "09:20~10:09", "10:10~10:59", "11:00~11:49", "11:50~12:39"],
    "Tarde": ["13:30~14:19", "14:20~15:09", "15:20~16:09", "16:10~16:59", "17:00~17:49", "17:50~18:39"],
    "Noite": ["18:50~19:39", "19:40~20:29", "20:40~21:29", "21:30~22:19"]
}

horarios_fixos = ["07:30~08:19", "08:20~09:09", "09:20~10:09", "10:10~10:59", "11:00~11:49", "11:50~12:39", "13:30~14:19", "14:20~15:09", "15:20~16:09", "16:10~16:59", "17:00~17:49", "17:50~18:39", "18:50~19:39", "19:40~20:29", "20:40~21:29", "21:30~22:19"]

# Obtenção de professores e turmas únicos
professores = df["PROFESSORES DO DIáRIO"].apply(lambda x: x.split(";")[0].strip()).unique().tolist()
turmas = df["TURMA"].unique().tolist()

matrizes = {}
for professor in professores:
    matrizes[professor] = [[None] * 16 for _ in range(6)]

for turma in turmas:
    matrizes[turma] = [[None] * 16 for _ in range(6)]

for index, row in df.iterrows():
    # codigo = row['CóDIGO']
    nome_disc = row['COMPONENTE CURRICULAR']
    turma = row['TURMA']
    professor = row['PROFESSORES DO DIáRIO'].split(";")[0].strip()
    horarios_str = row['HORáRIOS']
    horarios = re.findall(r"\w+\s\d{2}:\d{2}~\d{2}:\d{2}", horarios_str)

    for horario in horarios:
        dia, horario_intervalo = horario.split(" ")
        dia_index = dias_semana_num[dia]
        horario_inicio, horario_fim = horario_intervalo.split("~")
        periodo = ""

        # Determinar o período (manhã, tarde ou noite) com base no horário de início
        index = 0
        for i in range(0,16):
            if horario_inicio in horarios_fixos[i]:
                index = i
                break
        # Determinar o índice do horário na matriz com base no horário de início
        
        # Preencher a matriz com as informações da disciplina
        matrizes[professor][dia_index][index] = nome_disc
        matrizes[turma][dia_index][index] = nome_disc

# for professor, matriz in matrizes.items():
#     print(f"Matriz do Professor {professor}:")
#     for dia in range(6):
#         for horario in range(16):
#             print(matriz[dia][horario], end="\t")
#         print()
#     print()

# for turma, matriz in matrizes.items():
#     print(f"Matriz da Turma {turma}:")
#     for dia in range(6):
#         for horario in range(16):
#             print(matriz[dia][horario], end="\t")
#         print()
#     print()


def gerar_tabela_laTeX(nome, matriz, vetor):
    dias_semana = ["SEG", "TER", "QUA", "QUI", "SEX", "SAB"]
    horarios = ["07:30 - 08:20", "08:20 - 09:10", "09:20 - 10:10", "10:10 - 11:00", "11:00 - 11:50", "11:50 - 12:40", "13:30 - 14:20", "14:20 - 15:10", "15:20 - 16:10", "16:10 - 17:00", "17:00 - 17:50", "17:50 - 18:40", "18:50 - 19:40", "19:40 - 20:30", "20:40 - 21:30", "21:30 - 22:20"]
    
    with open(nome + ".tex", "w") as arquivo:
        arquivo.write(r"\documentclass{article}" + "\n")
        arquivo.write(r"\usepackage[a4paper, landscape, margin=0.12cm]{geometry}" + "\n")
        arquivo.write(r"\usepackage{array}" + "\n")
        arquivo.write(r"\begin{document}" + "\n")
        arquivo.write(r"\pagenumbering{gobble}" + "\n")
        arquivo.write(r"\newcolumntype{P}[1]{ >{\vbox to 5ex\bgroup\vfill\centering} p{#1} <{\egroup}}" + "\n")
        arquivo.write(r"\newcolumntype{C}[1]{ >{\vbox to 14.5ex\bgroup\vfill\centering} p{#1} <{\egroup}}" + "\n")

        for item in vetor:
            arquivo.write(r"\begin{tabular}{| C{0.78cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} |} " +"\n")
            arquivo.write(r"\hline" + "\n")
            arquivo.write(r"\multicolumn{17}{|P{20.52cm}|}{ \bfseries " + item +" } \tabularnewline \hline " + "\n")
            arquivo.write(r"\bfseries Dia  & \bfseries 07:30 \\ - \\ 08:20 & \bfseries 08:20 \\ - \\ 09:10 & \bfseries 09:20 \\ - \\ 10:10 & \bfseries 10:10 \\ - \\ 11:00 & \bfseries 11:00 \\ - \\ 11:50 & \bfseries 11:50 \\ - \\ 12:40 & \bfseries 13:30 \\ - \\ 14:20 & \bfseries 14:20 \\ - \\ 15:10 & \bfseries 15:20 \\ - \\ 16:10 & \bfseries 16:10 \\ - \\ 17:00 & \bfseries 17:00 \\ - \\ 17:50 & \bfseries 17:50 \\ - \\ 18:40 & \bfseries 18:50 \\ - \\ 19:40 & \bfseries 19:40 \\ - \\ 20:30 & \bfseries 20:40 \\ - \\ 21:30 & \bfseries 21:30 \\ - \\ 22:20 \tabularnewline \\hline" + "\n")

            for dia in range(6):
                arquivo.write(r"\textbf{" + dias_semana[dia] + "} ")
                for horario in range(16):
                    arquivo.write(f" & \\tiny {matrizes[item][dia][horario]}")
                arquivo.write(r"\tabularnewline \hline" + "\n")

            arquivo.write(r"\end{tabular}" + "\n")
            arquivo.write(r"\newpage" + "\n")

        arquivo.write(r"\end{document}" + "\n")

gerar_tabela_laTeX("data/og-horarios/" + instancia + "/" + instancia + "-professores", matrizes, professores)
gerar_tabela_laTeX("data/og-horarios/" + instancia + "/" + instancia + "-turma", matrizes, turmas)