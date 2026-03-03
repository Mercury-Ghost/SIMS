# SIMS - 学生信息管理系统

## 项目简介

SIMS（Student Information Management System）是一个基于C语言开发的学生信息管理系统，旨在为学校提供一个简单、高效的学生信息管理解决方案。系统支持学生信息的增删改查、用户管理、申诉处理等功能，并具有不同角色的权限管理。

## 系统架构

### 核心模块

- **学生信息管理**：处理学生基本信息和成绩的管理
- **用户管理**：管理不同角色的用户账号
- **申诉管理**：处理学生的申诉请求
- **文件操作**：负责数据的持久化存储
- **UI界面**：提供用户交互界面
- **工具函数**：提供通用功能支持
- **数据分析**：提供数据统计和分析功能
- **页面管理**：处理分页显示功能

### 系统角色

- **学生**：查看个人信息，提交申诉
- **教师**：管理学生信息，处理申诉
- **管理员**：管理所有用户，拥有最高权限

## 目录结构

```
SIMS/
├── analyze.c        # 数据分析模块
├── analyze.h
├── appeal.c         # 申诉管理模块
├── appeal.h
├── file.c           # 文件操作模块
├── file.h
├── main.c           # 主程序入口
├── page.c           # 页面管理模块
├── page.h
├── student.c        # 学生信息管理模块
├── student.h
├── student_sys.exe  # 可执行文件
├── ui.c             # 界面模块
├── ui.h
├── user.c           # 用户管理模块
├── user.h
├── users.txt        # 用户数据文件
├── utils.c          # 工具函数模块
└── utils.h
```

## 主要功能

### 1. 学生信息管理
- 添加学生信息
- 删除学生信息
- 修改学生信息
- 查询学生信息（按ID或姓名）
- 学生成绩排序
- 学生信息统计分析

### 2. 用户管理
- 用户登录
- 用户注册
- 修改密码
- 管理员重置用户密码
- 管理员删除用户

### 3. 申诉管理
- 学生提交申诉
- 查看申诉列表
- 标记申诉为已处理
- 统计未处理申诉数量

### 4. 数据持久化
- 自动加载数据文件
- 自动保存数据到文件
- 支持数据的备份和恢复

## 技术特点

- **纯C语言实现**：无需额外依赖，跨平台兼容性好
- **模块化设计**：各功能模块独立封装，便于维护和扩展
- **数据结构**：使用链表存储数据，操作灵活高效
- **权限控制**：基于角色的权限管理，确保数据安全
- **用户友好**：清晰的命令行界面，操作简单直观

## 编译与运行

### 编译

使用C编译器编译所有源文件：

```bash
gcc -o student_sys.exe main.c student.c user.c file.c appeal.c ui.c utils.c analyze.c page.c
```

### 运行

直接运行生成的可执行文件：

```bash
./student_sys.exe
```

## 使用说明

1. **登录系统**：运行程序后，输入用户名和密码登录
2. **选择角色**：根据提示选择相应的角色（学生、教师、管理员）
3. **功能操作**：根据角色权限，选择相应的功能进行操作
4. **退出系统**：完成操作后，选择退出选项

### 初始账号

- **管理员**：用户名：admin，密码：admin
- **教师**：用户名：teacher，密码：teacher
- **学生**：系统初始无学生账号，需要通过注册或管理员添加

## 数据文件说明

- **users.txt**：存储用户账号信息
- **students.txt**：存储学生信息（系统自动生成）
- **appeals.txt**：存储申诉信息（系统自动生成）

## 注意事项

1. 系统使用简单的文件存储，不支持并发操作
2. 密码以明文形式存储，仅用于演示，实际应用中应加密存储
3. 数据文件应妥善保管，避免误删除
4. 系统未实现网络功能，仅支持本地运行

## 扩展建议

1. 添加数据库支持，提高数据存储的可靠性和效率
2. 实现网络功能，支持多用户同时访问
3. 增加更多数据分析和报表功能
4. 开发图形化界面，提升用户体验
5. 添加数据备份和恢复机制

## 许可证

本项目采用 MIT 许可证开源。

### MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## 作者

- 项目维护者：Mercury-Ghost
- 联系邮箱：sbc0124@outlook.com

---

(c) 2026 SIMS 学生信息管理系统