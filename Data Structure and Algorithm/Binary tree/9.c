#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// ����������ڵ�ṹ
typedef struct TreeNode {
    int val;                  // �ڵ�ֵ
    struct TreeNode *left;    // ���ӽڵ�
    struct TreeNode *right;   // ���ӽڵ�
} TreeNode;

// ������нڵ�ṹ
typedef struct QueueNode {
    TreeNode *node;           // �洢�������ڵ�ָ��
    struct QueueNode *next;   // ָ����һ�����нڵ�
} QueueNode;

// ������нṹ
typedef struct {
    QueueNode *front;         // ����ͷ
    QueueNode *rear;          // ����β
} Queue;

// ��ʼ������
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

// �ж϶����Ƿ�Ϊ��
bool isEmpty(Queue *q) {
    return q->front == NULL;
}

// ��Ӳ���
void enqueue(Queue *q, TreeNode *node) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// ���Ӳ���
TreeNode *dequeue(Queue *q) {
    if (isEmpty(q)) return NULL;
    QueueNode *temp = q->front;
    TreeNode *node = temp->node;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return node;
}

// �ж϶������Ƿ�Ϊ��ż��
bool isEvenOddTree(TreeNode *root) {
    if (!root) return true;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    int level = 0; // ��ǰ���

    while (!isEmpty(&q)) {
        // ���㵱ǰ��Ľڵ�����
        int size = 0;
        QueueNode *cur = q.front;
        while (cur) {
            size++;
            cur = cur->next;
        }

        // ���ó�ʼֵ��ż������СΪ0�����������ΪINT_MAX
        int prevVal = (level % 2 == 0) ? 0 : INT_MAX;

        // ������ǰ������нڵ�
        for (int i = 0; i < size; i++) {
            TreeNode *node = dequeue(&q);
            int val = node->val;

            // ż���㣺ֵΪ���������ϸ����
            if (level % 2 == 0) {
                if (val % 2 == 0 || val <= prevVal) return false;
            }
            // �����㣺ֵΪż�������ϸ�ݼ�
            else {
                if (val % 2 != 0 || val >= prevVal) return false;
            }
            prevVal = val;

            // ���ӽڵ�������
            if (node->left) enqueue(&q, node->left);
            if (node->right) enqueue(&q, node->right);
        }
        level++; // ������һ��
    }

    return true;
}

// �����¶������ڵ�
TreeNode *createNode(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// ���ݲ�α�������������
TreeNode* buildTreeFromLevelOrder(char *input) {
    if (input == NULL || input[0] == '\0') return NULL;

    // ʹ�� strtok �ָ������ַ���
    char *token = strtok(input, ",");
    if (token == NULL) return NULL;

    // �������ڵ㲢��ʼ������
    TreeNode *root = createNode(atoi(token));
    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    // ����������
    while (!isEmpty(&q)) {
        TreeNode *current = dequeue(&q);

        // �������ӽڵ�
        token = strtok(NULL, ",");
        if (token != NULL && strcmp(token, "null") != 0) {
            current->left = createNode(atoi(token));
            enqueue(&q, current->left);
        }

        // �������ӽڵ�
        token = strtok(NULL, ",");
        if (token != NULL && strcmp(token, "null") != 0) {
            current->right = createNode(atoi(token));
            enqueue(&q, current->right);
        }
    }

    return root;
}

// �ͷŶ������ڴ�
void freeTree(TreeNode *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// ������
int main() {
    char input[1000];
    // ��ȡ�û�����Ĳ�α����ַ���
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // ȥ��ĩβ�Ļ��з�

    // ����������
    TreeNode *root = buildTreeFromLevelOrder(input);

    // �ж��Ƿ�Ϊ��ż����������
    if (isEvenOddTree(root)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    // �ͷŶ������ڴ�
    freeTree(root);

    return 0;
}

