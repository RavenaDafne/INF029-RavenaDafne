#ifndef DATABASE_H
#define DATABASE_H
#include "person.h"
#include "subject.h"

#define MAX_STUDENTS 200
#define MAX_TEACHERS 20
#define MAX_SUBJECTS 10

typedef struct DataBase{
    Person students[MAX_STUDENTS];
    Person teachers[MAX_TEACHERS];
    Subject subjects[MAX_SUBJECTS];
    int studentsCount;
    int teachersCount;
    int subjectsCount;
} DataBase;

void saveDataBaseToFile(DataBase *db, const char* arqDados);
void readDataBaseFromFile(DataBase *db, const char* arqDados);


#endif