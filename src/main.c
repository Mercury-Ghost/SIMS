#include "student.h"
#include "user.h"
#include "file.h"
#include "appeal.h"
#include "ui.h"
#include "utils.h"
#include "backup.h"

// 全局变量定义
StuNode *stuHead = NULL;  // 学生链表头指针

/**
 * 主函数
 * @return 程序退出状态码
 */
int main() {
    // 加载数据
    stuHead = loadStudentsFromFile();  // 从文件加载学生数据
    loadUsers();                      // 加载用户数据
    loadAppeals();                    // 加载申诉数据

    // 执行自动备份
    autoBackup(stuHead);

    // 进入登录界面
    loginMenu();

    // 释放资源
    freeList(stuHead);   // 释放学生链表内存
    freeUsers();         // 释放用户链表内存
    freeAppeals();       // 释放申诉链表内存
    return 0;
}