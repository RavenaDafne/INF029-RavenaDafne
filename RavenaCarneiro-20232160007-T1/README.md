# INF029-RavenaDafne

## Projeto 01

### Descrição
// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Ravena Dafne Costa Carneiro
//  email:ravena.dafne@gmail.com
//  Matrícula: 20232160007
//  Semestre: 2º

// #################################################
## Compilação

Para compilar o projeto, siga os passos abaixo:

1. Navegue até o diretório do projeto:

    ```bash
    cd RavenaCarneiro-20232160007-T1/
    ```

2. Execute o comando de compilação:

    ```bash
    gcc RavenaCarneiro20232160007.c novoCorretor.c -Wno-unused-result -o t1 && ./t1
    ```
   ```bash
   gcc RavenaCarneiro20232160007-Q7.c -Wno-unused-result -o t1 && ./t1
   ```
    ```bash
    gcc RavenaCarneiro20232160007-Q8.c -Wno-unused-result -o t1 && ./t1
    ```

## Lista

### 01 Questões
Faça um programa que valide uma data informada formato dd/mm/aaaa (d/m/aa, d/m/aaaa). As
seguintes datas são válidas: 02/03/2015, 12/1/15, 1/9/2016. Considere ano bissexto.

### 02 Questões
Faça um programa em que o usuário informa a sua data de aniversário, o programa deve:
a) Verificar se a data é válida (usar função da questão anterior);
b) Quantidade de anos, meses, e dias, até a data atual.

### 03 Questões
Faça um programa que o usuário informa um texto de até 250, e uma letra. O programa deve
informar quantas vezes essa letra aparece no texto. Desconsidere acentos nas vogais. Ou seja, um
'á' é igual a 'a'.

### 04 Questões
Faça um programa em que o usuário informa um texto de até 250, e uma palavra. O
programa deve informar a posição inicial e fim de todas as ocorrências da palavra no texto.

### 05 Questões(ok)
Faça uma função que permita inverter um número inteiro N. Ex:
• 456 – 654
• 5430 – 345
• 100 – 1

### 06 Questões (ok)
Escreva uma função que determine quantas vezes um número K (de qualquer quantidade de
dígitos) ocorre em um número natural N. Por exemplo:
• O número 3 ocorre quatro vezes em 3539343.
• O número 44 ocorre uma vez em 5444, e duas vezes em 54444
• O número 23 ocorre duas vezes em 1234562354

### 07 Questões
Fazer um programa que implementa o jogo da velha.
a) O programa deve sempre mostrar o tabuleiro do jogo da velha, com o jogador que deve
jogar, da seguinte forma:
Jogador 2, informe sua jogada:
b) Cada jogador (jogador 1 e jogador 2) terá sua vez de jogar. O jogador um tem a marca “X” e o
jogador 2 a marca “0”.
c) O jogador deve informar a célula de interesse: ex: B3. O programa deve verificar se é uma
célula válida
d) O programa deve informar qual foi o ganhador, ou se não houve ganhador

### 08 Questões
Faça um programa que implemente o jogo de batalha naval.
Ver o jogo em http://www.ludijogos.com/multiplayer/batalha-naval/
a) O número de navios de guerra deve ser um parâmetro global. Precisando aumentar a
quantidade de navios, o programador deve apenas mudar esse valor. b) Deve ter pelo menos 1
barco de tamanho 4, 1 de tamanho 3, 3 barcos de tamanho 1. Os demais barcos, se existirem
devem ser obrigatoriamente de tamanho 2. Desta forma, o número mínimo de barco é: 5 barcos.
c) O tabuleiro de cada jogador deve ser uma matriz 10 x 10. d) Cada jogador, no início do
jogo deve dizer onde vai posicionar, cada um dos seus barcos. O programa deve controlar se os
barcos estão posicionados de forma correta e) Use a seguinte configuração para representar o
mapa:
i. [ ] espaço em branco -> posição do mar sem nada (e.g. barco, tiro do oponente,
tiro do jogador.
ii. [ N ] Navio posicionado
iii. [ 0 ] Posição do navio abatida
iv. [ X ] Tiro inválido
f) O programa deve ter uma função para o jogador poder Listar o tabuleiro.
i. Em seu tabuleiro ele deve ver seus barcos, os tiros do oponente e os espaços em
branco.
ii. No tabuleiro do adversário deve ver seus tiros certeiros e seus tiros errados
g) O programa deve ter a função para o jogador atirar, onde ele deve escolher uma célula da
matriz para jogar.
h) Cada jogador joga uma vez, depois é a vez do oponente.
i) Vence o jogador que acertar todos os navios do oponente primeiro.