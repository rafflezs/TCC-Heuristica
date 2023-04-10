#include "../src/cpp/public/public_includes.hpp"
#include "../src/cpp/engine/heuristica.hpp"
#include "../src/cpp/helpers/gravar-arquivo.hpp"

int main(int argc, char **argv)
{
    std::string nome_instancia(argv[1]);
    int tam_pop = std::stoi(argv[2]);
    float peso_janela = std::stof(argv[3]);
    float peso_sexto = std::stof(argv[4]);

    // std::string filePath = "/home/rafflezs/TCC-Heuristica/data/csv/" + nome_instancia + "/Cursos.csv";
    // std::ifstream file(filePath);
    // if (file.good()) {
    //     std::cout << "File exists and is readable" << std::endl;
    // } else {
    //     std::cout << "File does not exist or is not readable" << std::endl;
    // } 

    srand(time(0));
    // Instancia inst = Instancia(nome_instancia);
    // inst.print_instancia();

    // Solucao sol = Solucao(nome_instancia, {});
    // sol.exibir_solucao();

    std::cout << "argc: " << (argc) << std::endl;
    for (int c = 0; c < argc; c++)
        printf("arg[%d]: <%s> %s\n", c, typeid(argv[c]).name(), argv[c]);

    Heuristica h = Heuristica(nome_instancia, tam_pop);
    h.heuristica_construtiva();
    printf("\n\n\n\n\n\nSOLUCOES ENCONTRADAS\n\n");
    h.exibir_solucoes();

    // printf("Avaliando Solucoes Inicial\n");
    // h.avaliar_solucoes(peso_janela, peso_sexto);
    
    // printf("Iniciando Pos-processamento\n");
    // h.pos_processamento();

    // printf("\nAvaliando Solucoes Pos\n");
    // h.avaliar_solucoes(peso_janela, peso_sexto);

    // printf("\n\nGravando Saida\n");
    // GravarArquivo ga = GravarArquivo();
    // ga.salvar_solucao_prof("data/output/test.tex", h.get_solucao(1));
    
    printf("Encerrando Programa\n");
    return 0;
}