#include "appeal.h"
#include "page.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AppealNode *appealHead = NULL;

void loadAppeals() {
    FILE *fp = fopen("appeals.txt", "r");
    if (!fp) return;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        int id, status;
        char content[100];
        // 格式: 学号 内容 状态，内容中无空格
        sscanf(line, "%d %s %d", &id, content, &status);
        AppealNode *newNode = (AppealNode*)malloc(sizeof(AppealNode));
        newNode->studentId = id;
        strcpy(newNode->content, content);
        newNode->status = status;
        newNode->next = appealHead;
        appealHead = newNode;
    }
    fclose(fp);
}

void saveAppeals() {
    FILE *fp = fopen("appeals.txt", "w");
    if (!fp) return;
    AppealNode *cur = appealHead;
    while (cur) {
        fprintf(fp, "%d %s %d\n", cur->studentId, cur->content, cur->status);
        cur = cur->next;
    }
    fclose(fp);
}

void addAppeal(int stuId, const char *content) {
    AppealNode *newNode = (AppealNode*)malloc(sizeof(AppealNode));
    newNode->studentId = stuId;
    strncpy(newNode->content, content, 99);
    newNode->content[99] = '\0';
    newNode->status = 0;
    newNode->next = appealHead;
    appealHead = newNode;
    saveAppeals();
    printf("申诉已提交。\n");
    // TODO: commit point
}

int getPendingAppealCount() {
    int cnt = 0;
    AppealNode *cur = appealHead;
    while (cur) {
        if (cur->status == 0) cnt++;
        cur = cur->next;
    }
    return cnt;
}

void showAllAppeals() {
    // 将申诉转换为数组或直接利用翻页函数
    // 简单起见，这里直接显示全部，但为了复用翻页，我们构建一个字符串数组？
    // 但page模块需要处理双向链表，我们可重新实现翻页，或使用简单打印。
    // 为了符合需求，我们实现一个翻页显示函数在page.c中，可显示任意节点列表。
    // 这里我们简单打印，后续可扩展。但要求是翻页显示，所以我们调用page模块的通用翻页函数。
    // 定义显示回调：
    void printAppealNode(void *data) {
        AppealNode *a = (AppealNode*)data;
        printf("学号: %d, 内容: %s, 状态: %s\n", a->studentId, a->content, a->status ? "已处理" : "未处理");
    }
    // 但page.h需要接受链表头，我们暂时简单实现翻页。
    // 为了快速完成，我们直接分页打印。
    AppealNode *cur = appealHead;
    int total = 0;
    while (cur) { total++; cur = cur->next; }
    if (total == 0) { printf("暂无申诉。\n"); return; }
    int page = 1;
    int totalPages = (total + PAGE_SIZE - 1) / PAGE_SIZE;
    while (1) {
        clearScreen();
        printf("=== 申诉列表 (第 %d/%d 页) ===\n", page, totalPages);
        cur = appealHead;
        // 找到当前页起始
        int start = (page-1) * PAGE_SIZE;
        for (int i = 0; i < start && cur; i++) cur = cur->next;
        for (int i = 0; i < PAGE_SIZE && cur; i++) {
            printf("%d. 学号: %d, 内容: %s, 状态: %s\n", start+i+1, cur->studentId, cur->content, cur->status ? "已处理" : "未处理");
            cur = cur->next;
        }
        printf("\n[N]下一页 [P]上一页 [Q]返回: ");
        char ch = getchar();
        while (getchar() != '\n'); // 清空缓冲区
        if (ch == 'n' || ch == 'N') {
            if (page < totalPages) page++;
        } else if (ch == 'p' || ch == 'P') {
            if (page > 1) page--;
        } else if (ch == 'q' || ch == 'Q') {
            break;
        }
    }
}

void markAppealProcessed(int stuId) {
    AppealNode *cur = appealHead;
    while (cur) {
        if (cur->studentId == stuId && cur->status == 0) {
            cur->status = 1;
            saveAppeals();
            printf("学号 %d 的申诉已标记为已处理。\n", stuId);
            return;
        }
        cur = cur->next;
    }
    printf("未找到该学号的未处理申诉。\n");
}