#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"
//Estrutura principal, o qual atende 
int vetorPrincipal[TAM];
//Um vetor de ponteiros para armazenar as referências (endereços) das estruturas auxiliares alocadas dinamicamente.
int *estruturasAuxiliares[TAM] = {NULL};
//Armazena o tamanho atual de cada estrutura auxiliar, necessário para validar inserções e exclusões.
int tamanhoEstruturaAuxiliares[TAM] = {0};

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
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > TAM)
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

    if (ehPosicaoValida(posicao + 1) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }
    //validando o tamanho
    if(tamanho < 1){
        return TAMANHO_INVALIDO;
    }
    //verificando se ja tem estrutura auxiliar
    if(estruturasAuxiliares[posicao] != NULL){
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }
    //aloca memoria pra estruturas auxiliares
    estruturasAuxiliares[posicao] = (int*) malloc(tamanho * sizeof(int));
    if(estruturasAuxiliares[posicao] == NULL){
        return SEM_ESPACO_DE_MEMORIA;
    }

    tamanhoEstruturaAuxiliares[posicao] = tamanho;

    return SUCESSO;
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
    if(posicao < 0 || posicao > TAM ){
    return POSICAO_INVALIDA;
    }
    
    if (ehPosicaoValida(posicao + 1) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }
    // verificar se existe estrutura auxiliar na posicao
    if(estruturasAuxiliares[posicao] == NULL){
        return SEM_ESTRUTURA_AUXILIAR;   
    }
    //verificando se a espaço na estrutura auxiliar
    int tamanhoAtual =  tamanhoEstruturaAuxiliares[posicao];
    int qtdAtual = 0;
    
    //contando quantos elementos tem na estrutura auxiliar
    for(int i =0;i <tamanhoAtual; i++){
        if(estruturasAuxiliares[posicao][i] != 0){
            qtdAtual++;
        }
    }
    if(qtdAtual >= tamanhoAtual){
        return SEM_ESPACO;
    }
    for(int i = 0; i < tamanhoAtual;i++){
        if(estruturasAuxiliares[posicao][i] == 0){
            estruturasAuxiliares[posicao][i] =  valor;
            break;
        }
    }
    
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

    if (ehPosicaoValida(posicao + 1) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }
    //verifica se existe estrutura auxiliar na posicao
    if( estruturasAuxiliares[posicao] == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
     int tamanhoAtual =  tamanhoEstruturaAuxiliares[posicao];
     int qtdAtual= 0;

    for(int i = 0 ; i< tamanhoAtual - 1; i++){
        if(estruturasAuxiliares[posicao][i] != 0){
            qtdAtual++;
        }
    }

     if(qtdAtual == 0){
      return ESTRUTURA_AUXILIAR_VAZIA;
}
    //exclusao logica
    for( int i =  tamanhoAtual - 1; i>=0;i--){
        if(estruturasAuxiliares[posicao][i] != 0){
            estruturasAuxiliares[posicao][i] = 0;
            break;
        }
    }
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
    if (ehPosicaoValida(posicao + 1) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }
    int *estrutura = estruturasAuxiliares[posicao];
    
    if(estrutura == NULL){
        return SEM_ESTRUTURA_AUXILIAR;  
    }
    int tamanhoAtual =  tamanhoEstruturaAuxiliares[posicao];
    int *ptr = estrutura;
    int qtdAtual = 0;
    for(int i = 0; i<tamanhoAtual;i++){
        if(*ptr != 0){
            qtdAtual++;
        }
        ptr++;
    }
    if(qtdAtual == 0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    int encontrou =0;
    for(int i =0 ; i< tamanhoAtual-1; i++){
        if(*(estrutura + i) == valor){
            encontrou = 1;
            for(int j = 0; j <  tamanhoAtual-1;j++){
                *(estrutura + j) = *(estrutura + j + 1);
            }
            *(estrutura + tamanhoAtual-1) = 0;
            break;
        }
    }
    if(!encontrou){
        return NUMERO_INEXISTENTE;
    }
    
    return SUCESSO;
}


/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){
 posicao --;
   if(ehPosicaoValida(posicao + 1) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }
   if(estruturasAuxiliares[posicao] == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
   int *estrutura = estruturasAuxiliares[posicao];
   int tamanho = tamanhoEstruturaAuxiliares[posicao];
   if(tamanho > TAM){
    return TAM;
   }
   for(int i = 0; i<tamanho;i++){
        *(vetorAux + i) = *(estrutura + i);
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
    posicao --;
    if(ehPosicaoValida(posicao + 1) == POSICAO_INVALIDA) {
      return POSICAO_INVALIDA;
        }
    if(estruturasAuxiliares[posicao] == NULL){
      return SEM_ESTRUTURA_AUXILIAR;
        }
    int *estrutura = estruturasAuxiliares[posicao];
    int tamanho = tamanhoEstruturaAuxiliares[posicao];
    for(int i = 0; i<tamanho;i++){
        *(vetorAux + i) = *(estrutura + i);
        }
    for(int *i = vetorAux; i < vetorAux + tamanho -1; i++){
        for(int *j = i + 1; j < vetorAux + tamanho -1; j++){
        if(*i > *j){
            int temp = *i;
            *i = *j;
            *j = temp;
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
    int *ptrAux = vetorAux; // Ponteiro para rastrear a posicao atual da estrutura auxiliar
    int todasVazias = 1;
    //Rodando no vetor principal
    for(int i =  0; i< TAM; i++){
        if(estruturasAuxiliares[i] == NULL){
            todasVazias = 0;
            int *estrutura = estruturasAuxiliares[i];
            int tamanho = tamanhoEstruturaAuxiliares[i];
            //Rodando no vetor auxiliar
            for( int  *j = estrutura; j < estrutura + tamanho; j++){
                *ptrAux = *j;
                ptrAux++;
            }  
        }
    }
    if(todasVazias){
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    return SUCESSO;
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
    for(int i =0; i < TAM; i++){
        if(estruturasAuxiliares[i] != NULL){
            tamanhoTotal += tamanhoEstruturaAuxiliares[i];
        }
    }
    for(int *i = vetorAux; i < vetorAux + tamanhoTotal; i++){
        for(int *j = i +1; j< vetorAux + tamanhoTotal;j++){
            if(*i > *j){
                int temp = *i;
                *i = *j;
                *j = temp;
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
    posicao --;
    if(ehPosicaoValida(posicao + 1) ==  POSICAO_INVALIDA){
        return POSICAO_INVALIDA;
    }
    if(estruturasAuxiliares[posicao] == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    int tamanhoAtual =  tamanhoEstruturaAuxiliares[posicao];
    novoTamanho += tamanhoAtual;

    if(novoTamanho < 1){
        return NOVO_TAMANHO_INVALIDO;
    }
    int *novaEstrutura = realloc(estruturasAuxiliares[posicao],novoTamanho * sizeof(int));
    if(novaEstrutura == NULL){
        return SEM_ESPACO_DE_MEMORIA;
    }else{
    estruturasAuxiliares[posicao] = novaEstrutura;
    //Inicia os novos espaços adicionados na estrutura auxiliar com o valor 0;
    for( int i = tamanhoAtual; i <  novoTamanho; i++){
        novaEstrutura[i] = 0;
    }
    tamanhoEstruturaAuxiliares[posicao] =  novoTamanho;
    return SUCESSO;
    }
 
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
    if(ehPosicaoValida(posicao + 1) == POSICAO_INVALIDA){
        return POSICAO_INVALIDA;
    }
    if(estruturasAuxiliares[posicao] == NULL){
    return SEM_ESTRUTURA_AUXILIAR;
    }
    int *estrutura =  estruturasAuxiliares[posicao];
    int tamanho = tamanhoEstruturaAuxiliares[posicao];
    int qtd = 0;
     for( int *i = estrutura; i < estrutura+ tamanho; i++){
         if(*i!=0){
             qtd++;
         }
     }
    return qtd > 0 ? qtd : ESTRUTURA_AUXILIAR_VAZIA;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote(){
    No *cabecote = malloc(sizeof (No));

    if(cabecote == NULL){
    return NULL;
    }
    cabecote -> conteudo = 
    0; // SEM VALOR
    cabecote -> prox = NULL; //NAO A ELEMENTOS NA LISTA

    No * atual = cabecote;

    for(int i = 0; i < TAM; i++){
        if(estruturasAuxiliares[i] !=  NULL){
            int *estrutura =  estruturasAuxiliares[i];
            int tamanho =  tamanhoEstruturaAuxiliares[i];

            for( int *j = estrutura; j < estrutura + tamanho; j++){
                if( *j != 0){
                    No *novo  = malloc(sizeof(No));
                    if( novo == NULL){
                        destruirListaEncadeadaComCabecote(&cabecote);
                        return NULL;
                    }
                    novo-> conteudo =*j;
                    novo-> prox = NULL;
                    atual->prox =novo;
                    atual = novo;
                }
            }
        }
    }
    return cabecote;
    
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){
    if( inicio == NULL){
        return;
    }
    No *atual =  inicio -> prox;
    int i = 0;
     while( atual != NULL){
        vetorAux[i++] = atual ->conteudo;
         atual = atual->prox;
     }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio){
    if(*inicio == NULL){
        return;

    }
    No *atual = *inicio;
    No *proxNo;

    while(atual != NULL){
        proxNo = atual ->prox;
        free(atual);
        atual = proxNo;
    }
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar(){
  for(int i = 0; i< TAM; i++){
      estruturasAuxiliares[i] = NULL;
      tamanhoEstruturaAuxiliares[i] = 0;
  }  
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar(){
      for(int i = 0; i< TAM; i++){
          if(estruturasAuxiliares[i] != NULL){
          free(estruturasAuxiliares[i]);
          estruturasAuxiliares[i] = NULL; 
         }
    }  
}