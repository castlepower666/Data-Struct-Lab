#include "Maze.h"
#include <iostream>
#include <iomanip>
using namespace std;

// 构造函数
Maze::Maze() : rows(0), cols(0) {
    // 初始化迷宫数组
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            maze[i][j] = 1;  // 默认为墙
        }
    }
}

// 检查位置是否有效（可以走）
bool Maze::isValid(int r, int c) const {
    return r >= 0 && r < rows && c >= 0 && c < cols && maze[r][c] == 0;
}

// 检查迷宫是否已输入
bool Maze::isLoaded() const {
    return rows > 0 && cols > 0;
}

// 输入迷宫
void Maze::inputMaze() {
    cout << "\n===== 输入迷宫 =====" << endl;
    cout << "请输入迷宫的行数和列数（如：5 5）: ";
    cin >> rows >> cols;
    
    if (rows <= 0 || cols <= 0 || rows > MAX_SIZE || cols > MAX_SIZE) {
        cout << "无效的迷宫大小！" << endl;
        rows = cols = 0;
        return;
    }
    
    cout << "\n请输入迷宫数据（0表示通路，1表示墙壁）：" << endl;
    cout << "例如 5x5 迷宫：" << endl;
    cout << "0 1 0 0 0" << endl;
    cout << "0 1 0 1 0" << endl;
    cout << "0 0 0 0 0" << endl;
    cout << "0 1 1 1 0" << endl;
    cout << "0 0 0 1 0" << endl;
    cout << "\n请输入：" << endl;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> maze[i][j];
        }
    }
    
    cout << "\n请输入入口位置（行 列，从0开始）: ";
    cin >> entry.row >> entry.col;
    entry.dir = 0;
    
    cout << "请输入出口位置（行 列，从0开始）: ";
    cin >> exit_pos.row >> exit_pos.col;
    exit_pos.dir = 0;
    
    // 验证入口出口
    if (maze[entry.row][entry.col] != 0) {
        cout << "警告：入口位置是墙壁！" << endl;
    }
    if (maze[exit_pos.row][exit_pos.col] != 0) {
        cout << "警告：出口位置是墙壁！" << endl;
    }
    
    cout << "迷宫输入完成！" << endl;
}

// 显示迷宫
void Maze::displayMaze() const {
    if (!isLoaded()) {
        cout << "迷宫未加载！" << endl;
        return;
    }
    
    cout << "\n===== 迷宫 =====" << endl;
    cout << "（0-通路，1-墙壁，S-入口，E-出口）\n" << endl;
    
    // 打印列号
    cout << "   ";
    for (int j = 0; j < cols; j++) {
        cout << setw(2) << j << " ";
    }
    cout << endl;
    
    for (int i = 0; i < rows; i++) {
        cout << setw(2) << i << " ";  // 打印行号
        for (int j = 0; j < cols; j++) {
            if (i == entry.row && j == entry.col) {
                cout << " S ";
            } else if (i == exit_pos.row && j == exit_pos.col) {
                cout << " E ";
            } else if (maze[i][j] == 1) {
                cout << " # ";  // 墙壁
            } else {
                cout << " . ";  // 通路
            }
        }
        cout << endl;
    }
    cout << "\n入口: (" << entry.row << "," << entry.col << ")";
    cout << "  出口: (" << exit_pos.row << "," << exit_pos.col << ")" << endl;
}

// 重置迷宫（清除走过的标记）
void Maze::resetMaze() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 2) {  // 清除已走过的标记
                maze[i][j] = 0;
            }
        }
    }
    // 清空路径栈
    while (!path.empty()) {
        path.pop();
    }
}

// 非递归求解迷宫（使用栈）
bool Maze::solveMaze() {
    if (!isLoaded()) {
        cout << "迷宫未加载！" << endl;
        return false;
    }
    
    // 重置迷宫
    resetMaze();
    
    // 检查入口是否有效
    if (maze[entry.row][entry.col] != 0) {
        cout << "入口被阻塞，无法求解！" << endl;
        return false;
    }
    
    // 将入口压入栈
    Position cur = entry;
    path.push(cur);
    maze[cur.row][cur.col] = 2;  // 标记为已走过
    
    while (!path.empty()) {
        cur = path.top();
        
        // 检查是否到达出口
        if (cur.row == exit_pos.row && cur.col == exit_pos.col) {
            return true;  // 找到路径
        }
        
        // 尝试四个方向：右、下、左、上
        bool found = false;
        while (cur.dir < 4 && !found) {
            int newRow = cur.row + dirRow[cur.dir];
            int newCol = cur.col + dirCol[cur.dir];
            
            path.pop();
            cur.dir++;
            path.push(cur);  // 更新当前位置的方向
            
            if (isValid(newRow, newCol)) {
                // 找到新的可走位置
                Position next(newRow, newCol, 0);
                path.push(next);
                maze[newRow][newCol] = 2;  // 标记为已走过
                found = true;
            }
        }
        
        // 四个方向都走不通，回溯
        if (!found) {
            path.pop();
        }
    }
    
    return false;  // 无解
}

