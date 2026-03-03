#include "ui.h"
#include "student.h"
#include "user.h"
#include "file.h"
#include "appeal.h"
#include "analyze.h"
#include "page.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

// 全局学生头指针，在main.c中定义
extern StuNode *stuHead;

/**
 * 显示登录界面
 */
void loginMenu() {
    int choice;
    do {
        clearScreen();
        printf("===== 学生信息管理系统 =====\n");
        printf("1. 登录\n");
        printf("2. 注册\n");
        printf("3. 退出\n");
        printf("请选择: ");
        choice = readInt();
        switch (choice) {
            case 1: {
                char username[20], password[20];
                int role;
                printf("用户名: ");
                safeInput(username, sizeof(username));
                printf("密码: ");
                safeInput(password, sizeof(password));
                printf("角色 (0学生 1教师 2管理员): ");
                role = readInt();
                if (loginUser(username, password, role)) {
                    printf("登录成功！\n");
                    pauseConsole();
                    if (role == ROLE_STUDENT) studentMenu();
                    else if (role == ROLE_TEACHER) teacherMenu();
                    else adminMenu();
                } else {
                    printf("用户名或密码错误！\n");
                    pauseConsole();
                }
                break;
            }
            case 2: {
                char username[20], password[20];
                int role, stuId = -1;
                printf("用户名: ");
                safeInput(username, sizeof(username));
                printf("密码: ");
                safeInput(password, sizeof(password));
                printf("角色 (0学生 1教师 2管理员): ");
                role = readInt();
                if (role == ROLE_STUDENT) {
                    printf("请输入你的学号: ");
                    stuId = readInt();
                }
                registerUser(username, password, role, stuId);
                pauseConsole();
                break;
            }
            case 3:
                printf("再见！\n");
                return;
            default:
                printf("无效选项。\n");
                pauseConsole();
        }
    } while (choice != 3);
}

/**
 * 学生主菜单
 */
void studentMenu() {
    int choice;
    do {
        clearScreen();
        printf("===== 学生端 [%s] =====\n", currentUser.username);
        printf("1. 成绩查询\n");
        printf("2. 班内排名\n");
        printf("3. 查询本班成绩（翻页）\n");
        printf("4. 提交成绩申诉\n");
        printf("5. 修改密码\n");
        printf("6. 成绩分析（条状图）\n");
        printf("7. 返回登录\n");
        printf("请选择: ");
        choice = readInt();
        switch (choice) {
            case 1: {
                // 成绩查询
                StuNode *me = findById(stuHead, currentUser.studentId);
                if (me) {
                    printf("你的成绩: %.2f\n", me->score);
                } else {
                    printf("未找到你的学号信息，请联系管理员。\n");
                }
                pauseConsole();
                break;
            }
            case 2: {
                // 班内排名
                int rank = getRank(stuHead, currentUser.studentId);
                if (rank != -1) {
                    printf("你在班内排名第 %d\n", rank);
                } else {
                    printf("无法获取排名。\n");
                }
                pauseConsole();
                break;
            }
            case 3:
                showStudentsPage(stuHead);
                break;
            case 4: {
                char content[100];
                printf("请输入申诉内容: ");
                safeInput(content, sizeof(content));
                addAppeal(currentUser.studentId, content);
                pauseConsole();
                break;
            }
            case 5: {
                char newPass[20];
                printf("请输入新密码: ");
                safeInput(newPass, sizeof(newPass));
                UserNode *me = findUserByUsername(currentUser.username);
                if (me) changePassword(me, newPass);
                pauseConsole();
                break;
            }
            case 6: {
                StuNode *me = findById(stuHead, currentUser.studentId);
                if (me) {
                    printBarChart(me->score);
                } else {
                    printf("未找到你的信息。\n");
                }
                pauseConsole();
                break;
            }
            case 7:
                return;
            default:
                printf("无效选项。\n");
                pauseConsole();
        }
    } while (1);
}

