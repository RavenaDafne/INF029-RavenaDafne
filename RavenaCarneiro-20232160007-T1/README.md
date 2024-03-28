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
    gcc RavenaCarneiro20232160007.c corretor.c -Wno-unused-result -o t1 && ./t1
    ```

## Funcionalidades

### Cadastro de Pessoas (alunos e professores)

- Criar, editar e excluir.
- Validação de campos como:
  - Nome: Capitalização automática, caracteres alfabéticos, ausência de espaços duplicados ou no início da palavra, entre outros.
  - Matrícula: Valores positivos não nulos, não repetição de matrículas já cadastradas, etc.
  - CPF: Verificação dos dígitos verificadores através de cálculo matemático, exemplos de CPFs válidos: 12345678909, 06077218049, 56040728000, entre outros.
  - Sexo: Capitalização automática (ex: 'm' ou 'M' são aceitos).
  - Data de nascimento: Coleta em formato dd/mm/aaaa, validação de limites (inclusive anos bissextos).
  - Idade (calculada através da data de nascimento): Validação de limites (idade mínima 5 anos e máxima 120 anos), entre outros.

### Cadastro de Matérias

- Criar, editar e excluir.
- Validação de campos como:
  - Nome: Mesmos critérios de validação utilizados para Pessoas.
  - Código e semestre: Positivos e não nulos.
  - Professor e Aluno: Cadastro de pessoas existentes e não cadastradas na respectiva matéria.

### Emissão de Relatórios

Além das funcionalidades de cadastro, o sistema permite a emissão de alguns relatórios.

###                                     Menus do Projeto 

Este é o ponto de entrada do sistema. Ele permite que o usuário acesse as diferentes funcionalidades disponíveis.

|             Menu Principal          |
|-------------------------------------|
|  0 - Sair                           |
|  1 - Cadastro de Aluno              |
|  2 - Cadastro de Professor          |
|  3 - Cadastro de Disciplina         |
|  4 - Relatórios                     |
=======================================

Cadastro de Aluno

Neste menu, o usuário pode realizar operações relacionadas aos alunos.

=======================================
|        Cadastro de Aluno            |
|-------------------------------------|
|  0 - Voltar                         |
|  1 - Cadastrar Aluno                |
|  2 - Atualizar Aluno                |
|  3 - Excluir Aluno                  |
=======================================

Cadastro de Professor

Aqui, o usuário pode gerenciar os professores cadastrados.


|       Cadastro de Professor         |
|-------------------------------------|
|  0 - Voltar                         |
|  1 - Cadastrar Professor            |
|  2 - Atualizar Professor            |
|  3 - Excluir Professor              |
=======================================


Cadastro de Disciplina

Este menu permite operações relacionadas às disciplinas.Cadastro de disciplina, professor e aluno na disciplina.

|      Cadastro de Disciplina         |
|-------------------------------------|
|  0 - Voltar                         |
|  1 - Cadastrar Disciplina           |
|  2 - Atualizar Disciplina           |
|  3 - Excluir Disciplina             |
=======================================


Relatórios

Neste menu, o usuário pode gerar diversos relatórios,listagens e filtragens com base nos dados armazenados.

|             Relatórios                 |
|----------------------------------------|
|  0 - Voltar                            |
|  1 - Listar Alunos                     |
|  2 - Listar Professores                |
|  3 - Listar Disciplinas                |
|  4 - Listar uma Disciplina             |
|  5 - Listar Alunos por Sexo            |
|  6 - Listar Alunos por Nome            |
|  7 - Listar Alunos por Data Nasc.      |
|  8 - Listar Professores por Sexo       |
|  9 - Listar Professores por Nome       |
| 10 - Listar Professores por Data Nasc. |
| 11 - Aniversariantes do Mês            |
| 12 - Lista de pessoas (professor/aluno)|
| 13 - Lista de Alunos < 3 Disciplinas   | 
| 14 - Lista de Disciplinas > 40 Vagas   |
=========================================
