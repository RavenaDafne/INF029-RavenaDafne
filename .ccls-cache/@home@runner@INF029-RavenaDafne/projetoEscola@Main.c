#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_STUDENTS_CLASS 3
#define MAX_LETTERS 32

#define MAX_STUDENTS 2
#define MAX_TEACHERS 2
#define MAX_SUBJECTS 2

typedef struct {
  int regist, age, birth[3], cpf;
  char gender;
  char name[MAX_LETTERS];
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

int* validateBirth(char* birthStr){
  int birth[3];

  for(int i = 0; i < 11; i++){
    int equivalentInt = birthStr[i] - '0';
    // '/' - '0' = -1
    if((i == 2 || i == 5) && equivalentInt != -1){
      printf("Por favor digite a data de nascimento no formato dd/mm/aaaa\n");
      return birth;
    }
    else if(equivalentInt >= 0 && equivalentInt <= 9){

    }
    if(i < 2){
      birth[0] += equivalentInt * pow(10, i - 1);
    }
  }
}

// Cadastrar 
Person createPerson(){
  Person person;
  printf(" === Cadastro de Pessoa === \n");
  printf("Digite o nome: ");
  scanf("%s", person.name);
  printf("Digite o numero de matricula: ");
  scanf("%d", &person.regist);
  printf("Digite a idade: ");
  scanf("%d", &person.age);
  printf("Digite o sexo(M/F): ");
  scanf(" %c", &person.gender);
  printf("Digite a data de nascimento no formato dd/mm/aaaa: ");
  char birthStr[11];
  scanf("%s", birthStr);
  int* validatedBirth = validateBirth(birthStr);
  for (int i = 0; i < 3; ++i) {
      person.birth[i] = validatedBirth[i];

  }
  printf("\n");
  return person;
}

void addPerson(Person* persons, int* actualSize, int maxSize){
  if(*actualSize == maxSize){
    printf("Nao e possivel adicionar mais pessoas.\n");
    return;
  }
  Person person = createPerson();
  persons[(*actualSize)++] = person;
};

// Listar
void listPersons(Person* persons, int actualSize){
  if(actualSize == 0){
    printf("Nao ha pessoas cadastradas.\n");
    return;
  }

  for(int i = 0; i < actualSize; i++){
    printf("Pessoa %d\n", i+1);
    printf("Nome: %s\n", persons[i].name);
    printf("Regist: %d\n", persons[i].regist);
    printf("Idade: %d\n", persons[i].age);
    printf("Sexo: %c\n", persons[i].gender);
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