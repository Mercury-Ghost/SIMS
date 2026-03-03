#include "student.h"
#include "user.h"
#include "file.h"
#include "appeal.h"
#include "ui.h"
#include "utils.h"

// 全局变量定义
StuNode *stuHead = NULL;

int main() {
    // 加载数据
    stuHead = loadStudentsFromFile();
    loadUsers();
    loadAppeals();

    // 进入登录界面
    loginMenu();

    // 释放资源
    freeList(stuHead);
    freeUsers();  // 需要实现freeUsers函数，已在user.h声明
    // 申诉链表也需释放，简单起见在freeUsers类似处理，但未定义，可加
    // 这里略，实际可以加一个freeAppeals，但为了简洁，不处理也无大碍。
    return 0;
}