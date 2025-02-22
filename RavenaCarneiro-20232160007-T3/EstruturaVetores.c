    #include <stdio.h>
    #include <stdlib.h>
    #define TAM 10

    #include "EstruturaVetores.h"
    //Estrutura principal, o qual atende 
    EstruturaAuxiliar *vetorPrincipal[TAM] = {NULL};

    EstruturaAuxiliar *criarEstruturaAux(int tam){
        EstruturaAuxiliar *aux = malloc(sizeof(EstruturaAuxiliar));
        if(aux ==  NULL){
            return NULL;
        }
        aux -> vetor =  malloc(tam * sizeof(int));
        aux -> pos =-1;
        aux -> tam = tam;

        return aux;
    }
void carregarDados(const char *trabalho2) {
    FILE *arquivo = fopen("mainTeste.c", "r"); // Usando modo "r" para ler texto
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para carregar os dados\n");
        return;
    }
    for (int i = 0; i < TAM; i++) {
        int tam;
        fscanf(arquivo, "%d", &tam); // Lendo o tamanho da estrutura
        if (tam > 0) {
            vetorPrincipal[i] = criarEstruturaAux(tam);
            if (vetorPrincipal[i] == NULL) {
                printf("Erro ao alocar memória para estrutura auxiliar!\n");
                fclose(arquivo);
                return;
            }
            for (int j = 0; j < tam; j++) {
                fscanf(arquivo, "%d", &vetorPrincipal[i]->vetor[j]); // Lendo os valores
            }
            vetorPrincipal[i]->pos = tam - 1;
        } else {
            vetorPrincipal[i] = NULL;
        }
    }
    fclose(arquivo);
    printf("Dados carregados com sucesso\n");
}

