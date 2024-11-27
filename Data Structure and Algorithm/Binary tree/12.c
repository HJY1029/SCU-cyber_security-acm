#include <stdio.h>
#define MAX 100005

int preOrder[MAX];   // ǰ���������
int inOrder[MAX];    // �����������
int postOrder[MAX];  // �����������
int postIndex = 0;   // ����������������

// �ݹ麯���������������
void constructPostOrder(int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) return;  // �ݹ���ֹ����

    // ��ǰ�����ĸ��ڵ���ǰ������ĵ�һ��Ԫ��
    int root = preOrder[preStart];
    
    // ������������ҵ����ڵ��λ��
    int rootIndex = inStart;
    while (rootIndex <= inEnd && inOrder[rootIndex] != root) {
        rootIndex++;
    }

    // �����������Ĵ�С
    int leftTreeSize = rootIndex - inStart;
    
    // �ݹ鹹����������������
    constructPostOrder(preStart + 1, preStart + leftTreeSize, inStart, rootIndex - 1);
    constructPostOrder(preStart + leftTreeSize + 1, preEnd, rootIndex + 1, inEnd);
    
    // ����ǰ���ڵ���ӵ�������������
    postOrder[postIndex++] = root;
}

int main() {
    int n;  // �ڵ���
    scanf("%d", &n);  // ����ڵ���

    // ����ǰ���������
    for (int i = 0; i < n; i++) {
        scanf("%d", &preOrder[i]);
    }

    // ���������������
    for (int i = 0; i < n; i++) {
        scanf("%d", &inOrder[i]);
    }

    // �Ӹ��ڵ㣨ǰ��ĵ�һ���ڵ㣩��ʼ�����������
    constructPostOrder(0, n - 1, 0, n - 1);

    // �������������
    for (int i = 0; i < n; i++) {
        printf("%d%c", postOrder[i], i == n - 1 ? '\n' : ' ');  // �����ʽ����
    }

    return 0;
}

