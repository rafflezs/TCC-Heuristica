import os
from helpers import table_reader as tb


print("\033[95mSelecione a instância à ser trabalhada\033[0m\n")
for i, folder in enumerate(os.listdir("data\\instancias\\")):
  print(f"[{i}] {folder}")

inp = input("Digite a instancia à ser executada: ")

tb.convert_file("data\\instancias\\", inp)