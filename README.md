# 这是一个实现中国象棋的项目
## 类关系简介
1. Game类，提供游戏接口，作为用户最终使用的头文件，对外接口只有一个start()成员。此类用于实现和用户几乎所有游戏中交互的接口，包括用户创建与登录、菜单选择、存档与读档、游戏进行。对Board进行操作。
2. Board类，实现棋盘，承载双方棋子。在Game类开始对局或者加载对局的时候被创建，并在被创建时创建Piece。对Piece进行操作。
3. Piece类，抽象基类，代表棋子，下派生出七种棋子。本身只用于检测移动条件，真正的移动由Board类完成。
    | 类名   | 红方   | 黑方  |
    |:------:|:-----:|:-----:|
    |Pawn    |兵     |卒     |
    |Cannon  |炮     |砲     |
    |Chariot |车     |車     |
    |Horse   |马     |馬     |
    |Minister|相     |象     |
    |Mandarin|仕     |士     |
    |King    |帅     |将     |
4. 下面是UML类图
    ![ChineseChess.jpg](https://i.loli.net/2020/03/14/WyruEUsRtHK8An4.png)
## 类的使用
1. 仅仅是添加了用户、菜单和存档的中国象棋而已。所以只需要包含Game.hpp之后，创建Game对象，调用start()成员就可以运行了。
## 一些注意事项
1. 由于本项目无法做到鼠标交互，所以只能通过键盘输入进行选择和命令，这就不可避免地导致了输入流错误的可能性。本人尽力做到保证鲁棒性，但还是不敌EOF在有效字符输入之后的情况，这会导致其后字符无效，并且需要在下一行继续输入。其余可能产生的输入问题不再赘述，还望hack的时候下手能轻一点。~~虽然炸的不是我的电脑。~~
2. 由于本项目选材的局限性，所创建类的应用范围比较窄，类的设计上也有局限性。~~所以如果真的要hack可以调用类的公有接口成员。~~
3. 由于本项目需要实现彩色文本，所以就导致了会产生windows和linux两个版本。在windows平台上使用cmake遇到了本人目前无法解决的问题(指多方百度无果)，所以需要亲手编译。各平台版本的运行方式请参见相应文件夹下的README。
4. 由于本项目涉及存档，但是多平台下创建文件夹需要对应头文件，并且操作不同且复杂，所以会将数据文件存在运行目录下。所以如果不想让文件夹被污染，建议在一个新建文件夹里运行。~~其实就是作者偷懒的锅。~~
5. 本项目设有彩蛋。
## 一些题外话(~~急的话现在就可以走了~~)
1. 这么多行的代码，怎么想都觉得好多啊。
2. 其实上面那一条就是石乐志，大部分都是重复cv堆出来的。
3. 妄图添加自定义模式和更多彩蛋，但是时间关系没有完成。
4. 两个平台的彩色文本代码和选择的字符编码都不同，实在是搞人心态。
5. windows的cmake，开始能跑，后面就疯狂抽风。vscode令人又爱又恨。但该香还得香。
6. 实际上菜单等功能和实现对局本身的设计时间和代码量似乎不相上下。
7. 最开始是想做一个抽卡+养成+回合制的小游戏，但是过于沙雕被pass了。
8. 其实我一直在模仿ilem教主的分点简介。
9. 磅15便士。
10. 完结撒花！
