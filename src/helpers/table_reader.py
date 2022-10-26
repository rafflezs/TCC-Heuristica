import pandas as pd
import os
import re
import unicodedata

##


def convert_file(dir, inp):
    os.chdir(dir)
    if inp == '*':
        for xls_file in os.listdir():
            folder_path = parse_directory(xls_file)
            for sheet_name, df in pd.read_excel(xls_file, index_col=0, sheet_name=None).items():
                df.to_csv(folder_path+sheet_name+".csv",
                          sep=";", encoding='utf-8', index=True)
    else:
        folder_path = parse_directory(inp)
        for sheet_name, df in pd.read_excel(inp, index_col=0, sheet_name=None).items():
            df.to_csv(folder_path+sheet_name+".csv",
                      sep=";", encoding='utf-8', index=True)
##


def parse_directory(file_name):
    dir_name = file_name.split(".")
    dir_name = dir_name[0]
    print("Diretorio da Instancia: " + dir_name)
    if not os.path.exists('../csv/'+dir_name):
        os.makedirs('../csv/'+dir_name)
    return "../csv/"+dir_name+"/"
##
