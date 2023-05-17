import argparse
import os
import pandas


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--instancia', required=True, help='Arquivo c++ (com path completo)')

    args = parser.parse_args()

    instancia_folder = str(args.instancia).split(sep="/")[-1].split(sep='.')[0]

    # Create the instance folder if it doesn't exist
    instance_folder_path = os.path.join("data/csv", instancia_folder)
    if not os.path.exists(instance_folder_path):
        os.makedirs(instance_folder_path)

    for sheet_name, df in pandas.read_excel(args.instancia, index_col=0, sheet_name=None).items():
        csv_file_path = os.path.join(instance_folder_path, f"{sheet_name}.csv")
        df.to_csv(csv_file_path, sep=";", encoding='utf-8', index=True)
