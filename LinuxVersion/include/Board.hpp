#pragma once

#include <vector>
#include <memory>
#include "Piece.hpp"

class Piece;

// 作为棋盘，承载棋子，提供移动操作
class Board 
{
    friend class Game;

private:
    // 三个数据成员，一个工具函数

    // 对局是否结束
    bool is_end;
    // 当前回合行动方，true为红，false为黑
    bool red_playing;
    // 承载棋子的棋盘
    std::vector<std::vector<std::shared_ptr<Piece>>> board;

    // 用于构造函数的模板，创建棋子智能指针，无棋子则空指针
    template<typename pieceT>
        void make_piece(int xpos, int ypos, bool team);

public:
    // 棋盘操作

    // 构造函数，初始化棋盘
    Board();
    // 展示棋盘
    void show_board() const ;
    // 移动棋子
    void move_piece(int fromx, int fromy, int tox, int toy);
    // 是否结束
    bool end() const ;
    
    // 以下为为piece类提供的接口

    // 某处是否有棋子
    bool check_exist(int xpos, int ypos) const ;
    // 某处棋子的阵营
    bool check_team(int xpos, int ypos) const ;
    // 某处是否为将帅
    bool check_king(int xpos, int ypos) const ;
    // 闭区间内棋子数
    int check_cnt(int fromx, int fromy, int tox, int toy) const ;
};
