#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

// ����������ڵ�ṹ
typedef struct TreeNode {
    int val;                // �ڵ��ֵ
    struct TreeNode* left;  // ���ӽڵ�
    struct TreeNode* right; // ���ӽڵ�
} TreeNode;

// ����һ���µĽڵ�
TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));  // ��̬�����ڴ�
    newNode->val = val;  // ���ýڵ��ֵ
    newNode->left = NULL; // ��ʼ�����ӽڵ�Ϊ��
    newNode->right = NULL; // ��ʼ�����ӽڵ�Ϊ��
    return newNode;
}

// ��������ַ�������������
TreeNode* buildTree(char* input) {
    if (strlen(input) == 0) return NULL;  // �������Ϊ�գ����ؿ���

    char* tokens[MAX];  // ���ڴ洢�ַ����зֺ��ÿ������
    int count = 0;       // ��¼�ָ����Ӵ�����
    char* token = strtok(input, ","); // ͨ�����ŷָ������ַ���
    while (token) {
        tokens[count++] = token;  // ��ÿ���Ӵ����� tokens ����
        token = strtok(NULL, ","); // ��ȡ��һ���Ӵ�
    }

    // �������ĸ��ڵ㣬���ڵ��ֵ���ַ����еĵ�һ������
    TreeNode* root = createNode(atoi(tokens[0]));  
    TreeNode* queue[MAX];  // �������ڰ���α���������
    int front = 0, rear = 0;  // ���е�ͷ��β
    queue[rear++] = root;  // �����ڵ�������

    int i = 1; // ���ڱ��� tokens ����
    while (i < count) {
        TreeNode* current = queue[front++];  // ȡ�����׽ڵ�
        if (current) {
            // �����ǰ�ڵ����ӽڵ㲻Ϊ�գ��������ӽڵ�
            if (i < count && strcmp(tokens[i], "null") != 0) {
                current->left = createNode(atoi(tokens[i]));
                queue[rear++] = current->left;  // �����ӽڵ�������
            }
            i++; // �ƶ�����һ��λ��

            // �����ǰ�ڵ����ӽڵ㲻Ϊ�գ��������ӽڵ�
            if (i < count && strcmp(tokens[i], "null") != 0) {
                current->right = createNode(atoi(tokens[i]));
                queue[rear++] = current->right; // �����ӽڵ�������
            }
            i++; // �ƶ�����һ��λ��
        }
    }
    return root;  // ���ع����õĶ������ĸ��ڵ�
}

// ��ת������
TreeNode* invertTree(TreeNode* root) {
    if (root == NULL) {
        return NULL;  // �����Ϊ�գ����ؿ�
    }
    // ������������
    TreeNode* temp = root->left;  // ��ʱ����������
    root->left = invertTree(root->right);  // �ݹ鷭ת������
    root->right = invertTree(temp);  // �ݹ鷭ת������
    return root;  // ���ط�ת��ĸ��ڵ�
}

// ��α������������
void printTree(TreeNode* root) {
    if (root == NULL) {
        printf("null");  // �����Ϊ�գ���� null
        return;
    }

    TreeNode* queue[100];  // �������ڲ�α���
    int front = 0, rear = 0;  // ���е�ͷ��β

    queue[rear++] = root;  // �����ڵ�������

    while (front < rear) {
        TreeNode* current = queue[front++];  // ȡ�����׽ڵ�
        if (current) {
            printf("%d,", current->val);  // �����ǰ�ڵ��ֵ
            queue[rear++] = current->left;  // �����ӽڵ�������
            queue[rear++] = current->right; // �����ӽڵ�������
        } else {
            // �����ǰ�ڵ�Ϊ�գ���� null
            printf("null,");
        }
    }

    // ��ӡ�����нڵ��ȥ�����һ������Ķ��ţ�������
    printf("\b \n");
}

// ������
int main() {
    char input[256];  // �洢�û���������ı�ʾ
    fgets(input, sizeof(input), stdin);  // ��ȡ����
    input[strcspn(input, "\n")] = 0;  // ȥ������ĩβ�Ļ��з�

    // �������빹��������
    TreeNode* root = buildTree(input);

    // ��ת������
    root = invertTree(root);

    // �����ת��Ķ�����
    printTree(root);

    return 0;
}

