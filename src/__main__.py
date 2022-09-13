import os

print("\033[95mSelecione a instância à ser trabalhada\033[0m\n")
for i, folder in enumerate(os.listdir("data\\csv\\")):
  print(f"[{i}] {folder}")

inp = input("Digite a instancia à ser executada: ")

os.chdir("data\\csv\\"+ inp + "\\")
print(os.getcwd())