from ast import parse
import re

with open('D:\Programacao\TCC\data\csv\\turma_turno_parse_input.txt', 'r') as file:
    # read a list of lines into data
    data = file.readlines()
    
for line in range(0,len(data)):
  parsed = data[line].replace("\n","").split(".")
  print(parsed)
  if parsed[len(parsed)-1] == "-":
    del parsed[-1]
  if parsed[len(parsed)-1].endswith("N"):
    data[line] = "Noite\n"
  elif parsed[len(parsed)-1].endswith("M"):
    data[line] = "Manhã\n"
  elif parsed[len(parsed)-1].endswith("V"):
    data[line] = "Tarde\n"
  else:
    data[line] = "Integral\n"
    
with open('D:\Programacao\TCC\data\\automated_data\\turma_turno_parse_out.txt', 'w+') as file:
    file.writelines(data)