#include "page.h"
#include "utils.h"
#include <stdio.h>

void showStudentsPage(StuNode *head) {
    if (!head) {
        printf("暂无学生数据。\n");
        pauseConsole();
        return;
    }
    int total = getLength(head);
    int totalPages = (total + PAGE_SIZE - 1) / PAGE_SIZE;
    int page = 1;
    while (1) {
        clearScreen();
        printf("=== 学生列表 (第 %d/%d 页) ===\n", page, totalPages);
        StuNode *cur = head;
        // 移动到当前页起始
        int start = (page - 1) * PAGE_SIZE;
        for (int i = 0; i < start && cur; i++) cur = cur->next;
        for (int i = 0; i < PAGE_SIZE && cur; i++) {
            printf("%d. 学号: %d, 姓名: %s, 成绩: %.2f\n", start + i + 1, cur->id, cur->name, cur->score);
            cur = cur->next;
        }
        printf("\n[N]下一页 [P]上一页 [Q]返回: ");
        char ch = getchar();
        while (getchar() != '\n');
        if (ch == 'n' || ch == 'N') {
            if (page < totalPages) page++;
        } else if (ch == 'p' || ch == 'P') {
            if (page > 1) page--;
        } else if (ch == 'q' || ch == 'Q') {
            break;
        }
    }
}