#include <iostream>
#include <cstdio>
#include <vector>
#include <memory>
#include <cmath>
#include "Board.hpp"
#include "Piece.hpp"

// 控制输出的颜色

#define BRIGHT "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define ORIGIN "\033[0m"

template<typename pieceT>
        void Board::make_piece(int xpos, int ypos, bool team)
{
    board[xpos][ypos] = std::make_shared<pieceT>(xpos, ypos, team);
}
Board::Board() : 
        is_end(0), red_playing(1), board(10, std::vector<std::shared_ptr<Piece>>(9, nullptr))
{
    // 实在想不到什么好办法的构造
    make_piece<Chariot>(0, 0, 0);
    make_piece<Chariot>(0, 8, 0);
    make_piece<Chariot>(9, 0, 1);
    make_piece<Chariot>(9, 8, 1);
    make_piece<Horse>(0, 1, 0);
    make_piece<Horse>(0, 7, 0);
    make_piece<Horse>(9, 1, 1);
    make_piece<Horse>(9, 7, 1);
    make_piece<Minister>(0, 2, 0);
    make_piece<Minister>(0, 6, 0);
    make_piece<Minister>(9, 2, 1);
    make_piece<Minister>(9, 6, 1);
    make_piece<Mandarin>(0, 3, 0);
    make_piece<Mandarin>(0, 5, 0);
    make_piece<Mandarin>(9, 3, 1);
    make_piece<Mandarin>(9, 5, 1);
    make_piece<King>(0, 4, 0);
    make_piece<King>(9, 4, 1);
    make_piece<Cannon>(2, 1, 0);
    make_piece<Cannon>(2, 7, 0);
    make_piece<Cannon>(7, 1, 1);
    make_piece<Cannon>(7, 7, 1);
    make_piece<Pawn>(3, 0, 0);
    make_piece<Pawn>(3, 2, 0);
    make_piece<Pawn>(3, 4, 0);
    make_piece<Pawn>(3, 6, 0);
    make_piece<Pawn>(3, 8, 0);
    make_piece<Pawn>(6, 0, 1);
    make_piece<Pawn>(6, 2, 1);
    make_piece<Pawn>(6, 4, 1);
    make_piece<Pawn>(6, 6, 1);
    make_piece<Pawn>(6, 8, 1);
}
void Board::show_board() const 
{
    std::cout << std::string(31, '-') << std::endl;
    // 显示列坐标
    std::cout << "    一 二 三 四 五 六 七 八 九 " << std::endl;
    // 输出行坐标以及棋子
    // 每个棋子的输出委托给棋子本身
    for(int row = 0; row != 10; ++row)
    {
        printf("%3d", row+1);
        for(int col = 0; col != 9; ++col)
            if(board[row][col])
                board[row][col]->show();
            else
                std::cout << "   " ;
        std::cout << std::endl;
    }
    std::cout << std::string(31, '-') << std::endl;
    // 根据情况输出操作提示语句
    if(!is_end)
        if(red_playing)
            std::cout << BRIGHT << RED << "红方行动" << std::endl;
        else
            std::cout << BRIGHT << GREEN << "黑方行动" << std::endl;
    else
        if(!red_playing)
            std::cout << BRIGHT << RED << "红方胜利" << std::endl;
        else
            std::cout << BRIGHT << GREEN << "黑方胜利" << std::endl;
    std::cout << ORIGIN ;
}
void Board::move_piece(int fromx, int fromy, int tox, int toy)
{
    // 保证落点不越界
    if( 0 <= tox && tox <= 9 && 0 <= toy && toy <= 8 && 0 <= fromx && fromx <= 9 && 0 <= fromy && fromy <= 8 )
    {
        // 简化书写
        std::shared_ptr<Piece> pfrom(board[fromx][fromy]), pto(board[tox][toy]);
        // 判断起点和落点的合理性
        // 并且结合各棋子移动方式
        if( pfrom && pfrom->is_red == red_playing && 
                (!pto || pto->is_red != red_playing) && pfrom->check_legal(*this, tox, toy))
        {
            // 落点为王则游戏结束
            if(board[tox][toy] && board[tox][toy]->is_king())
                is_end = 1;
            // 修改棋子记录的坐标
            board[fromx][fromy]->move(tox, toy);
            // 修改棋盘上棋子坐标
            board[tox][toy] = board[fromx][fromy];
            board[fromx][fromy] = nullptr;
            // 交换双方的行动顺序
            red_playing = !red_playing;
        }
        // 无效移动
        else
            std::cout << "无效的行动！请重新移动。" << std::endl;
    }
    // 无效移动
    else
        std::cout << "无效的行动！请重新移动。" << std::endl;
}
bool Board::check_exist(int xpos, int ypos) const 
{
    return board[xpos][ypos] != nullptr;
}
bool Board::check_team(int xpos, int ypos) const 
{
    return board[xpos][ypos]->is_red ;
}
bool Board::check_king(int xpos, int ypos) const
{
    bool ans = board[xpos][ypos]->is_king() ;
    return ans;
}
int Board::check_cnt(int fromx, int fromy, int tox, int toy) const 
{
    int ans = 0;
    if(fromx == tox)
    {
        for(int i = std::min(fromy, toy); i != std::max(fromy, toy)+1; ++i)
            if(board[tox][i])
                ++ans;
    }
    else if(fromy == toy)
    {
        for(int j = std::min(fromx, tox); j != std::max(fromx, tox)+1; ++j)
            if(board[j][toy])
                ++ans;
    }
    return ans;
}
bool Board::end() const
{
    if(is_end)
        return true;
    else
        return false;
}
