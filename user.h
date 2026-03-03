#ifndef USER_H
#define USER_H

#include "utils.h"

#define ROLE_STUDENT 0
#define ROLE_TEACHER 1
#define ROLE_ADMIN   2

typedef struct User {
    char username[20];
    char password[20];
    int role;          // 0学生,1教师,2管理员
    int studentId;     // 学生关联学号，教师/管理员为-1
} User;

// 全局用户数组（动态？）这里简单用链表存储
typedef struct UserNode {
    User user;
    struct UserNode *next;
} UserNode;

extern UserNode *userHead;
extern User currentUser;        // 当前登录用户信息

// 从users.txt加载所有用户
void loadUsers();
// 保存所有用户到users.txt
void saveUsers();
// 注册新用户
int registerUser(const char *username, const char *password, int role, int studentId);
// 登录验证
int loginUser(const char *username, const char *password, int role);
// 按用户名查找用户节点
UserNode *findUserByUsername(const char *username);
// 修改密码
void changePassword(UserNode *userNode, const char *newPass);
// 管理员重置用户密码
void adminResetPassword(const char *username, const char *newPass);
// 管理员删除用户
int deleteUser(const char *username);
// 释放用户链表
void freeUsers();

#endif