#include "analyze.h"
#include <stdio.h>

void printBarChart(float score) {
    int len = (int)(score / 5); // 每5分一个#，20个满
    if (len > 40) len = 40;     // 最大限制
    printf("成绩条: [");
    for (int i = 0; i < len; i++) putchar('#');
    for (int i = len; i < 40; i++) putchar(' ');
    printf("] %.2f\n", score);
}

void analyzeClass(StuNode *head) {
    if (!head) {
        printf("暂无学生数据。\n");
        return;
    }
    int count = 0;
    float sum = 0, max = -1, min = 101;
    int level[5] = {0}; // 0-59,60-69,70-79,80-89,90-100
    StuNode *cur = head;
    while (cur) {
        count++;
        sum += cur->score;
        if (cur->score > max) max = cur->score;
        if (cur->score < min) min = cur->score;
        if (cur->score < 60) level[0]++;
        else if (cur->score < 70) level[1]++;
        else if (cur->score < 80) level[2]++;
        else if (cur->score < 90) level[3]++;
        else level[4]++;
        cur = cur->next;
    }
    printf("全班人数: %d\n", count);
    printf("平均分: %.2f\n", sum / count);
    printf("最高分: %.2f, 最低分: %.2f\n", max, min);
    printf("分数段分布:\n");
    printf("<60 : "); for (int i=0; i<level[0]; i++) putchar('#'); printf(" (%d人)\n", level[0]);
    printf("60-69: "); for (int i=0; i<level[1]; i++) putchar('#'); printf(" (%d人)\n", level[1]);
    printf("70-79: "); for (int i=0; i<level[2]; i++) putchar('#'); printf(" (%d人)\n", level[2]);
    printf("80-89: "); for (int i=0; i<level[3]; i++) putchar('#'); printf(" (%d人)\n", level[3]);
    printf("90-100:"); for (int i=0; i<level[4]; i++) putchar('#'); printf(" (%d人)\n", level[4]);
}

int getRank(StuNode *head, int stuId) {
    // 先按成绩降序排序（复制一份或临时排序？）这里简单做法：遍历计数比它高的
    float score = 0;
    StuNode *stu = findById(head, stuId);
    if (!stu) return -1;
    score = stu->score;
    int rank = 1;
    StuNode *cur = head;
    while (cur) {
        if (cur->score > score) rank++;
        cur = cur->next;
    }
    return rank;
}

void printRanking(StuNode *head) {
    if (!head) { printf("无数据。\n"); return; }
    // 复制链表或使用临时数组
    int n = getLength(head);
    StuNode **arr = (StuNode**)malloc(n * sizeof(StuNode*));
    StuNode *cur = head;
    for (int i = 0; i < n; i++) {
        arr[i] = cur;
        cur = cur->next;
    }
    // 冒泡排序降序
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (arr[j]->score < arr[j+1]->score) {
                StuNode *tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
    printf("全班排名（降序）:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. 学号: %d, 姓名: %s, 成绩: %.2f\n", i+1, arr[i]->id, arr[i]->name, arr[i]->score);
    }
    free(arr);
}