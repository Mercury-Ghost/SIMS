#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 创建学生节点
 * @param id 学号
 * @param name 姓名
 * @param score 成绩
 * @return 创建的学生节点指针
 */
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

/**
 * 添加学生到链表末尾
 * @param head 链表头指针
 * @param id 学号
 * @param name 姓名
 * @param score 成绩
 * @return 更新后的链表头指针
 */
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

/**
 * 根据学号删除学生
 * @param head 链表头指针
 * @param id 要删除的学号
 * @return 更新后的链表头指针
 */
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

/**
 * 根据学号查找学生
 * @param head 链表头指针
 * @param id 要查找的学号
 * @return 找到的学生节点指针，未找到返回NULL
 */
StuNode *findById(StuNode *head, int id) {
    StuNode *cur = head;
    while (cur) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

/**
 * 根据姓名模糊查找学生
 * @param head 链表头指针
 * @param name 要查找的姓名关键字
 */
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

/**
 * 更新学生信息
 * @param node 要更新的学生节点
 * @param newName 新姓名
 * @param newScore 新成绩
 */
void updateStudent(StuNode *node, const char *newName, float newScore) {
    if (node) {
        strncpy(node->name, newName, 19);
        node->name[19] = '\0';
        node->score = newScore;
        printf("信息更新成功。\n");
    }
}

/**
 * 获取链表长度
 * @param head 链表头指针
 * @return 链表长度
 */
int getLength(StuNode *head) {
    int cnt = 0;
    StuNode *cur = head;
    while (cur) {
        cnt++;
        cur = cur->next;
    }
    return cnt;
}

/**
 * 在指定位置插入学生
 * @param head 链表头指针
 * @param pos 插入位置（从1开始）
 * @param id 学号
 * @param name 姓名
 * @param score 成绩
 * @return 更新后的链表头指针
 */
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

/**
 * 释放链表内存
 * @param head 链表头指针
 */
void freeList(StuNode *head) {
    StuNode *cur = head;
    while (cur) {
        StuNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

/**
 * 按成绩排序
 * @param head 链表头指针
 * @param ascending 1为升序，0为降序
 */
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