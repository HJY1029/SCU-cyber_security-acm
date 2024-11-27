#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义二叉树节点结构体
typedef struct TreeNode {
    int val;                // 节点的值
    struct TreeNode *left;  // 左子节点
    struct TreeNode *right; // 右子节点
} TreeNode;

// 创建新节点
TreeNode* createNewNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 根据输入字符串构建二叉树
TreeNode* buildTree(char* input) {
    // 分割输入字符串，按逗号分隔
    char* tokens[1000];
    int tokenCount = 0;
    char* token = strtok(input, ",");
    while (token) {
        tokens[tokenCount++] = token; // 存储每个节点值或"null"
        token = strtok(NULL, ",");
    }

    if (tokenCount == 0) return NULL; // 如果输入为空，返回空树

    // 创建节点数组
    TreeNode** nodes = (TreeNode**)malloc(sizeof(TreeNode*) * tokenCount);
    for (int i = 0; i < tokenCount; i++) {
        if (strcmp(tokens[i], "null") == 0) {
            nodes[i] = NULL; // "null" 表示空节点
        } else {
            nodes[i] = createNewNode(atoi(tokens[i])); // 创建新节点
        }
    }

    // 根据节点数组构建树
    int parentIndex = 0;
    for (int i = 0; i < tokenCount; i++) {
        if (nodes[i] != NULL) {
            // 为当前节点分配左子节点
            if (2 * parentIndex + 1 < tokenCount) {
                nodes[i]->left = nodes[2 * parentIndex + 1];
            }
            // 为当前节点分配右子节点
            if (2 * parentIndex + 2 < tokenCount) {
                nodes[i]->right = nodes[2 * parentIndex + 2];
            }
            parentIndex++;
        }
    }

    TreeNode* root = nodes[0]; // 根节点
    free(nodes); // 释放节点数组
    return root;
}

// 中序遍历并找到被交换的两个节点
void inorderTraversal(TreeNode* root, TreeNode** previous, TreeNode** first, TreeNode** second) {
    if (root == NULL) return;

    // 遍历左子树
    inorderTraversal(root->left, previous, first, second);

    // 检查当前节点是否与前一个节点构成逆序
    if (*previous && (*previous)->val > root->val) {
        if (*first == NULL) {
            *first = *previous; // 找到第一个错误节点
        }
        *second = root; // 找到第二个错误节点
    }
    *previous = root; // 更新前一个节点

    // 遍历右子树
    inorderTraversal(root->right, previous, first, second);
}

// 恢复二叉搜索树（交换两个错误节点的值）
void recoverTree(TreeNode* root) {
    TreeNode *previous = NULL, *first = NULL, *second = NULL;

    // 中序遍历找到错误的两个节点
    inorderTraversal(root, &previous, &first, &second);

    // 交换两个节点的值以恢复树的正确性
    if (first && second) {
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }
}

// 按层次打印二叉树
void printTree(TreeNode* root) {
    if (!root) return;

    // 队列用于层次遍历
    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    // 遍历二叉树的所有节点
    while (front < rear) {
        TreeNode* currentNode = queue[front++];
        if (currentNode) {
            queue[rear++] = currentNode->left;
            queue[rear++] = currentNode->right;
        }
    }

    // 从队列尾部去除多余的 NULL 节点
    int rearIndex = rear - 1;
    while (queue[rearIndex--] == NULL) {}

    // 打印非 NULL 节点和 "null" 节点
    for (int i = 0; i <= rearIndex; i++) {
        if (queue[i]) {
            printf("%d,", queue[i]->val);
        } else {
            printf("null,");
        }
    }

    // 打印最后一个节点（避免最后多一个逗号）
    if (queue[rearIndex + 1]) {
        printf("%d", queue[rearIndex + 1]->val);
    } else {
        printf("null");
    }
}

int main() {
    char input[1000];
    scanf("%s", input); // 输入二叉树节点的层次遍历（以逗号分隔）

    // 构建二叉树
    TreeNode* root = buildTree(input);

    // 恢复二叉搜索树
    recoverTree(root);

    // 打印恢复后的树
    printTree(root);

    return 0;
}

