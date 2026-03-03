#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StuNode *createStuNode(int id, const char *name, float score) {
    StuNode *newNode = (StuNode*)malloc(sizeof(StuNode));
    if (!newNode) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->id = id;
    strncpy(newNode->name, name, 19);
    newNode->name[19] = '\0';
    newNode->score = score;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

StuNode *addStudent(StuNode *head, int id, const char *name, float score) {
    StuNode *newNode = createStuNode(id, name, score);
    if (head == NULL) {
        return newNode;
    }
    StuNode *cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = newNode;
    newNode->prev = cur;
    return head;
}

StuNode *deleteById(StuNode *head, int id) {
    StuNode *cur = head;
    while (cur) {
        if (cur->id == id) {
            if (cur->prev) cur->prev->next = cur->next;
            else head = cur->next; // 删除头节点
            if (cur->next) cur->next->prev = cur->prev;
            free(cur);
            printf("学号 %d 已删除。\n", id);
            return head;
        }
        cur = cur->next;
    }
    printf("未找到学号 %d。\n", id);
    return head;
}

StuNode *findById(StuNode *head, int id) {
    StuNode *cur = head;
    while (cur) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

void findByName(StuNode *head, const char *name) {
    StuNode *cur = head;
    int found = 0;
    while (cur) {
        if (strstr(cur->name, name) != NULL) {
            printf("学号: %d, 姓名: %s, 成绩: %.2f\n", cur->id, cur->name, cur->score);
            found = 1;
        }
        cur = cur->next;
    }
    if (!found) printf("未找到姓名包含 '%s' 的学生。\n", name);
}

void updateStudent(StuNode *node, const char *newName, float newScore) {
    if (node) {
        strncpy(node->name, newName, 19);
        node->name[19] = '\0';
        node->score = newScore;
        printf("信息更新成功。\n");
    }
}

int getLength(StuNode *head) {
    int cnt = 0;
    StuNode *cur = head;
    while (cur) {
        cnt++;
        cur = cur->next;
    }
    return cnt;
}

StuNode *insertAtPosition(StuNode *head, int pos, int id, const char *name, float score) {
    if (pos < 1 || pos > getLength(head) + 1) {
        printf("位置无效。\n");
        return head;
    }
    StuNode *newNode = createStuNode(id, name, score);
    if (pos == 1) { // 插入到头部
        newNode->next = head;
        if (head) head->prev = newNode;
        return newNode;
    }
    StuNode *cur = head;
    for (int i = 1; i < pos - 1; i++) {
        cur = cur->next;
    }
    // 插入到 cur 之后
    newNode->next = cur->next;
    newNode->prev = cur;
    if (cur->next) cur->next->prev = newNode;
    cur->next = newNode;
    return head;
}

void freeList(StuNode *head) {
    StuNode *cur = head;
    while (cur) {
        StuNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

void sortByScore(StuNode *head, int ascending) {
    if (!head) return;
    int swapped;
    StuNode *ptr1;
    StuNode *lptr = NULL;
    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            int needSwap = ascending ? (ptr1->score > ptr1->next->score) : (ptr1->score < ptr1->next->score);
            if (needSwap) {
                // 交换数据域（不改变节点位置）
                int tmpId = ptr1->id;
                char tmpName[20];
                strcpy(tmpName, ptr1->name);
                float tmpScore = ptr1->score;

                ptr1->id = ptr1->next->id;
                strcpy(ptr1->name, ptr1->next->name);
                ptr1->score = ptr1->next->score;

                ptr1->next->id = tmpId;
                strcpy(ptr1->next->name, tmpName);
                ptr1->next->score = tmpScore;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}