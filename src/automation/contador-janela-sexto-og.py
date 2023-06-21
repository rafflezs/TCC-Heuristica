import re
import argparse

def count_sextos_janelas(file_path):
    with open(file_path, 'r') as file:
        tex_content = file.read()

    tables = re.findall(r'\\begin\{tabular\}.*?\\end\{tabular\}', tex_content, re.DOTALL)

    sextos = 0
    janelas = 0

    for table in tables:
        lines = table.strip().split('\n')
        headers = [header.strip() for header in lines[0].split('&')]
        row_indices = {header.upper(): i for i, header in enumerate(headers)}

        for line in lines[4:-1]:
            cells = [cell.strip() for cell in line.split('&')]
            day = cells[0]


            # SEXTO HORARIO
            if any(cells[1] or cells[7] ):
                sextos += 1

            # JANELA
            primeiro_slot = 0;
            ultimo_slot = 0;

            # Manhã
            for slot in range(1,6):
                if (r" \tiny{}  " not in cells[slot]):
                    primeiro_slot = slot;
                    break
            print(cells)
            for slot in range(7,1):
                print(cells[slot])
                if (r" \tiny{}  " not in cells[slot]):
                    ultimo_slot = slot;
                    break

            print("Manhã ",primeiro_slot, ultimo_slot)

            for slot in range(primeiro_slot + 1, ultimo_slot):
                if (r" \tiny{}  " in cells[slot]):
                    janelas = janelas + 1;

            # Tarde
            primeiro_slot = 0;
            ultimo_slot = 0;

            for slot in range(8,14):
                if (r" \tiny{}  " not in cells[slot]):
                    primeiro_slot = slot;
                    break

            for slot in range(15,8):
                if (r" \tiny{}  " not in cells[slot]):
                    ultimo_slot = slot;
                    break

            print("Tarde ",primeiro_slot, ultimo_slot)

            for slot in range(primeiro_slot + 1, ultimo_slot):
                if (r" \tiny{}  " in cells[slot]):
                    janelas = janelas + 1;

            # Noite
            primeiro_slot = 0;
            ultimo_slot = 0;

            for slot in range(14,17):
                if (r" \tiny{}  " not in cells[slot]):
                    primeiro_slot = slot;
                    break
            
            for slot in range(17,14):
                if (r" \tiny{}  " not in cells[slot]):
                    ultimo_slot = slot;
                    break

            print("Noite ",primeiro_slot, ultimo_slot)

            for slot in range(primeiro_slot + 1, ultimo_slot):
                if (r" \tiny{}  " in cells[slot]):
                    janelas = janelas + 1;
    
    print("Sextos horarios ",sextos)
    print("Janelas ",janelas)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--instancia', required=True, help='Nome da instância')
    args = parser.parse_args()
    file_path = args.instancia
    count_sextos_janelas(args.instancia)

