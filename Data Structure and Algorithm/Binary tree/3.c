#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

// 定义二叉树节点结构
typedef struct TreeNode {
    int val;                // 节点的值
    struct TreeNode* left;  // 左子节点
    struct TreeNode* right; // 右子节点
} TreeNode;

// 创建一个新的节点
TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));  // 动态分配内存
    newNode->val = val;  // 设置节点的值
    newNode->left = NULL; // 初始化左子节点为空
    newNode->right = NULL; // 初始化右子节点为空
    return newNode;
}

// 从输入的字符串构建二叉树
TreeNode* buildTree(char* input) {
    if (strlen(input) == 0) return NULL;  // 如果输入为空，返回空树

    char* tokens[MAX];  // 用于存储字符串切分后的每个部分
    int count = 0;       // 记录分割后的子串数量
    char* token = strtok(input, ","); // 通过逗号分割输入字符串
    while (token) {
        tokens[count++] = token;  // 将每个子串存入 tokens 数组
        token = strtok(NULL, ","); // 获取下一个子串
    }

    // 创建树的根节点，根节点的值是字符串中的第一个数字
    TreeNode* root = createNode(atoi(tokens[0]));  
    TreeNode* queue[MAX];  // 队列用于按层次遍历构建树
    int front = 0, rear = 0;  // 队列的头和尾
    queue[rear++] = root;  // 将根节点加入队列

    int i = 1; // 用于遍历 tokens 数组
    while (i < count) {
        TreeNode* current = queue[front++];  // 取出队首节点
        if (current) {
            // 如果当前节点左子节点不为空，创建左子节点
            if (i < count && strcmp(tokens[i], "null") != 0) {
                current->left = createNode(atoi(tokens[i]));
                queue[rear++] = current->left;  // 将左子节点加入队列
            }
            i++; // 移动到下一个位置

            // 如果当前节点右子节点不为空，创建右子节点
            if (i < count && strcmp(tokens[i], "null") != 0) {
                current->right = createNode(atoi(tokens[i]));
                queue[rear++] = current->right; // 将右子节点加入队列
            }
            i++; // 移动到下一个位置
        }
    }
    return root;  // 返回构建好的二叉树的根节点
}

// 翻转二叉树
TreeNode* invertTree(TreeNode* root) {
    if (root == NULL) {
        return NULL;  // 如果树为空，返回空
    }
    // 交换左右子树
    TreeNode* temp = root->left;  // 临时保存左子树
    root->left = invertTree(root->right);  // 递归翻转右子树
    root->right = invertTree(temp);  // 递归翻转左子树
    return root;  // 返回翻转后的根节点
}

// 层次遍历输出二叉树
void printTree(TreeNode* root) {
    if (root == NULL) {
        printf("null");  // 如果树为空，输出 null
        return;
    }

    TreeNode* queue[100];  // 队列用于层次遍历
    int front = 0, rear = 0;  // 队列的头和尾

    queue[rear++] = root;  // 将根节点加入队列

    while (front < rear) {
        TreeNode* current = queue[front++];  // 取出队首节点
        if (current) {
            printf("%d,", current->val);  // 输出当前节点的值
            queue[rear++] = current->left;  // 将左子节点加入队列
            queue[rear++] = current->right; // 将右子节点加入队列
        } else {
            // 如果当前节点为空，输出 null
            printf("null,");
        }
    }

    // 打印完所有节点后，去掉最后一个多余的逗号，并换行
    printf("\b \n");
}

// 主函数
int main() {
    char input[256];  // 存储用户输入的树的表示
    fgets(input, sizeof(input), stdin);  // 读取输入
    input[strcspn(input, "\n")] = 0;  // 去掉输入末尾的换行符

    // 根据输入构建二叉树
    TreeNode* root = buildTree(input);

    // 翻转二叉树
    root = invertTree(root);

    // 输出翻转后的二叉树
    printTree(root);

    return 0;
}

