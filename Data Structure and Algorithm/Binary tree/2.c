#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

// 定义二叉树节点结构体
typedef struct TreeNode {
    int val;                // 节点的值
    struct TreeNode* left;  // 左子节点
    struct TreeNode* right; // 右子节点
} TreeNode;

// 创建一个新节点并初始化
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode)); // 动态分配内存
    newNode->val = value;  // 设置节点的值
    newNode->left = NULL;   // 初始化左子节点为空
    newNode->right = NULL;  // 初始化右子节点为空
    return newNode;
}

// 从输入字符串构建二叉树
TreeNode* buildTree(char* input) {
    if (strlen(input) == 0) return NULL;  // 如果输入为空字符串，返回空树

    char* tokens[MAX];  // 存储拆分后的字符串片段
    int count = 0;
    char* token = strtok(input, ","); // 按逗号分隔字符串
    while (token) {
        tokens[count++] = token;  // 将每个子串存入数组
        token = strtok(NULL, ","); // 获取下一个子串
    }

    // 创建树的根节点
    TreeNode* root = createNode(atoi(tokens[0])); // 根节点的值是第一个子串
    TreeNode* queue[MAX];  // 队列用于按层次遍历构建二叉树
    int front = 0, rear = 0;
    queue[rear++] = root; // 将根节点加入队列
    
    int i = 1;
    while (i < count) {
        TreeNode* current = queue[front++]; // 取出队首元素
        if (current) {
            // 处理左子节点
            if (i < count && strcmp(tokens[i], "null") != 0) {
                current->left = createNode(atoi(tokens[i])); // 创建左子节点
                queue[rear++] = current->left;  // 将左子节点加入队列
            }
            i++;  // 处理下一个节点
            
            // 处理右子节点
            if (i < count && strcmp(tokens[i], "null") != 0) {
                current->right = createNode(atoi(tokens[i])); // 创建右子节点
                queue[rear++] = current->right; // 将右子节点加入队列
            }
            i++; // 处理下一个节点
        }
    }
    return root;  // 返回构建好的树的根节点
}

// 判断两棵子树是否对称
int isSymmetricHelper(TreeNode* left, TreeNode* right) {
    if (!left && !right) return 1;  // 如果两棵子树都为空，返回 true
    if (!left || !right) return 0;  // 如果只有一个子树为空，返回 false
    if (left->val != right->val) return 0;  // 如果节点值不相等，返回 false
    // 递归判断左右子树是否对称
    return isSymmetricHelper(left->left, right->right) && isSymmetricHelper(left->right, right->left);
}

// 判断整棵树是否对称
int isSymmetric(TreeNode* root) {
    if (!root) return 1;  // 如果树为空，则认为是对称的
    return isSymmetricHelper(root->left, root->right);  // 检查左右子树是否对称
}

int main() {
    char input[MAX];  // 存储用户输入的二叉树表示
    fgets(input, sizeof(input), stdin);  // 读取输入
    input[strcspn(input, "\n")] = 0;  // 去除末尾的换行符

    // 构建二叉树
    TreeNode* root = buildTree(input);
    
    // 判断树是否对称并输出结果
    if (isSymmetric(root)) {
        printf("true\n");  // 如果对称，输出 true
    } else {
        printf("false\n");  // 如果不对称，输出 false
    }

    return 0;
}

