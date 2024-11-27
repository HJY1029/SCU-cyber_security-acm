#include <stdio.h>
#define MAX 100005

int preOrder[MAX];   // 前序遍历数组
int inOrder[MAX];    // 中序遍历数组
int postOrder[MAX];  // 后序遍历数组
int postIndex = 0;   // 后序遍历结果的索引

// 递归函数，构建后序遍历
void constructPostOrder(int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) return;  // 递归终止条件

    // 当前子树的根节点是前序遍历的第一个元素
    int root = preOrder[preStart];
    
    // 在中序遍历中找到根节点的位置
    int rootIndex = inStart;
    while (rootIndex <= inEnd && inOrder[rootIndex] != root) {
        rootIndex++;
    }

    // 计算左子树的大小
    int leftTreeSize = rootIndex - inStart;
    
    // 递归构建左子树和右子树
    constructPostOrder(preStart + 1, preStart + leftTreeSize, inStart, rootIndex - 1);
    constructPostOrder(preStart + leftTreeSize + 1, preEnd, rootIndex + 1, inEnd);
    
    // 将当前根节点添加到后序遍历结果中
    postOrder[postIndex++] = root;
}

int main() {
    int n;  // 节点数
    scanf("%d", &n);  // 输入节点数

    // 输入前序遍历数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &preOrder[i]);
    }

    // 输入中序遍历数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &inOrder[i]);
    }

    // 从根节点（前序的第一个节点）开始构建后序遍历
    constructPostOrder(0, n - 1, 0, n - 1);

    // 输出后序遍历结果
    for (int i = 0; i < n; i++) {
        printf("%d%c", postOrder[i], i == n - 1 ? '\n' : ' ');  // 输出格式控制
    }

    return 0;
}

