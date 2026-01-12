#ifndef MONKEYKING_H
#define MONKEYKING_H

#include <vector>
using namespace std;

// 猴子节点结构
struct Monkey {
    int number;      // 猴子编号
    bool isAlive;    // 是否还在圈中
    
    Monkey(int num) : number(num), isAlive(true) {}
};

// 猴子选大王类
class MonkeyKing {
private:
    vector<Monkey> monkeys;  // 使用线性表存储猴子
    int totalMonkeys;        // 猴子总数
    int countNumber;         // 数到第几个出圈

public:
    // 构造函数
    MonkeyKing(int m, int n);
    
    // 开始选大王过程
    int selectKing();
    
    // 显示选大王的详细过程
    void selectKingWithProcess();
    
    // 获取存活猴子数量
    int getAliveCount() const;
};

// 运行猴子选大王功能
void runMonkeyKingSystem();

#endif
