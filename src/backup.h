#ifndef BACKUP_H
#define BACKUP_H

#include "student.h"
#include <stdbool.h>

// 生成备份文件名
void generateBackupFilename(char *filename, size_t size);

// 执行数据备份
bool backupData(StuNode *head);

// 从备份文件恢复数据
bool restoreData(const char *filename, StuNode **head);

// 执行自动备份
void autoBackup(StuNode *head);

// 列出所有备份文件
void listBackupFiles();

#endif