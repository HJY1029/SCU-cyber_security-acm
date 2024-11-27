#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义二叉树节点结构体
struct TreeNode {
    int val;                // 节点值
    struct TreeNode* left;  // 左子树
    struct TreeNode* right; // 右子树
};

// 递归构建二叉搜索树（平衡二叉树）
struct TreeNode* buildBST(int* nums, int left, int right) {
    if (left > right) {
        return NULL;  // 基础条件：区间为空，返回 NULL
    }
    
    // 选择中间元素作为根节点，以保证平衡
    int mid = (left + right) / 2;  // 计算中间位置
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));  // 创建根节点
    root->val = nums[mid];  // 设置根节点的值
    
    // 递归构建左子树和右子树
    root->left = buildBST(nums, left, mid - 1);
    root->right = buildBST(nums, mid + 1, right);
    
    return root;  // 返回构建好的二叉搜索树
}

// 层次遍历并打印二叉树
void printTree(struct TreeNode* root) {
    if (!root) return;  // 如果树为空，返回

    struct TreeNode* queue[100];  // 队列用于层次遍历
    int front = 0, rear = 0;
    queue[rear++] = root;  // 将根节点入队
    
    // 层次遍历二叉树
    while (front < rear) {
        struct TreeNode* node = queue[front++];  // 出队
        if (node) {
            queue[rear++] = node->left;  // 左子节点入队
            queue[rear++] = node->right; // 右子节点入队
        } 
    }

    // 打印层次遍历的结果
    int i = 0;
    while (queue[i] != NULL) {
        if (queue[i]) {
            printf("%d,", queue[i]->val);  // 如果节点不为空，打印节点值
        } else {
            printf("null,");  // 如果节点为空，打印 null
        }
        i++;
    }

    // 打印最后一个节点，避免多余的逗号
    if (queue[i]) {
        printf("%d", queue[i]->val);
    } else {
        printf("null");
    }
}

// 解析输入字符串为数组
int parseInput(char* input, int* nums) {
    int count = 0;
    char* token = strtok(input, ",");
    
    // 按逗号分割输入的字符串，转换成整数并存入数组
    while (token) {
        nums[count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    
    return count;  // 返回数组的大小
}

int main() {
    char input[100];  // 存储输入的字符串
    scanf("%s", input);  // 读取输入
    
    int nums[100];  // 存储解析后的整数数组
    int size = parseInput(input, nums);  // 解析输入并获取数组大小
    
    // 构建二叉搜索树
    struct TreeNode* tree = buildBST(nums, 0, size - 1);
    
    // 打印二叉树
    printTree(tree);

    return 0;
}

