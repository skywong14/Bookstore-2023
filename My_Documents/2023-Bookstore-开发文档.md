# Bookstore开发文档
作者：2023级，skywong

## 程序功能概述

这是一个书店管理系统，可以通过命令行交互实现各类操作。

## 主体逻辑说明

### 子系统

- 在`main.cpp`中，通过`user_class`, `book_class`, `log_class`实现操作，各个`class`间相互独立，各自管理文件，数据不互通，通过`main`主程序实现三个`class`间必要的数据传输。

### 系统的初始化，开启，和退出

- 如果为**初次运行系统**，即为创建相关文件，则在初始化存储文件的同时调用初始化函数，**创建**店主账户。
- 如果已初始化（即文件存在），则正常初始化。
- 退出系统(`exit`和`quit`指令)或输入流结束(`eof`)时，清空用户栈，结束程序。

### 处理指令的一般流程（main函数）


由主程序负责调度，在**运行过程**中，对于每一条指令：

- 在`main.cpp`中使用`format.h/cpp`中的`get_tokens`拆分指令到`tokens[]`，根据头部的单词判断需要执行的指令。
- 如果不正确的指令流，返回错误信息（错误信息由`enum class ReturnMode`限定类别，调试时可输出具体错误内容）
- 一般需要考虑的内容：`tokens`格式是否正确，`now_permission(当前用户信息)`是否足够，`ISBN`对应书是否存在等等。

### 具体指令

#### 基础指令

- `quit`或`exit`：退出系统 

#### 账户系统指令
此部分调用`User.h/cpp`模块
**User文件的维护**：调用`memoryio.h/cpp`的函数来维护，`index`为用户名，`value`为`用户名，用户权限，密码加密值`。文件存储在`./Users_index(value).txt`。

**登录栈（User_Stack）的维护**：使用`vector<pair<Userinfo, string> >`模拟栈，其中`pair<Userinfo, string>`中`userinfo`存用户相关信息，后一个存储`select`操作选的数的`ISBN`，初始为空。

**now_permission, now_select**：存储登录栈顶用户的权限和`select`书目，较常用

- `su [UserID] ([Password])?`：如果当前用户权限大于要登陆的用户，可忽略密码，否则判断密码时候正确。操作合法则执行`User_Stack.push_back(...)`。
- `logout`：`User_Stack.pop_back()`，如果弹出后登陆栈为空，`push_back`一个游客账户。
- `register`：判断用户名是否冲突，为冲突则在`./Database/Users.txt`中添加新用户信息
- `passwd`：判断操作是否合法，然后再`./Database/Users.txt`中更新密码
- `useradd`：判断当前账户权限和用户名冲突以及是否权限足够，随后更新`./Database/Users.txt`
- `delete`：合法则调用`Fileio.h`中的`del`函数即可。

#### 图书系统指令
此部分调用`Bookinfo.h/cpp`
- `show`：检索图书，如果关键字为`ISBN`则直接调用`Bookinfo.h`的`seek`，否则在`./Database/Search/xxx.txt`中查询关键词，把所有符合条件的图书加入`vector`返回后输出。（*可考虑实现*：额外创建一个文件，用于存储各关键字所对应的图书，一样采用块状链表维护）
- `select`：检查`ISBN`对应书是否存在，存在则把登陆栈中对应该用户的`.second`修改，不存在则创建。
- `modify`：检验操作是否合法，随后调用`Bookinfo`的修改函数。
- `buy`：检验操作是否合法，随后更新`./Database/Order.txt`和`./Database/Stock.txt`。
- `import`：检验操作是否合法，随后根据数量和价格更新`./Database/Order.txt`和`./Database/Stock.txt`。

#### 日志系统指令
此部分调用`log`模块
- `show finance ([Count])?`：在`./Order.txt`找到最后的`Count`条记录(或全部记录)
- `report finance`, `report employee`, `log`：用csv格式导出

## 代码文件结构
Bookstore程序的代码文件结构如下：
- `main.cpp`  主函数，程序的入口点。
- `liner_memoryio.h`和`memoryio.h`  线性文件 和 块状链表
- `format.h` 和 `format.cpp`  处理`tokens流`以及`token格式`
- `basic_tool.h` 和 `basic_tool.cpp` 包含报错信息，`int/longlong/double/string/char[]`之间的转换
- `bookinfo.h` 和 `bookinfo.cpp`  处理书籍信息相关，以及购买和进货指令
- `log.h` 和 `log.cpp`  日志相关
- `user.h` 和 `user.cpp`  用户相关
## 类及成员说明

### 功能说明
#### Memoryio类
- 块状链表：在`main.cpp`中实例化类模板，支持根据`index`实现查找、新增、修改、删除。
- 顺序文件：线性存储，一个文件对应一个`class`类型信息的存储。
#### Bookinfo类成员变量
- `index`: `[ISBN]`
- `value`：`[ISBN]-[BookName]-[Auther]-[Keyword]`，后面三个值统一长度后存储。
#### User类成员变量
- `index`: `username`
- `value`：存储内容即为`Userinfo`

#### Log类（负责Document）
该类负责生成和保存文档，以及`show finance`指令

## 文件存储说明

**存储的文件**
- 在`./Bookinfo*.txt`内保存书籍数据与数据的`Price`和相应库存
- 在`./User*.txt`内保存用户数据
- 在`./Log.txt`内保存交易数据
- 在`./Author*.txt, Keyword*.txt, Name*.txt`内保存关键字和拥有该关键字的所有图书的ISBN
- 其中带`*`的使用`memoryio`的块状链表，`Log.txt`按正常顺序存储

除此之外，目录下还会有由指令生成的文档。

除了生成的文档外，所有数据采用二进制保存。

## 其他补充说明
**程序的使用方法**:将该系统存储在某个位置，运行`main.exe`启动系统，输入`quit/exit`指令退出系统