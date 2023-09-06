#include<string>

#ifndef _SIMPREFERENCES_H_
#define _SIMPREFERENCES_H_
    const int probcnt = 4;   // 题总数
    const int ppl     = 5;   // 总人数
    const int len     = 270; // 比赛长（单位：分）
    const bool userating = true; // 是否使用rating机制
    const bool delayed   = true; // 输出延迟启用情况
    const int rating   [ppl+1]     = {0, 500,9999, 855, 500, 500}; // 选手rating
    const int diff     [probcnt+1] = {0,1800,1600,2000,2500}; // 难度分
    const int scoredist[probcnt+1] = {0, 100, 100, 100, 100}; // Score Distribution
    const int infoDelay=100; // 比赛信息输出间隔
    const int testDelay=200; // Final Test 信息输出间隔
    const std::string competitionname = "Educational Round #155"; // 比赛名称
    const std::string names[ppl+1]    = {"","master","Confringo","sunnygreen","yeyuzhe","zhjzhmh"}; // 选手

#else
#pragma message("Please don't include this file twice or more!")

#endif
