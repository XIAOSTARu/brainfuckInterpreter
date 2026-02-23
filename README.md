# brainfuckInterpreter
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
