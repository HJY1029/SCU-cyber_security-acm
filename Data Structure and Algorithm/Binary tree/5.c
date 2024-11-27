#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����������ڵ�ṹ��
struct TreeNode {
    int val;                // �ڵ�ֵ
    struct TreeNode* left;  // ������
    struct TreeNode* right; // ������
};

// �ݹ鹹��������������ƽ���������
struct TreeNode* buildBST(int* nums, int left, int right) {
    if (left > right) {
        return NULL;  // ��������������Ϊ�գ����� NULL
    }
    
    // ѡ���м�Ԫ����Ϊ���ڵ㣬�Ա�֤ƽ��
    int mid = (left + right) / 2;  // �����м�λ��
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));  // �������ڵ�
    root->val = nums[mid];  // ���ø��ڵ��ֵ
    
    // �ݹ鹹����������������
    root->left = buildBST(nums, left, mid - 1);
    root->right = buildBST(nums, mid + 1, right);
    
    return root;  // ���ع����õĶ���������
}

// ��α�������ӡ������
void printTree(struct TreeNode* root) {
    if (!root) return;  // �����Ϊ�գ�����

    struct TreeNode* queue[100];  // �������ڲ�α���
    int front = 0, rear = 0;
    queue[rear++] = root;  // �����ڵ����
    
    // ��α���������
    while (front < rear) {
        struct TreeNode* node = queue[front++];  // ����
        if (node) {
            queue[rear++] = node->left;  // ���ӽڵ����
            queue[rear++] = node->right; // ���ӽڵ����
        } 
    }

    // ��ӡ��α����Ľ��
    int i = 0;
    while (queue[i] != NULL) {
        if (queue[i]) {
            printf("%d,", queue[i]->val);  // ����ڵ㲻Ϊ�գ���ӡ�ڵ�ֵ
        } else {
            printf("null,");  // ����ڵ�Ϊ�գ���ӡ null
        }
        i++;
    }

    // ��ӡ���һ���ڵ㣬�������Ķ���
    if (queue[i]) {
        printf("%d", queue[i]->val);
    } else {
        printf("null");
    }
}

// ���������ַ���Ϊ����
int parseInput(char* input, int* nums) {
    int count = 0;
    char* token = strtok(input, ",");
    
    // �����ŷָ�������ַ�����ת������������������
    while (token) {
        nums[count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    
    return count;  // ��������Ĵ�С
}

int main() {
    char input[100];  // �洢������ַ���
    scanf("%s", input);  // ��ȡ����
    
    int nums[100];  // �洢���������������
    int size = parseInput(input, nums);  // �������벢��ȡ�����С
    
    // ��������������
    struct TreeNode* tree = buildBST(nums, 0, size - 1);
    
    // ��ӡ������
    printTree(tree);

    return 0;
}

