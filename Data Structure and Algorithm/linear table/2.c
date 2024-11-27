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

// 删除链表中重复元素的函数
ListNode* deleteNode(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head; // 链表为空或只有一个节点时直接返回
    }
    ListNode* current = head; // 当前遍历的节点指针
    while (current->next != NULL) {
        if (current->value == current->next->value) {
            // 如果当前节点和下一个节点的值相同，跳过下一个节点
            current->next = current->next->next;
        } else {
            // 否则移动到下一个节点
            current = current->next;
        }
    }
    return head; // 返回去重后的链表头节点
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
    int inputValue;                 // 存储用户输入的值
    ListNode *head = NULL;          // 链表头指针
    ListNode *current = NULL;       // 当前链表尾部指针

    // 循环读取用户输入，-1 表示输入结束
    while (scanf("%d", &inputValue) && inputValue != -1) {
        ListNode* newNode = createNode(inputValue); // 创建新节点
        if (head == NULL) {
            head = newNode;         // 如果链表为空，初始化头节点
            current = head;
        } else {
            current->next = newNode; // 将新节点追加到链表末尾
            current = newNode;
        }
    }

    return head; // 返回链表的头节点
}

int main() {
    // 从用户输入读取链表
    ListNode* head = readList();

    // 删除链表中重复的节点
    head = deleteNode(head);

    // 打印处理后的链表
    printList(head);

    // 释放链表内存
    ListNode* current = head;
    while (current != NULL) {
        ListNode* nextNode = current->next; // 保存下一节点指针
        free(current);                      // 释放当前节点内存
        current = nextNode;                 // 移动到下一节点
    }

    return 0;
}

