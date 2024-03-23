// Ravena e Maria, esse aqui é o main com tudo junto, mas eu comecei a separacao dos arquivos. Tem o person.c, person.h, common.c, common.h. O outro main (em minuscuslo) ja esta em conformidade com os arquivos que eu mencionei, ou seja, compilando eles e o main.c, funciona normalmente.
// Ou seja, esse Main.c a gente exclui quando tiver migrado cada coisa pra seu devido lugar kk. Eu ia fazer a separacao de tudo e exluir, mas como Ravena surgeriu seria bom voces treinarem include. Acho que ravena vai separar as funções de menu em outro arquivo e organizar os respectivos includes. Maria voce poderia fazer para Subject, dai se quiser ver como eu fiz e tenta replicar. Qualquer duvida a gente vai se comunicando. Mas tentem fazer isso logo para a gente continuar fazendo as funcoes que faltam. 
// Atualizei o README.md, com os comandos para compilação, quando fizerem a separacao editem la tambem

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MAX_STUDENTS_CLASS 3
#define MAX_LETTERS 32

#define MAX_STUDENTS 2
#define MAX_TEACHERS 2
#define MAX_SUBJECTS 2

typedef struct {
  int regist, age, birth[3];
  char gender;
  char name[MAX_LETTERS], cpf[13];
} Person;

typedef struct {
  char name[MAX_LETTERS];
  int code, period;
  int number_of_students;
  Person students[MAX_STUDENTS_CLASS];
  Person teacher;
} Subject;

Person students[MAX_STUDENTS];
Person teachers[MAX_TEACHERS];
Subject subjects[MAX_SUBJECTS];
int numberOfStudents = 0;
int numberOfTeachers = 0;
int numberOfSubjects = 0;

// Utilizada para remover a quebra de linha (\n) da string, que eh registrada pelo fgets
// Usar apos o uso do fgets
void cleanNewLine(char *string){
  int i = 0;
  while(string[i] != '\0'){
    if(string[i] == '\n'){
      string[i] = '\0';
    }
    i++;
  }
}

// Utilizada para limpar o buffer (stdin) e remover possiveis quebra de linha deixadas pelo scanf, e que podem ser lidas erroneamente pelo fgets
// Usar apos um scanf, ou antes de um fgets. Usar APENAS caso tenha certeza que um \n foi deixado no buffer
void cleanStream(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

// utilizada para converter uma regiao de uma string para inteiro, retorna -1 caso a regiao da string contenha qualquer caractere que nao seja um numero
int convertStrToInt(const char* array, int start, int end){
  int value = 0;
  for(int i = end; i >= start; i--){
    int equivalentInt = array[i] - '0';
    if(equivalentInt < 0 || equivalentInt > 9){
      return -1;
    }
    value += equivalentInt * pow(10, end - i);
  }
  return value;
}

// utilizada para validar uma data no formato dd/mm/aaaa, retorna true caso a data seja valida, false caso contrario. Caso seja valida escreve a data no parametro birth
// birth deve ter ao menos 3 posicoes, e birthStr ao menos 10 posicoes
bool validateBirth(int* birth, char* birthStr){
  int daysByMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  //Valida o formato XX/XX/XXXX
  if(birthStr[2] != '/' || birthStr[5] != '/'){
    printf("Digite uma data valida dd/mm/yyyy, formato invalido\n");
    return false;
  }

  int day = convertStrToInt(birthStr, 0, 1);
  int month = convertStrToInt(birthStr, 3, 4);
  int year = convertStrToInt(birthStr, 6, 9);
  if(day == -1 || month == -1 || year == -1){
    printf("Digite uma data valida, caracteres nao numericos encontrados\n");
    return false;
  }
  // Valida o ano

  // Valida o mes
  if(month < 1 || month > 12){
    printf("Mês invalido!\n");
    return false;
  }
  int lastTwoDigitsYear = year % 100;
  if(lastTwoDigitsYear == 0){
    if(year % 400 == 0){
      daysByMonth[1] = 29;
    }
  }
  else if(lastTwoDigitsYear % 4 == 0){
    daysByMonth[1] = 29;
  }
  // Valida o dia
  if(day < 1 || day > daysByMonth[month - 1]){
    printf("Dia invalido!\n");
    return false;
  }

  birth[0] = day;
  birth[1] = month;
  birth[2] = year;
  return true;
}

bool validateCpf(const char *cpf){
  int i, j, num1 =0, num2 = 0;

  //Checa se todos os caracteres de um vetor sao iguais
  for (i = 1; i < 11; i++) {
      if (cpf[i] != cpf[0]) {
          break;
      }
  }
  if (i == 11) {
      return false;  
  }
  if (strlen(cpf) != 11) {
      return false;
  }
  //Validação do primeiro dígito: Primeiramente multiplica-se os 9 primeiros dígitos pela sequência decrescente de números de 10 à 2 e soma os resultados.
  for(i = 0; i < strlen(cpf)-2; i++){
    //num1 += (cpf[i]-48) * j; // convertendo cada caractere para int
    num1 += convertStrToInt(cpf, i , i) * (10 - i);
  }
  num1 %= 11;
  if(num1 < 2){
      num1 = 0;
  }
  else{
      num1 = 11 - num1;
    if(convertStrToInt(cpf, 9, 9) != num1){
      return false;
      //Validação do segundo dígito: Primeiramente multiplica-se os 10 primeiros dígitos pela sequência decrescente de números de 11 à 2 e soma os resultados.
   }else {
    for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--)
      num2 += convertStrToInt(cpf, i, i+1) * j;
      num2 %= 11;
  } if(num2 < 2){
          num2 = 0;
  }else{
          num2 = 11 - num2;
      if(convertStrToInt(cpf, 10, 10) != num2)
          return false;
     }
   }
  return true;

}

