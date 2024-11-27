#include <stdio.h>
#include <stdlib.h>

// ��������ڵ�ṹ��
typedef struct ListNode {
    int val;               // �ڵ�洢��ֵ
    struct ListNode* next; // ָ����һ���ڵ��ָ��
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
            head = newNode;    // ��ʼ�������ͷ�ڵ�
            current = head;    // ���õ�ǰָ��Ϊͷ�ڵ�
        } else {
            current->next = newNode; // ���½ڵ�׷�ӵ�����ĩβ
            current = newNode;       // ���µ�ǰָ��
        }
    }
    return head; // ��������ͷ�ڵ�
}

// ��ת����
ListNode* reverseList(ListNode* head) {
    ListNode *prev = NULL, *current = head;

    // ����������תָ�뷽��
    while (current) {
        ListNode* nextNode = current->next; // �ݴ���һ���ڵ�
        current->next = prev;              // ��ǰ�ڵ�� next ָ��ǰһ���ڵ�
        prev = current;                    // ���� prev Ϊ��ǰ�ڵ�
        current = nextNode;                // �ƶ�����һ���ڵ�
    }
    return prev; // �����µ�ͷ�ڵ�
}

// ������Ӳ����ؽ������
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int num1 = 0, num2 = 0;

    // ������ l1 ��ʾ����ת��Ϊ����
    while (l1) {
        num1 = num1 * 10 + l1->val; // ��λ�ۼӹ�������
        l1 = l1->next;
    }

    // ������ l2 ��ʾ����ת��Ϊ����
    while (l2) {
        num2 = num2 * 10 + l2->val;
        l2 = l2->next;
    }

    int total = num1 + num2; // �����������ĺ�
    ListNode *head = NULL, *current = NULL;

    // ����ܺ�Ϊ 0��ֱ�ӷ���һ���ڵ�ֵΪ 0 ������
    if (total == 0) {
        return createNode(0);
    }

    // ���ܺͲ��Ϊ����
    while (total > 0) {
        ListNode* newNode = createNode(total % 10); // ȡ�����ɽڵ�ֵ
        total /= 10;                                // ȥ�����λ

        if (!head) {
            head = newNode;    // ��ʼ������ͷ�ڵ�
            current = head;    // ���õ�ǰָ��
        } else {
            current->next = newNode; // ���½ڵ�׷�ӵ�����ĩβ
            current = newNode;       // ���µ�ǰָ��
        }
    }

    return reverseList(head); // ���������Ҫ��ת����ȷ˳��
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

int main() {
    ListNode* l1 = readList(); // ��ȡ��һ������
    ListNode* l2 = readList(); // ��ȡ�ڶ�������

    ListNode* result = addTwoNumbers(l1, l2); // ��������֮��
    printList(result); // ����������

    return 0;
}

