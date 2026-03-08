# SIMS API 文档

## 概述

本文档描述了学生信息管理系统（SIMS）的主要API接口，旨在为开发者提供系统集成和扩展的参考。

## 核心模块API

### 1. 学生信息管理模块

#### 函数列表

| 函数名 | 说明 | 参数 | 返回值 |
|--------|------|------|--------|
| `createStuNode` | 创建学生节点 | id: int 学号<br>name: const char* 姓名<br>score: float 成绩 | StuNode* 学生节点指针 |
| `addStudent` | 添加学生到链表末尾 | head: StuNode* 链表头指针<br>id: int 学号<br>name: const char* 姓名<br>score: float 成绩 | StuNode* 更新后的链表头指针 |
| `deleteById` | 根据学号删除学生 | head: StuNode* 链表头指针<br>id: int 要删除的学号 | StuNode* 更新后的链表头指针 |
| `findById` | 根据学号查找学生 | head: StuNode* 链表头指针<br>id: int 要查找的学号 | StuNode* 找到的学生节点指针，未找到返回NULL |
| `findByName` | 根据姓名模糊查找学生 | head: StuNode* 链表头指针<br>name: const char* 要查找的姓名关键字 | void |
| `updateStudent` | 更新学生信息 | node: StuNode* 要更新的学生节点<br>newName: const char* 新姓名<br>newScore: float 新成绩 | void |
| `getLength` | 获取链表长度 | head: StuNode* 链表头指针 | int 链表长度 |
| `insertAtPosition` | 在指定位置插入学生 | head: StuNode* 链表头指针<br>pos: int 插入位置（从1开始）<br>id: int 学号<br>name: const char* 姓名<br>score: float 成绩 | StuNode* 更新后的链表头指针 |
| `freeList` | 释放链表内存 | head: StuNode* 链表头指针 | void |
| `sortByScore` | 按成绩排序 | head: StuNode* 链表头指针<br>ascending: int 1为升序，0为降序 | void |
| `queryStudents` | 多条件查询学生 | head: StuNode* 链表头指针<br>name: const char* 姓名关键字（NULL表示不按姓名查询）<br>minId: int 最小学号（-1表示不限制）<br>maxId: int 最大学号（-1表示不限制）<br>minScore: float 最低成绩（-1表示不限制）<br>maxScore: float 最高成绩（-1表示不限制） | StuNode* 查询结果链表头指针 |
| `sortQueryResults` | 按指定字段排序查询结果 | head: StuNode* 查询结果链表头指针<br>field: const char* 排序字段（"id", "name", "score"）<br>ascending: int 1为升序，0为降序 | void |

### 2. 用户管理模块

#### 函数列表

| 函数名 | 说明 | 参数 | 返回值 |
|--------|------|------|--------|
| `loadUsers` | 从users.txt加载所有用户 | 无 | void |
| `saveUsers` | 保存所有用户到users.txt | 无 | void |
| `registerUser` | 注册新用户 | username: const char* 用户名<br>password: const char* 密码<br>role: int 角色<br>studentId: int 学生学号（仅学生角色需要） | int 注册成功返回1，失败返回0 |
| `loginUser` | 登录验证 | username: const char* 用户名<br>password: const char* 密码 | int 登录成功返回用户角色，失败返回-1 |
| `findUserByUsername` | 按用户名查找用户节点 | username: const char* 用户名 | UserNode* 找到的用户节点指针，未找到返回NULL |
| `changePassword` | 修改密码 | userNode: UserNode* 用户节点<br>newPass: const char* 新密码 | void |
| `adminResetPassword` | 管理员重置用户密码 | username: const char* 用户名<br>newPass: const char* 新密码 | void |
| `deleteUser` | 管理员删除用户 | username: const char* 用户名 | int 删除成功返回1，失败返回0 |
| `freeUsers` | 释放用户链表 | 无 | void |

### 3. 申诉管理模块

#### 函数列表

