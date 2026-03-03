#include "user.h"
#include "student.h"  // 新增，用于学号验证
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UserNode *userHead = NULL;
User currentUser;

void loadUsers() {
    FILE *fp = fopen("users.txt", "r");
    if (!fp) {
        fp = fopen("users.txt", "w");
        if (!fp) {
            printf("无法创建用户文件！\n");
            exit(1);
        }
        fprintf(fp, "admin admin 2 -1\n");
        fclose(fp);
        fp = fopen("users.txt", "r");
    }
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        UserNode *newNode = (UserNode*)malloc(sizeof(UserNode));
        char username[20], password[20];
        int role, stuId;
        sscanf(line, "%s %s %d %d", username, password, &role, &stuId);
        strcpy(newNode->user.username, username);
        strcpy(newNode->user.password, password);
        newNode->user.role = role;
        newNode->user.studentId = stuId;
        newNode->next = userHead;
        userHead = newNode;
    }
    fclose(fp);
}

void saveUsers() {
    FILE *fp = fopen("users.txt", "w");
    if (!fp) {
        printf("无法打开用户文件写入！\n");
        return;
    }
    UserNode *cur = userHead;
    while (cur) {
        fprintf(fp, "%s %s %d %d\n", cur->user.username, cur->user.password,
                cur->user.role, cur->user.studentId);
        cur = cur->next;
    }
    fclose(fp);
}

int registerUser(const char *username, const char *password, int role, int studentId) {
    if (findUserByUsername(username) != NULL) {
        printf("用户名已存在！\n");
        return 0;
    }
    if (role == ROLE_STUDENT) {
        // 直接使用全局 stuHead，已在 student.h 中声明为 extern
        if (findById(stuHead, studentId) == NULL) {
            printf("学号不存在，学生注册失败。\n");
            return 0;
        }
    }
    UserNode *newNode = (UserNode*)malloc(sizeof(UserNode));
    strcpy(newNode->user.username, username);
    strcpy(newNode->user.password, password);
    newNode->user.role = role;
    newNode->user.studentId = (role == ROLE_STUDENT) ? studentId : -1;
    newNode->next = userHead;
    userHead = newNode;
    saveUsers();
    printf("注册成功！\n");
    return 1;
    // TODO: commit point
}

int loginUser(const char *username, const char *password, int role) {
    UserNode *cur = userHead;
    while (cur) {
        if (strcmp(cur->user.username, username) == 0 &&
            strcmp(cur->user.password, password) == 0 &&
            cur->user.role == role) {
            currentUser = cur->user;
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

UserNode *findUserByUsername(const char *username) {
    UserNode *cur = userHead;
    while (cur) {
        if (strcmp(cur->user.username, username) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

void changePassword(UserNode *userNode, const char *newPass) {
    if (userNode) {
        strcpy(userNode->user.password, newPass);
        saveUsers();
        printf("密码修改成功。\n");
    }
}

void adminResetPassword(const char *username, const char *newPass) {
    UserNode *u = findUserByUsername(username);
    if (u) {
        strcpy(u->user.password, newPass);
        saveUsers();
        printf("用户 %s 的密码已重置。\n", username);
    } else {
        printf("用户不存在。\n");
    }
}

int deleteUser(const char *username) {
    UserNode *cur = userHead, *prev = NULL;
    while (cur) {
        if (strcmp(cur->user.username, username) == 0) {
            if (prev) prev->next = cur->next;
            else userHead = cur->next;
            free(cur);
            saveUsers();
            printf("用户 %s 已删除。\n", username);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("用户不存在。\n");
    return 0;
}

void freeUsers() {
    UserNode *cur = userHead;
    while (cur) {
        UserNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}