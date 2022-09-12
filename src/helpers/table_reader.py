import pandas as pd
import os
import re

##

def convert_file():
  os.chdir('data\instancias')
  for xls_file in os.listdir():
    folder_path = parse_directory(xls_file)
    for sheet_name, df in pd.read_excel(xls_file, index_col=0, sheet_name=None).items():
      df.to_csv (folder_path+sheet_name+".csv", sep=",",encoding='utf-8', index = False)

##

def parse_directory(file_name):
  dir_name = ""
  for s in re.findall(r'\b\d+-\d+\b', file_name):
    dir_name += s
  print(dir_name)
  if not os.path.exists('../csv/'+dir_name):
    os.makedirs('../csv/'+dir_name)
  return "../csv/"+dir_name+"/"
##

convert_file()