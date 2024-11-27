#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// 定义二叉树节点结构
typedef struct TreeNode {
    int val;                  // 节点值
    struct TreeNode *left;    // 左子节点
    struct TreeNode *right;   // 右子节点
} TreeNode;

// 定义队列节点结构
typedef struct QueueNode {
    TreeNode *node;           // 存储二叉树节点指针
    struct QueueNode *next;   // 指向下一个队列节点
} QueueNode;

// 定义队列结构
typedef struct {
    QueueNode *front;         // 队列头
    QueueNode *rear;          // 队列尾
} Queue;

// 初始化队列
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

// 判断队列是否为空
bool isEmpty(Queue *q) {
    return q->front == NULL;
}

// 入队操作
void enqueue(Queue *q, TreeNode *node) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// 出队操作
TreeNode *dequeue(Queue *q) {
    if (isEmpty(q)) return NULL;
    QueueNode *temp = q->front;
    TreeNode *node = temp->node;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return node;
}

// 判断二叉树是否为奇偶树
bool isEvenOddTree(TreeNode *root) {
    if (!root) return true;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    int level = 0; // 当前层次

    while (!isEmpty(&q)) {
        // 计算当前层的节点数量
        int size = 0;
        QueueNode *cur = q.front;
        while (cur) {
            size++;
            cur = cur->next;
        }

        // 设置初始值：偶数层最小为0，奇数层最大为INT_MAX
        int prevVal = (level % 2 == 0) ? 0 : INT_MAX;

        // 遍历当前层的所有节点
        for (int i = 0; i < size; i++) {
            TreeNode *node = dequeue(&q);
            int val = node->val;

            // 偶数层：值为奇数，且严格递增
            if (level % 2 == 0) {
                if (val % 2 == 0 || val <= prevVal) return false;
            }
            // 奇数层：值为偶数，且严格递减
            else {
                if (val % 2 != 0 || val >= prevVal) return false;
            }
            prevVal = val;

            // 将子节点加入队列
            if (node->left) enqueue(&q, node->left);
            if (node->right) enqueue(&q, node->right);
        }
        level++; // 进入下一层
    }

    return true;
}

// 创建新二叉树节点
TreeNode *createNode(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 根据层次遍历构建二叉树
TreeNode* buildTreeFromLevelOrder(char *input) {
    if (input == NULL || input[0] == '\0') return NULL;

    // 使用 strtok 分割输入字符串
    char *token = strtok(input, ",");
    if (token == NULL) return NULL;

    // 创建根节点并初始化队列
    TreeNode *root = createNode(atoi(token));
    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    // 构建二叉树
    while (!isEmpty(&q)) {
        TreeNode *current = dequeue(&q);

        // 处理左子节点
        token = strtok(NULL, ",");
        if (token != NULL && strcmp(token, "null") != 0) {
            current->left = createNode(atoi(token));
            enqueue(&q, current->left);
        }

        // 处理右子节点
        token = strtok(NULL, ",");
        if (token != NULL && strcmp(token, "null") != 0) {
            current->right = createNode(atoi(token));
            enqueue(&q, current->right);
        }
    }

    return root;
}

// 释放二叉树内存
void freeTree(TreeNode *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// 主函数
int main() {
    char input[1000];
    // 获取用户输入的层次遍历字符串
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // 去掉末尾的换行符

    // 构建二叉树
    TreeNode *root = buildTreeFromLevelOrder(input);

    // 判断是否为奇偶树并输出结果
    if (isEvenOddTree(root)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    // 释放二叉树内存
    freeTree(root);

    return 0;
}