// Cadastrar
// utilizada para criar um struct do tipo Person, e preencher seus campos com os dados fornecidos pelo usuario.
Person createPerson(){
  Person person;
  printf(" === Cadastro de Pessoa === \n");
  printf("Digite o nome: ");
  cleanStream();
  fgets(person.name, MAX_LETTERS, stdin);
  cleanNewLine(person.name);
  printf("Digite o numero de matricula: ");
  (void)scanf("%d", &person.regist);

  printf("Digite a idade: ");
  (void)scanf("%d", &person.age);
  printf("Digite o sexo(M/F): ");
  (void)scanf(" %c", &person.gender);
  // 12 (10 da data, mais 1 do \n e mais 1 do \0)
  char birthStr[12];
  cleanStream();
  do{
    printf("Digite a data de nascimento no formato dd/mm/aaaa: ");
    fgets(birthStr, 12, stdin);
    cleanNewLine(birthStr);
    printf("\n");
  } while(validateBirth(person.birth, birthStr) == false);
  printf("Cadastro realizado com sucesso!\n");
  return person;
}

//Utilizada para adicionar um struct do tipo Person a um vetor dado
void addPerson(Person* persons, int* actualSize, int maxSize){
  if(*actualSize == maxSize){
    printf("Nao e possivel adicionar mais pessoas.\n");
    return;
  }
  Person person = createPerson();
  persons[(*actualSize)++] = person;
}

// Listar
// utilizada para listar os dados de um struct do tipo Person que esteja em um vetor
void listPersons(Person* persons, int actualSize){
  if(actualSize == 0){
    printf("Nao ha pessoas cadastradas.\n");
    return;
  }

  for(int i = 0; i < actualSize; i++){
    printf("Pessoa %d\n", i+1);
    printf("Nome: %s\n", persons[i].name);
    printf("Matricula: %d\n", persons[i].regist);
    printf("Idade: %d\n", persons[i].age);
    printf("Sexo: %c\n", persons[i].gender);
    printf("Data de nascimento: %02d/%02d/%d\n", persons[i].birth[0], persons[i].birth[1], persons[i].birth[2]);
    
    printf("\n");
  }
}


