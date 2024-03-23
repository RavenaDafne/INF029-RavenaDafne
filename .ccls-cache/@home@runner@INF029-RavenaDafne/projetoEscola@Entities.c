#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_STUDENTS_CLASS 3
#define MAX_LETTERS 32

#define MAX_STUDENTS 2
#define MAX_TEACHERS 2
#define MAX_SUBJECTS 2

typedef struct {
  int regist, age, birth[3];
  char gender, cpf[11];
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

int validateCpf(char *cpf){
  int i, j, num1 =0, num2 = 0;

  //Checa se todos os caracteres de um vetor sao iguais
  for (i = 1; i < 11; i++) {
      if (cpf[i] != cpf[0]) {
          break;
      }
  }if (i == 11) {
      return 0;  
  } if (strlen(cpf) != 11) {
      return 0;
  }else{
    //Validação do primeiro dígito: Primeiramente multiplica-se os 9 primeiros dígitos pela sequência decrescente de números de 10 à 2 e soma os resultados.
    for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--)
      //num1 += (cpf[i]-48) * j; // convertendo cada caractere para int
      num1 += convertStrToInt(cpf, i , i+1) *j;
      num1 %= 11;
    if(num1 < 2){
        num1 = 0;
    }else{
        num1 = 11 - num1;
      if(convertStrToInt(cpf, 9, 9) != num1){
        return 0;
        //Validação do segundo dígito: Primeiramente multiplica-se os 10 primeiros dígitos pela sequência decrescente de números de 11 à 2 e soma os resultados.
     } else {
      for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--)
         /// num2 += (cpf[i]-48) * j;
        num2 += convertStrToInt(cpf, i, i+1) * j;
        num2 %= 11;
    } if(num2 < 2){
            num2 = 0;
    }else{
            num2 = 11 - num2;
        if(convertStrToInt(cpf, 10, 10) != num2)
            return 0;
       }
     }
    return 1;
  }
}

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









