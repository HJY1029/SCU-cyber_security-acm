#include<stdio.h>
#include<stdlib.h>

// ��������ڵ�Ľṹ��
typedef struct ListNode {
    int value;                 // �ڵ�ֵ
    struct ListNode* next;     // ָ����һ���ڵ��ָ��
} ListNode;

// �����½ڵ�ĺ���
ListNode* createNode(int nodeValue) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // �����ڴ�
    newNode->value = nodeValue;   // ��ʼ���ڵ��ֵ
    newNode->next = NULL;         // ��ʼ����һ�ڵ�ָ��Ϊ��
    return newNode;
}

// ɾ���������ظ�Ԫ�صĺ���
ListNode* deleteNode(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head; // ����Ϊ�ջ�ֻ��һ���ڵ�ʱֱ�ӷ���
    }
    ListNode* current = head; // ��ǰ�����Ľڵ�ָ��
    while (current->next != NULL) {
        if (current->value == current->next->value) {
            // �����ǰ�ڵ����һ���ڵ��ֵ��ͬ��������һ���ڵ�
            current->next = current->next->next;
        } else {
            // �����ƶ�����һ���ڵ�
            current = current->next;
        }
    }
    return head; // ����ȥ�غ������ͷ�ڵ�
}

// ��ӡ����ĺ���
void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->value); // ��ӡ�ڵ��ֵ
        head = head->next;          // �ƶ�����һ���ڵ�
    }
    printf("\n");                   // ����
}

// ���û������ȡ����ĺ���
ListNode* readList() {
    int inputValue;                 // �洢�û������ֵ
    ListNode *head = NULL;          // ����ͷָ��
    ListNode *current = NULL;       // ��ǰ����β��ָ��

    // ѭ����ȡ�û����룬-1 ��ʾ�������
    while (scanf("%d", &inputValue) && inputValue != -1) {
        ListNode* newNode = createNode(inputValue); // �����½ڵ�
        if (head == NULL) {
            head = newNode;         // �������Ϊ�գ���ʼ��ͷ�ڵ�
            current = head;
        } else {
            current->next = newNode; // ���½ڵ�׷�ӵ�����ĩβ
            current = newNode;
        }
    }

    return head; // ���������ͷ�ڵ�
}

int main() {
    // ���û������ȡ����
    ListNode* head = readList();

    // ɾ���������ظ��Ľڵ�
    head = deleteNode(head);

    // ��ӡ����������
    printList(head);

    // �ͷ������ڴ�
    ListNode* current = head;
    while (current != NULL) {
        ListNode* nextNode = current->next; // ������һ�ڵ�ָ��
        free(current);                      // �ͷŵ�ǰ�ڵ��ڴ�
        current = nextNode;                 // �ƶ�����һ�ڵ�
    }

    return 0;
}