/*void addStudentOnClass(Subject* sub, Person student){
  int i;
  for(i = 0; i < MAX_STUDENTS_CLASS; i++){
    if(sub->students[i].is_registered == false){
      student.is_registered = true;
      sub->students[i] = student;
      break;
    }
  }
  if(i == MAX_STUDENTS){
    printf("Não tem vagas disponíveis para o aluno %s.\n", student.name);
  }
}
*/

//Menu's
//submenu para cadastrar aluno
void registerStudentMenu(){
  int chat;
  while(true){
    printf("=== Registro de aluno ===\n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar novo aluno.\n");
    printf("2 - Atualizar dados de um aluno.\n");
    printf("3 - Excluir um aluno.\n");
    printf("4 - Inserir aluno em uma disciplina.\n");
    printf("5 - Remover aluno de uma disciplina.\n");
    printf("Digite: ");
    scanf("%d", &chat);
    system("clear");
    printf("\n");
    if(chat == 0){
      return;
    }
    switch(chat){
      case 1:
        addPerson(students, &numberOfStudents, MAX_STUDENTS);
        break;
      //case 2:
        //updateStudent();
    }

  }
}

void registerTeacherMenu(){
  int chat;
  while(true){
    printf("=== Registro de Professor ===\n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar novo Professor.\n");
    printf("2 - Atualizar dados de um professor.\n");
    printf("3 - Remover aluno de uma disciplina.\n");
    printf("Digite: ");
    scanf("%d", &chat);
    system("clear");
    printf("\n");
    if(chat == 0){
      return;
    }
    switch(chat){
      case 1:
        addPerson(teachers, &numberOfTeachers, MAX_TEACHERS);
        break;
      //case 2:
        //updateTeacher();
    }

  }
}

//submenu para cadastrar disciplina
void registerSubjectMenu(){
  int chat;
  while(true){
    printf("=== Registro de Disciplina ===\n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Disciplina.\n");
    printf("2 - Atualizar Discplina\n");
    printf("3 - Excluir disciplina.\n");
    printf("Digite: ");
    scanf("%d", &chat);
    system("clear");
    printf("\n");
    if(chat == 0){
      return;
    }
    switch(chat){
      case 1:
        //addSubject();
        break;
      //case 2:
        //updateSubject();
    }
  }
}



//submenu para relatorios
void reportMenu(){
  int chat;
  while(true){
    printf("=== Relatorios ===\n");
    printf("0 - Voltar\n");
    printf("1 - Listar alunos.\n");
    printf("2 - Listar professores.\n");
    printf("Digite: ");
    scanf("%d", &chat);
    system("clear");
    printf("\n");
    if(chat == 0){
      return;
    }
    switch(chat){
      case 1:
        printf("=== Lista de Alunos ===\n");
        listPersons(students, numberOfStudents);
        break;
      case 2:
        printf("=== Lista de Professores ===\n");
        listPersons(teachers, numberOfTeachers);
        break;
    }
  }
}

int main() {
  // temporario: pedir ao usuario a data de hoje
  int today[3];
  char todayStr[12];
  do{
    printf("Digite a data de hoje no formato dd/mm/aaaa: ");
    fgets(todayStr, 12, stdin);
    cleanNewLine(todayStr);
    printf("\n");
  } while(validateBirth(today, todayStr) == false);
  int chat;
  while(true){
    printf("=== Bem vindo ao chat da escola! ===\n");
    printf("0 - Sair\n");
    printf("1 - Cadastrar aluno\n");
    printf("2 - Cadastrar professor\n");
    printf("3 - Cadastrar disciplina\n");
    printf("4 - Relatorios\n");
    printf("Digite: ");
    scanf("%d", &chat);
    system("clear");
    printf("\n");
    if(chat == 0){
      break;
    }
    switch(chat){
      case 1:
        registerStudentMenu();
        break;
      case 2:
        registerTeacherMenu();
        break;
      case 4:
        reportMenu();
        break;
    }
  }

  return 0;
}