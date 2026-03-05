#ifndef FILE_H
#define FILE_H

#include "student.h"

// 从文本文件加载学生链表
StuNode *loadStudentsFromTextFile();
// 从二进制文件加载学生链表
StuNode *loadStudentsFromFile();
// 保存学生链表到二进制文件
void saveStudentsToFile(StuNode *head);
// 从CSV文件批量导入学生数据
int importStudentsFromCSV(const char *filename, StuNode **head);
// 将学生数据导出为CSV格式
int exportStudentsToCSV(const char *filename, StuNode *head);

#endif