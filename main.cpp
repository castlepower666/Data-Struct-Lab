#include <iostream>
#include <string>
#include "Article.h"
#include "MonkeyKing.h"
#include "BinaryTree.h"
#include "Maze.h"
using namespace std;

// 显示主菜单
void showMainMenu() {
    cout << "      主系统" << endl;
    cout << "========================================" << endl;
    cout << "1. 文章编辑系统" << endl;
    cout << "2. 猴子选大王" << endl;
    cout << "3. 二叉树遍历" << endl;
    cout << "4. 迷宫求解" << endl;
    cout << "0. 退出程序" << endl;
    cout << "========================================" << endl;
    cout << "请选择功能模块: ";
}

// 显示文章编辑菜单
void showArticleMenu() {
    cout << "\n======== 文章编辑系统 ========" << endl;
    cout << "1. 输入文章" << endl;
    cout << "2. 显示文章" << endl;
    cout << "3. 统计字符（字母、数字、空格、总字数）" << endl;
    cout << "4. 统计某字符串出现次数" << endl;
    cout << "5. 删除某一子串" << endl;
    cout << "0. 返回主菜单" << endl;
    cout << "请选择操作: ";
}

// 运行文章编辑系统
void runArticleSystem() {
    Article article;
    int choice;
    string searchStr;

    while (true) {
        showArticleMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            article.inputArticle();
            cout << "文章输入完成！" << endl;
            break;

        case 2:
            if (article.isEmpty()) {
                cout << "文章为空，请先输入文章！" << endl;
            }
            else {
                article.displayArticle();
            }
            break;

        case 3:
            if (article.isEmpty()) {
                cout << "文章为空，请先输入文章！" << endl;
            }
            else {
                article.showStatistics();
            }
            break;

        case 4:
            if (article.isEmpty()) {
                cout << "文章为空，请先输入文章！" << endl;
            }
            else {
                cout << "请输入要查找的字符串: ";
                cin.ignore();
                getline(cin, searchStr);
                int count = article.countSubstring(searchStr);
                cout << "字符串 \"" << searchStr << "\" 在文章中出现了 " << count << " 次。" << endl;
            }
            break;

        case 5:
            if (article.isEmpty()) {
                cout << "文章为空，请先输入文章！" << endl;
            }
            else {
                cout << "请输入要删除的子串: ";
                cin.ignore();
                getline(cin, searchStr);
                article.deleteSubstring(searchStr);
                cout << "删除完成！删除后的文章：" << endl;
                article.displayArticle();
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

int main() {
    int choice;

    while (true) {
        showMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            runArticleSystem();
            break;

        case 2:
            runMonkeyKingSystem();
            break;

        case 3:
            runBinaryTreeSystem();
            break;

        case 4:
            runMazeSystem();
            break;

        case 0:
            cout << "\n感谢使用，再见！" << endl;
            return 0;

        default:
            cout << "无效选择，请重新输入！" << endl;
            break;
        }
    }

    return 0;
}
