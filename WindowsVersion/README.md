# Windows版本中国象棋
## 注意
- 采用GB2312编码
- 有windows.h头文件
- 未使用CMake
- 所有文件均在一个文件夹下
- 运行产生的文件在可执行文件所在目录
## 运行方式
编译所有cpp文件，你可以选择下两者之一：
> $ g++ *.cpp -o main.exe

> $ g++ main.cpp Game.cpp Board.cpp Piece.cpp -o main.exe

之后运行可执行文件即可：
> $ .\main.exe
