Semana 2 (07/03/2023)
    0. Gerar __output__ em \LaTeX\ (se vira aí pra fazer essa porra) [__DONE__]
    1. Gerar funções de avaliação [__DONE__]
        a. Janela
            Percorrer lista dos professores
        b. Sexto Horário
            Percorrer lista das turmas
    2. Gerar método de ordenação (case 6 : random_sort) em Heuristica::construtiva [__DONE]
    3. Gerar método da heuristica construtiva alocando dias aleatórios [__DONE]
        a. Trabalhar com 2 métodos de construtiva

Semana 3 (21/03/2023)
    0. Melhorar tabelas LaTeX (Geometry e afins)
    1. Na função objetivo, utilizar enumeradores de pesos [__TESTAR]
        - Os pesos devem ser atribuidos por pipeline em tempo de execução [__DONE]
        - Os pesos devem atribuidos na função Heuristica::avaliar_solucao() [__DONE]
        - Caso não definidos, atribuir um peso __DEFAULT__ = 1 [__DONE]
        - Atribuir o valor de janelas e sextos horarios na solucao Solucao::m_* [__DONE]
    2. Implementar Heuristicas de Melhoria
        - Busca Local
        - Metodo aleatorio: selecionar uma turma, destruir o horario e realocar.


___
Ponto de melhoria: implementar randomização e classificação na ordenação das disciplinas
    - Ex: ao gerar a order de disciplinas por professores com mais carga horario, separar os professores em grupos e realizar um shuffle nesses grupos, e concatena-los em seguida.