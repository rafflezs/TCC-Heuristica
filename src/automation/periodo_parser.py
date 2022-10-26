from ast import parse
import re

with open('data/automated_data/peirodo_input.txt', 'r') as file:
    # read a list of lines into data
    data = file.readlines()

for line in range(0, len(data)):
    parsed = data[line].replace("\n", "").split("\t")
    data[line] = parsed[1]
    parsed = parsed[0].split(".");
    if "1N" in parsed:
        data[line] = data[line] + " (Primeiro Noturno)\n"
    elif "2N" in parsed:
        data[line] = data[line] + " (Segundo Noturno)\n"
    elif "3N" in parsed:
        data[line] = data[line] + " (Terceiro Noturno)\n"
    elif "4N" in parsed:
        data[line] = data[line] + " (Quarto Noturno)\n"
    elif "5N" in parsed:
        data[line] = data[line] + " (Quinto Noturno)\n"
    elif "6N" in parsed:
        data[line] = data[line] + " (Sexto Noturno)\n"
    elif "7N" in parsed:
        data[line] = data[line] + " (Setimo Noturno)\n"
    elif "8N" in parsed:
        data[line] = data[line] + " (Oitavo Noturno)\n"
    elif "9N" in parsed:
        data[line] = data[line] + " (Nono Noturno)\n"
    elif "10N" in parsed:
        data[line] = data[line] + " (Decimo Noturno)\n"
    elif "1M" in parsed or "1" in parsed or "1V" in parsed or "1MV" in parsed:
        data[line] = data[line] + " (Primeiro Periodo)\n"
    elif "2M" in parsed or "2" in parsed or "2V" in parsed or "2MV" in parsed:
        data[line] = data[line] + " (Segundo Periodo)\n"
    elif "3M" in parsed or "3" in parsed or "3V" in parsed or "3MV" in parsed:
        data[line] = data[line] + " (Terceiro Periodo)\n"
    elif "4M" in parsed or "4" in parsed or "4V" in parsed or "4MV" in parsed:
        data[line] = data[line] + " (Quarto Periodo)\n"
    elif "5M" in parsed or "5" in parsed or "5V" in parsed or "5MV" in parsed:
        data[line] = data[line] + " (Quinto Periodo)\n"
    elif "6M" in parsed or "6" in parsed or "6V" in parsed or "6MV" in parsed:
        data[line] = data[line] + " (Sexto Periodo)\n"
    elif "7M" in parsed or "7" in parsed or "7V" in parsed or "7MV" in parsed:
        data[line] = data[line] + " (Setimo Periodo)\n"
    elif "8M" in parsed or "8" in parsed or "8V" in parsed or "8MV" in parsed:
        data[line] = data[line] + " (Oitavo Periodo)\n"
    elif "9M" in parsed or "9" in parsed or "9V" in parsed or "9MV" in parsed:
        data[line] = data[line] + " (Nono Periodo)\n"
    elif "10M" in parsed or "10" in parsed or "10V" in parsed or "10MV" in parsed:
        data[line] = data[line] + " (Decimo Periodo)\n"
    elif "11M" in parsed or "11" in parsed or "11V" in parsed or "11MV" in parsed:
        data[line] = data[line] + " (Decimo-Primeiro Periodo)\n"
    elif "12M" in parsed or "12" in parsed or "12V" in parsed or "12MV" in parsed:
        data[line] = data[line] + " (Decimo Segundo Periodo)\n"
    
    if "ESPECIAL" in parsed or "ESP" in parsed or "ESP" in parsed[len(parsed)-1] or "ESPECIAL" in parsed[len(parsed)-1]:
        data[line] = data[line] + " (Turma Especial)\n"
    elif "FERIAS" in parsed:
        data[line] = data[line] + " (Turma de Ferias)\n"

with open('data/automated_data/peirodo_output.txt', 'w+') as file:
    file.writelines(data)
