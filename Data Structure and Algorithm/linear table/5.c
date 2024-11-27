#include <stdio.h>
#include <stdlib.h>

// ��������ڵ�ṹ��
typedef struct ListNode {
    int value;                 // �ڵ��ֵ
    struct ListNode *next;     // ָ����һ���ڵ��ָ��
} ListNode;

// �����½ڵ�ĺ���
ListNode* createNode(int nodeValue) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // �����ڴ�
    newNode->value = nodeValue;   // ��ʼ���ڵ��ֵ
    newNode->next = NULL;         // ��ʼ����һ�ڵ�Ϊ��
    return newNode;
}

// ���û������ȡ����ĺ���
ListNode* readList() {
    int inputValue;
    ListNode *head = NULL, *current = NULL;

    // ѭ����ȡ�û����룬-1 ��ʾ�������
    while (scanf("%d", &inputValue) && inputValue != -1) {
        ListNode* newNode = createNode(inputValue); // �����½ڵ�
        if (head == NULL) {
            head = newNode;       // �������Ϊ�գ���ʼ��ͷ�ڵ�
            current = head;       // ���õ�ǰָ��Ϊͷ�ڵ�
        } else {
            current->next = newNode; // ���½ڵ�׷�ӵ�����ĩβ
            current = newNode;       // ���µ�ǰָ��
        }
    }

    return head; // ���������ͷ�ڵ�
}

// ��ӡ����ڵ�ֵ�ĺ���
void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->value); // ��ӡ�ڵ�ֵ
        head = head->next;          // �ƶ�����һ���ڵ�
    }
    printf("\n"); // �����������
}

// �ϲ���������ĺ���
void mergeLists(ListNode** head, int start, int end, ListNode* list2) {
    ListNode *current = *head, *previous = NULL;
    int index = 0;

    // �ҵ���Χ [start, end] ����ʼλ�õ�ǰһ���ڵ�
    while (current != NULL && index < start) {
        previous = current;
        current = current->next;
        index++;
    }

    // ɾ�������� [start, end] �Ľڵ�
    ListNode *lastDeleted = NULL;
    while (current != NULL && index <= end) {
        ListNode *toDelete = current; // ��ǰ�ڵ���Ҫɾ��
        current = current->next;      // �ƶ�����һ���ڵ�
        free(toDelete);               // �ͷŵ�ǰ�ڵ��ڴ�
        index++;
        lastDeleted = toDelete;       // ��¼���һ����ɾ���Ľڵ�
    }

    // �� list2 ���뵽ɾ���ڵ���λ��
    if (previous != NULL) {
        previous->next = list2;       // ���ӵ� list1 ��ǰ�벿��
    } else {
        *head = list2;                // ���ɾ����Χ����ͷ�ڵ㣬����ͷ�ڵ�
    }

    // �ҵ� list2 ��ĩβ�ڵ�
    if (list2 != NULL) {
        ListNode *lastNode = list2;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        // �� list2 ��ĩβ��ԭ����ʣ�ಿ������
        lastNode->next = current;
    }
}

int main() {
    // ��ȡ���� list1
    ListNode *list1 = readList();

    // ��ȡɾ����Χ����ʼ�ͽ���λ��
    int start, end;
    scanf("%d %d", &start, &end);

    // ��ȡ���� list2
    ListNode *list2 = readList();

    // �ϲ� list1 �� list2
    mergeLists(&list1, start, end, list2);

    // ��ӡ�ϲ��������
    printList(list1);

    // ע�⣺�˴���δ�ͷ�����������ڴ棬�������ʵ����������ڴ��ͷ��߼�

    return 0;
}

