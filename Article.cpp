#include "Article.h"
#include <iostream>
using namespace std;

// 输入文章
void Article::inputArticle() {
    cout << "请输入文章内容（输入单独一行 # 结束输入）：" << endl;
    string line;
    cin.ignore();  // 清除缓冲区中的换行符
    while (true) {
        getline(cin, line);  // 等待用户输入
        if (line == "#") break;
        if (line.length() > MAX_LINE_LENGTH) {
            line = line.substr(0, MAX_LINE_LENGTH);
            cout << "警告：该行超过80字符，已截断。" << endl;
        }
        lines.push_back(line);
    }
}

// 显示文章内容
void Article::displayArticle() const {
    cout << "\n===== 文章内容 =====" << endl;
    for (size_t i = 0; i < lines.size(); i++) {
        cout << "第" << (i + 1) << "行: " << lines[i] << endl;
    }
    cout << "====================" << endl;
}

// 统计英文字母数
int Article::countLetters() const {
    int count = 0;
    for (const string& line : lines) {
        for (char c : line) {
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                count++;
            }
        }
    }
    return count;
}

// 统计数字个数
int Article::countDigits() const {
    int count = 0;
    for (const string& line : lines) {
        for (char c : line) {
            if (c >= '0' && c <= '9') {
                count++;
            }
        }
    }
    return count;
}

// 统计空格个数
int Article::countSpaces() const {
    int count = 0;
    for (const string& line : lines) {
        for (char c : line) {
            if (c == ' ') {
                count++;
            }
        }
    }
    return count;
}

// 统计文章总字数（所有字符）
int Article::countTotalChars() const {
    int count = 0;
    for (const string& line : lines) {
        count += line.length();
    }
    return count;
}

// 显示统计结果
void Article::showStatistics() const {
    cout << "\n===== 统计结果 =====" << endl;
    cout << "全部字母数: " << countLetters() << endl;
    cout << "数字个数: " << countDigits() << endl;
    cout << "空格个数: " << countSpaces() << endl;
    cout << "文章总字数: " << countTotalChars() << endl;
    cout << "====================" << endl;
}

// 获取整篇文章为一个字符串
string Article::getFullText() const {
    string fullText;
    for (size_t i = 0; i < lines.size(); i++) {
        fullText += lines[i];
        if (i < lines.size() - 1) {
            fullText += "\n";
        }
    }
    return fullText;
}

// 统计某一字符串出现的次数
int Article::countSubstring(const string& substr) const {
    if (substr.empty()) return 0;

    string fullText = getFullText();
    int count = 0;
    size_t pos = 0;

    while ((pos = fullText.find(substr, pos)) != string::npos) {
        count++;
        pos += 1;  // 移动一位继续查找（允许重叠匹配）
    }
    return count;
}

// 删除某一子串，并将后面的字符前移
void Article::deleteSubstring(const string& substr) {
    if (substr.empty()) return;

    string fullText = getFullText();
    size_t pos;

    // 循环删除所有出现的子串
    while ((pos = fullText.find(substr)) != string::npos) {
        fullText.erase(pos, substr.length());
    }

    // 重新分割为行
    lines.clear();
    string line;
    for (char c : fullText) {
        if (c == '\n') {
            lines.push_back(line);
            line.clear();
        }
        else {
            line += c;
        }
    }
    if (!line.empty() || fullText.empty() || fullText.back() == '\n') {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
}

// 检查文章是否为空
bool Article::isEmpty() const {
    return lines.empty();
}
