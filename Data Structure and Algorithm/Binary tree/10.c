#include <stdio.h>

#define MAX 100005  // �����������ڵ���

// ����ڵ�ṹ�壬��ʾ����ÿ���ڵ����������������
typedef struct Node {
    int left;  // ���ӽڵ�
    int right; // ���ӽڵ�
} Node;

Node tree[MAX];  // �洢����ÿ���ڵ�
int size[MAX];   // �洢ÿ���ڵ��������С�������ýڵ㣩

// �ݹ����ڵ��������С
int calculateSubtreeSize(int node) {
    if (node == -1) return 0;  // ����ڵ�Ϊ�գ�����0
    
    // �ݹ�������������������Ĵ�С
    int leftSubtreeSize = calculateSubtreeSize(tree[node].left);
    int rightSubtreeSize = calculateSubtreeSize(tree[node].right);
    
    // ��ǰ�ڵ��������С = 1����ǰ�ڵ㣩 + ��������С + ��������С
    size[node] = 1 + leftSubtreeSize + rightSubtreeSize;
    
    return size[node];  // ���ص�ǰ�ڵ��������С
}

int main() {
    int n;
    scanf("%d", &n);  // �������Ľڵ���
    
    // ����ÿ���ڵ�������ӽڵ�
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &tree[i].left, &tree[i].right);
    }
    
    // ������ڵ㣨�ڵ�1����������С
    calculateSubtreeSize(1);
    
    // ���ÿ���ڵ��������С
    for (int i = 1; i <= n; i++) {
        printf("%d%c", size[i], i == n ? '\n' : ' ');  // �����С�����Ƹ�ʽ
    }
    
    return 0;
}

