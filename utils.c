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

/**
 * 验证学号是否有效
 * @param str 学号字符串
 * @return 有效返回1，否则返回0
 */
int isValidStudentId(const char *str) {
    // 学号只能包含数字
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

/**
 * 验证成绩是否在有效范围内
 * @param score 成绩
 * @return 有效返回1，否则返回0
 */
int isValidScore(float score) {
    return score >= 0 && score <= 100;
}

/**
 * 验证用户名是否有效
 * @param str 用户名
 * @return 有效返回1，否则返回0
 */
int isValidUsername(const char *str) {
    int len = strlen(str);
    // 用户名长度应在1-20之间
    if (len < 1 || len > 20) return 0;
    // 用户名只能包含字母、数字和下划线
    while (*str) {
        if (!isalnum(*str) && *str != '_') return 0;
        str++;
    }
    return 1;
}

/**
 * 验证密码是否有效
 * @param str 密码
 * @return 有效返回1，否则返回0
 * @note 密码策略：
 *       1. 密码长度：任意长度
 *       2. 允许字符：字母（大小写）、数字、下划线
 *       3. 不允许特殊字符和空格
 */
int isValidPassword(const char *str) {
    // 密码可以是任意长度，但只能包含字母、数字和下划线
    while (*str) {
        if (!isalnum(*str) && *str != '_') return 0;
        str++;
    }
    return 1;
}

/**
 * 检查输入是否为浮点数
 * @param str 输入字符串
 * @return 是浮点数返回1，否则返回0
 */
int isFloat(const char *str) {
    if (*str == '-' || *str == '+') str++;
    int dotCount = 0;
    if (*str == '.') {
        dotCount++;
        str++;
        if (*str == '\0') return 0;
    }
    while (*str) {
        if (*str == '.') {
            dotCount++;
            if (dotCount > 1) return 0;
        } else if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

/**
 * 从标准输入读取一个浮点数（带错误处理）
 * @return 读取的浮点数
 */
float readFloat() {
    char input[MAX_INPUT];
    safeInput(input, sizeof(input));
    while (!isFloat(input)) {
        printf("输入无效，请重新输入一个数字：");
        safeInput(input, sizeof(input));
    }
    return atof(input);
}