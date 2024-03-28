#ifndef TRABALHO1_RAVENACARNEIRO20232160007_H
#define TRABALHO1_RAVENACARNEIRO20232160007_H

typedef struct DQ
{
    int iDia; 
    int iMes;
    int iAno;
    int valido; // 0 se inválido, e 1 se válido 

} DataQuebrada;

typedef struct Qtd
{
    int qtdDias;
    int qtdMeses;
    int qtdAnos;
    int retorno;

} DiasMesesAnos;

int somar(int x, int y); //função utilizada para testes
int fatorial(int x); //função utilizada para testes
int q1(char data[]);
DiasMesesAnos q2(char datainicial[], char datafinal[]);
int q3(char *texto, char c, int isCaseSensitive);
int q4(char *strTexto, char *strBusca, int posicoes[30]);
int q5(int num);
int q6(int numerobase, int numerobusca);
DataQuebrada quebraData(char data[]);

#endif  // TRABALHO1_RAVENACARNEIRO20232160007_H