| 函数名 | 说明 | 参数 | 返回值 |
|--------|------|------|--------|
| `loadAppeals` | 从appeals.txt加载申诉 | 无 | void |
| `saveAppeals` | 保存申诉到appeals.txt | 无 | void |
| `addAppeal` | 添加申诉（学生端） | stuId: int 学生学号<br>content: const char* 申诉内容 | void |
| `getPendingAppealCount` | 获取未处理申诉数量 | 无 | int 未处理申诉数量 |
| `showAllAppeals` | 显示所有申诉（翻页） | 无 | void |
| `markAppealProcessed` | 标记申诉为已处理 | stuId: int 学生学号 | void |
| `freeAppeals` | 释放申诉链表内存 | 无 | void |

### 4. 文件操作模块

#### 函数列表

| 函数名 | 说明 | 参数 | 返回值 |
|--------|------|------|--------|
| `loadStudentsFromTextFile` | 从文本文件加载学生链表 | 无 | StuNode* 加载的学生链表头指针 |
| `loadStudentsFromFile` | 从二进制文件加载学生链表 | 无 | StuNode* 加载的学生链表头指针 |
| `saveStudentsToFile` | 保存学生链表到二进制文件 | head: StuNode* 学生链表头指针 | void |
| `importStudentsFromCSV` | 从CSV文件批量导入学生数据 | filename: const char* CSV文件名<br>head: StuNode** 学生链表头指针的指针 | int 导入的学生数量，失败返回-1 |
| `exportStudentsToCSV` | 将学生数据导出为CSV格式 | filename: const char* CSV文件名<br>head: StuNode* 学生链表头指针 | int 导出的学生数量，失败返回-1 |

### 5. 工具函数模块

#### 函数列表

| 函数名 | 说明 | 参数 | 返回值 |
|--------|------|------|--------|
| `clearScreen` | 清屏（跨平台） | 无 | void |
| `pauseConsole` | 暂停并提示按enter键继续 | 无 | void |
| `safeInput` | 安全输入字符串，自动去除换行 | buffer: char* 输入缓冲区<br>size: int 缓冲区大小 | void |
| `isNumber` | 检查输入是否为数字（整数或浮点数） | str: const char* 输入字符串 | int 是数字返回1，否则返回0 |
| `readInt` | 从标准输入读取一个整数（带错误处理） | 无 | int 读取的整数 |
| `isValidStudentId` | 验证学号是否有效 | str: const char* 学号字符串 | int 有效返回1，否则返回0 |
| `isValidScore` | 验证成绩是否在有效范围内 | score: float 成绩 | int 有效返回1，否则返回0 |
| `isValidUsername` | 验证用户名是否有效 | str: const char* 用户名 | int 有效返回1，否则返回0 |
| `isValidPassword` | 验证密码是否有效 | str: const char* 密码 | int 有效返回1，否则返回0 |
| `isFloat` | 检查输入是否为浮点数 | str: const char* 输入字符串 | int 是浮点数返回1，否则返回0 |
| `readFloat` | 从标准输入读取一个浮点数（带错误处理） | 无 | float 读取的浮点数 |
| `handleWriteError` | 处理写入错误 | fp: FILE* 文件指针<br>msg: const char* 错误消息 | bool 总是返回false |

### 6. 数据分析模块

#### 函数列表

| 函数名 | 说明 | 参数 | 返回值 |
|--------|------|------|--------|
| `analyzeClass` | 分析班级成绩 | head: StuNode* 学生链表头指针 | void |
| `printBarChart` | 打印成绩条状图 | score: float 学生成绩 | void |
| `getRank` | 获取学生在班级中的排名 | head: StuNode* 学生链表头指针<br>id: int 学生学号 | int 排名，未找到返回-1 |

### 7. 页面管理模块

#### 函数列表

| 函数名 | 说明 | 参数 | 返回值 |
|--------|------|------|--------|
| `showStudentsPage` | 显示学生列表（翻页） | head: StuNode* 学生链表头指针 | void |

### 8. 备份模块

#### 函数列表

