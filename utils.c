#include "utils.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseConsole() {
    printf("\n按任意键继续...");
    getchar();
    getchar();
}

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

int isNumber(const char *str) {
    if (*str == '-' || *str == '+') str++;
    if (*str == '\0') return 0;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int readInt() {
    char input[MAX_INPUT];
    safeInput(input, sizeof(input));
    while (!isNumber(input)) {
        printf("输入无效，请重新输入一个整数：");
        safeInput(input, sizeof(input));
    }
    return atoi(input);
}