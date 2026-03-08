#ifndef STUDENT_H
#define STUDENT_H

#include "utils.h"

// 学生节点结构体
typedef struct Student {
    int id;             // 学号
    char name[20];      // 姓名
    float score;        // 成绩
    struct Student *prev; // 前一个节点指针
    struct Student *next; // 后一个节点指针
} StuNode;

// 全局链表头指针，在main.c中定义
extern StuNode *stuHead;

// 创建学生节点
StuNode *createStuNode(int id, const char *name, float score);
// 添加学生到链表末尾
StuNode *addStudent(StuNode *head, int id, const char *name, float score);
// 根据学号删除学生
StuNode *deleteById(StuNode *head, int id);
// 根据学号查找学生
StuNode *findById(StuNode *head, int id);
// 根据姓名模糊查找学生
void findByName(StuNode *head, const char *name);
// 更新学生信息
void updateStudent(StuNode *node, const char *newName, float newScore);
// 获取链表长度
int getLength(StuNode *head);
// 在指定位置插入学生
StuNode *insertAtPosition(StuNode *head, int pos, int id, const char *name, float score);
// 释放链表内存
void freeList(StuNode *head);
// 按成绩排序
void sortByScore(StuNode *head, int ascending);
// 多条件查询学生
StuNode *queryStudents(StuNode *head, const char *name, int minId, int maxId, float minScore, float maxScore);
// 按指定字段排序查询结果
void sortQueryResults(StuNode *head, const char *field, int ascending);

#endif