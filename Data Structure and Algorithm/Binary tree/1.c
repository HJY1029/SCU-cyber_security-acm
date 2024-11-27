#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义二叉树节点结构体
typedef struct TreeNode {
    int val;               // 节点的值
    struct TreeNode* left; // 左子节点
    struct TreeNode* right; // 右子节点
} TreeNode;

// 创建新节点并初始化其值
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode)); // 动态分配内存
    newNode->val = value;   // 设置节点值
    newNode->left = NULL;    // 初始化左子节点为空
    newNode->right = NULL;   // 初始化右子节点为空
    return newNode;
}

// 根据数组构造二叉树，采用层序遍历方式
TreeNode* buildTreeFromArray(int* array, int arraySize, int currentIndex) {
    if (currentIndex >= arraySize || array[currentIndex] == -1) {
        return NULL; // 如果超出数组范围或遇到值为 -1，表示空节点
    }
    TreeNode* root = createNode(array[currentIndex]); // 创建当前节点
    root->left = buildTreeFromArray(array, arraySize, 2 * currentIndex + 1); // 递归创建左子树
    root->right = buildTreeFromArray(array, arraySize, 2 * currentIndex + 2); // 递归创建右子树
    return root;
}

// 判断两棵二叉树是否完全相同
int isSameTree(TreeNode* tree1, TreeNode* tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        return 1; // 两棵树都为空，认为相同
    }
    if (tree1 == NULL || tree2 == NULL) {
        return 0; // 其中一棵树为空，认为不同
    }
    // 递归判断当前节点值以及左右子树是否相同
    return (tree1->val == tree2->val) && 
           isSameTree(tree1->left, tree2->left) && 
           isSameTree(tree1->right, tree2->right);
}

// 解析用户输入的数组字符串，将其转换为整数数组
void parseInputArray(char* inputString, int* outputArray, int* outputSize) {
    *outputSize = 0;
    char* token = strtok(inputString, "[,] "); // 使用空格、逗号和方括号作为分隔符
    while (token != NULL) {
        if (strcmp(token, "null") == 0) {
            outputArray[(*outputSize)++] = -1; // 将 "null" 转换为 -1 表示空节点
        } else {
            outputArray[(*outputSize)++] = atoi(token); // 转换数字字符串为整数
        }
        token = strtok(NULL, "[,] "); // 获取下一个标记
    }
}

// 主函数
int main() {
    char input[200];            // 存储用户输入的字符串
    int arrP[100], arrQ[100];   // 存储两棵树的数组表示
    int sizeP, sizeQ;           // 数组的大小（即树的节点数）

    // 输入两棵树的数组表示
    fgets(input, sizeof(input), stdin); // 从标准输入读取字符串

    // 找到 "p" 和 "q" 数组在输入中的位置
    char* pStart = strstr(input, "p = [") + 5;  // 跳过 "p = ["
    char* pEnd = strstr(input, "], q = [");     // 找到 "p" 部分的结束位置
    char* qStart = pEnd + 7;                    // 跳过 "], q = ["

    // 临时存储字符串用于截取
    char pArray[100], qArray[100];
    strncpy(pArray, pStart, pEnd - pStart);    // 截取 "p" 数组部分
    pArray[pEnd - pStart] = '\0';              // 添加字符串结束符
    strcpy(qArray, qStart);                    // 截取 "q" 数组部分

    // 去掉 "q" 数组部分末尾的 "]"
    qArray[strlen(qArray) - 1] = '\0';

    // 解析 "p" 和 "q" 数组字符串为整数数组
    parseInputArray(pArray, arrP, &sizeP); // 解析 "p" 数组
    parseInputArray(qArray, arrQ, &sizeQ); // 解析 "q" 数组

    // 构造二叉树
    TreeNode* treeP = buildTreeFromArray(arrP, sizeP, 0); // 构造树 "p"
    TreeNode* treeQ = buildTreeFromArray(arrQ, sizeQ, 0); // 构造树 "q"

    // 判断两棵树是否相同
    if (isSameTree(treeP, treeQ)) {
        printf("输出: true\n"); // 如果相同，输出 true
    } else {
        printf("输出: false\n"); // 如果不同，输出 false
    }

    return 0;
}

