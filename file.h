#ifndef FILE_H
#define FILE_H

#include "student.h"

// 从文本文件加载学生链表
StuNode *loadStudentsFromTextFile();
// 从二进制文件加载学生链表
StuNode *loadStudentsFromFile();
// 保存学生链表到二进制文件
void saveStudentsToFile(StuNode *head);

#endif