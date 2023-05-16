import subprocess, argparse

def convert_tex_to_pdf(tex_file_path):
    try:
        subprocess.run(['pdflatex', tex_file_path])
    except FileNotFoundError:
        print("LaTeX compiler (pdflatex) not found.")
    except subprocess.CalledProcessError as e:
        print(f"Error occurred while converting {tex_file_path} to PDF: {e}")

def tex_merger(tex_file_path):
    ## Implementar processo de merge e ajuste de celulas tex geradas
    print("")

if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('--file', required=True,help='Arquivo c++ (com path completo)')

    args = parser.parse_args()
    
    convert_tex_to_pdf(args.file)
