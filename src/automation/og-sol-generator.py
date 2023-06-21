import pandas as pd
import re
import argparse


def pipe(args):

    path = args.instancia

    instancia = path.split("/")[-1]

    # Leitura do arquivo Excel
    df = pd.read_excel(path+"/"+instancia+".xls")

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
    df["PROFESSORES DO DIáRIO"].astype("str")
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

    janelas = 0
    sextos = 0

    for professor, matriz in matrizes.items():
        print(f"Matriz do Professor {professor}:")
        for dia in range(6):
            print("AAAAAAAAAAAAAAAAAAa",matriz[dia][5])
            if (matriz[dia][5] is not None) or (matriz[dia][11] is not None):
                sextos = sextos + 1
            for horario in range(16):
                print(matriz[dia][horario], end="\t")
            
            primeiro_slot = 0
            ultimo_slot = 0
            for slot in range(0,6):
                if (matriz[dia][slot] == None):
                    primeiro_slot = slot;
                    break

            for slot in range(5,0):
                
                if (matriz[dia][slot] == None):
                    ultimo_slot = slot;
                    break


            for slot in range(primeiro_slot + 1, ultimo_slot):
                if (matriz[dia][slot] == None):
                    janelas = janelas + 1;

            # Tarde
            primeiro_slot = 0;
            ultimo_slot = 0;

            for slot in range(7,12):
                if (matriz[dia][slot] == None):
                    primeiro_slot = slot;
                    break

            for slot in range(11,7):
                if (matriz[dia][slot] == None):
                    ultimo_slot = slot;
                    break


            for slot in range(primeiro_slot + 1, ultimo_slot):
                if (matriz[dia][slot] == None):
                    janelas = janelas + 1;

            # Noite
            primeiro_slot = 0;
            ultimo_slot = 0;

            for slot in range(13,16):
                if (matriz[dia][slot] == None):
                    primeiro_slot = slot;
                    break
            
            for slot in range(15,13):
                if (matriz[dia][slot] == None):
                    ultimo_slot = slot;
                    break


            for slot in range(primeiro_slot + 1, ultimo_slot):
                if (matriz[dia][slot] == None):
                    janelas = janelas + 1;
            print()
        print()

    for turma, matriz in matrizes.items():
        print(f"Matriz da Turma {turma}:")
        for dia in range(6):
            if (matriz[dia][5] is not None) or (matriz[dia][11] is not None):
                sextos = sextos + 1
            for horario in range(16):
                print(matriz[dia][horario], end="\t")
			# Manhã
            primeiro_slot = 0
            ultimo_slot = 0
            for slot in range(0,6):
                if (matriz[dia][slot] == None):
                    primeiro_slot = slot;
                    break

            for slot in range(5,0):
                
                if (matriz[dia][slot] == None):
                    ultimo_slot = slot;
                    break


            for slot in range(primeiro_slot + 1, ultimo_slot):
                if (matriz[dia][slot] == None):
                    janelas = janelas + 1;

            # Tarde
            primeiro_slot = 0;
            ultimo_slot = 0;

            for slot in range(7,12):
                if (matriz[dia][slot] == None):
                    primeiro_slot = slot;
                    break

            for slot in range(11,7):
                if (matriz[dia][slot] == None):
                    ultimo_slot = slot;
                    break


            for slot in range(primeiro_slot + 1, ultimo_slot):
                if (matriz[dia][slot] == None):
                    janelas = janelas + 1;

            # Noite
            primeiro_slot = 0;
            ultimo_slot = 0;

            for slot in range(13,16):
                if (matriz[dia][slot] == None):
                    primeiro_slot = slot;
                    break
            
            for slot in range(15,13):
                if (matriz[dia][slot] == None):
                    ultimo_slot = slot;
                    break


            for slot in range(primeiro_slot + 1, ultimo_slot):
                if (matriz[dia][slot] == None):
                    janelas = janelas + 1;
            print()
        print()
    gerar_tabela_laTeX(path + "/" + instancia + "-professores", matrizes, professores)
    gerar_tabela_laTeX(path + "/" + instancia + "-turma", matrizes, turmas)

    print(janelas)
    print(sextos)


def gerar_tabela_laTeX(nome, matrizes, vetor):
    dias_semana = ["SEG", "TER", "QUA", "QUI", "SEX", "SAB"]
    
    with open(nome + ".tex", "w") as arquivo:
        arquivo.write(r"\documentclass{article}" + "\n")
        arquivo.write(r"\usepackage[a4paper, landscape, margin=0.12cm]{geometry}" + "\n")
        arquivo.write(r"\usepackage[utf8]{inputenc} % Specify input encoding as UTF-8" + "\n")
        arquivo.write(r"\usepackage[T1]{fontenc} % Specify font encoding" + "\n")
        arquivo.write(r"\usepackage{array}"+"\n \n")

        arquivo.write(r"\begin{document}" + "\n")
        arquivo.write(r"\pagenumbering{gobble}" + "\n")
        arquivo.write(r"\newcolumntype{P}[1]{ >{\vbox to 5ex\bgroup\vfill\centering} p{#1} <{\egroup}}" + "\n")
        arquivo.write(r"\newcolumntype{C}[1]{ >{\vbox to 14.5ex\bgroup\vfill\centering} p{#1} <{\egroup}}" + "\n\n")

        for item in vetor:
            
            arquivo.write(r"\begin{tabular}{| C{0.78cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} | C{1.31cm} |}" +"\n")
            arquivo.write(r"\hline" + "\n")
            arquivo.write(r"\multicolumn{17}{|P{20.52cm}|}{"+ item + r"} \tabularnewline \hline" + "\n")
            arquivo.write(r"\footnotesize{Dia} & \footnotesize{07:30 - 08:20} & \footnotesize{08:20 - 09:10} & \footnotesize{09:20 - 10:10} & \footnotesize{10:10 - 11:00} & \footnotesize{11:00 - 11:50} & \footnotesize{11:50 - 12:40} & \footnotesize{13:30 - 14:20} & \footnotesize{14:20 - 15:10} & \footnotesize{15:20 - 16:10} & \footnotesize{16:10 - 17:00} & \footnotesize{17:00 - 17:50} & \footnotesize{17:50 - 18:40} & \footnotesize{18:50 - 19:40} & \footnotesize{19:40 - 20:30} & \footnotesize{20:40 - 21:30} & \footnotesize{21:30 - 22:20} \tabularnewline \hline" + "\n")

            for dia in range(6):
                arquivo.write(r"\textbf{" + dias_semana[dia] + "} ")
                for horario in range(16):
                    if matrizes[item][dia][horario] == None:
                        arquivo.write(r" & \tiny{} ")
                    else:
                        arquivo.write(r" & \tiny{ " + str(matrizes[item][dia][horario]) + r"} ")
                arquivo.write(r"\tabularnewline \hline" + "\n")

            arquivo.write(r"\end{tabular}" + "\n")
            arquivo.write(r"\newpage" + "\n")

        arquivo.write(r"\end{document}" + "\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--instancia', required=True, help='Nome da instância')
    args = parser.parse_args()
    pipe(args=args)