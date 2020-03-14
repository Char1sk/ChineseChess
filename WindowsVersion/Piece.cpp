#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include "Board.hpp"
#include "Piece.hpp"

// 抽象基类

void Piece::team_out(const std::string &s1, const std::string &s2)
{
    if(is_red)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        std::cout << s1 ;
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        std::cout << s2 ;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
bool Piece::out_sea()
{
    if(is_red)
        if(x <= 4)
            return true;
        else
            return false;
    else
        if(x >= 5)
            return true;
        else
            return false;
}
bool Piece::out_sea(int xpos)
{
    if(is_red)
        if(xpos <= 4)
            return true;
        else
            return false;
    else
        if(xpos >= 5)
            return true;
        else
            return false;
}
bool Piece::out_camp(int xpos, int ypos)
{
    if(is_red)
        if(7 <= xpos && xpos <= 9 && 3 <= ypos && ypos <= 5)
            return false;
        else
            return true;
    else
        if(0 <= xpos && xpos <= 2 && 3 <= ypos && ypos <= 5)
            return false;
        else
            return true;
}
void Piece::move(int tox, int toy)
{
    x = tox;
    y = toy;
}

// 兵

bool Pawn::check_legal(const Board &bd, int tox, int toy)
{
    // 没过河，只能向前
    if(!out_sea())
        if(is_red)
            if(tox == x-1 && toy == y)
                return true;
            else
                return false;
        else
            if(tox == x+1 && toy == y)
                return true;
            else
                return false;
    // 过河卒，移动一格，不可后退
    else
        if(is_red)
            if( tox <= x && std::abs(x-tox) + std::abs(y-toy) == 1 )
                return true;
            else
                return false;
        else
            if( tox >= x && std::abs(x-tox) + std::abs(y-toy) == 1 )
                return true;
            else
                return false;
}
char Pawn::save()
{
    return is_red ? 'A' : 'a';
}
void Pawn::show()
{
    team_out(" 兵", " 卒");
}

// 炮

bool Cannon::check_legal(const Board &bd, int tox, int toy)
{
    // 攻击，除开两点，中有一子
    if(bd.check_exist(tox, toy))
        if(bd.check_cnt(x, y, tox, toy) == 3)
            return true;
        else
            return false;
    // 移动，除开自己，中无一子
    else
        if(bd.check_cnt(x, y, tox, toy) == 1)
            return true;
        else
            return false;
}
char Cannon::save()
{
    return is_red ? 'B' : 'b';
}
void Cannon::show()
{
    team_out(" 炮", " 砲");
}

// 车

bool Chariot::check_legal(const Board &bd, int tox, int toy)
{
    // 攻击，除开两点，中无一子
    if(bd.check_exist(tox, toy))
        if(bd.check_cnt(x, y, tox, toy) == 2)
            return true;
        else
            return false;
    // 移动，除开自己，中无一子
    else
        if(bd.check_cnt(x, y, tox, toy) == 1)
            return true;
        else
            return false;
}
char Chariot::save()
{
    return is_red ? 'C' : 'c';
}
void Chariot::show()
{
    team_out(" 车", " 車");
}

// 马

bool Horse::check_legal(const Board &bd, int tox, int toy)
{
    // 上下跳，不蹩脚
    if( std::abs(x-tox) == 2 && std::abs(y-toy) == 1 )
        if(x <= tox)
            return !bd.check_exist(x+1, y);
        else
            return !bd.check_exist(x-1, y);
    // 左右跳，不蹩脚
    else if( std::abs(x-tox) == 1 && std::abs(y-toy) == 2 )
        if(y <= toy)
            return !bd.check_exist(x, y+1);
        else
            return !bd.check_exist(x, y-1);
    else
        return false;
}
char Horse::save()
{
    return is_red ? 'D' : 'd';
}
void Horse::show()
{
    team_out(" 马", " 馬");
}

// 相

bool Minister::check_legal(const Board &bd, int tox, int toy)
{
    // 不得过河，只能走田，不能蹩脚
    if( !out_sea(tox) && std::abs(x-tox) == 2 && std::abs(y-toy) == 2 && !bd.check_exist( (x+tox)/2, (y+toy)/2 ) )
        return true;
    else
        return false;
}
char Minister::save()
{
    return is_red ? 'E' : 'e';
}
void Minister::show()
{
    team_out(" 相", " 象");
}

// 士

bool Mandarin::check_legal(const Board &bd, int tox, int toy)
{
    // 不得出营，只能斜行
    if( !out_camp(tox, toy) && std::abs(x-tox) == 1 && std::abs(y-toy) == 1 )
        return true;
    else
        return false;
}
char Mandarin::save()
{
    return is_red ? 'F' : 'f';
}
void Mandarin::show()
{
    team_out(" 仕", " 士");
}

// 王

bool King::check_legal(const Board &bd, int tox, int toy)
{
    // 中门对狙
    if( bd.check_exist(tox, toy) && bd.check_king(tox, toy) )
        if( bd.check_cnt(x, y, tox, toy) == 2 )
            return true;
        else
            return false;
    // 不得出营，移动一格
    else
        if( !out_camp(tox, toy) && std::abs(x-tox) + std::abs(y-toy) == 1)
            return true;
        else
            return false;
}
char King::save()
{
    return is_red ? 'G' : 'g';
}
void King::show()
{
    team_out(" 帅", " 将");
}
