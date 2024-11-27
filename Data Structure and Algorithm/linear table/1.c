#include<stdio.h>
#include<stdlib.h>

// ��������ڵ�Ľṹ��
typedef struct ListNode {
    int value;                 // �ڵ�ֵ
    struct ListNode* next;     // ָ����һ���ڵ��ָ��
} ListNode;

// �����½ڵ�ĺ���
ListNode* createNode(int nodeValue) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // �����½ڵ���ڴ�
    newNode->value = nodeValue;     // ��ʼ���ڵ��ֵ
    newNode->next = NULL;           // ��ʼ����һ�ڵ�ָ��Ϊ��
    return newNode;
}

// �ϲ�������������ĺ���
ListNode* mergeList(ListNode* list1, ListNode* list2) {
    ListNode dummyNode;             // ����һ���ƽڵ㣨����ͷ�ڵ㣩
    dummyNode.next = NULL;
    ListNode* tail = &dummyNode;    // ָ��ָ��ϲ��������β��

    // �����ϲ���������
    while (list1 != NULL && list2 != NULL) {
        if (list1->value < list2->value) {
            tail->next = list1;     // ����С�ڵ����ϲ�����
            list1 = list1->next;    // �ƶ�����һ���ڵ�
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;          // ����β�ڵ�ָ��
    }

    // ���ĳһ����δ�ϲ��ֱ꣬�ӽӵ��ϲ�����ĩβ
    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    return dummyNode.next;          // �����ƽڵ����һ���ڵ㣨�ϲ������ͷ�ڵ㣩
}

// ��ӡ����ĺ���
void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->value); // ����ڵ�ֵ
        head = head->next;          // �ƶ�����һ���ڵ�
    }
    printf("\n");                   // ����
}

// �ͷ�������ڴ�
void freeList(ListNode* head) {
    ListNode* temp;
    while (head != NULL) {
        temp = head;                // ���浱ǰ�ڵ�
        head = head->next;          // �ƶ�����һ���ڵ�
        free(temp);                 // �ͷŵ�ǰ�ڵ��ڴ�
    }
}

int main() {
    int inputValue1, inputValue2; // ���ڴ洢�û������ֵ

    ListNode* list1 = NULL;       // ��һ�������ͷָ��
    ListNode* list1Tail = NULL;   // ��һ�������βָ��

    ListNode* list2 = NULL;       // �ڶ��������ͷָ��
    ListNode* list2Tail = NULL;   // �ڶ��������βָ��

    // ��ȡ��һ�������ֵ������ -1 ����
    scanf("%d", &inputValue1);
    while (inputValue1 != -1) {
        if (list1 == NULL) {       // �������Ϊ�գ���ʼ��ͷ�ڵ�
            list1 = createNode(inputValue1);
            list1Tail = list1;
        } else {                   // ����׷�ӵ�����ĩβ
            list1Tail->next = createNode(inputValue1);
            list1Tail = list1Tail->next;
        }
        scanf("%d", &inputValue1);
    }

    // ��ȡ�ڶ��������ֵ������ -1 ����
    scanf("%d", &inputValue2);
    while (inputValue2 != -1) {
        if (list2 == NULL) {       // �������Ϊ�գ���ʼ��ͷ�ڵ�
            list2 = createNode(inputValue2);
            list2Tail = list2;
        } else {                   // ����׷�ӵ�����ĩβ
            list2Tail->next = createNode(inputValue2);
            list2Tail = list2Tail->next;
        }
        scanf("%d", &inputValue2);
    }

    // �ϲ���������
    ListNode* mergedList = mergeList(list1, list2);

    // ��ӡ�ϲ��������
    printList(mergedList);

    // �ͷźϲ�������ڴ�
    freeList(mergedList);

    return 0;
}

