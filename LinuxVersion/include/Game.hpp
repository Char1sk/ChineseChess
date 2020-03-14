#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>
#include <cctype>
#include "Board.hpp"

//提供接口，存放对局，进行对局
class Game
{
private:
    // 工具函数

    // 获取用户输入，同时保证不让输入炸掉
    std::string choose(const std::string &hint);
    // 读取存档菜单全部内容
    std::string get_all(const std::string &fname);
    // 合法名称
    bool legal_name(const std::string &name);
    // 登陆界面
    void login();
    // 菜单页面
    void menu();
    // 开始游戏
    void new_game();
    // 读取存档
    void continue_game();
    // 退出游戏
    void quit_game();
    // 进行对局
    void play_game(Board &bd);
    // 保存对局
    void save_game(Board &bd);
    // 加载对局
    void load_game(const std::string &name);
    // 对局帮助
    void get_help();
    
public:
    // 对外接口，进入游戏
    void start();
};