void teacherMenu() {
    int choice;
    do {
        clearScreen();
        printf("===== 教师端 [%s] =====\n", currentUser.username);
        printf("1. 增删改查学生信息\n");
        printf("2. 查看班内成绩（翻页）\n");
        printf("3. 学生信息下载至CSV\n");
        printf("4. 成绩分析\n");
        printf("5. 修改密码\n");
        printf("6. 返回登录\n");
        printf("请选择: ");
        choice = readInt();
        switch (choice) {
            case 1: {
                // 增删改查子菜单
                int sub;
                do {
                    clearScreen();
                    printf("--- 学生信息管理 ---\n");
                    printf("1. 添加学生\n");
                    printf("2. 按学号删除\n");
                    printf("3. 修改学生信息\n");
                    printf("4. 按学号查询\n");
                    printf("5. 按姓名模糊查询\n");
                    printf("6. 插入到指定位置\n");
                    printf("7. 按成绩排序（升序/降序）\n");
                    printf("8. 返回上级\n");
                    printf("请选择: ");
                    sub = readInt();
                    switch (sub) {
                        case 1: {
                            int id; char name[20]; float score;
                            printf("学号: "); id = readInt();
                            if (findById(stuHead, id)) {
                                printf("学号已存在！\n");
                                break;
                            }
                            printf("姓名: "); safeInput(name, sizeof(name));
                            printf("成绩: "); scanf("%f", &score); getchar();
                            stuHead = addStudent(stuHead, id, name, score);
                            saveStudentsToFile(stuHead);
                            printf("添加成功。\n");
                            pauseConsole();
                            break;
                        }
                        case 2: {
                            int id;
                            printf("要删除的学号: "); id = readInt();
                            stuHead = deleteById(stuHead, id);
                            saveStudentsToFile(stuHead);
                            pauseConsole();
                            break;
                        }
                        case 3: {
                            int id; char name[20]; float score;
                            printf("要修改的学号: "); id = readInt();
                            StuNode *node = findById(stuHead, id);
                            if (node) {
                                printf("新姓名: "); safeInput(name, sizeof(name));
                                printf("新成绩: "); scanf("%f", &score); getchar();
                                updateStudent(node, name, score);
                                saveStudentsToFile(stuHead);
                            } else printf("学号不存在。\n");
                            pauseConsole();
                            break;
                        }
                        case 4: {
                            int id; printf("学号: "); id = readInt();
                            StuNode *node = findById(stuHead, id);
                            if (node) printf("学号: %d, 姓名: %s, 成绩: %.2f\n", node->id, node->name, node->score);
                            else printf("未找到。\n");
                            pauseConsole();
                            break;
                        }
                        case 5: {
                            char name[20];
                            printf("姓名关键字: "); safeInput(name, sizeof(name));
                            findByName(stuHead, name);
                            pauseConsole();
                            break;
                        }
                        case 6: {
                            int pos, id; char name[20]; float score;
                            printf("插入位置 (1~%d): ", getLength(stuHead)+1); pos = readInt();
                            printf("学号: "); id = readInt();
                            if (findById(stuHead, id)) { printf("学号已存在。\n"); break; }
                            printf("姓名: "); safeInput(name, sizeof(name));
                            printf("成绩: "); scanf("%f", &score); getchar();
                            stuHead = insertAtPosition(stuHead, pos, id, name, score);
                            saveStudentsToFile(stuHead);
                            printf("插入成功。\n");
                            pauseConsole();
                            break;
                        }
                        case 7: {
                            printf("排序方式：1升序 2降序: ");
                            int asc = readInt();
                            sortByScore(stuHead, asc == 1);
                            saveStudentsToFile(stuHead);
                            printf("排序完成。\n");
                            pauseConsole();
                            break;
                        }
                        case 8:
                            break;
                        default:
                            printf("无效选项。\n");
                            pauseConsole();
                    }
                } while (sub != 8);
                break;
            }
            case 2:
                showStudentsPage(stuHead);
                break;
            case 3: {
                // 导出CSV
                FILE *fp = fopen("students.csv", "w");
                if (fp) {
                    fprintf(fp, "学号,姓名,成绩\n");
                    StuNode *cur = stuHead;
                    while (cur) {
                        fprintf(fp, "%d,%s,%.2f\n", cur->id, cur->name, cur->score);
                        cur = cur->next;
                    }
                    fclose(fp);
                    printf("已导出到 students.csv\n");
                } else {
                    printf("无法创建文件。\n");
                }
                pauseConsole();
                break;
            }
            case 4:
                analyzeClass(stuHead);
                pauseConsole();
                break;
            case 5: {
                char newPass[20];
                printf("请输入新密码: ");
                safeInput(newPass, sizeof(newPass));
                UserNode *me = findUserByUsername(currentUser.username);
                if (me) changePassword(me, newPass);
                pauseConsole();
                break;
            }
            case 6:
                return;
            default:
                printf("无效选项。\n");
                pauseConsole();
        }
    } while (1);
    // TODO: commit point (教师功能点)
}

