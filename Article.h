#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include <vector>
using namespace std;

const int MAX_LINE_LENGTH = 80;

// 线性表存储结构 - 存储文章
class Article {
private:
    vector<string> lines;  // 使用线性表存储每行文字

public:
    // 输入文章
    void inputArticle();

    // 显示文章内容
    void displayArticle() const;

    // 统计英文字母数
    int countLetters() const;

    // 统计数字个数
    int countDigits() const;

    // 统计空格个数
    int countSpaces() const;

    // 统计文章总字数（所有字符）
    int countTotalChars() const;

    // 显示统计结果
    void showStatistics() const;

    // 获取整篇文章为一个字符串
    string getFullText() const;

    // 统计某一字符串出现的次数
    int countSubstring(const string& substr) const;

    // 删除某一子串，并将后面的字符前移
    void deleteSubstring(const string& substr);

    // 检查文章是否为空
    bool isEmpty() const;
};

#endif
