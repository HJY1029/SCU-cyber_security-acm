#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct ListNode {
    int value;                 // 节点的值
    struct ListNode *next;     // 指向下一个节点的指针
} ListNode;

// 创建新节点的函数
ListNode* createNode(int nodeValue) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // 分配内存
    newNode->value = nodeValue;   // 初始化节点的值
    newNode->next = NULL;         // 初始化下一节点为空
    return newNode;
}

// 从用户输入读取链表的函数
ListNode* readList() {
    int inputValue;
    ListNode *head = NULL, *current = NULL;

    // 循环读取用户输入，-1 表示输入结束
    while (scanf("%d", &inputValue) && inputValue != -1) {
        ListNode* newNode = createNode(inputValue); // 创建新节点
        if (head == NULL) {
            head = newNode;       // 如果链表为空，初始化头节点
            current = head;       // 设置当前指针为头节点
        } else {
            current->next = newNode; // 将新节点追加到链表末尾
            current = newNode;       // 更新当前指针
        }
    }

    return head; // 返回链表的头节点
}

// 打印链表节点值的函数
void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->value); // 打印节点值
        head = head->next;          // 移动到下一个节点
    }
    printf("\n"); // 输出结束后换行
}

// 合并两个链表的函数
void mergeLists(ListNode** head, int start, int end, ListNode* list2) {
    ListNode *current = *head, *previous = NULL;
    int index = 0;

    // 找到范围 [start, end] 的起始位置的前一个节点
    while (current != NULL && index < start) {
        previous = current;
        current = current->next;
        index++;
    }

    // 删除从索引 [start, end] 的节点
    ListNode *lastDeleted = NULL;
    while (current != NULL && index <= end) {
        ListNode *toDelete = current; // 当前节点需要删除
        current = current->next;      // 移动到下一个节点
        free(toDelete);               // 释放当前节点内存
        index++;
        lastDeleted = toDelete;       // 记录最后一个被删除的节点
    }

    // 将 list2 插入到删除节点后的位置
    if (previous != NULL) {
        previous->next = list2;       // 连接到 list1 的前半部分
    } else {
        *head = list2;                // 如果删除范围包括头节点，更新头节点
    }

    // 找到 list2 的末尾节点
    if (list2 != NULL) {
        ListNode *lastNode = list2;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        // 将 list2 的末尾与原链表剩余部分连接
        lastNode->next = current;
    }
}

int main() {
    // 读取链表 list1
    ListNode *list1 = readList();

    // 读取删除范围的起始和结束位置
    int start, end;
    scanf("%d %d", &start, &end);

    // 读取链表 list2
    ListNode *list2 = readList();

    // 合并 list1 和 list2
    mergeLists(&list1, start, end, list2);

    // 打印合并后的链表
    printList(list1);

    // 注意：此代码未释放链表的所有内存，建议根据实际需求添加内存释放逻辑

    return 0;
}

