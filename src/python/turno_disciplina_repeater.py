with open('D:\Programacao\TCC\data\\automated_data\disciplina_turno_formula.txt', 'w+') as file:
  for i in range (2,700):
    file.write('=ÍNDICE(Turmas!C2:C106;CORRESP(D'+str(i)+';Turmas!A2:A106;0))\n')