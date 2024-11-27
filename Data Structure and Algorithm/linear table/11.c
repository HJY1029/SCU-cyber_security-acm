#include<stdio.h>
#include<stdlib.h>

// ��������ڵ�ṹ��
typedef struct ListNode {
    int val;  // �ڵ�ֵ
    struct ListNode* next;  // ָ����һ���ڵ��ָ��
} ListNode; 

// �����½ڵ㲢����ָ��ýڵ��ָ��
ListNode* createNode(int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));  // �����ڴ�
    newNode->val = value;  // ���ýڵ�ֵ
    newNode->next = NULL;  // �½ڵ��nextָ���ʼ��ΪNULL
    return newNode;  // �����½ڵ��ָ��
}

// ��ȡ��������ͷ�ڵ�ָ��
ListNode* readList() {
    ListNode* head = NULL, *current = NULL, *newNode;
    int value;
    // ������ȡ����ֱ������-1
    while(scanf("%d", &value) && value != -1) {
        newNode = createNode(value);  // �����½ڵ�
        if (!head) {
            head = newNode;  // ����ǵ�һ���ڵ㣬����ͷ�ڵ�
            current = head;  // ����currentָ��ָ��ͷ�ڵ�
        } else {
            current->next = newNode;  // ����ǰ�ڵ��nextָ���½ڵ�
            current = newNode;  // ����currentָ��
        }
    }
    return head;  // ��������ͷ�ڵ��ָ��
}

// �ҵ�������м�ڵ�
ListNode* findMiddle(ListNode *head) {
    ListNode *slow = head;  // ��ָ�룬����Ϊ1
    ListNode *fast = head;  // ��ָ�룬����Ϊ2
    // ��ָ�����ָ��ͬʱ�ƶ���ֱ����ָ�뵽������ĩβ
    while (fast && fast->next) {
        slow = slow->next;  // ��ָ����һ��
        fast = fast->next->next;  // ��ָ��������
    }
    return slow;  // �����м�ڵ�
}

// ��ת���������µ�ͷ�ڵ�
ListNode* reverseList(ListNode *head) {
    ListNode *prev = NULL;  // ��һ���ڵ��ʼ��ΪNULL
    while (head) {
        ListNode *next = head->next;  // ���浱ǰ�ڵ����һ���ڵ�
        head->next = prev;  // ��ת��ǰ�ڵ��nextָ��
        prev = head;  // ����prevΪ��ǰ�ڵ�
        head = next;  // ����headΪ��һ���ڵ�
    }
    return prev;  // ���ط�ת�������ͷ�ڵ�
}

// ������������ʹ�ýڵ㰴Ҫ���˳������
void reorderList(ListNode *head) {
    if (!head || !head->next) return;  // �������Ϊ�ջ�ֻ��һ���ڵ㣬ֱ�ӷ���

    // 1. �ҵ�������м�ڵ�
    ListNode *middle = findMiddle(head);
    ListNode *secondHalf = middle->next;  // �ڶ���������
    middle->next = NULL;  // �Ͽ������ָ��������

    // 2. ��ת��벿������
    secondHalf = reverseList(secondHalf);

    // 3. ��������ǰ��������
    ListNode *firstHalf = head;
    ListNode *temp1, *temp2;
    while (secondHalf) {
        temp1 = firstHalf->next;  // ����ǰ�벿�ֵ���һ���ڵ�
        temp2 = secondHalf->next;  // �����벿�ֵ���һ���ڵ�

        firstHalf->next = secondHalf;  // ��ǰ�벿�ֵĵ�ǰ�ڵ����벿�ֵĵ�ǰ�ڵ�����
        secondHalf->next = temp1;     // ����벿�ֵĵ�ǰ�ڵ���ǰ�벿�ֵ���һ���ڵ�����
        firstHalf = temp1;  // �ƶ�����һ��ǰ�벿�ֵĽڵ�
        secondHalf = temp2; // �ƶ�����һ����벿�ֵĽڵ�
    }
}

// ��ӡ����
void printList(ListNode *head) {
    ListNode *current = head;
    while (current) {
        printf("%d ", current->val);  // ��ӡ��ǰ�ڵ��ֵ
        current = current->next;  // �ƶ�����һ���ڵ�
    }
}

int main() {
    ListNode* list;
    list = readList();  // ��ȡ����
    reorderList(list);  // �����������������
    printList(list);    // ��ӡ��������������
    return 0;
}

