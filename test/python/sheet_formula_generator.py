with open('./data/csv/disciplina_turno_formula.txt', 'w+') as file:
  for i in range (2,105):
    file.write('=ÍNDICE(Turmas!D2:D104;CORRESP(E'+str(i)+';Turmas!A2:A104;0))\n')