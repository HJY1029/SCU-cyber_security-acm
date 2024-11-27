#include <stdio.h>
#include <stdlib.h>

// ��������ڵ�ṹ��
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

// �����½ڵ�
ListNode* createNode(int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// �������ȡ����
ListNode* readList() {
    ListNode *head = NULL, *current = NULL;
    int value;
    while (scanf("%d", &value) && value != -1) {
        ListNode* newNode = createNode(value);
        if (!head) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }
    return head;
}

// �������������
int maxTwinSum(ListNode* head) {
    if (head == NULL) return 0;

    // ���������Ȳ��洢�ڵ�ֵ
    int n = 0;
    ListNode* current = head;
    while (current != NULL) {
        n++;
        current = current->next;
    }

    // ��̬��������洢����ֵ
    int *values = (int*)malloc(n * sizeof(int));
    current = head;
    for (int i = 0; i < n; i++) {
        values[i] = current->val;
        current = current->next;
    }

    // ���������͵����ֵ
    int maxSum = 0;
    for (int i = 0; i < n / 2; i++) {
        int twinSum = values[i] + values[n - i - 1];
        if (twinSum > maxSum) {
            maxSum = twinSum;
        }
    }

    free(values); // �ͷ������ڴ�
    return maxSum;
}

// �ͷ������ڴ�
void freeList(ListNode* head) {
    while (head != NULL) {
        ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // ��ȡ����
    ListNode* head = readList();

    // �������������
    int result = maxTwinSum(head);
    printf("%d\n", result);

    // �ͷ������ڴ�
    freeList(head);

    return 0;
}

