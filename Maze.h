#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>
using namespace std;

const int MAX_SIZE = 100;

// 位置结构体
struct Position {
    int row;    // 行
    int col;    // 列
    int dir;    // 方向：0-未探索, 1-右, 2-下, 3-左, 4-上
    
    Position(int r = 0, int c = 0, int d = 0) : row(r), col(c), dir(d) {}
};

// 迷宫类
class Maze {
private:
    int maze[MAX_SIZE][MAX_SIZE];  // 迷宫数组：0-通路，1-墙壁，2-已走过
    int rows;                       // 行数
    int cols;                       // 列数
    Position entry;                 // 入口
    Position exit_pos;              // 出口（exit是关键字，改用exit_pos）
    stack<Position> path;           // 路径栈
    
    // 方向增量：右、下、左、上
    int dirRow[4] = {0, 1, 0, -1};
    int dirCol[4] = {1, 0, -1, 0};
    
    // 检查位置是否有效
    bool isValid(int r, int c) const;
    
public:
    // 构造函数
    Maze();
    
    // 输入迷宫
    void inputMaze();
    
    // 显示迷宫
    void displayMaze() const;
    
    // 非递归求解迷宫
    bool solveMaze();
    
    // 显示路径
    void displayPath();
    
    // 显示带路径的迷宫
    void displayMazeWithPath();
    
    // 检查迷宫是否已输入
    bool isLoaded() const;
    
    // 重置迷宫（清除走过的标记）
    void resetMaze();
};

// 运行迷宫系统
void runMazeSystem();

#endif
