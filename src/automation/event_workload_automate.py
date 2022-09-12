import io
from datetime import datetime, timedelta
import re
import math

with open('D:\Programacao\TCC\data\csv\horario_disciplina_input_20181.txt', 'r') as file:
    # read a list of lines into data
    if file.readline() == "HORáRIOS\n":
      print("ADWADAWD")
      next(file)
    data = file.readlines()
    
for line in range(0,len(data)):
  data[line] = re.sub('[\[\]\n\bSEG\b\bTER\b\bQUA\b\bQUI\b\bSEX\b\bSAB\b]', '', data[line])
  split_line = data[line].split()
  workload = 0
  for horario in split_line:
    h1 = re.split('~',horario)
    if (len(h1) > 1):
      t_delta = datetime.strptime(h1[1], '%H:%M') - datetime.strptime(h1[0], '%H:%M')
      to_minutes = t_delta.total_seconds() / 60
      workload += to_minutes
    else:
      workload = 0
  data[line] = str(math.ceil(workload / 50))+'\n'
  # print(data[line])
    
with open('D:\Programacao\TCC\data\\automated_data\horario_disciplina_out_20181.txt', 'w') as file:
    file.writelines(data)