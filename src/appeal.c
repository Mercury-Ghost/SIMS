#include "appeal.h"
#include "page.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 全局变量初始化
AppealNode *appealHead = NULL;

/**
 * 从appeals.txt加载申诉
 */
void loadAppeals() {
    char dataDir[MAX_PATH_LEN];
    char filePath[MAX_PATH_LEN];
    getDataDir(dataDir, sizeof(dataDir));
    buildFilePath(dataDir, "appeals.txt", filePath, sizeof(filePath));
    
    FILE *fp = fopen(filePath, "r");
    if (!fp) return;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        int id, status;
        char content[100];
        // 格式: 学号 内容 状态，内容中可以包含空格
        char *token = strtok(line, " ");
        if (token) {
            id = atoi(token);
            token = strtok(NULL, " ");
            if (token) {
                // 读取所有内容，直到最后一个空格
                int len = 0;
                char *lastToken = NULL;
                while (token) {
                    lastToken = token;
                    if (len > 0) content[len++] = ' ';
                    size_t token_len = strlen(token);
                    if (len + token_len >= sizeof(content)) {
                        token_len = sizeof(content) - len - 1;
                    }
                    strncpy(content + len, token, token_len);
                    content[len + token_len] = '\0'; // 在strncpy后立即添加null终止符
                    len += token_len;
                    token = strtok(NULL, " ");
                }
                if (lastToken) {
                    // 最后一个token是状态
                    status = atoi(lastToken);
                    // 从内容中移除最后一个token
                    len -= strlen(lastToken);
                    if (len > 0 && content[len-1] == ' ') {
                        len--;
                    }
                    content[len] = '\0';
                    AppealNode *newNode = (AppealNode*)malloc(sizeof(AppealNode));
                    newNode->studentId = id;
                    strncpy(newNode->content, content, 99);
                    newNode->content[99] = '\0';
                    newNode->status = status;
                    newNode->next = appealHead;
                    appealHead = newNode;
                }
            }
        }
    }
    fclose(fp);
}

/**
 * 保存申诉到appeals.txt
 */
void saveAppeals() {
    char dataDir[MAX_PATH_LEN];
    char filePath[MAX_PATH_LEN];
    getDataDir(dataDir, sizeof(dataDir));
    buildFilePath(dataDir, "appeals.txt", filePath, sizeof(filePath));
    
    FILE *fp = fopen(filePath, "w");
    if (!fp) return;
    AppealNode *cur = appealHead;
    while (cur) {
        if (fprintf(fp, "%d %s %d\n", cur->studentId, cur->content, cur->status) < 0) {
            handleWriteError(fp, "保存申诉数据失败！");
            return;
        }
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

/**
 * 释放申诉链表内存
 */
void freeAppeals() {
    if (!appealHead) return; // 空指针检查
    AppealNode *cur = appealHead;
    while (cur) {
        AppealNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    appealHead = NULL;
}