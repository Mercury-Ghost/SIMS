#include "backup.h"
#include "file.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * 生成备份文件名
 * @param filename 输出文件名缓冲区
 * @param size 缓冲区大小
 */
void generateBackupFilename(char *filename, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(filename, size, "backup_%Y%m%d_%H%M%S.dat", tm_info);
}

/**
 * 执行数据备份
 * @param head 学生链表头指针
 * @return 备份是否成功
 */
bool backupData(StuNode *head) {
    char filename[100];
    generateBackupFilename(filename, sizeof(filename));
    
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("无法创建备份文件！\n");
        return false;
    }
    
    // 备份学生数据
    StuNode *cur = head;
    while (cur) {
        if (fwrite(&cur->id, sizeof(int), 1, fp) != 1) {
            return handleWriteError(fp, "备份失败！");
        }
        if (fwrite(cur->name, sizeof(char), 20, fp) != 20) {
            return handleWriteError(fp, "备份失败！");
        }
        if (fwrite(&cur->score, sizeof(float), 1, fp) != 1) {
            return handleWriteError(fp, "备份失败！");
        }
        cur = cur->next;
    }
    
    // 写入结束标记
    int end_marker = -1;
    if (fwrite(&end_marker, sizeof(int), 1, fp) != 1) {
        return handleWriteError(fp, "备份失败！");
    }
    
    fclose(fp);
    printf("备份成功！备份文件：%s\n", filename);
    return true;
}

/**
 * 从备份文件恢复数据
 * @param filename 备份文件名
 * @param head 学生链表头指针的指针
 * @return 恢复是否成功
 */
bool restoreData(const char *filename, StuNode **head) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("无法打开备份文件！\n");
        return false;
    }
    
    // 清空现有链表
    freeList(*head);
    *head = NULL;
    
    StuNode *tail = NULL;
    
    while (1) {
        int id;
        size_t read = fread(&id, sizeof(int), 1, fp);
        if (read != 1) break;
        
        // 检查结束标记
        if (id == -1) break;
        
        char name[20];
        float score;
        
        if (fread(name, sizeof(char), 20, fp) != 20) break;
        if (fread(&score, sizeof(float), 1, fp) != 1) break;
        
        StuNode *newNode = createStuNode(id, name, score);
        if (!newNode) continue;
        
        if (!*head) {
            *head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    fclose(fp);
    printf("数据恢复成功！\n");
    return true;
}

/**
 * 执行自动备份
 * @param head 学生链表头指针
 */
void autoBackup(StuNode *head) {
    // 检查是否需要自动备份（每天一次）
    char last_backup_file[100] = "last_backup.txt";
    FILE *fp = fopen(last_backup_file, "r");
    
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char today[11];
    strftime(today, sizeof(today), "%Y-%m-%d", tm_info);
    
    bool need_backup = true;
    
    if (fp) {
        char last_date[11];
        if (fgets(last_date, sizeof(last_date), fp)) {
            last_date[strcspn(last_date, "\n")] = '\0';
            if (strcmp(last_date, today) == 0) {
                need_backup = false;
            }
        }
        fclose(fp);
    }
    
    if (need_backup) {
        if (backupData(head)) {
                // 更新最后备份日期
                fp = fopen(last_backup_file, "w");
                if (fp) {
                    if (fprintf(fp, "%s\n", today) < 0) {
                        printf("更新备份日期失败！\n");
                    }
                    fclose(fp);
                }
            }
    }
}

/**
 * 列出所有备份文件
 */
void listBackupFiles() {
    system("dir backup_*.dat /B");
}