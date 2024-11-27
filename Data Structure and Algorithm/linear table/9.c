#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

// 创建新节点
ListNode* createNode(int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// 从输入读取链表
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

// 计算最大孪生和
int maxTwinSum(ListNode* head) {
    if (head == NULL) return 0;

    // 计算链表长度并存储节点值
    int n = 0;
    ListNode* current = head;
    while (current != NULL) {
        n++;
        current = current->next;
    }

    // 动态分配数组存储链表值
    int *values = (int*)malloc(n * sizeof(int));
    current = head;
    for (int i = 0; i < n; i++) {
        values[i] = current->val;
        current = current->next;
    }

    // 计算孪生和的最大值
    int maxSum = 0;
    for (int i = 0; i < n / 2; i++) {
        int twinSum = values[i] + values[n - i - 1];
        if (twinSum > maxSum) {
            maxSum = twinSum;
        }
    }

    free(values); // 释放数组内存
    return maxSum;
}

// 释放链表内存
void freeList(ListNode* head) {
    while (head != NULL) {
        ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // 读取链表
    ListNode* head = readList();

    // 计算最大孪生和
    int result = maxTwinSum(head);
    printf("%d\n", result);

    // 释放链表内存
    freeList(head);

    return 0;
}

