#pragma once

#include <iostream>
#include "Board.hpp"

class Board;

// 抽象基类，保留棋子共同部分
class Piece
{
    friend class Board;

protected:
    // 数据成员

    // 坐标，行为x，列为y
    int x;
    int y;
    // 棋子阵营
    bool is_red;

    // 工具函数
    
    // 根据阵营，选择颜色和文本输出
    void team_out(const std::string &s1, const std::string &s2);
    // 本身是否过河
    bool out_sea();
    // 落点是否过河
    bool out_sea(int xpos);
    // 落点是否出营
    bool out_camp(int xpos, int ypos);
    // 代表棋子是否为王
    virtual bool is_king() { return false; };
    // 纯虚函数，移动法则，判断移动是否合法
    virtual bool check_legal(const Board &bd, int tox, int toy) = 0;

public:
    // 构造函数，象征性地写一个默认构造，别的拷贝控制还是免了
    Piece() : x(0), y(0), is_red(1) {}
    Piece(int i1, int i2, bool team) : 
            x(i1), y(i2), is_red(team) {}
    // 更新数据成员中储存的本身位置
    void move(int tox, int toy);
    // 用于保存到文件中
    virtual char save() = 0;
    // 纯虚函数，根据阵营来输出自己
    virtual void show() = 0;

};
// 兵
class Pawn : public Piece
{
private:
    bool check_legal(const Board &bd, int tox, int toy) override;

public:
    Pawn() : Piece(){}
    Pawn(int i1, int i2, bool team) : 
            Piece(i1, i2, team) {}
    char save() override ;
    void show() override ;
};
// 炮
class Cannon : public Piece
{
private:
    bool check_legal(const Board &bd, int tox, int toy) override ;

public:
    Cannon() : Piece() {}
    Cannon(int i1, int i2, bool team) : 
            Piece(i1, i2, team) {}
    char save() override ;
    void show() override ;

};
// 车
class Chariot : public Piece
{
private:
    bool check_legal(const Board &bd, int tox, int toy) override ;

public:
    Chariot() : Piece() {}
    Chariot(int i1, int i2, bool team) : 
            Piece(i1, i2, team) {}
    char save() override ;
    void show() override ;

};
// 马
class Horse : public Piece
{
private:
    bool check_legal(const Board &bd, int tox, int toy) override ;

public:
    Horse() : Piece() {}
    Horse(int i1, int i2, bool team) : 
            Piece(i1, i2, team) {}
    char save() override ;
    void show() override ;

};
// 相
class Minister : public Piece
{
private:
    bool check_legal(const Board &bd, int tox, int toy) override ;

public:
    Minister() : Piece() {}
    Minister(int i1, int i2, bool team) : 
            Piece(i1, i2, team) {}
    char save() override ;
    void show() override ;

};
// 士
class Mandarin : public Piece
{
private:
    bool check_legal(const Board &bd, int tox, int toy) override ;

public:
    Mandarin() : Piece() {}
    Mandarin(int i1, int i2, bool team) : 
            Piece(i1, i2, team) {}
    char save() override ;
    void show() override ;

};
// 王
class King : public Piece
{
private:
    bool check_legal(const Board &bd, int tox, int toy) override ;

public:
    King() : Piece() {}
    King(int i1, int i2, bool team) : 
            Piece(i1, i2, team) {}
    // 值得注意，王本身是王
    bool is_king() override { return true; }
    char save() override ;
    void show() override ;

};
