#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>
using namespace std;

// 二叉树节点结构
struct TreeNode {
    char data;           // 节点数据
    TreeNode* left;      // 左子树指针
    TreeNode* right;     // 右子树指针
    
    TreeNode(char val) : data(val), left(nullptr), right(nullptr) {}
};

// 二叉树类
class BinaryTree {
private:
    TreeNode* root;      // 根节点指针
    
    // 辅助函数：递归构建二叉树
    TreeNode* buildTreeHelper(int& index, const string& preorder);
    
    // 辅助函数：先序遍历（递归）
    void preorderRecursive(TreeNode* node);
    
    // 辅助函数：中序遍历（递归）
    void inorderRecursive(TreeNode* node);
    
    // 辅助函数：后序遍历（递归）
    void postorderRecursive(TreeNode* node);
    
    // 辅助函数：销毁二叉树
    void destroyTree(TreeNode* node);
    
    // 辅助函数：计算树的高度
    int getHeight(TreeNode* node) const;

public:
    // 构造函数
    BinaryTree();
    
    // 析构函数
    ~BinaryTree();
    
    // 输入二叉树（先序序列，#表示空节点）
    void buildTree();
    
    // 层序遍历
    void levelOrder();
    
    // 先序遍历（递归）
    void preorderTraversal();
    
    // 中序遍历（递归）
    void inorderTraversal();
    
    // 后序遍历（递归）
    void postorderTraversal();
    
    // 检查树是否为空
    bool isEmpty() const;
    
    // 获取树的高度
    int height() const;
};

// 运行二叉树系统
void runBinaryTreeSystem();

#endif
