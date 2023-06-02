typedef struct analise
{
    int id_solucao;
    float peso_janela;
    float peso_sexto;
    int qtd_janela;
    int qtd_sexto;
    // (qtd_janela * peso_janela);
    // (qtd_sexto_horario * peso_sexto);
    int t_iteracao;
    int t_case_construtiva;
    // since(t_tempo_inicial_solucao).count ;
    float valor_solucao;
} Analise;
