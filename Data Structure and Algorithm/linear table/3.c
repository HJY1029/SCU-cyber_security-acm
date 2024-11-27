#include<stdio.h>
#include<stdlib.h>

// 定义链表节点的结构体
typedef struct ListNode {
    int value;                 // 节点值
    struct ListNode* next;     // 指向下一个节点的指针
} ListNode;

// 创建新节点的函数
ListNode* createNode(int nodeValue) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // 分配内存
    newNode->value = nodeValue;   // 初始化节点的值
    newNode->next = NULL;         // 初始化下一节点指针为空
    return newNode;
}

// 删除链表中指定值节点的函数
ListNode* deleteNode(ListNode* head, int targetValue) {
    // 创建一个虚拟头节点，方便处理头节点的删除
    ListNode* dummyHead = createNode(0);
    dummyHead->next = head;       // 虚拟头节点指向实际链表头
    ListNode* current = dummyHead;

    // 遍历链表
    while (current->next != NULL) {
        if (current->next->value == targetValue) {
            // 如果下一个节点的值为目标值，跳过该节点
            current->next = current->next->next;
        } else {
            // 否则移动到下一个节点
            current = current->next;
        }
    }

    // 获取新链表的头节点并释放虚拟头节点内存
    ListNode* newHead = dummyHead->next;
    free(dummyHead);
    return newHead;
}

// 打印链表的函数
void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->value); // 打印节点的值
        head = head->next;          // 移动到下一个节点
    }
    printf("\n");                   // 换行
}

// 从用户输入读取链表的函数
ListNode* readList() {
    int inputValue;
    ListNode *head = NULL, *tail = NULL;

    // 循环读取用户输入，-1 表示输入结束
    scanf("%d", &inputValue);
    while (inputValue != -1) {
        ListNode* newNode = createNode(inputValue); // 创建新节点
        if (head == NULL) {
            head = newNode;       // 如果链表为空，初始化头节点
            tail = newNode;       // 同时更新尾节点
        } else {
            tail->next = newNode; // 将新节点追加到链表末尾
            tail = newNode;       // 更新尾节点
        }
        scanf("%d", &inputValue);
    }

    return head; // 返回链表的头节点
}

int main() {
    // 从用户输入读取链表
    ListNode* head = readList();

    // 读取要删除的值
    int targetValue;
    scanf("%d", &targetValue);

    // 删除链表中所有等于目标值的节点
    ListNode* newHead = deleteNode(head, targetValue);

    // 打印处理后的链表
    printList(newHead);

    // 释放链表内存
    ListNode* current = newHead;
    while (current != NULL) {
        ListNode* temp = current;  // 保存当前节点
        current = current->next;  // 移动到下一个节点
        free(temp);               // 释放当前节点内存
    }

    return 0;
}

