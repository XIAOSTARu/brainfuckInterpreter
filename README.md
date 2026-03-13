# brainfuckInterpreter
- 版本 1.0.4
- brainfuck解释器，带调试功能。
- 优化了原版brainfuck指令，对连续的`+-><`进行压缩
- 使用栈存储循环位置
- 当遇到[且当前值等于0的情况下mode保存栈指针转跳过模式
- 可以使用debug模式来进行一个一个指令执行，搭配其他debug实时查看当前内存格状态和指令执行状态
---
# 使用教程
- 使用编译器编译链接main.c interpreter.c setting.c bfio.c文件即可。
```shell
clang main.c interpreter.c setting.c bfio.c -o brainfuck
./brainfuck [bf file]
```
- 其他选项在help中查看
```shell
./brainfuck --help
```
# 更新内容
- 参数 `-E` 可以直接执行bf代码，而不是从文件读取
如：
```shell
./brainfuck -E "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>."
```
- 2026y 2m 26d

---
English:
-V / --version         --- Get version number
-H / --help            --- Get help
-C / --auto-codesize   --- Automatically calculate code size
-D / --debug           --- Toggle debug mode (step)
-M / --debug-printmem  --- Toggle memory print
-P / --debug-print     --- Print program execution status
-O / --debug-print-outputbuffer  --- Print output buffer
-E / --execute         --- Read code directly from the command line
-m / --mem       [int] --- Set the memory size
-s / --stacksize [int] --- Set the stack size
-c / --codesize  [int] --- Set the code buffer size
-r / --debug-callsystem [string] --- Every time the code is executed,the system is called once.

Chinese:
-V / --version                   --- 获取版本号
-H / --help                      --- 获取帮助
-C / --auto-codesize             --- 自动计算代码大小
-D / --debug                     --- 切换调试模式（步骤）
-M / --debug-printmem            --- 切换内存打印
-P / --debug-print               --- 打印程序执行状态
-O / --debug-print-outputbuffer  --- 打印输出缓冲区
-E / --execute                   --- 直接从命令行读取代码
-m / --mem [int]                 --- 设置内存大小
-s / --stacksize [int]           --- 设置堆栈大小
-c / --codesize [int]            --- 设置代码缓冲区大小
-r / --debug-callsystem [string] --- 每次执行代码时，系统都会被调用一次。

- version: 1.0.4

---
作者:
最近很忙，没时间更新此仓库。
功能已经做的差不多了，感觉没什么可做的。
以后可能只会更新一点优化的。
---