// 显示路径
void Maze::displayPath() {
    if (path.empty()) {
        cout << "没有找到路径！" << endl;
        return;
    }
    
    // 将栈中的路径复制出来（逆序）
    stack<Position> tempStack;
    stack<Position> pathCopy = path;
    
    while (!pathCopy.empty()) {
        tempStack.push(pathCopy.top());
        pathCopy.pop();
    }
    
    cout << "\n===== 路径 =====" << endl;
    cout << "从入口到出口的路径：" << endl;
    
    int step = 0;
    while (!tempStack.empty()) {
        Position pos = tempStack.top();
        tempStack.pop();
        cout << "第" << step++ << "步: (" << pos.row << ", " << pos.col << ")";
        if (!tempStack.empty()) {
            cout << " -> ";
        }
        if (step % 5 == 0) cout << endl;  // 每5步换行
    }
    cout << endl;
    cout << "总步数: " << step << endl;
}

// 显示带路径的迷宫
void Maze::displayMazeWithPath() {
    if (!isLoaded()) {
        cout << "迷宫未加载！" << endl;
        return;
    }
    
    // 创建临时迷宫用于显示
    int tempMaze[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tempMaze[i][j] = (maze[i][j] == 1) ? 1 : 0;  // 只保留墙壁
        }
    }
    
    // 标记路径
    stack<Position> pathCopy = path;
    while (!pathCopy.empty()) {
        Position pos = pathCopy.top();
        pathCopy.pop();
        tempMaze[pos.row][pos.col] = 3;  // 3表示路径
    }
    
    cout << "\n===== 带路径的迷宫 =====" << endl;
    cout << "（#-墙壁，.-通路，*-路径，S-入口，E-出口）\n" << endl;
    
    // 打印列号
    cout << "   ";
    for (int j = 0; j < cols; j++) {
        cout << setw(2) << j << " ";
    }
    cout << endl;
    
    for (int i = 0; i < rows; i++) {
        cout << setw(2) << i << " ";
        for (int j = 0; j < cols; j++) {
            if (i == entry.row && j == entry.col) {
                cout << " S ";
            } else if (i == exit_pos.row && j == exit_pos.col) {
                cout << " E ";
            } else if (tempMaze[i][j] == 1) {
                cout << " # ";  // 墙壁
            } else if (tempMaze[i][j] == 3) {
                cout << " * ";  // 路径
            } else {
                cout << " . ";  // 通路
            }
        }
        cout << endl;
    }
}

// 运行迷宫系统
void runMazeSystem() {
    Maze maze;
    int choice;
    
    while (true) {
        cout << "\n======== 迷宫求解系统 ========" << endl;
        cout << "1. 输入迷宫" << endl;
        cout << "2. 显示迷宫" << endl;
        cout << "3. 求解迷宫（非递归）" << endl;
        cout << "4. 显示路径" << endl;
        cout << "5. 显示带路径的迷宫" << endl;
        cout << "6. 使用示例迷宫" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "==============================" << endl;
        cout << "请选择操作: ";
        cin >> choice;
        
        switch (choice) {
        case 1:
            maze.inputMaze();
            break;
            
        case 2:
            if (!maze.isLoaded()) {
                cout << "请先输入迷宫！" << endl;
            } else {
                maze.displayMaze();
            }
            break;
            
        case 3:
            if (!maze.isLoaded()) {
                cout << "请先输入迷宫！" << endl;
            } else {
                cout << "\n正在求解迷宫..." << endl;
                if (maze.solveMaze()) {
                    cout << "找到路径！" << endl;
                    maze.displayPath();
                    maze.displayMazeWithPath();
                } else {
                    cout << "迷宫无解，找不到从入口到出口的路径！" << endl;
                }
            }
            break;
            
        case 4:
            maze.displayPath();
            break;
            
        case 5:
            maze.displayMazeWithPath();
            break;
            
        case 6:
            {
                // 使用示例迷宫
                cout << "\n加载示例迷宫（8x8）..." << endl;
                // 手动设置示例迷宫
                Maze& m = maze;
                // 这里我们通过输入流模拟
                cout << "示例迷宫已准备，请选择选项1手动输入，或参考以下数据：" << endl;
                cout << "\n8 8" << endl;
                cout << "0 1 0 0 0 1 0 0" << endl;
                cout << "0 1 0 1 0 1 0 1" << endl;
                cout << "0 0 0 1 0 0 0 1" << endl;
                cout << "1 1 0 1 1 1 0 1" << endl;
                cout << "0 0 0 0 0 1 0 1" << endl;
                cout << "0 1 1 1 0 1 0 0" << endl;
                cout << "0 1 0 0 0 1 1 0" << endl;
                cout << "0 0 0 1 0 0 0 0" << endl;
                cout << "入口: 0 0" << endl;
                cout << "出口: 7 7" << endl;
            }
            break;
            
        case 0:
            cout << "返回主菜单..." << endl;
            return;
            
        default:
            cout << "无效选择，请重新输入！" << endl;
            break;
        }
    }
}
