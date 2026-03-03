#include "appeal.h"
#include "page.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 全局变量初始化
AppealNode *appealHead = NULL;

/**
 * 从appeals.txt加载申诉
 */
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

/**
 * 保存申诉到appeals.txt
 */
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

/**
 * 添加申诉（学生端）
 * @param stuId 学生学号
 * @param content 申诉内容
 */
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
}

/**
 * 获取未处理申诉数量
 * @return 未处理申诉数量
 */
int getPendingAppealCount() {
    int cnt = 0;
    AppealNode *cur = appealHead;
    while (cur) {
        if (cur->status == 0) cnt++;
        cur = cur->next;
    }
    return cnt;
}

/**
 * 显示所有申诉（翻页）
 */
void showAllAppeals() {
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

/**
 * 标记申诉为已处理
 * @param stuId 学生学号
 */
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