#include "file.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

/**
 * 从文本文件加载学生链表
 * @return 加载的学生链表头指针
 */
StuNode *loadStudentsFromTextFile() {
    char dataDir[MAX_PATH_LEN];
    char filePath[MAX_PATH_LEN];
    getDataDir(dataDir, sizeof(dataDir));
    buildFilePath(dataDir, "students.txt", filePath, sizeof(filePath));
    
    FILE *fp = fopen(filePath, "r");
    if (!fp) {
        // 文件不存在，返回空链表
        return NULL;
    }
    StuNode *head = NULL;
    StuNode *tail = NULL;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        int id;
        char name[20];
        float score;
        if (sscanf(line, "%d %s %f", &id, name, &score) == 3) {
            StuNode *newNode = createStuNode(id, name, score);
            if (!head) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    fclose(fp);
    return head;
}

/**
 * 从二进制文件加载学生链表
 * @return 加载的学生链表头指针
 */
StuNode *loadStudentsFromFile() {
    char dataDir[MAX_PATH_LEN];
    char filePath[MAX_PATH_LEN];
    getDataDir(dataDir, sizeof(dataDir));
    buildFilePath(dataDir, "students.dat", filePath, sizeof(filePath));
    
    FILE *fp = fopen(filePath, "rb");
    if (!fp) {
        // 二进制文件不存在，尝试从文本文件加载
        return loadStudentsFromTextFile();
    }
    StuNode *head = NULL;
    StuNode *tail = NULL;
    while (1) {
        int id;
        char name[20];
        float score;
        size_t read = fread(&id, sizeof(int), 1, fp);
        if (read != 1) break;
        if (fread(name, sizeof(char), 20, fp) != 20) break;
        if (fread(&score, sizeof(float), 1, fp) != 1) break;
        StuNode *newNode = createStuNode(id, name, score);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    fclose(fp);
    return head;
}

/**
 * 保存学生链表到二进制文件
 * @param head 学生链表头指针
 */
void saveStudentsToFile(StuNode *head) {
    char dataDir[MAX_PATH_LEN];
    char filePath[MAX_PATH_LEN];
    getDataDir(dataDir, sizeof(dataDir));
    buildFilePath(dataDir, "students.dat", filePath, sizeof(filePath));
    
    FILE *fp = fopen(filePath, "wb");
    if (!fp) {
        printf("无法打开学生文件保存！\n");
        return;
    }
    StuNode *cur = head;
    while (cur) {
        if (fwrite(&cur->id, sizeof(int), 1, fp) != 1) {
            handleWriteError(fp, "保存学生学号数据失败！");
            return;
        }
        if (fwrite(cur->name, sizeof(char), 20, fp) != 20) {
            handleWriteError(fp, "保存学生姓名数据失败！");
            return;
        }
        if (fwrite(&cur->score, sizeof(float), 1, fp) != 1) {
            handleWriteError(fp, "保存学生成绩数据失败！");
            return;
        }
        cur = cur->next;
    }
    fclose(fp);
    
    // 同时保存到文本文件，方便查看
    buildFilePath(dataDir, "students.txt", filePath, sizeof(filePath));
    fp = fopen(filePath, "w");
    if (fp) {
        cur = head;
        while (cur) {
            if (fprintf(fp, "%d %s %.2f\n", cur->id, cur->name, cur->score) < 0) {
                handleWriteError(fp, "保存学生文本数据失败！");
                return;
            }
            cur = cur->next;
        }
        fclose(fp);
    }
}

/**
 * 从CSV文件批量导入学生数据
 * @param filename CSV文件名
 * @param head 学生链表头指针的指针
 * @return 导入的学生数量，失败返回-1
 */
int importStudentsFromCSV(const char *filename, StuNode **head) {
    char filePath[MAX_PATH_LEN];
    
    // 检查filename是否为绝对路径
    if (filename[0] == '\\' || (filename[1] == ':' && filename[2] == '\\')) {
        // 绝对路径，直接使用
        strncpy(filePath, filename, sizeof(filePath) - 1);
    } else {
        // 相对路径，视为相对于data目录
        char dataDir[MAX_PATH_LEN];
        getDataDir(dataDir, sizeof(dataDir));
        buildFilePath(dataDir, filename, filePath, sizeof(filePath));
    }
    
    FILE *fp = fopen(filePath, "r");
    if (!fp) {
        printf("无法打开CSV文件！\n");
        return -1;
    }
    
    int count = 0;
    char line[256];
    
    // 跳过表头
    if (fgets(line, sizeof(line), fp) == NULL) {
        fclose(fp);
        return 0;
    }
    
    while (fgets(line, sizeof(line), fp)) {
        int id;
        char name[20];
        float score;
        
        // 解析CSV行
        char *token = strtok(line, ",");
        if (!token) continue;
        id = atoi(token);
        
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(name, token, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        
        token = strtok(NULL, ",");
        if (!token) continue;
        score = atof(token);
        
        // 创建新节点并添加到链表
        StuNode *newNode = createStuNode(id, name, score);
        if (!newNode) continue;
        
        if (!*head) {
            *head = newNode;
        } else {
            StuNode *tail = *head;
            while (tail->next) {
                tail = tail->next;
            }
            tail->next = newNode;
            newNode->prev = tail;
        }
        
        count++;
    }
    
    fclose(fp);
    return count;
}

/**
 * 将学生数据导出为CSV格式
 * @param filename CSV文件名
 * @param head 学生链表头指针
 * @return 导出的学生数量，失败返回-1
 */
int exportStudentsToCSV(const char *filename, StuNode *head) {
    char filePath[MAX_PATH_LEN];
    
    // 检查filename是否为绝对路径
    if (filename[0] == '\\' || (filename[1] == ':' && filename[2] == '\\')) {
        // 绝对路径，直接使用
        strncpy(filePath, filename, sizeof(filePath) - 1);
    } else {
        // 相对路径，视为相对于data目录
        char dataDir[MAX_PATH_LEN];
        getDataDir(dataDir, sizeof(dataDir));
        buildFilePath(dataDir, filename, filePath, sizeof(filePath));
    }
    
    FILE *fp = fopen(filePath, "w");
    if (!fp) {
        printf("无法创建CSV文件！\n");
        return -1;
    }
    
    // 写入表头
    if (fprintf(fp, "学号,姓名,成绩\n") < 0) {
        fclose(fp);
        printf("导出CSV文件失败！\n");
        return -1;
    }
    
    int count = 0;
    StuNode *cur = head;
    while (cur) {
        if (fprintf(fp, "%d,%s,%.2f\n", cur->id, cur->name, cur->score) < 0) {
            fclose(fp);
            printf("导出CSV文件失败！\n");
            return -1;
        }
        cur = cur->next;
        count++;
    }
    
    fclose(fp);
    return count;
}