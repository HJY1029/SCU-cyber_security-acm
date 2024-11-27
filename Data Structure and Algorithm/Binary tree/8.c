#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����������ڵ�ṹ��
typedef struct TreeNode {
    int val;                // �ڵ��ֵ
    struct TreeNode *left;  // ���ӽڵ�
    struct TreeNode *right; // ���ӽڵ�
} TreeNode;

// �����½ڵ�
TreeNode* createNewNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// ���������ַ�������������
TreeNode* buildTree(char* input) {
    // �ָ������ַ����������ŷָ�
    char* tokens[1000];
    int tokenCount = 0;
    char* token = strtok(input, ",");
    while (token) {
        tokens[tokenCount++] = token; // �洢ÿ���ڵ�ֵ��"null"
        token = strtok(NULL, ",");
    }

    if (tokenCount == 0) return NULL; // �������Ϊ�գ����ؿ���

    // �����ڵ�����
    TreeNode** nodes = (TreeNode**)malloc(sizeof(TreeNode*) * tokenCount);
    for (int i = 0; i < tokenCount; i++) {
        if (strcmp(tokens[i], "null") == 0) {
            nodes[i] = NULL; // "null" ��ʾ�սڵ�
        } else {
            nodes[i] = createNewNode(atoi(tokens[i])); // �����½ڵ�
        }
    }

    // ���ݽڵ����鹹����
    int parentIndex = 0;
    for (int i = 0; i < tokenCount; i++) {
        if (nodes[i] != NULL) {
            // Ϊ��ǰ�ڵ�������ӽڵ�
            if (2 * parentIndex + 1 < tokenCount) {
                nodes[i]->left = nodes[2 * parentIndex + 1];
            }
            // Ϊ��ǰ�ڵ�������ӽڵ�
            if (2 * parentIndex + 2 < tokenCount) {
                nodes[i]->right = nodes[2 * parentIndex + 2];
            }
            parentIndex++;
        }
    }

    TreeNode* root = nodes[0]; // ���ڵ�
    free(nodes); // �ͷŽڵ�����
    return root;
}

// ����������ҵ��������������ڵ�
void inorderTraversal(TreeNode* root, TreeNode** previous, TreeNode** first, TreeNode** second) {
    if (root == NULL) return;

    // ����������
    inorderTraversal(root->left, previous, first, second);

    // ��鵱ǰ�ڵ��Ƿ���ǰһ���ڵ㹹������
    if (*previous && (*previous)->val > root->val) {
        if (*first == NULL) {
            *first = *previous; // �ҵ���һ������ڵ�
        }
        *second = root; // �ҵ��ڶ�������ڵ�
    }
    *previous = root; // ����ǰһ���ڵ�

    // ����������
    inorderTraversal(root->right, previous, first, second);
}

// �ָ�������������������������ڵ��ֵ��
void recoverTree(TreeNode* root) {
    TreeNode *previous = NULL, *first = NULL, *second = NULL;

    // ��������ҵ�����������ڵ�
    inorderTraversal(root, &previous, &first, &second);

    // ���������ڵ��ֵ�Իָ�������ȷ��
    if (first && second) {
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }
}

// ����δ�ӡ������
void printTree(TreeNode* root) {
    if (!root) return;

    // �������ڲ�α���
    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    // ���������������нڵ�
    while (front < rear) {
        TreeNode* currentNode = queue[front++];
        if (currentNode) {
            queue[rear++] = currentNode->left;
            queue[rear++] = currentNode->right;
        }
    }

    // �Ӷ���β��ȥ������� NULL �ڵ�
    int rearIndex = rear - 1;
    while (queue[rearIndex--] == NULL) {}

    // ��ӡ�� NULL �ڵ�� "null" �ڵ�
    for (int i = 0; i <= rearIndex; i++) {
        if (queue[i]) {
            printf("%d,", queue[i]->val);
        } else {
            printf("null,");
        }
    }

    // ��ӡ���һ���ڵ㣨��������һ�����ţ�
    if (queue[rearIndex + 1]) {
        printf("%d", queue[rearIndex + 1]->val);
    } else {
        printf("null");
    }
}

int main() {
    char input[1000];
    scanf("%s", input); // ����������ڵ�Ĳ�α������Զ��ŷָ���

    // ����������
    TreeNode* root = buildTree(input);

    // �ָ�����������
    recoverTree(root);

    // ��ӡ�ָ������
    printTree(root);

    return 0;
}

