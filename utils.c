#include "utils.h"

/**
 * 清屏（跨平台）
 */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * 暂停并提示按enter键继续
 */
void pauseConsole() {
    printf("\n按enter键继续...");
    // 清除输入缓冲区中的残留字符
    fflush(stdin);
    // 等待用户输入enter键
    getchar();
}

/**
 * 安全输入字符串，自动去除换行
 * @param buffer 输入缓冲区
 * @param size 缓冲区大小
 */
void safeInput(char *buffer, int size) {
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

/**
 * 检查输入是否为数字（整数或浮点数）
 * @param str 输入字符串
 * @return 是数字返回1，否则返回0
 */
int isNumber(const char *str) {
    if (*str == '-' || *str == '+') str++;
    if (*str == '\0') return 0;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

/**
 * 从标准输入读取一个整数（带错误处理）
 * @return 读取的整数
 */
int readInt() {
    char input[MAX_INPUT];
    safeInput(input, sizeof(input));
    while (!isNumber(input)) {
        printf("输入无效，请重新输入一个整数：");
        safeInput(input, sizeof(input));
    }
    return atoi(input);
}