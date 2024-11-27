#include<stdio.h>
#include<stdlib.h>

// 定义链表节点结构体
typedef struct ListNode {
    int value;                 // 节点的值
    struct ListNode *next;     // 指向下一个节点的指针
} ListNode;

// 创建新节点的函数
ListNode* createNode(int nodeValue) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // 分配内存
    newNode->value = nodeValue;   // 设置节点的值
    newNode->next = NULL;         // 初始化下一节点为空
    return newNode;
}

// 从用户输入读取链表的函数
ListNode* readList() {
    int inputValue;
    ListNode *head = NULL, *current = NULL;

    // 读取用户输入，-1 表示输入结束
    while (scanf("%d", &inputValue) && inputValue != -1) {
        ListNode* newNode = createNode(inputValue); // 创建新节点
        if (!head) {
            head = newNode;       // 如果链表为空，初始化头节点
            current = head;       // 设置当前指针为头节点
        } else {
            current->next = newNode; // 将新节点追加到链表末尾
            current = newNode;       // 更新当前指针
        }
    }

    return head; // 返回链表的头节点
}

// 反向输出链表节点值的函数
void reversePrint(ListNode *head, int *array, int *size) {
    ListNode *current = head;

    // 遍历链表，将节点值存入数组
    while (current != NULL) {
        array[(*size)++] = current->value; // 保存当前节点值到数组并更新数组大小
        current = current->next;          // 移动到下一个节点
    }

    // 从数组尾部开始打印，实现反向输出
    for (int i = *size - 1; i >= 0; i--) {
        printf("%d ", array[i]);
    }
    printf("\n"); // 输出结束后换行
}

int main() {
    // 从用户输入读取链表
    ListNode *head = readList();

    // 定义存储链表值的数组和数组大小
    int array[10000]; // 假设链表长度不会超过10000
    int size = 0;

    // 反向打印链表
    reversePrint(head, array, &size);

    // 释放链表内存
    while (head != NULL) {
        ListNode *temp = head;  // 保存当前节点
        head = head->next;      // 移动到下一个节点
        free(temp);             // 释放当前节点内存
    }

    return 0;
}

