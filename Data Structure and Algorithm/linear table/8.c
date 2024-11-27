#include <stdio.h>
#include <stdlib.h>

// ��������ڵ�ṹ��
typedef struct ListNode {
    int val;                // �ڵ�洢��ֵ
    struct ListNode* next;  // ָ����һ���ڵ��ָ��
} ListNode;

// �����½ڵ�ĺ���
ListNode* createNode(int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // �����ڴ�
    newNode->val = value;    // ��ʼ���ڵ�ֵ
    newNode->next = NULL;    // ������һ���ڵ�Ϊ��
    return newNode;
}

// ���û������ȡ����
ListNode* readList() {
    ListNode *head = NULL, *current = NULL;
    int value;

    // ѭ����ȡ���룬���� -1 ��ʾ����
    while (scanf("%d", &value) && value != -1) {
        ListNode* newNode = createNode(value); // �����½ڵ�
        if (!head) {
            head = newNode;    // ��ʼ������ͷ�ڵ�
            current = head;    // ���õ�ǰָ��Ϊͷ�ڵ�
        } else {
            current->next = newNode; // ���½ڵ�׷�ӵ�����ĩβ
            current = newNode;       // ���µ�ǰָ��
        }
    }
    return head; // ��������ͷ�ڵ�
}

// ��ת�����ָ������ [a, b]
ListNode* reverseList(ListNode* head, int a, int b) {
    if (!head || a == b) return head; // �������Ϊ�ջ���Ҫ��ת��ֱ�ӷ���ԭ����

    // ��������ͷ�ڵ㣬����ͳһ����ͷ�ڵ�ķ�ת
    ListNode dummy;
    dummy.next = head;
    ListNode* prev = &dummy;

    // �ҵ���ת���ֵ�ǰһ���ڵ�
    for (int i = 1; i < a; i++) {
        prev = prev->next;
    }

    ListNode* start = prev->next; // ��ת��ʼ�Ľڵ�
    ListNode* then = start->next; // ��ת���ֵĵڶ����ڵ�

    // ��תָ������
    for (int i = 0; i < b - a; i++) {
        start->next = then->next; // ���µ�ǰ��ʼ�ڵ�� next ָ��
        then->next = prev->next;  // ��ת��ǰ�ڵ�ָ��ǰ���� next
        prev->next = then;        // ����ǰ���� next Ϊ��ǰ�ڵ�
        then = start->next;       // �ƶ�����һ��Ҫ��ת�Ľڵ�
    }

    return dummy.next; // �����µ�ͷ�ڵ�
}

// ��ӡ����
void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d", head->val); // ��ӡ��ǰ�ڵ�ֵ
        head = head->next;
        if (head != NULL) {
            printf(" "); // �ڵ�֮���ÿո�ָ�
        }
    }
}

// ������
int main() {
    ListNode* list = readList(); // ��ȡ��������
    int a, b;
    scanf("%d %d", &a, &b); // ����Ҫ��ת������ [a, b]

    ListNode* head = reverseList(list, a, b); // ��ת����ָ������
    printList(head); // ����������

    return 0;
}

