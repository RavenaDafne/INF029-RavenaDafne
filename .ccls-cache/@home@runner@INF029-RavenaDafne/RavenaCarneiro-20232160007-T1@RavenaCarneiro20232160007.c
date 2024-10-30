// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do
//  trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include "RavenaCarneiro20232160007.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y) {
  int soma;
  soma = x + y;
  return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x) {
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a) {
  int val;
  if (a == 2)
    val = 3;
  else
    val = 4;

  return val;
}
DataQuebrada quebraData(char data[]) {
    DataQuebrada dq;
    char sDia[3];
    char sMes[3];
    char sAno[5];
    int i = 0, j = 0;

    while (data[i] != '/' && data[i] != '\0') {
        sDia[j++] = data[i++];
    }
    sDia[j] = '\0';
    if (j == 0 || j > 2) {
        dq.valido = 0;
        return dq;
    }

    dq.iDia = atoi(sDia); 

    i++;
    j = 0;

    while (data[i] != '/' && data[i] != '\0') {
        sMes[j++] = data[i++];
    }
    sMes[j] = '\0';
    if (j == 0 || j > 2) {
        dq.valido = 0;
        return dq;
    }

    dq.iMes = atoi(sMes); 

    i++;
    j = 0;

    while (data[i] != '\0') {
        sAno[j++] = data[i++];
    }
    sAno[j] = '\0';
    if (j == 0 || j > 4) {
        dq.valido = 0;
        return dq;
    }

    dq.iAno = atoi(sAno); 

    if (dq.iAno < 0 || dq.iAno > 9999) {
        dq.valido = 0;
        return dq;
    }

    if (dq.iAno < 100) {
        if (dq.iAno >= 0 && dq.iAno <= 29) {
            dq.iAno += 2000; 
        } else {
            dq.iAno += 1900;
        }
    }

    dq.valido = 1;
    return dq;
}
/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia,
mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa
podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[]) {
  int datavalida = 1;
  DataQuebrada dataQuebrada = quebraData(data);
  if (dataQuebrada.valido == 0) {
    return 0;
  }

  if (dataQuebrada.iAno < 1900 || dataQuebrada.iAno > 9999) {
    return 0;
  }
  if (dataQuebrada.iMes < 1 || dataQuebrada.iMes > 12) {
    return 0;
  }
  int bissexto = 0;
  if ((dataQuebrada.iAno % 4 == 0 && dataQuebrada.iAno % 100 != 0) ||
      dataQuebrada.iAno % 400 == 0) {
    bissexto = 1;
  }

  int diasMes[12] = {31, 28 + bissexto, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (dataQuebrada.iDia < 1 ||
      dataQuebrada.iDia > diasMes[dataQuebrada.iMes - 1]) {
    return 0;
  }
  return 1;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal.
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis
 valores abaixo 1 -> cálculo de diferença realizado com sucesso 2 -> datainicial
 inválida 3 -> datafinal inválida 4 -> datainicial > datafinal Caso o cálculo
 esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos
 com os valores correspondentes.
 */
int ehBissexto(int ano) {
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        return 1; 
    } else {
        return 0; 
    }
}

DiasMesesAnos q2(char datainicial[], char datafinal[]) {
  DiasMesesAnos dma;

  if (q1(datainicial) == 0) {
    dma.retorno = 2;
    return dma;
  } else if (q1(datafinal) == 0) {
    dma.retorno = 3;
    return dma;
  }
  DataQuebrada dataInicial = quebraData(datainicial);
  DataQuebrada dataFinal = quebraData(datafinal);
  if (
    dataFinal.iAno < dataInicial.iAno || dataFinal.iAno == dataInicial.iAno  // ano final menor ou igual e
    && dataFinal.iMes < dataInicial.iMes || dataFinal.iAno == dataInicial.iAno // mes final menor ou ano igual e
    && dataFinal.iMes == dataInicial.iMes && dataFinal.iDia < dataInicial.iDia) {  // mes final igual a mes inicial e dia final menor que dia inicial
    dma.retorno = 4;
    return dma;
  }
  int bissextoInicial = ehBissexto(dataInicial.iAno);
  int bissextoFinal = ehBissexto(dataFinal.iAno);

  int diasMes[12];
    if (bissextoInicial == 0) {
      int diasMesInicial[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
      memcpy(diasMes, diasMesInicial, sizeof(diasMesInicial));
    } else {
      int diasMesInicial[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
      memcpy(diasMes, diasMesInicial, sizeof(diasMesInicial));
    }
  int qtdDias = 0, qtdMeses = 0, qtdAnos = 0;

  qtdAnos = dataFinal.iAno - dataInicial.iAno;

  qtdMeses = dataFinal.iMes - dataInicial.iMes;

    if (dataFinal.iDia < dataInicial.iDia) {
        qtdMeses--;
        if (qtdMeses < 0) {
            qtdAnos--;
            qtdMeses += 12;
        }
        int diasNoMesInicial = diasMes[dataInicial.iMes - 1];
        // Considerando ano bissexto se for fevereiro
        if (dataInicial.iMes == 2 && bissextoInicial) {
          diasNoMesInicial = 29; 
        }
        qtdDias = diasNoMesInicial - dataInicial.iDia + dataFinal.iDia;
    } else {
        qtdDias = dataFinal.iDia - dataInicial.iDia;
    }
  dma.retorno = 1;
  dma.qtdAnos = qtdAnos;
  dma.qtdMeses = qtdMeses;
  dma.qtdDias = qtdDias;

  return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa
 Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar
 diferenças entre maiúsculos e minúsculos. Se isCaseSensitive != 1, a pesquisa
 não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive) {
  int i;
  int qtdOcorrencias = 0;

if (isCaseSensitive == 1) {
  for (i = 0; texto[i] != '\0'; i++) {
    if (texto[i] == c) {
      qtdOcorrencias++;
          }
      }
  } else {
    char lower_c = c;
      if (c >= 'A' && c <= 'Z') {
          lower_c = c + ('a' - 'A');
      }

    for (i = 0; texto[i] != '\0'; i++) {
      char lower_texto = texto[i];
          if (texto[i] >= 'A' && texto[i] <= 'Z') {
              lower_texto = texto[i] + ('a' - 'A');
          }

          if (lower_texto == lower_c) {
              qtdOcorrencias++;
          }
      }
  }

  return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros
 (posicoes) que irá guardar as posições de início e fim de cada ocorrência da
 palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída
 correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do
 vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve
 ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a
 segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente.
 Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como
 há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da
 seguinte forma: posicoes[0] = 13; posicoes[1] = 16; Observe que o índice da
 posição no texto deve começar ser contado a partir de 1. O retorno da função,
 n, nesse caso seria 1;

 */
int ehCaractereAcentuado(unsigned char *strTexto, int posicao) {
  if (strTexto[posicao] == 0xC3 && (strTexto[posicao + 1] == 0xA1 || // á
                                    strTexto[posicao + 1] == 0xA9 || // é
                                    strTexto[posicao + 1] == 0xAD || // í
                                    strTexto[posicao + 1] == 0xB3 || // ó
                                    strTexto[posicao + 1] == 0xBA || // ú
                                    strTexto[posicao + 1] == 0xA2 || // â
                                    strTexto[posicao + 1] == 0xAA || // ê
                                    strTexto[posicao + 1] == 0xEE || // î
                                    strTexto[posicao + 1] == 0xF4 || // ô
                                    strTexto[posicao + 1] == 0xFB))  // û
  {
    return 1;
  }
  return 0;
}
int q4(char *strTexto, char *strBusca, int posicoes[30]) {
  int qtdOcorrencias = 0;
  int tamanhoTexto = strlen(strTexto);
  int tamanhoBusca = strlen(strBusca);
  for (int i = 0; i <= tamanhoTexto - tamanhoBusca; i++) {
    int j;
    for (j = 0; j < tamanhoBusca; j++) {
      if (strTexto[i + j] != strBusca[j]) {
        break;
      }
    }
    if (j == tamanhoBusca) {
      int inicio = i + 1;
      int fim = i + tamanhoBusca;
      for (int k = 0; k < i; k++) {
        if (ehCaractereAcentuado((unsigned char *)strTexto, k)) {
          inicio--;
          fim--;
        }
      }
      posicoes[qtdOcorrencias * 2] = inicio;
      posicoes[qtdOcorrencias * 2 + 1] = fim;
      qtdOcorrencias++;
    }
  }

  return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num) {
  int numberInvert = 0;
  while (num != 0) {
    int lastDig = num % 10;
    numberInvert = numberInvert * 10 + lastDig;
    num = num / 10;
  }

  return numberInvert;
}
/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */
int q6(int numerobase, int numerobusca) {
  int qtdOcorrencias = 0;
  int tempBase = numerobase;
  int tamanhoBusca = 0;
  int busca = numerobusca;
  while (busca != 0) {
    busca /= 10;
    tamanhoBusca++;
  }
  while (tempBase != 0) {
    int digitoBase = tempBase % 10;
    if (digitoBase == numerobusca % 10) {
      int divisor = 10;
      int tempBusca = numerobusca / 10;
      int tempBase2 = tempBase / 10;
      int coincide = 1;
      for (int i = 1; i < tamanhoBusca; i++) {
        if (tempBase2 % divisor != tempBusca % 10) {
          coincide = 0;
          break;
        }
        divisor *= 10;
        tempBusca /= 10;
        tempBase2 /= 10;
      }
      if (coincide) {
        qtdOcorrencias++;
      }
    }
    tempBase /= 10;
  }
  return qtdOcorrencias;
}
