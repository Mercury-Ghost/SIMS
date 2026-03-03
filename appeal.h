#ifndef APPEAL_H
#define APPEAL_H

#include "utils.h"

typedef struct Appeal {
    int studentId;
    char content[100];
    int status; // 0未处理，1已处理
    struct Appeal *next;
} AppealNode;

extern AppealNode *appealHead;

// 从appeals.txt加载申诉
void loadAppeals();
// 保存申诉到appeals.txt
void saveAppeals();
// 添加申诉（学生端）
void addAppeal(int stuId, const char *content);
// 获取未处理申诉数量
int getPendingAppealCount();
// 显示所有申诉（翻页）
void showAllAppeals();
// 标记申诉为已处理
void markAppealProcessed(int stuId); // 简单起见，通过学号匹配第一个未处理申诉

#endif