void salvarDados(const char *trabalho2) {
    FILE *arquivo = fopen("saida.txt", "w"); // Usando modo "w" para salvar texto
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados\n");
        return;
    }

    // Salvar dados do vetor principal
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            fprintf(arquivo, "Vetor Principal %d: ", i + 1);
            fprintf(arquivo, "%d ", vetorPrincipal[i]->tam); // Salvando tamanho
            for (int j = 0; j <= vetorPrincipal[i]->pos; j++) {
                fprintf(arquivo, "%d ", vetorPrincipal[i]->vetor[j]); // Salvando os valores
            }
            fprintf(arquivo, "\n");
        }
    }

    // Salvar dados das estruturas auxiliares
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            EstruturaAuxiliar *aux = vetorPrincipal[i];
            for (int j = 0; j <= aux->pos; j++) {
                // Salvando os valores e a posição de início para cada estrutura auxiliar
                fprintf(arquivo, "Estrutura Auxiliar %d - Valor: %d, Posição: %d\n", i + 1, aux->vetor[j], j);
            }
        }
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso\n");
}

    void destruirEstruturaAuxiliar(EstruturaAuxiliar *aux){
    if(  aux!= NULL){
        free(aux -> vetor);
        free(aux);
        }

    }

    int checarVazia(EstruturaAuxiliar aux){
        return aux.pos == -1;
        }

    int checarCheia(EstruturaAuxiliar aux){
        return aux.pos == aux.tam -1;
    }

    /*
    Objetivo: criar estrutura auxiliar na posição 'posicao'.
    com tamanho 'tamanho'

    Rertono (int)
        SUCESSO - criado com sucesso
        JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
        SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
        TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
    */
    // se posição é um valor válido {entre 1 e 10}
    int ehPosicaoValida(int posicao){
        int retorno = 0;
        if (posicao < 1 || posicao >= TAM)
        {
            retorno = POSICAO_INVALIDA;
        }
        else
            retorno = SUCESSO;

        return retorno;
    }
    void dobrar(int *x){
        if(x != NULL){
            *x = *x * 2;
        }
    }
    int criarEstruturaAuxiliar(int posicao, int tamanho){
        //ajustando o indice
        posicao --;
        // validando tamanho
        if (tamanho < 1) {
            return TAMANHO_INVALIDO;
        }

        //validando posicao
        if(posicao < 0 || posicao >= TAM){
            return POSICAO_INVALIDA;
        }

        //verificando se ja tem estrutura auxiliar
        if(vetorPrincipal[posicao] != NULL){
            return JA_TEM_ESTRUTURA_AUXILIAR;
        }
        //aloca memoria pra estruturas auxiliares 
        EstruturaAuxiliar *aux = criarEstruturaAux(tamanho);

        if(aux == NULL){
            return SEM_ESPACO_DE_MEMORIA;
        }
        vetorPrincipal[posicao] = aux;
        return vetorPrincipal[posicao] == NULL ? SEM_ESPACO_DE_MEMORIA : SUCESSO;
    }

    /*
    Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
    Rertono (int)
        SUCESSO - inserido com sucesso
        SEM_ESPACO - não tem espaço
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    CONSTANTES
    */
    int inserirNumeroEmEstrutura(int posicao, int valor){
        posicao --;
        if(posicao < 0 || posicao >= TAM ){
        return POSICAO_INVALIDA;
        }
        
        EstruturaAuxiliar *aux = vetorPrincipal[posicao];
        // verificar se existe estrutura auxiliar na posicao
        if(aux == NULL){
            return SEM_ESTRUTURA_AUXILIAR;   
        }

        if(checarCheia(*aux)){
            return SEM_ESPACO;
        }

        //incremento antes a posição e colocou o valor depois naquela posicao
        aux -> vetor[++aux->pos] = valor;
        
        return SUCESSO;
    }

    /*
    Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
    ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
    Obs. Esta é uma exclusão lógica

    Rertono (int)
        SUCESSO - excluido com sucesso
        ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    */
    int excluirNumeroDoFinaldaEstrutura(int posicao){
        
        //ajustar a posicao do vetor
        posicao --;
        EstruturaAuxiliar *aux =  vetorPrincipal[posicao];
        if(posicao < 0 || posicao >= TAM ){
        return POSICAO_INVALIDA;
        }

        if(aux == NULL){
            return SEM_ESTRUTURA_AUXILIAR;
        }
        if(checarVazia(*aux)){
        return ESTRUTURA_AUXILIAR_VAZIA;
        }
        aux->pos--;

            return SUCESSO;  

    }

    /*
    Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
    Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
    ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
    Obs. Esta é uma exclusão lógica
    Rertono (int)
        SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
        ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        NUMERO_INEXISTENTE - Número não existe
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

    */
    int excluirNumeroEspecificoDeEstrutura(int posicao, int valor){
        posicao --;
        EstruturaAuxiliar *aux =  vetorPrincipal[posicao];
        if(posicao < 0 || posicao >= TAM ){
        return POSICAO_INVALIDA;
        }

        if(aux == NULL){
            return SEM_ESTRUTURA_AUXILIAR;
        }

        if(checarVazia(*aux)){
        return ESTRUTURA_AUXILIAR_VAZIA;
        }

        int x = 0;
        int achou = 0;

        while(x <= aux->pos){
        if(achou){
            aux -> vetor[x -1] = aux-> vetor[x];
        }else if( aux-> vetor[x] == valor){
            achou =1;
            }
        x++;
        } 
        if(achou){
            aux->pos--;
            return SUCESSO;
                    }else{   return NUMERO_INEXISTENTE;
            }
    }

    /*
    Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.o0s números devem ser armazenados em vetorAux

    Retorno (int)
        SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    */
    int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    posicao --;
    if(posicao < 0 || posicao >= TAM) {
            return POSICAO_INVALIDA;
        }
        EstruturaAuxiliar *aux =  vetorPrincipal[posicao];

    if(aux == NULL){
            return SEM_ESTRUTURA_AUXILIAR;
    }
        int i = 0;
        while( i <= aux-> pos){
        vetorAux[i]  =  aux->vetor[i];
        i++;
        }
        return SUCESSO;
    }


    /*
    Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
    os números devem ser armazenados em vetorAux

    Rertono (int)
        SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    */
    int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){
        int checar = getDadosEstruturaAuxiliar(posicao, vetorAux);
            if(checar != SUCESSO){
                return checar;
            }
        
        EstruturaAuxiliar *aux =  vetorPrincipal[posicao - 1];

        for(int i= 0; i <= aux->pos; i++){
            for( int j = i + 1; j <= aux->pos;j++){
                if( vetorAux[j] <  vetorAux[i]){
                int temporaria =  vetorAux[i];
                vetorAux[i] =  vetorAux[j];
                vetorAux[j] = temporaria;  
                }
            }
        }
            return SUCESSO;
    }

    /*
    Objetivo: retorna os números de todas as estruturas auxiliares.
    os números devem ser armazenados em vetorAux

    Rertono (int)
        SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
        TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
        */
        int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]){
        int *inicioAux = vetorAux;
        for( int i = 0;  i < TAM; i++){
            EstruturaAuxiliar *aux =  vetorPrincipal[i];
            if( aux != NULL && !checarVazia(*aux)){
                getDadosEstruturaAuxiliar(i + 1,vetorAux);
                vetorAux += aux->pos + 1;
            }
        }
        if(inicioAux == vetorAux){
            return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
        }else{

            return SUCESSO;
            }
        }
        /*
        Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
        os números devem ser armazenados em vetorAux

        Rertono (int)
            SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
            TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
        */
        int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){
        int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
            if(retorno != SUCESSO){
                return retorno;
            }

            int tamanhoTotal = 0;
            for(int i = 0; i < TAM; i++){
                EstruturaAuxiliar *aux =  vetorPrincipal[i];
                if(aux != NULL && !checarVazia(*aux)){
                    tamanhoTotal += aux->pos + 1;
                }
            }
            for(int a = 0 ;a < tamanhoTotal -1; a++){
                for(int b = a + 1 ; b < tamanhoTotal; b++){
                    if(vetorAux[b]< vetorAux[a]){
                        int temporaria = vetorAux[a];
                        vetorAux[a] = vetorAux[b];
                        vetorAux[b] = temporaria;
                    }
                }
            }
            return SUCESSO;

        }

    /*
    Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
    Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

    Rertono (int)
        SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
        NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
        SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
    */
    int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){
        
        if(posicao < 1 || posicao >= TAM){
            return POSICAO_INVALIDA;
        }
        posicao --;
        EstruturaAuxiliar *aux =  vetorPrincipal[posicao];

        if(vetorPrincipal[posicao] == NULL){
            return SEM_ESTRUTURA_AUXILIAR;
        }
        int  tamanhoAtualizado =  aux->tam + novoTamanho;

        if(tamanhoAtualizado < 1){
            return NOVO_TAMANHO_INVALIDO;
        }
        int *atualizandoEstrutura = realloc(aux->vetor,tamanhoAtualizado*sizeof(int));
        if(atualizandoEstrutura  == NULL){
            return SEM_ESPACO_DE_MEMORIA;
        }
        aux->vetor =  atualizandoEstrutura;

        if( tamanhoAtualizado < aux->tam){
            aux->pos =  tamanhoAtualizado -1;
        }
        if (tamanhoAtualizado < aux->pos + 1) {
        aux->pos = tamanhoAtualizado - 1;   
        }
        aux->tam = tamanhoAtualizado;

        return SUCESSO;
    
    }

    /*
    Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

    Retorno (int)
        POSICAO_INVALIDA - posição inválida
        SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
        ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
        Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
    */
    int getQuantidadeElementosEstruturaAuxiliar(int posicao){
    posicao --;
    EstruturaAuxiliar *aux =  vetorPrincipal[posicao];
        if(posicao <= 0 || posicao >= TAM){
            return POSICAO_INVALIDA;
        }
        if(aux== NULL){
            return SEM_ESTRUTURA_AUXILIAR;
        }
        if(checarVazia(*aux)){
            return ESTRUTURA_AUXILIAR_VAZIA;
        }
    
        return aux->pos +1;

    }

    No * criandoNo(int valor){
        No *no  = malloc(sizeof(No));
        no->conteudo = valor;
        no->prox = NULL;
        return no;

    }

    /*
    Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

    Retorno (No*)
        NULL, caso não tenha nenhum número nas listas
        No*, ponteiro para o início da lista com cabeçote
    */
    No *montarListaEncadeadaComCabecote(){
        No *cabecote =  criandoNo(0);
        No *temp = NULL;

        for(int i = 0 ;  i < TAM; i++){
            EstruturaAuxiliar *aux =  vetorPrincipal[i];
            if( aux != NULL && !checarVazia(*aux)){
            int l = 0;
            while( l <= aux->pos){
                int valor =  aux->vetor[l];
                if(temp ==  NULL){
                temp =  criandoNo(valor);
                cabecote->prox = temp;
                }else{
                    temp->prox = criandoNo(valor);
                    temp =  temp->prox;
                }
                l++;
            }
            }
        }
        return cabecote->prox != NULL ? cabecote->prox : NULL;

    }

    /*
    Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
    Retorno void
    */
    void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){
    int i  =0;
        while( inicio != NULL){
            vetorAux[i] = inicio->conteudo;
            inicio = inicio->prox;
            i++;
        }
    }

    /*
    Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
    O ponteiro inicio deve ficar com NULL.

    Retorno 
        void.
    */
    void destruirListaEncadeadaComCabecote(No **inicio){
        if(inicio != NULL){
        while(*inicio != NULL){
            No *temp = *inicio;
            *inicio = (*inicio)->prox;
            free(temp);
            }
        }   
    }

    /*
    Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

    */

    void inicializar() {
        for (int i = 0; i < TAM; i++) {
            vetorPrincipal[i] = NULL;
        }
    }


    /*
    Objetivo: finaliza o programa. deve ser chamado ao final do programa 
    para poder liberar todos os espaços de memória das estruturas auxiliares.

    */

    void finalizar() {
        for (int i = 0; i < TAM; i++) {
            if (vetorPrincipal[i] != NULL) {
                free(vetorPrincipal[i]->vetor);  // Libera o vetor auxiliar
                free(vetorPrincipal[i]);        // Libera a estrutura auxiliar
                vetorPrincipal[i] = NULL;       // Evita acessos inválidos
            }
        }
    }