| 函数名 | 说明 | 参数 | 返回值 |
|--------|------|------|--------|
| `generateBackupFilename` | 生成备份文件名 | filename: char* 输出文件名缓冲区<br>size: size_t 缓冲区大小 | void |
| `backupData` | 执行数据备份 | head: StuNode* 学生链表头指针 | bool 备份是否成功 |
| `restoreData` | 从备份文件恢复数据 | filename: const char* 备份文件名<br>head: StuNode** 学生链表头指针的指针 | bool 恢复是否成功 |
| `autoBackup` | 执行自动备份 | head: StuNode* 学生链表头指针 | void |
| `listBackupFiles` | 列出所有备份文件 | 无 | void |

## 数据结构

### 1. 学生节点结构体

```c
typedef struct Student {
    int id;             // 学号
    char name[20];      // 姓名
    float score;        // 成绩
    struct Student *prev; // 前一个节点指针
    struct Student *next; // 后一个节点指针
} StuNode;
```

### 2. 用户结构体

```c
typedef struct User {
    char username[20];    // 用户名
    char password[20];    // 密码
    int role;             // 角色：0学生,1教师,2管理员
    int studentId;        // 学生关联学号，教师/管理员为-1
} User;
```

### 3. 用户节点结构体

```c
typedef struct UserNode {
    User user;            // 用户信息
    struct UserNode *next; // 下一个节点指针
} UserNode;
```

### 4. 申诉节点结构体

```c
typedef struct Appeal {
    int studentId;       // 学生学号
    char content[100];   // 申诉内容
    int status;          // 状态：0未处理，1已处理
    struct Appeal *next; // 下一个节点指针
} AppealNode;
```

## 全局变量

| 变量名 | 类型 | 说明 |
|--------|------|------|
| `stuHead` | StuNode* | 学生链表头指针 |
| `userHead` | UserNode* | 用户链表头指针 |
| `currentUser` | User | 当前登录用户信息 |
| `appealHead` | AppealNode* | 申诉链表头指针 |

## 常量定义

| 常量名 | 值 | 说明 |
|--------|------|------|
| `ROLE_STUDENT` | 0 | 学生角色 |
| `ROLE_TEACHER` | 1 | 教师角色 |
| `ROLE_ADMIN` | 2 | 管理员角色 |
| `MAX_NAME_LEN` | 20 | 最大姓名长度 |
| `MAX_CONTENT_LEN` | 100 | 最大内容长度 |
| `PAGE_SIZE` | 5 | 每页显示条数 |
| `MAX_INPUT` | 256 | 最大输入长度 |

## 使用示例

### 1. 添加学生

```c
// 添加一个新学生
stuHead = addStudent(stuHead, 20230001, "张三", 85.5);
// 保存到文件
saveStudentsToFile(stuHead);
```

### 2. 用户登录

```c
// 登录验证
int role = loginUser("admin", "admin");
if (role != -1) {
    printf("登录成功！\n");
    // 根据角色进入相应菜单
    if (role == ROLE_STUDENT) studentMenu();
    else if (role == ROLE_TEACHER) teacherMenu();
    else adminMenu();
} else {
    printf("用户名或密码错误！\n");
}
```

### 3. 提交申诉

```c
// 提交申诉
addAppeal(currentUser.studentId, "成绩计算错误，请重新核查。");
```

## 扩展建议

1. **模块化扩展**：可以基于现有模块进行扩展，添加新的功能模块
2. **接口适配**：可以为现有API添加适配层，方便与其他系统集成
3. **数据存储**：未来可以将文件存储替换为数据库存储，提高数据管理效率
4. **网络功能**：可以添加网络接口，支持远程访问和操作
5. **插件系统**：可以设计插件系统，支持功能的动态扩展

## 注意事项

1. 所有API函数都假设输入参数是有效的，实际使用时应进行参数验证
2. 内存管理由调用者负责，使用完链表后应调用相应的free函数释放内存
3. 文件操作函数假设文件路径正确，实际使用时应进行错误处理
4. 本API文档基于当前版本，未来版本可能会有变化
