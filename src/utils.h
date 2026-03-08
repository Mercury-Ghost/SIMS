#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// 常量定义
#define MAX_NAME_LEN 20     // 最大姓名长度
#define MAX_CONTENT_LEN 100 // 最大内容长度
#define PAGE_SIZE 5         // 每页显示条数
#define MAX_INPUT 256       // 最大输入长度
#define MAX_PATH_LEN 256    // 最大路径长度

// 清屏（跨平台）
void clearScreen();
// 暂停并提示按任意键继续
void pauseConsole();
// 安全输入字符串，自动去除换行
void safeInput(char *buffer, int size);
// 检查输入是否为数字（整数或浮点数）
int isNumber(const char *str);
// 从标准输入读取一个整数（带错误处理）
int readInt();
// 验证学号是否有效
int isValidStudentId(const char *str);
// 验证成绩是否在有效范围内
int isValidScore(float score);
// 验证用户名是否有效
int isValidUsername(const char *str);
// 验证密码是否有效
int isValidPassword(const char *str);
// 从标准输入读取一个浮点数（带错误处理）
float readFloat();
// 处理写入错误
bool handleWriteError(FILE *fp, const char *msg);

// 路径处理函数
// 获取项目根目录路径
void getProjectRoot(char *path, size_t size);
// 获取数据目录路径
void getDataDir(char *path, size_t size);
// 获取bin目录路径
void getBinDir(char *path, size_t size);
// 构建完整的文件路径
void buildFilePath(const char *dir, const char *filename, char *path, size_t size);

#endif