#ifndef STUDENT_H
#define STUDENT_H

#include "utils.h"

typedef struct Student {
    int id;
    char name[20];
    float score;
    struct Student *prev;
    struct Student *next;
} StuNode;

// 全局链表头指针，在main.c中定义
extern StuNode *stuHead;

StuNode *createStuNode(int id, const char *name, float score);
StuNode *addStudent(StuNode *head, int id, const char *name, float score);
StuNode *deleteById(StuNode *head, int id);
StuNode *findById(StuNode *head, int id);
void findByName(StuNode *head, const char *name);
void updateStudent(StuNode *node, const char *newName, float newScore);
int getLength(StuNode *head);
StuNode *insertAtPosition(StuNode *head, int pos, int id, const char *name, float score);
void freeList(StuNode *head);
void sortByScore(StuNode *head, int ascending);

#endif