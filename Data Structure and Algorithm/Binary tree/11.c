#include <stdio.h>

// 定义全局变量存储节点信息
int nodeValues[100];     // 节点权值数组
int leftChild[100];      // 左孩子数组
int rightChild[100];     // 右孩子数组
int subtreeSums[100];    // 每个节点为根的子树权值和数组

// 递归函数，计算以当前节点为根的子树权值和
int calculateSubtreeSum(int node) {
    if (node == -1) {  // 如果当前节点不存在
        return 0;  // 返回0表示没有节点
    }
    
    // 递归计算左子树和右子树的权值和
    int leftSubtreeSum = calculateSubtreeSum(leftChild[node]);
    int rightSubtreeSum = calculateSubtreeSum(rightChild[node]);
    
    // 当前子树的权值和 = 左子树 + 右子树 + 当前节点的权值
    subtreeSums[node] = leftSubtreeSum + rightSubtreeSum + nodeValues[node];
    
    return subtreeSums[node];  // 返回当前节点为根的子树的权值和
}

int main() {
    int n;  // 节点数
    scanf("%d", &n);  // 输入节点数

    // 读取每个节点的权值
    for (int i = 0; i < n; i++) {
        scanf("%d", &nodeValues[i]);  // 输入节点权值
    }

    // 读取每个节点的左右孩子的编号
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &leftChild[i], &rightChild[i]);
        
        // 如果孩子节点存在，将其编号转换为 0 索引
        if (leftChild[i] != -1) {
            leftChild[i] -= 1;
        }
        if (rightChild[i] != -1) {
            rightChild[i] -= 1;
        }
    }

    // 从根节点（节点 0）开始计算整个树的子树权值和
    calculateSubtreeSum(0);

    // 输出每个节点为根的子树的权值和
    for (int i = 0; i < n; i++) {
        printf("%d ", subtreeSums[i]);  // 输出每个节点子树的权值和
    }
    printf("\n");

    return 0;
}