void adminMenu() {
    int choice;
    do {
        clearScreen();
        int pending = getPendingAppealCount();
        printf("===== 管理员端 [%s] =====\n", currentUser.username);
        if (pending > 0) printf("【待办】有 %d 条未处理的申诉\n", pending);
        printf("1. 查看代办（申诉管理）\n");
        printf("2. 账号管理\n");
        printf("3. 从文件录入所有账号密码\n");
        printf("4. 从文件导出所有账号密码\n");
        printf("5. 进入教师端操作\n");
        printf("6. 修改密码\n");
        printf("7. 返回登录\n");
        printf("请选择: ");
        choice = readInt();
        switch (choice) {
            case 1:
                // 申诉管理
                showAllAppeals();
                // 提供一个标记处理的功能
                printf("输入要标记为已处理的学号（0返回）: ");
                int sid = readInt();
                if (sid != 0) {
                    markAppealProcessed(sid);
                }
                pauseConsole();
                break;
            case 2: {
                // 账号管理子菜单
                int sub;
                do {
                    clearScreen();
                    printf("--- 账号管理 ---\n");
                    printf("1. 查看所有用户\n");
                    printf("2. 添加用户\n");
                    printf("3. 删除用户\n");
                    printf("4. 重置用户密码\n");
                    printf("5. 返回上级\n");
                    printf("请选择: ");
                    sub = readInt();
                    switch (sub) {
                        case 1: {
                            UserNode *cur = userHead;
                            printf("用户名\t角色\t学号\n");
                            while (cur) {
                                printf("%s\t", cur->user.username);
                                switch (cur->user.role) {
                                    case 0: printf("学生\t"); break;
                                    case 1: printf("教师\t"); break;
                                    case 2: printf("管理员\t"); break;
                                }
                                if (cur->user.role == 0) printf("%d\n", cur->user.studentId);
                                else printf("-\n");
                                cur = cur->next;
                            }
                            pauseConsole();
                            break;
                        }
                        case 2: {
                            char un[20], pw[20];
                            int role, stuId = -1;
                            printf("用户名: "); safeInput(un, sizeof(un));
                            printf("密码: "); safeInput(pw, sizeof(pw));
                            printf("角色 (0学生 1教师 2管理员): "); role = readInt();
                            if (role == 0) {
                                printf("学号: "); stuId = readInt();
                            }
                            registerUser(un, pw, role, stuId);
                            pauseConsole();
                            break;
                        }
                        case 3: {
                            char un[20];
                            printf("要删除的用户名: "); safeInput(un, sizeof(un));
                            deleteUser(un);
                            pauseConsole();
                            break;
                        }
                        case 4: {
                            char un[20], newpw[20];
                            printf("用户名: "); safeInput(un, sizeof(un));
                            printf("新密码: "); safeInput(newpw, sizeof(newpw));
                            adminResetPassword(un, newpw);
                            pauseConsole();
                            break;
                        }
                        case 5:
                            break;
                        default:
                            printf("无效选项。\n");
                            pauseConsole();
                    }
                } while (sub != 5);
                break;
            }
            case 3: {
                // 从文件录入账号密码
                char filename[100];
                printf("请输入文件名（例如 users.txt）: ");
                safeInput(filename, sizeof(filename));
                FILE *fp = fopen(filename, "r");
                if (!fp) {
                    printf("文件打开失败。\n");
                    pauseConsole();
                    break;
                }
                char line[256];
                while (fgets(line, sizeof(line), fp)) {
                    char un[20], pw[20];
                    int role, sid;
                    if (sscanf(line, "%s %s %d %d", un, pw, &role, &sid) == 4) {
                        // 直接添加，不检查重复（简单处理）
                        UserNode *newNode = (UserNode*)malloc(sizeof(UserNode));
                        strcpy(newNode->user.username, un);
                        strcpy(newNode->user.password, pw);
                        newNode->user.role = role;
                        newNode->user.studentId = sid;
                        newNode->next = userHead;
                        userHead = newNode;
                    }
                }
                fclose(fp);
                saveUsers();
                printf("导入完成。\n");
                pauseConsole();
                break;
            }
            case 4: {
                // 导出所有账号
                FILE *fp = fopen("export_users.txt", "w");
                if (fp) {
                    UserNode *cur = userHead;
                    while (cur) {
                        fprintf(fp, "%s %s %d %d\n", cur->user.username, cur->user.password,
                                cur->user.role, cur->user.studentId);
                        cur = cur->next;
                    }
                    fclose(fp);
                    printf("已导出到 export_users.txt\n");
                } else {
                    printf("文件创建失败。\n");
                }
                pauseConsole();
                break;
            }
            case 5:
                teacherMenu();  // 复用教师菜单
                break;
            case 6: {
                char newPass[20];
                printf("请输入新密码: ");
                safeInput(newPass, sizeof(newPass));
                UserNode *me = findUserByUsername(currentUser.username);
                if (me) changePassword(me, newPass);
                pauseConsole();
                break;
            }
            case 7:
                return;
            default:
                printf("无效选项。\n");
                pauseConsole();
        }
    } while (1);
}