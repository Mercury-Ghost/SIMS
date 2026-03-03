#include "file.h"
#include <stdio.h>

StuNode *loadStudentsFromFile() {
    FILE *fp = fopen("students.dat", "rb");
    if (!fp) {
        // 文件不存在，返回空链表
        return NULL;
    }
    StuNode *head = NULL;
    StuNode *tail = NULL;
    while (1) {
        int id;
        char name[20];
        float score;
        size_t read = fread(&id, sizeof(int), 1, fp);
        if (read != 1) break;
        fread(name, sizeof(char), 20, fp);
        fread(&score, sizeof(float), 1, fp);
        StuNode *newNode = createStuNode(id, name, score);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    fclose(fp);
    return head;
}

void saveStudentsToFile(StuNode *head) {
    FILE *fp = fopen("students.dat", "wb");
    if (!fp) {
        printf("无法打开学生文件保存！\n");
        return;
    }
    StuNode *cur = head;
    while (cur) {
        fwrite(&cur->id, sizeof(int), 1, fp);
        fwrite(cur->name, sizeof(char), 20, fp);
        fwrite(&cur->score, sizeof(float), 1, fp);
        cur = cur->next;
    }
    fclose(fp);
}