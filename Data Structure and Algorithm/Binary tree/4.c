#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NULL_NODE -1  // 用 -1 代表 null 节点

// 定义二叉树节点结构体
struct TreeNode {
    int val;                // 节点的值
    struct TreeNode *left;  // 左子节点
    struct TreeNode *right; // 右子节点
};

// 创建一个新节点并初始化
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));  // 分配内存
    node->val = val;   // 设置节点的值
    node->left = NULL;  // 初始化左子节点为空
    node->right = NULL; // 初始化右子节点为空
    return node;
}

// 递归计算二叉树左叶子节点的和
int sumOfLeftLeaves(struct TreeNode* root) {
    if (root == NULL) return 0;  // 如果树为空，返回0

    int leftSum = 0;

    // 检查当前节点的左子节点是否是叶子节点
    if (root->left && root->left->left == NULL && root->left->right == NULL) {
        leftSum += root->left->val;  // 如果是左叶子节点，累加其值
    }

    // 递归地计算左子树和右子树的左叶子节点和
    leftSum += sumOfLeftLeaves(root->left);
    leftSum += sumOfLeftLeaves(root->right);

    return leftSum;
}

// 从输入字符串解析成数组
int parseInput(char* input, int* arr) {
    int index = 0;
    char* token = strtok(input, "[, ]");

    // 逐个分割并解析输入
    while (token != NULL) {
        // 如果是 "null" 字符串，表示当前节点为空
        if (strcmp(token, "null") == 0) {
            arr[index++] = NULL_NODE;  // 用 NULL_NODE 表示空节点
        }
        // 如果是整数，转换为整数并存入数组
        else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            arr[index++] = atoi(token);  // 将字符串转为整数
        }
        token = strtok(NULL, "[, ]");  // 继续分割
    }
    return index;  // 返回解析的数组长度
}

// 根据数组构建二叉树
struct TreeNode* buildTree(int* arr, int size) {
    if (size == 0 || arr[0] == NULL_NODE) return NULL;  // 如果数组为空或根节点为 null，则返回空树

    struct TreeNode** nodes = (struct TreeNode**)malloc(size * sizeof(struct TreeNode*));  // 创建节点数组
    struct TreeNode* root = newNode(arr[0]);  // 创建根节点
    nodes[0] = root;  // 根节点入队列

    // 逐步构建树的节点
    for (int i = 0, j = 1; j < size; ++i) {
        if (nodes[i] != NULL) {
            // 构建左子节点
            if (j < size && arr[j] != NULL_NODE) {
                nodes[i]->left = newNode(arr[j]);  // 创建左子节点
                nodes[j] = nodes[i]->left;         // 将左子节点入队
            }
            j++;

            // 构建右子节点
            if (j < size && arr[j] != NULL_NODE) {
                nodes[i]->right = newNode(arr[j]);  // 创建右子节点
                nodes[j] = nodes[i]->right;         // 将右子节点入队
            }
            j++;
        }
    }

    free(nodes);  // 释放临时分配的节点数组内存
    return root;  // 返回构建好的树的根节点
}

int main() {
    char input[100];  // 存储输入的字符串
    int arr[100];     // 存储解析后的数组

    fgets(input, sizeof(input), stdin);  // 读取输入
    int size = parseInput(input, arr);   // 解析输入字符串为数组
    struct TreeNode* root = buildTree(arr, size);  // 根据数组构建二叉树

    int result = sumOfLeftLeaves(root);  // 计算左叶子节点之和
    printf("%d\n", result);  // 输出结果

    return 0;
}

