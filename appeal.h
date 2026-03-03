#ifndef APPEAL_H
#define APPEAL_H

#include "utils.h"

// 申诉节点结构体
typedef struct Appeal {
    int studentId;       // 学生学号
    char content[100];   // 申诉内容
    int status;          // 状态：0未处理，1已处理
    struct Appeal *next; // 下一个节点指针
} AppealNode;

// 全局变量
extern AppealNode *appealHead; // 申诉链表头指针

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