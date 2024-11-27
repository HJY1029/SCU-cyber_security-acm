#include <stdio.h> 
#include <stdlib.h>

// ��������ڵ�Ľṹ��
typedef struct ListNode {
    int val;              // �ڵ�洢��ֵ
    struct ListNode *next; // ָ����һ���ڵ��ָ��
} ListNode;

// �����½ڵ�ĺ���
ListNode* createNode(int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // �����ڴ�
    newNode->val = value;    // ��ʼ���ڵ�ֵ
    newNode->next = NULL;    // ������һ���ڵ�Ϊ��
    return newNode;
}

// ���û����빹������ĺ���
ListNode* readList() {
    int inputValue;
    ListNode *head = NULL, *current = NULL;

    // ѭ����ȡ���룬������ֵΪ -1 ʱ����
    while (scanf("%d", &inputValue) && inputValue != -1) {
        ListNode* newNode = createNode(inputValue); // �����½ڵ�
        if (!head) {
            head = newNode;    // ��ʼ�������ͷ�ڵ�
            current = head;    // ���õ�ǰ�ڵ�Ϊͷ�ڵ�
        } else {
            current->next = newNode; // ���½ڵ�׷�ӵ�����ĩβ
            current = newNode;       // ���µ�ǰָ��
        }
    }

    return head; // ��������ͷ�ڵ�
}

// ��������Ķ�����ֵ��ת��Ϊʮ����
int binaryToDecimal(ListNode* head) {
    int decimalValue = 0; // ���ڴ洢ʮ���ƽ��
    int length = 0;       // ������
    ListNode* current = head;

    // ����������
    while (current != NULL) {
        length++;
        current = current->next;
    }

    current = head;       // ����ָ�뵽����ͷ��
    int weight = length - 1; // Ȩ�أ����λΪ�����ȼ�1

    // ������������ʮ����ֵ
    while (current != NULL) {
        decimalValue += current->val * (1 << weight); // ʹ��λ������� 2^weight
        current = current->next; // �ƶ�����һ���ڵ�
        weight--; // Ȩ�صݼ�
    }

    return decimalValue;
}

int main() {
    ListNode* list = readList(); // ��ȡ����
    int decimalValue = binaryToDecimal(list); // ����ʮ����ֵ
    printf("%d", decimalValue); // ������
    return 0;
}

