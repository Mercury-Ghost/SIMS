#include "user.h"
#include "student.h"  // 新增，用于学号验证
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 全局变量初始化
UserNode *userHead = NULL;
User currentUser;

/**
 * 从users.txt加载所有用户
 */
void loadUsers() {
    FILE *fp = fopen("users.txt", "r");
    if (!fp) {
        fp = fopen("users.txt", "w");
        if (!fp) {
            printf("无法创建用户文件！\n");
            exit(1);
        }
        if (fprintf(fp, "admin admin 2 -1\n") < 0) {
            fclose(fp);
            printf("无法写入用户文件！\n");
            exit(1);
        }
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

/**
 * 保存所有用户到users.txt
 */
void saveUsers() {
    FILE *fp = fopen("users.txt", "w");
    if (!fp) {
        printf("无法打开用户文件写入！\n");
        return;
    }
    UserNode *cur = userHead;
    while (cur) {
        if (fprintf(fp, "%s %s %d %d\n", cur->user.username, cur->user.password,
                cur->user.role, cur->user.studentId) < 0) {
            fclose(fp);
            printf("保存用户数据失败！\n");
            return;
        }
        cur = cur->next;
    }
    fclose(fp);
}

/**
 * 注册新用户
 * @param username 用户名
 * @param password 密码
 * @param role 角色
 * @param studentId 学生学号（仅学生角色需要）
 * @return 注册成功返回1，失败返回0
 */
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
}

/**
 * 登录验证
 * @param username 用户名
 * @param password 密码
 * @return 登录成功返回用户角色，失败返回-1
 */
int loginUser(const char *username, const char *password) {
    UserNode *cur = userHead;
    while (cur) {
        if (strcmp(cur->user.username, username) == 0 &&
            strcmp(cur->user.password, password) == 0) {
            currentUser = cur->user;
            return cur->user.role;
        }
        cur = cur->next;
    }
    return -1;
}

/**
 * 按用户名查找用户节点
 * @param username 用户名
 * @return 找到的用户节点指针，未找到返回NULL
 */
UserNode *findUserByUsername(const char *username) {
    UserNode *cur = userHead;
    while (cur) {
        if (strcmp(cur->user.username, username) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

/**
 * 修改密码
 * @param userNode 用户节点
 * @param newPass 新密码
 */
void changePassword(UserNode *userNode, const char *newPass) {
    if (userNode) {
        strcpy(userNode->user.password, newPass);
        saveUsers();
        printf("密码修改成功。\n");
    }
}

/**
 * 管理员重置用户密码
 * @param username 用户名
 * @param newPass 新密码
 */
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

/**
 * 管理员删除用户
 * @param username 用户名
 * @return 删除成功返回1，失败返回0
 */
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

/**
 * 释放用户链表
 */
void freeUsers() {
    UserNode *cur = userHead;
    while (cur) {
        UserNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}