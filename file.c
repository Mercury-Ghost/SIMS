#include "file.h"
#include <stdio.h>

/**
 * 从文本文件加载学生链表
 * @return 加载的学生链表头指针
 */
StuNode *loadStudentsFromTextFile() {
    FILE *fp = fopen("students.txt", "r");
    if (!fp) {
        // 文件不存在，返回空链表
        return NULL;
    }
    StuNode *head = NULL;
    StuNode *tail = NULL;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        int id;
        char name[20];
        float score;
        if (sscanf(line, "%d %s %f", &id, name, &score) == 3) {
            StuNode *newNode = createStuNode(id, name, score);
            if (!head) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    fclose(fp);
    return head;
}

/**
 * 从二进制文件加载学生链表
 * @return 加载的学生链表头指针
 */
StuNode *loadStudentsFromFile() {
    FILE *fp = fopen("students.dat", "rb");
    if (!fp) {
        // 二进制文件不存在，尝试从文本文件加载
        return loadStudentsFromTextFile();
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

/**
 * 保存学生链表到二进制文件
 * @param head 学生链表头指针
 */
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
    
    // 同时保存到文本文件，方便查看
    fp = fopen("students.txt", "w");
    if (fp) {
        cur = head;
        while (cur) {
            fprintf(fp, "%d %s %.2f\n", cur->id, cur->name, cur->score);
            cur = cur->next;
        }
        fclose(fp);
    }
}