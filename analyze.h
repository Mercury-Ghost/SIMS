#ifndef ANALYZE_H
#define ANALYZE_H

#include "student.h"

// 打印字符条状图（给定分数，打印#个数）
void printBarChart(float score);
// 统计全班成绩：平均分、最高、最低、各分数段人数，并打印条状图
void analyzeClass(StuNode *head);
// 获取某个学生的班内排名（按成绩降序）
int getRank(StuNode *head, int stuId);
// 打印全班排名（降序）
void printRanking(StuNode *head);

#endif