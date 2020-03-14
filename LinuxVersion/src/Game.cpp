#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>
#include <cctype>
#include "Game.hpp"
#include "Board.hpp"

std::string Game::choose(const std::string &hint = "输入你要进行的操作: ")
{
    std::string ans;                //防止类型不匹配
    std::cout << hint << std::flush;
    std::getline(std::cin, ans);    //防止一行堆叠
    std::cin.clear();               //防止ctrl+Z
    return ans;
}
std::string Game::get_all(const std::string &fname)
{
    std::string ans, temp;
    // 若无该文件，创建一个
    std::ofstream new_or_read(fname, std::ofstream::app);
    new_or_read.close();
    // 读取，拼接
    std::ifstream ifs(fname);
    while(ifs >> temp)
        ans += temp + ' ';
    ifs.close();
    return ans;
}
bool Game::legal_name(const std::string &name)
{
    if( !isalpha(name[0]) && name[0] != '_' )
    {
        std::cout << "输入不符合规则！" << std::endl;
        return false;
    }
    for(auto &c: name)
        if( !isalnum(c) && c != '_')
        {
            std::cout << "输入不符合规则！" << std::endl;
            return false;
        }
    return true;
}
void Game::start()
{
    login();
    menu();
}
void Game::login()
{
    // 登录界面
    std::cout << "\n-----------登录界面------------" << std::endl;
    std::cout << "-- 1. 注册账号" << std::endl;
    std::cout << "-- 2. 登录账号" << std::endl;
    std::cout << "-- 3. 退出游戏" << std::endl;
    // 获取选项
    std::string cmd;
    do cmd = choose();
    while (cmd != "1" && cmd != "2" && cmd != "3");
    //ֻ 执行操作
    switch (cmd.front())
    {
    case '1':
        {   // 注册账号
            // 导入彩蛋
            std::ifstream ifs("easter.dat");
            while(!ifs.is_open())
            {
                std::ofstream ofs("easter.dat");
                ofs << "imkiva" << " 昵称重复，建议改为：imkiwa。开个玩笑，建议：不改。" << std::endl;
                ofs << "imkiwa" << " 昵称重复，建议改为：imkiva。开个玩笑，建议：不改。" << std::endl;
                ofs << "mikecovlee" << " 检测到该用户为root权限。嗯，root权限也没什么用。" << std::endl;
                ofs << "flowey" << " 我已经选了那个名字了。" << std::endl;
                ofs << "toriel" << " 我想你应该想一个你自己的名字，我的孩子。" << std::endl;
                ofs << "sans" << " 没门。" << std::endl;
                ofs << "papyrus" << " 我准了！" << std::endl;
                ofs << "undyne" << " 找你自己的名字！" << std::endl;
                ofs << "alphys" << " 别...别那样。" << std::endl;
                ofs << "alphy" << " 额，可以？" << std::endl;
                ofs << "mett" << " ohhhhhhh! 你是在推广我的品牌吗？" << std::endl;
                ofs << "asgore" << " 你不能。" << std::endl;
                ofs << "napsta" << " ...(他无力阻止你)" << std::endl;
                ofs << "asriel" << " ......" << std::endl;
                ofs << "chara" << " 真正的名字。" << std::endl;
                ofs << "frisk" << " 警告:这个名字会使你堕入地狱，无论如何都...等等，走错片场了。" << std::endl;
                ofs.close();
                ifs.open("easter.dat");
            }
            std::map<std::string, std::string> eggs;
            std::string key, value;
            while(ifs >> key >> value)
                eggs[key] = value;
            ifs.close();
            // 进行注册
            std::string acnts = get_all("accounts.dat");
            std::string unames = get_all("usersnames.dat");
            std::string acnt, pwd1, pwd2, uname;
            std::cout << std::string(31, '-') << std::endl;
            std::cout << "以下内容请只包含字母、数字、下划线，且不得以数字开头。" << std::endl;
            std::cout << "昵称输入建议全小写，也许会有什么事情发生？" << std::endl;
            std::cout << "如果需要返回上层界面，请在任何时候输入\"__back__\"" << std::endl;
            // 输入账号
            act:
            acnt = choose("请输入账号: ");
            if(acnt == "__back__")
                { login(); return; };
            if(!legal_name(acnt))
                goto act;
            if(acnts.find(acnt) != std::string::npos)
            {
                std::cout << "账号重复，请重新输入！" << std::endl;
                goto act;
            }
            // 输入密码
            pwd:
            pwd1 = choose("请输入密码: ");
            if(pwd1 == "__back__")
                { login(); return; };
            pwd2 = choose("请重复密码: ");
            if(pwd2 == "__back__")
                { login(); return; };
            if(pwd1 != pwd2)
            {
                std::cout << "两次密码必须相同！" << std::endl;
                goto pwd;
            }
            if(!legal_name(pwd1))
                goto pwd;
            // 输入昵称
            unm:
            uname = choose("请输入昵称: ");
            if(uname == "__back__")
                { login(); return; };
            if(!legal_name(uname))
                goto unm;
            if(eggs.find(uname) != eggs.end())
                std::cout << eggs[uname] << std::endl;
            if(unames.find(uname) != std::string::npos)
            {
                std::cout << "昵称重复，请重新输入！" << std::endl;
                goto unm;
            }
            // 注册完成
            std::cout << std::string(31, '-') << std::endl;
            std::cout << "注册成功！以下是您的用户信息，请妥善保存。" << std::endl;
            std::cout << "-- 账号: " << acnt  << std::endl;
            std::cout << "-- 密码: " << pwd1  << std::endl;
            std::cout << "-- 昵称: " << uname << std::endl;
            std::cout << "本次已为您自动登录" << std::endl;
            std::ofstream ofs;
            ofs.open("accounts.dat", std::ofstream::app);
            ofs << acnt << std::endl;
            ofs.close();
            ofs.open("usersnames.dat", std::ofstream::app);
            ofs << uname << std::endl;
            ofs.close();
            ofs.open(acnt + ".dat", std::ofstream::app);
            ofs << acnt << std::endl << pwd1 << std::endl << uname << std::endl << 0 << std::endl;
            ofs.close();
            // 为对局时提供接口
            ofs.open("now_playing.dat");
            ofs << uname << std::endl << 0 << std::endl;
            ofs.close();
        }
        break;
    case '2':
        {   // 登录账号
            // 导入账号资料
            std::string acnts = get_all("accounts.dat");
            std::string acnt, pwd, racnt, rpwd, runame;
            int dirty;
            std::cout << std::string(31, '-') << std::endl;
            std::cout << "如果需要返回上层界面，请在任何时候输入\"__back__\"" << std::endl;
            // 登录操作
            log:
            acnt = choose("请输入账号: ");
            if(acnt == "__back__")
                { login(); return; };
            pwd  = choose("请输入密码: ");
            if(pwd == "__back__")
                { login(); return; };
            if(acnts.find(acnt) == std::string::npos)
            {
                std::cout << "该账号不存在！" << std::endl;
                goto log;
            }
            std::ifstream ifs(acnt + ".dat");
            ifs >> racnt >> rpwd >> runame >> dirty;
            ifs.close();
            if(acnt != racnt || pwd != rpwd)
            {
                std::cout << "账号与密码不匹配！" << std::endl;
                goto log;
            }
            // 问候
            if(dirty == 0)
                std::cout << "欢迎回来，" << runame << "!" << std::endl;
            else
                std::cout << "你回来了？" << runame << ", 你这个肮脏的黑客。" << std::endl;
            // 为对局时提供接口
            std::ofstream ofs("now_playing.dat");
            ofs << runame << std::endl << dirty << std::endl;
            ofs.close();
        }
        break;
    case '3':
        // 退出游戏
        quit_game();
        break;
    default:
        break;
    }
}
void Game::menu()
{
    // 菜单界面
    std::cout << "\n-----------中国象棋------------" << std::endl;
    std::cout << "-- 1. 新游戏" << std::endl;
    std::cout << "-- 2. 继续游戏" << std::endl;
    std::cout << "-- 3. 退出游戏" << std::endl;
    // 菜单选项
    std::string cmd;
    do cmd = choose();
    while (cmd != "1" && cmd != "2" && cmd != "3");
    switch (cmd[0])
    {
    case '1':
        new_game();
        break;
    case '2':
        continue_game();
        break;
    case '3':
        quit_game();
        break;
    default:
        break;
    }
}
void Game::new_game()
{
    Board new_board;
    play_game(new_board);
}
void Game::continue_game()
{
    // 导入存档
    std::ifstream ifs("saves.dat");
    std::vector<std::string> snames, unames, ttimes;
    std::string stemp, utemp, ttemp;
    int len = 0;
    while(ifs >> stemp >> utemp >> ttemp)
    {
        ++len;
        snames.push_back(stemp);
        unames.push_back(utemp);
        ttimes.push_back(ttemp);
    }
    // 展示存档
    std::cout << std::string(31, '-') << std::endl;
    std::cout << "创建时间\t创建者\t\t存档名" << std::endl;
    for(int i = 0; i != len; ++i)
        std::cout << ttimes[i] << "\t" << unames[i] << "\t\t" << snames[i] << std::endl;
    // 选择存档
    choice:
    std::string cmd = choose("请输入要选择的存档名，输入\"__back__\"返回菜单: ");
    if(cmd == "__back__")
        menu();
    if(std::find(snames.begin(), snames.end(), cmd) == snames.end())
    {
        std::cout << "无效的输入！" << std::endl;
        goto choice;
    }
    load_game(cmd);
}
void Game::quit_game()
{
    std::cout << "游戏退出。" << std::endl;
    exit(0);
}
void Game::play_game(Board &bd)
{
    std::cout << std::string(31, '-') << std::endl;
    std::cout << "任何时候，输入\"__help__\"获取帮助，输入\"__save__\"保存对局，输入\"__quit__\"退出游戏。" << std::endl;
    while(1)
    {
        // 展示棋盘
        bd.show_board();
        // 获取输入
        std::string cmd = choose();
        if(cmd == "__help__")
        {
            get_help();
            continue;
        }
        if(cmd == "__save__")
        {
            save_game(bd);
            continue;
        }
        if(cmd == "__quit__")
        {
            std::cout << "对局成功退出。" << std::endl;
            break;
        }
        // 进行移动
        std::istringstream iss(cmd);
        int xfrom = 0, yfrom = 0, xto = 0, yto = 0;
        iss >> xfrom >> yfrom >> xto >> yto;
        bd.move_piece(xfrom-1, yfrom-1, xto-1, yto-1);
        // 结束对局
        if(bd.end())
        {
            bd.show_board();
            break;
        }
    }
    // 结束后菜单
    std::cout << std::string(31, '-') << std::endl;
    std::cout << "-- 1. 重新游戏" << std::endl;
    std::cout << "-- 2. 读取存档" << std::endl;
    std::cout << "-- 3. 返回菜单" << std::endl;
    // 结束后选项
    std::string cmd;
    do cmd = choose();
    while (cmd != "1" && cmd != "2" && cmd != "3");
    if(cmd == "1")  new_game();
    if(cmd == "2")  continue_game();
    if(cmd == "3")  menu();
}
void Game::save_game(Board &bd)
{
    // 导入存档
    std::string saves = get_all("saves.dat");
    // 存档取名
    name:
    std::string cmd = choose("输入对局名称，注意命名规范: ");
    if(!legal_name(cmd))
        goto name;
    if(saves.find(cmd) != std::string::npos)
    {
        std::cout << "存档名重复，请重新命名！" << std::endl;
        goto name;
    }
    // 获取创建者
    std::string now_name;
    std::ifstream ifs("now_playing.dat");
    ifs >> now_name;
    ifs.close();
    // 获取创建时间
    time_t nowtime;
	struct tm* p;;
	time(&nowtime);
	p = localtime(&nowtime);
    std::string h = std::to_string(p->tm_hour);
    std::string m = std::to_string(p->tm_min );
    std::string s = std::to_string(p->tm_sec );
    if(h.size() < 2)    h = '0' + h ;
    if(m.size() < 2)    m = '0' + m ;
    if(s.size() < 2)    s = '0' + s ;
    std::string ftime = h + ':' + m + ':' + s;
    std::ofstream ofs;
    // 添加存档信息
    ofs.open("saves.dat", std::ofstream::app);
    ofs << cmd << ' ' << now_name << ' ' << ftime << std::endl;
    ofs.close();
    // 保存存档
    ofs.open(cmd+".dat");
    ofs << bd.red_playing << std::endl;
    for(int row = 0; row != 10; ++row)
    {
        for(int col = 0; col != 9; ++col)
            if(bd.board[row][col])
                ofs << bd.board[row][col]->save() << ' ' ;
            else
                ofs << '*' << ' ' ;
        ofs << std::endl;
    }
    ofs.close();
    std::cout << "存档成功！" << std::endl;
}
void Game::load_game(const std::string &name)
{
    Board old_board;
    // 获取回合信息
    std::ifstream ifs(name+".dat");
    ifs >> old_board.red_playing ;
    // 获取棋子信息
    for(int row = 0; row != 10; ++row)
        for(int col = 0; col != 9; ++col)
        {
            char ctemp;
            ifs >> ctemp;
            if(ctemp == '*')        old_board.board[row][col] = nullptr;
            else if(ctemp == 'A')   old_board.make_piece<Pawn>(row, col, 1);
            else if(ctemp == 'a')   old_board.make_piece<Pawn>(row, col, 0);
            else if(ctemp == 'B')   old_board.make_piece<Cannon>(row, col, 1);
            else if(ctemp == 'b')   old_board.make_piece<Cannon>(row, col, 0);
            else if(ctemp == 'C')   old_board.make_piece<Chariot>(row, col, 1);
            else if(ctemp == 'c')   old_board.make_piece<Chariot>(row, col, 0);
            else if(ctemp == 'D')   old_board.make_piece<Horse>(row, col, 1);
            else if(ctemp == 'd')   old_board.make_piece<Horse>(row, col, 0);
            else if(ctemp == 'E')   old_board.make_piece<Minister>(row, col, 1);
            else if(ctemp == 'e')   old_board.make_piece<Minister>(row, col, 0);
            else if(ctemp == 'F')   old_board.make_piece<Mandarin>(row, col, 1);
            else if(ctemp == 'f')   old_board.make_piece<Mandarin>(row, col, 0);
            else if(ctemp == 'G')   old_board.make_piece<King>(row, col, 1);
            else if(ctemp == 'g')   old_board.make_piece<King>(row, col, 0);
        }
    ifs.close();
    play_game(old_board);
}
void Game::get_help()
{
    std::cout << std::string(31, '-') << std::endl;
    std::cout << "注意：所有操作请在一行之内完成。" << std::endl;
    std::cout << "-- 移动棋子: 依次输入 起点行数、起点列数、终点行数、终点列数，用空格分隔。\n"
                 "-- 退出游戏: 输入\"__quit__\"。请注意，任何进度都不会被保存。\n"
                 "-- 获取帮助: 我想这个不需要我来回答吧？我不相信你是碰巧输入__help__的。\n"
                 "-- 结束之后: 你可以通过选项选择重新开始或是回到菜单。\n"
                 "-- 象棋规则: \"你什么都不需要思考，只需要反复移动你的王就可以了。\"" << std::endl;
}
