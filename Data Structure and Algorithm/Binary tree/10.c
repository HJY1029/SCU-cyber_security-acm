#include <stdio.h>

#define MAX 100005  // 定义树的最大节点数

// 定义节点结构体，表示树的每个节点的左子树和右子树
typedef struct Node {
    int left;  // 左子节点
    int right; // 右子节点
} Node;

Node tree[MAX];  // 存储树的每个节点
int size[MAX];   // 存储每个节点的子树大小（包括该节点）

// 递归计算节点的子树大小
int calculateSubtreeSize(int node) {
    if (node == -1) return 0;  // 如果节点为空，返回0
    
    // 递归计算左子树和右子树的大小
    int leftSubtreeSize = calculateSubtreeSize(tree[node].left);
    int rightSubtreeSize = calculateSubtreeSize(tree[node].right);
    
    // 当前节点的子树大小 = 1（当前节点） + 左子树大小 + 右子树大小
    size[node] = 1 + leftSubtreeSize + rightSubtreeSize;
    
    return size[node];  // 返回当前节点的子树大小
}

int main() {
    int n;
    scanf("%d", &n);  // 输入树的节点数
    
    // 输入每个节点的左右子节点
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &tree[i].left, &tree[i].right);
    }
    
    // 计算根节点（节点1）的子树大小
    calculateSubtreeSize(1);
    
    // 输出每个节点的子树大小
    for (int i = 1; i <= n; i++) {
        printf("%d%c", size[i], i == n ? '\n' : ' ');  // 输出大小并控制格式
    }
    
    return 0;
}

