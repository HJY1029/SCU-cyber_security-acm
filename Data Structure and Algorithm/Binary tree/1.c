#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����������ڵ�ṹ��
typedef struct TreeNode {
    int val;               // �ڵ��ֵ
    struct TreeNode* left; // ���ӽڵ�
    struct TreeNode* right; // ���ӽڵ�
} TreeNode;

// �����½ڵ㲢��ʼ����ֵ
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode)); // ��̬�����ڴ�
    newNode->val = value;   // ���ýڵ�ֵ
    newNode->left = NULL;    // ��ʼ�����ӽڵ�Ϊ��
    newNode->right = NULL;   // ��ʼ�����ӽڵ�Ϊ��
    return newNode;
}

// �������鹹������������ò��������ʽ
TreeNode* buildTreeFromArray(int* array, int arraySize, int currentIndex) {
    if (currentIndex >= arraySize || array[currentIndex] == -1) {
        return NULL; // ����������鷶Χ������ֵΪ -1����ʾ�սڵ�
    }
    TreeNode* root = createNode(array[currentIndex]); // ������ǰ�ڵ�
    root->left = buildTreeFromArray(array, arraySize, 2 * currentIndex + 1); // �ݹ鴴��������
    root->right = buildTreeFromArray(array, arraySize, 2 * currentIndex + 2); // �ݹ鴴��������
    return root;
}

// �ж����ö������Ƿ���ȫ��ͬ
int isSameTree(TreeNode* tree1, TreeNode* tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        return 1; // ��������Ϊ�գ���Ϊ��ͬ
    }
    if (tree1 == NULL || tree2 == NULL) {
        return 0; // ����һ����Ϊ�գ���Ϊ��ͬ
    }
    // �ݹ��жϵ�ǰ�ڵ�ֵ�Լ����������Ƿ���ͬ
    return (tree1->val == tree2->val) && 
           isSameTree(tree1->left, tree2->left) && 
           isSameTree(tree1->right, tree2->right);
}

// �����û�����������ַ���������ת��Ϊ��������
void parseInputArray(char* inputString, int* outputArray, int* outputSize) {
    *outputSize = 0;
    char* token = strtok(inputString, "[,] "); // ʹ�ÿո񡢶��źͷ�������Ϊ�ָ���
    while (token != NULL) {
        if (strcmp(token, "null") == 0) {
            outputArray[(*outputSize)++] = -1; // �� "null" ת��Ϊ -1 ��ʾ�սڵ�
        } else {
            outputArray[(*outputSize)++] = atoi(token); // ת�������ַ���Ϊ����
        }
        token = strtok(NULL, "[,] "); // ��ȡ��һ�����
    }
}

// ������
int main() {
    char input[200];            // �洢�û�������ַ���
    int arrP[100], arrQ[100];   // �洢�������������ʾ
    int sizeP, sizeQ;           // ����Ĵ�С�������Ľڵ�����

    // �����������������ʾ
    fgets(input, sizeof(input), stdin); // �ӱ�׼�����ȡ�ַ���

    // �ҵ� "p" �� "q" �����������е�λ��
    char* pStart = strstr(input, "p = [") + 5;  // ���� "p = ["
    char* pEnd = strstr(input, "], q = [");     // �ҵ� "p" ���ֵĽ���λ��
    char* qStart = pEnd + 7;                    // ���� "], q = ["

    // ��ʱ�洢�ַ������ڽ�ȡ
    char pArray[100], qArray[100];
    strncpy(pArray, pStart, pEnd - pStart);    // ��ȡ "p" ���鲿��
    pArray[pEnd - pStart] = '\0';              // ����ַ���������
    strcpy(qArray, qStart);                    // ��ȡ "q" ���鲿��

    // ȥ�� "q" ���鲿��ĩβ�� "]"
    qArray[strlen(qArray) - 1] = '\0';

    // ���� "p" �� "q" �����ַ���Ϊ��������
    parseInputArray(pArray, arrP, &sizeP); // ���� "p" ����
    parseInputArray(qArray, arrQ, &sizeQ); // ���� "q" ����

    // ���������
    TreeNode* treeP = buildTreeFromArray(arrP, sizeP, 0); // ������ "p"
    TreeNode* treeQ = buildTreeFromArray(arrQ, sizeQ, 0); // ������ "q"

    // �ж��������Ƿ���ͬ
    if (isSameTree(treeP, treeQ)) {
        printf("���: true\n"); // �����ͬ����� true
    } else {
        printf("���: false\n"); // �����ͬ����� false
    }

    return 0;
}

