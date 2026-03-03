#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 常量定义
#define MAX_NAME_LEN 20
#define MAX_CONTENT_LEN 100
#define PAGE_SIZE 5        // 每页显示条数
#define MAX_INPUT 256

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

#endif