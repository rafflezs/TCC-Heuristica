import argparse, pandas



if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('--instancia', required=True,help='Arquivo c++ (com path completo)')
  
  args = parser.parse_args()

  instancia_folder = str(args.instancia).split(sep="/")[-1].split(sep='.')[0]
  for sheet_name, df in pandas.read_excel(args.instancia, index_col=0, sheet_name=None).items():
    df.to_csv("data/csv/"+instancia_folder+sheet_name+".csv", sep=";", encoding='utf-8', index=True)
