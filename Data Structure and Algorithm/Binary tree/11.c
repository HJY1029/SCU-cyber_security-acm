#include <stdio.h>

// ����ȫ�ֱ����洢�ڵ���Ϣ
int nodeValues[100];     // �ڵ�Ȩֵ����
int leftChild[100];      // ��������
int rightChild[100];     // �Һ�������
int subtreeSums[100];    // ÿ���ڵ�Ϊ��������Ȩֵ������

// �ݹ麯���������Ե�ǰ�ڵ�Ϊ��������Ȩֵ��
int calculateSubtreeSum(int node) {
    if (node == -1) {  // �����ǰ�ڵ㲻����
        return 0;  // ����0��ʾû�нڵ�
    }
    
    // �ݹ��������������������Ȩֵ��
    int leftSubtreeSum = calculateSubtreeSum(leftChild[node]);
    int rightSubtreeSum = calculateSubtreeSum(rightChild[node]);
    
    // ��ǰ������Ȩֵ�� = ������ + ������ + ��ǰ�ڵ��Ȩֵ
    subtreeSums[node] = leftSubtreeSum + rightSubtreeSum + nodeValues[node];
    
    return subtreeSums[node];  // ���ص�ǰ�ڵ�Ϊ����������Ȩֵ��
}

int main() {
    int n;  // �ڵ���
    scanf("%d", &n);  // ����ڵ���

    // ��ȡÿ���ڵ��Ȩֵ
    for (int i = 0; i < n; i++) {
        scanf("%d", &nodeValues[i]);  // ����ڵ�Ȩֵ
    }

    // ��ȡÿ���ڵ�����Һ��ӵı��
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &leftChild[i], &rightChild[i]);
        
        // ������ӽڵ���ڣ�������ת��Ϊ 0 ����
        if (leftChild[i] != -1) {
            leftChild[i] -= 1;
        }
        if (rightChild[i] != -1) {
            rightChild[i] -= 1;
        }
    }

    // �Ӹ��ڵ㣨�ڵ� 0����ʼ����������������Ȩֵ��
    calculateSubtreeSum(0);

    // ���ÿ���ڵ�Ϊ����������Ȩֵ��
    for (int i = 0; i < n; i++) {
        printf("%d ", subtreeSums[i]);  // ���ÿ���ڵ�������Ȩֵ��
    }
    printf("\n");

    return 0;
}

