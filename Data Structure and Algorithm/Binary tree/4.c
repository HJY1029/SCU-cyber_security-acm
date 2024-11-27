#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NULL_NODE -1  // �� -1 ���� null �ڵ�

// ����������ڵ�ṹ��
struct TreeNode {
    int val;                // �ڵ��ֵ
    struct TreeNode *left;  // ���ӽڵ�
    struct TreeNode *right; // ���ӽڵ�
};

// ����һ���½ڵ㲢��ʼ��
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));  // �����ڴ�
    node->val = val;   // ���ýڵ��ֵ
    node->left = NULL;  // ��ʼ�����ӽڵ�Ϊ��
    node->right = NULL; // ��ʼ�����ӽڵ�Ϊ��
    return node;
}

// �ݹ�����������Ҷ�ӽڵ�ĺ�
int sumOfLeftLeaves(struct TreeNode* root) {
    if (root == NULL) return 0;  // �����Ϊ�գ�����0

    int leftSum = 0;

    // ��鵱ǰ�ڵ�����ӽڵ��Ƿ���Ҷ�ӽڵ�
    if (root->left && root->left->left == NULL && root->left->right == NULL) {
        leftSum += root->left->val;  // �������Ҷ�ӽڵ㣬�ۼ���ֵ
    }

    // �ݹ�ؼ���������������������Ҷ�ӽڵ��
    leftSum += sumOfLeftLeaves(root->left);
    leftSum += sumOfLeftLeaves(root->right);

    return leftSum;
}

// �������ַ�������������
int parseInput(char* input, int* arr) {
    int index = 0;
    char* token = strtok(input, "[, ]");

    // ����ָ��������
    while (token != NULL) {
        // ����� "null" �ַ�������ʾ��ǰ�ڵ�Ϊ��
        if (strcmp(token, "null") == 0) {
            arr[index++] = NULL_NODE;  // �� NULL_NODE ��ʾ�սڵ�
        }
        // �����������ת��Ϊ��������������
        else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            arr[index++] = atoi(token);  // ���ַ���תΪ����
        }
        token = strtok(NULL, "[, ]");  // �����ָ�
    }
    return index;  // ���ؽ��������鳤��
}

// �������鹹��������
struct TreeNode* buildTree(int* arr, int size) {
    if (size == 0 || arr[0] == NULL_NODE) return NULL;  // �������Ϊ�ջ���ڵ�Ϊ null���򷵻ؿ���

    struct TreeNode** nodes = (struct TreeNode**)malloc(size * sizeof(struct TreeNode*));  // �����ڵ�����
    struct TreeNode* root = newNode(arr[0]);  // �������ڵ�
    nodes[0] = root;  // ���ڵ������

    // �𲽹������Ľڵ�
    for (int i = 0, j = 1; j < size; ++i) {
        if (nodes[i] != NULL) {
            // �������ӽڵ�
            if (j < size && arr[j] != NULL_NODE) {
                nodes[i]->left = newNode(arr[j]);  // �������ӽڵ�
                nodes[j] = nodes[i]->left;         // �����ӽڵ����
            }
            j++;

            // �������ӽڵ�
            if (j < size && arr[j] != NULL_NODE) {
                nodes[i]->right = newNode(arr[j]);  // �������ӽڵ�
                nodes[j] = nodes[i]->right;         // �����ӽڵ����
            }
            j++;
        }
    }

    free(nodes);  // �ͷ���ʱ����Ľڵ������ڴ�
    return root;  // ���ع����õ����ĸ��ڵ�
}

int main() {
    char input[100];  // �洢������ַ���
    int arr[100];     // �洢�����������

    fgets(input, sizeof(input), stdin);  // ��ȡ����
    int size = parseInput(input, arr);   // ���������ַ���Ϊ����
    struct TreeNode* root = buildTree(arr, size);  // �������鹹��������

    int result = sumOfLeftLeaves(root);  // ������Ҷ�ӽڵ�֮��
    printf("%d\n", result);  // ������

    return 0;
}

