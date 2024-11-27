#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

// ����������ڵ�ṹ��
typedef struct TreeNode {
    int val;                // �ڵ��ֵ
    struct TreeNode* left;  // ���ӽڵ�
    struct TreeNode* right; // ���ӽڵ�
} TreeNode;

// ����һ���½ڵ㲢��ʼ��
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode)); // ��̬�����ڴ�
    newNode->val = value;  // ���ýڵ��ֵ
    newNode->left = NULL;   // ��ʼ�����ӽڵ�Ϊ��
    newNode->right = NULL;  // ��ʼ�����ӽڵ�Ϊ��
    return newNode;
}

// �������ַ�������������
TreeNode* buildTree(char* input) {
    if (strlen(input) == 0) return NULL;  // �������Ϊ���ַ��������ؿ���

    char* tokens[MAX];  // �洢��ֺ���ַ���Ƭ��
    int count = 0;
    char* token = strtok(input, ","); // �����ŷָ��ַ���
    while (token) {
        tokens[count++] = token;  // ��ÿ���Ӵ���������
        token = strtok(NULL, ","); // ��ȡ��һ���Ӵ�
    }

    // �������ĸ��ڵ�
    TreeNode* root = createNode(atoi(tokens[0])); // ���ڵ��ֵ�ǵ�һ���Ӵ�
    TreeNode* queue[MAX];  // �������ڰ���α�������������
    int front = 0, rear = 0;
    queue[rear++] = root; // �����ڵ�������
    
    int i = 1;
    while (i < count) {
        TreeNode* current = queue[front++]; // ȡ������Ԫ��
        if (current) {
            // �������ӽڵ�
            if (i < count && strcmp(tokens[i], "null") != 0) {
                current->left = createNode(atoi(tokens[i])); // �������ӽڵ�
                queue[rear++] = current->left;  // �����ӽڵ�������
            }
            i++;  // ������һ���ڵ�
            
            // �������ӽڵ�
            if (i < count && strcmp(tokens[i], "null") != 0) {
                current->right = createNode(atoi(tokens[i])); // �������ӽڵ�
                queue[rear++] = current->right; // �����ӽڵ�������
            }
            i++; // ������һ���ڵ�
        }
    }
    return root;  // ���ع����õ����ĸ��ڵ�
}

// �ж����������Ƿ�Գ�
int isSymmetricHelper(TreeNode* left, TreeNode* right) {
    if (!left && !right) return 1;  // �������������Ϊ�գ����� true
    if (!left || !right) return 0;  // ���ֻ��һ������Ϊ�գ����� false
    if (left->val != right->val) return 0;  // ����ڵ�ֵ����ȣ����� false
    // �ݹ��ж����������Ƿ�Գ�
    return isSymmetricHelper(left->left, right->right) && isSymmetricHelper(left->right, right->left);
}

// �ж��������Ƿ�Գ�
int isSymmetric(TreeNode* root) {
    if (!root) return 1;  // �����Ϊ�գ�����Ϊ�ǶԳƵ�
    return isSymmetricHelper(root->left, root->right);  // ������������Ƿ�Գ�
}

int main() {
    char input[MAX];  // �洢�û�����Ķ�������ʾ
    fgets(input, sizeof(input), stdin);  // ��ȡ����
    input[strcspn(input, "\n")] = 0;  // ȥ��ĩβ�Ļ��з�

    // ����������
    TreeNode* root = buildTree(input);
    
    // �ж����Ƿ�ԳƲ�������
    if (isSymmetric(root)) {
        printf("true\n");  // ����Գƣ���� true
    } else {
        printf("false\n");  // ������Գƣ���� false
    }

    return 0;
}

