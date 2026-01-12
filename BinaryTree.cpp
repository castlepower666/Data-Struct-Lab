#include "BinaryTree.h"
#include <iostream>
#include <queue>
using namespace std;

// 构造函数
BinaryTree::BinaryTree() : root(nullptr) {}

// 析构函数
BinaryTree::~BinaryTree() {
    destroyTree(root);
}

// 销毁二叉树
void BinaryTree::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// 递归构建二叉树的辅助函数
TreeNode* BinaryTree::buildTreeHelper(int& index, const string& preorder) {
    if (index >= preorder.length() || preorder[index] == '#') {
        index++;
        return nullptr;
    }

    TreeNode* node = new TreeNode(preorder[index]);
    index++;
    node->left = buildTreeHelper(index, preorder);
    node->right = buildTreeHelper(index, preorder);

    return node;
}

// 输入二叉树（先序序列，#表示空节点）
void BinaryTree::buildTree() {
    cout << "\n请输入二叉树的先序序列（用 # 表示空节点）：" << endl;
    cout << "例如：AB#D##C## 表示如下树结构：" << endl;
    cout << "       A" << endl;
    cout << "      / \\" << endl;
    cout << "     B   C" << endl;
    cout << "      \\" << endl;
    cout << "       D" << endl;
    cout << "\n请输入: ";

    string preorder;
    cin >> preorder;

    // 销毁旧树
    if (root != nullptr) {
        destroyTree(root);
        root = nullptr;
    }

    // 构建新树
    int index = 0;
    root = buildTreeHelper(index, preorder);

    cout << "二叉树构建完成！" << endl;
}

// 检查树是否为空
bool BinaryTree::isEmpty() const {
    return root == nullptr;
}

// 获取树的高度
int BinaryTree::getHeight(TreeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int BinaryTree::height() const {
    return getHeight(root);
}

// 层序遍历（使用队列）
void BinaryTree::levelOrder() {
    if (isEmpty()) {
        cout << "树为空！" << endl;
        return;
    }

    cout << "\n层序遍历结果: ";
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        cout << current->data << " ";

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
    cout << endl;
}

// 先序遍历（递归）辅助函数
void BinaryTree::preorderRecursive(TreeNode* node) {
    if (node != nullptr) {
        cout << node->data << " ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }
}

// 先序遍历（递归）
void BinaryTree::preorderTraversal() {
    if (isEmpty()) {
        cout << "树为空！" << endl;
        return;
    }

    cout << "\n先序遍历结果: ";
    preorderRecursive(root);
    cout << endl;
}

// 中序遍历（递归）辅助函数
void BinaryTree::inorderRecursive(TreeNode* node) {
    if (node != nullptr) {
        inorderRecursive(node->left);
        cout << node->data << " ";
        inorderRecursive(node->right);
    }
}

// 中序遍历（递归）
void BinaryTree::inorderTraversal() {
    if (isEmpty()) {
        cout << "树为空！" << endl;
        return;
    }

    cout << "\n中序遍历结果: ";
    inorderRecursive(root);
    cout << endl;
}

// 后序遍历（递归）辅助函数
void BinaryTree::postorderRecursive(TreeNode* node) {
    if (node != nullptr) {
        postorderRecursive(node->left);
        postorderRecursive(node->right);
        cout << node->data << " ";
    }
}

// 后序遍历（递归）
void BinaryTree::postorderTraversal() {
    if (isEmpty()) {
        cout << "树为空！" << endl;
        return;
    }

    cout << "\n后序遍历结果: ";
    postorderRecursive(root);
    cout << endl;
}

// 运行二叉树系统
void runBinaryTreeSystem() {
    BinaryTree tree;
    int choice;

    while (true) {
        cout << "\n======== 二叉树遍历系统 ========" << endl;
        cout << "1. 输入二叉树" << endl;
        cout << "2. 层序遍历" << endl;
        cout << "3. 先序遍历" << endl;
        cout << "4. 中序遍历" << endl;
        cout << "5. 后序遍历" << endl;
        cout << "6. 显示所有遍历结果" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "================================" << endl;
        cout << "请选择操作: ";
        cin >> choice;

        switch (choice) {
        case 1:
            tree.buildTree();
            break;

        case 2:
            if (tree.isEmpty()) {
                cout << "树为空，请先输入二叉树！" << endl;
            }
            else {
                tree.levelOrder();
            }
            break;

        case 3:
            if (tree.isEmpty()) {
                cout << "树为空，请先输入二叉树！" << endl;
            }
            else {
                tree.preorderTraversal();
            }
            break;

        case 4:
            if (tree.isEmpty()) {
                cout << "树为空，请先输入二叉树！" << endl;
            }
            else {
                tree.inorderTraversal();
            }
            break;

        case 5:
            if (tree.isEmpty()) {
                cout << "树为空，请先输入二叉树！" << endl;
            }
            else {
                tree.postorderTraversal();
            }
            break;

        case 6:
            if (tree.isEmpty()) {
                cout << "树为空，请先输入二叉树！" << endl;
            }
            else {
                cout << "\n===== 所有遍历结果 =====" << endl;
                cout << "树的高度: " << tree.height() << endl;
                tree.levelOrder();
                tree.preorderTraversal();
                tree.inorderTraversal();
                tree.postorderTraversal();
                cout << "========================" << endl;
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
