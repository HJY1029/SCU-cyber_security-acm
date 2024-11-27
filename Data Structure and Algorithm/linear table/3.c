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

// ɾ��������ָ��ֵ�ڵ�ĺ���
ListNode* deleteNode(ListNode* head, int targetValue) {
    // ����һ������ͷ�ڵ㣬���㴦��ͷ�ڵ��ɾ��
    ListNode* dummyHead = createNode(0);
    dummyHead->next = head;       // ����ͷ�ڵ�ָ��ʵ������ͷ
    ListNode* current = dummyHead;

    // ��������
    while (current->next != NULL) {
        if (current->next->value == targetValue) {
            // �����һ���ڵ��ֵΪĿ��ֵ�������ýڵ�
            current->next = current->next->next;
        } else {
            // �����ƶ�����һ���ڵ�
            current = current->next;
        }
    }

    // ��ȡ�������ͷ�ڵ㲢�ͷ�����ͷ�ڵ��ڴ�
    ListNode* newHead = dummyHead->next;
    free(dummyHead);
    return newHead;
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
    int inputValue;
    ListNode *head = NULL, *tail = NULL;

    // ѭ����ȡ�û����룬-1 ��ʾ�������
    scanf("%d", &inputValue);
    while (inputValue != -1) {
        ListNode* newNode = createNode(inputValue); // �����½ڵ�
        if (head == NULL) {
            head = newNode;       // �������Ϊ�գ���ʼ��ͷ�ڵ�
            tail = newNode;       // ͬʱ����β�ڵ�
        } else {
            tail->next = newNode; // ���½ڵ�׷�ӵ�����ĩβ
            tail = newNode;       // ����β�ڵ�
        }
        scanf("%d", &inputValue);
    }

    return head; // ���������ͷ�ڵ�
}

int main() {
    // ���û������ȡ����
    ListNode* head = readList();

    // ��ȡҪɾ����ֵ
    int targetValue;
    scanf("%d", &targetValue);

    // ɾ�����������е���Ŀ��ֵ�Ľڵ�
    ListNode* newHead = deleteNode(head, targetValue);

    // ��ӡ����������
    printList(newHead);

    // �ͷ������ڴ�
    ListNode* current = newHead;
    while (current != NULL) {
        ListNode* temp = current;  // ���浱ǰ�ڵ�
        current = current->next;  // �ƶ�����һ���ڵ�
        free(temp);               // �ͷŵ�ǰ�ڵ��ڴ�
    }

    return 0;
}

