#include<stdio.h>
#include<stdlib.h>

// ��������ڵ�ṹ��
typedef struct ListNode {
    int value;                 // �ڵ��ֵ
    struct ListNode *next;     // ָ����һ���ڵ��ָ��
} ListNode;

// �����½ڵ�ĺ���
ListNode* createNode(int nodeValue) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // �����ڴ�
    newNode->value = nodeValue;   // ���ýڵ��ֵ
    newNode->next = NULL;         // ��ʼ����һ�ڵ�Ϊ��
    return newNode;
}

// ���û������ȡ����ĺ���
ListNode* readList() {
    int inputValue;
    ListNode *head = NULL, *current = NULL;

    // ��ȡ�û����룬-1 ��ʾ�������
    while (scanf("%d", &inputValue) && inputValue != -1) {
        ListNode* newNode = createNode(inputValue); // �����½ڵ�
        if (!head) {
            head = newNode;       // �������Ϊ�գ���ʼ��ͷ�ڵ�
            current = head;       // ���õ�ǰָ��Ϊͷ�ڵ�
        } else {
            current->next = newNode; // ���½ڵ�׷�ӵ�����ĩβ
            current = newNode;       // ���µ�ǰָ��
        }
    }

    return head; // ���������ͷ�ڵ�
}

// �����������ڵ�ֵ�ĺ���
void reversePrint(ListNode *head, int *array, int *size) {
    ListNode *current = head;

    // �����������ڵ�ֵ��������
    while (current != NULL) {
        array[(*size)++] = current->value; // ���浱ǰ�ڵ�ֵ�����鲢���������С
        current = current->next;          // �ƶ�����һ���ڵ�
    }

    // ������β����ʼ��ӡ��ʵ�ַ������
    for (int i = *size - 1; i >= 0; i--) {
        printf("%d ", array[i]);
    }
    printf("\n"); // �����������
}

int main() {
    // ���û������ȡ����
    ListNode *head = readList();

    // ����洢����ֵ������������С
    int array[10000]; // ���������Ȳ��ᳬ��10000
    int size = 0;

    // �����ӡ����
    reversePrint(head, array, &size);

    // �ͷ������ڴ�
    while (head != NULL) {
        ListNode *temp = head;  // ���浱ǰ�ڵ�
        head = head->next;      // �ƶ�����һ���ڵ�
        free(temp);             // �ͷŵ�ǰ�ڵ��ڴ�
    }

    return 0;
}

