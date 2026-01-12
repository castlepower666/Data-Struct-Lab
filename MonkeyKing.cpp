#include "MonkeyKing.h"
#include <iostream>
using namespace std;

// 构造函数
MonkeyKing::MonkeyKing(int m, int n) : totalMonkeys(m), countNumber(n) {
    // 初始化m只猴子
    for (int i = 1; i <= m; i++) {
        monkeys.push_back(Monkey(i));
    }
}

// 获取存活猴子数量
int MonkeyKing::getAliveCount() const {
    int count = 0;
    for (const Monkey& monkey : monkeys) {
        if (monkey.isAlive) {
            count++;
        }
    }
    return count;
}

// 开始选大王过程（只返回结果）
int MonkeyKing::selectKing() {
    int currentPos = 0;  // 当前位置
    int count = 0;       // 计数器

    while (getAliveCount() > 1) {
        // 如果当前猴子还活着，计数
        if (monkeys[currentPos].isAlive) {
            count++;
            // 如果数到n，该猴子出圈
            if (count == countNumber) {
                monkeys[currentPos].isAlive = false;
                count = 0;  // 重置计数器
            }
        }

        // 移动到下一个位置（循环）
        currentPos = (currentPos + 1) % totalMonkeys;
    }

    // 找到最后存活的猴子
    for (const Monkey& monkey : monkeys) {
        if (monkey.isAlive) {
            return monkey.number;
        }
    }

    return -1;  // 不应该到达这里
}

// 显示选大王的详细过程
void MonkeyKing::selectKingWithProcess() {
    int currentPos = 0;
    int count = 0;
    int round = 1;

    cout << "\n===== 猴子选大王详细过程 =====" << endl;
    cout << "总共 " << totalMonkeys << " 只猴子，数到第 " << countNumber << " 个出圈\n" << endl;

    // 显示初始状态
    cout << "初始猴子编号: ";
    for (int i = 0; i < totalMonkeys; i++) {
        cout << monkeys[i].number << " ";
    }
    cout << "\n" << endl;

    while (getAliveCount() > 1) {
        if (monkeys[currentPos].isAlive) {
            count++;

            if (count == countNumber) {
                cout << "第 " << round << " 轮: 猴子 " << monkeys[currentPos].number << " 号出圈" << endl;
                monkeys[currentPos].isAlive = false;
                count = 0;
                round++;

                // 显示剩余猴子
                cout << "   剩余猴子: ";
                for (const Monkey& monkey : monkeys) {
                    if (monkey.isAlive) {
                        cout << monkey.number << " ";
                    }
                }
                cout << "\n" << endl;
            }
        }

        currentPos = (currentPos + 1) % totalMonkeys;
    }

    // 找到大王
    for (const Monkey& monkey : monkeys) {
        if (monkey.isAlive) {
            cout << "=============================" << endl;
            cout << "*** 猴子 " << monkey.number << " 号成为大王！***" << endl;
            cout << "=============================" << endl;
        }
    }
}

// 运行猴子选大王功能
void runMonkeyKingSystem() {
    int m, n;
    int choice;

    while (true) {
        cout << "\n======== 猴子选大王 ========" << endl;
        cout << "1. 开始选大王（显示详细过程）" << endl;
        cout << "2. 快速计算大王编号" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "请选择操作: ";
        cin >> choice;

        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1:
        case 2:
            cout << "\n请输入猴子总数 m: ";
            cin >> m;
            cout << "请输入数到第几个出圈 n: ";
            cin >> n;

            // 验证输入
            if (m <= 0 || n <= 0) {
                cout << "错误：m 和 n 必须是正整数！" << endl;
                break;
            }
            if (n > m) {
                cout << "警告：n 大于 m，但程序仍可运行。" << endl;
            }

            {
                MonkeyKing game(m, n);

                if (choice == 1) {
                    // 显示详细过程
                    game.selectKingWithProcess();
                }
                else {
                    // 只显示结果
                    int king = game.selectKing();
                    cout << "\n结果：按照 " << m << " 个猴子，数 " << n << " 个数的方法，" << endl;
                    cout << "     大王是 " << king << " 号猴子！" << endl;
                }
            }
            break;

        default:
            cout << "无效选择，请重新输入！" << endl;
            break;
        }
    }
}
