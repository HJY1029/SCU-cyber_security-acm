#include<stdio.h>
#include<stdlib.h>

// 定义链表节点的结构体
typedef struct ListNode {
    int value;                 // 节点值
    struct ListNode* next;     // 指向下一个节点的指针
} ListNode;

// 创建新节点的函数
ListNode* createNode(int nodeValue) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // 分配新节点的内存
    newNode->value = nodeValue;     // 初始化节点的值
    newNode->next = NULL;           // 初始化下一节点指针为空
    return newNode;
}

// 合并两个有序链表的函数
ListNode* mergeList(ListNode* list1, ListNode* list2) {
    ListNode dummyNode;             // 创建一个哑节点（虚拟头节点）
    dummyNode.next = NULL;
    ListNode* tail = &dummyNode;    // 指针指向合并后的链表尾部

    // 迭代合并两个链表
    while (list1 != NULL && list2 != NULL) {
        if (list1->value < list2->value) {
            tail->next = list1;     // 将较小节点加入合并链表
            list1 = list1->next;    // 移动到下一个节点
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;          // 更新尾节点指针
    }

    // 如果某一链表未合并完，直接接到合并链表末尾
    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    return dummyNode.next;          // 返回哑节点的下一个节点（合并链表的头节点）
}

// 打印链表的函数
void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->value); // 输出节点值
        head = head->next;          // 移动到下一个节点
    }
    printf("\n");                   // 换行
}

// 释放链表的内存
void freeList(ListNode* head) {
    ListNode* temp;
    while (head != NULL) {
        temp = head;                // 保存当前节点
        head = head->next;          // 移动到下一个节点
        free(temp);                 // 释放当前节点内存
    }
}

int main() {
    int inputValue1, inputValue2; // 用于存储用户输入的值

    ListNode* list1 = NULL;       // 第一个链表的头指针
    ListNode* list1Tail = NULL;   // 第一个链表的尾指针

    ListNode* list2 = NULL;       // 第二个链表的头指针
    ListNode* list2Tail = NULL;   // 第二个链表的尾指针

    // 读取第一个链表的值，输入 -1 结束
    scanf("%d", &inputValue1);
    while (inputValue1 != -1) {
        if (list1 == NULL) {       // 如果链表为空，初始化头节点
            list1 = createNode(inputValue1);
            list1Tail = list1;
        } else {                   // 否则追加到链表末尾
            list1Tail->next = createNode(inputValue1);
            list1Tail = list1Tail->next;
        }
        scanf("%d", &inputValue1);
    }

    // 读取第二个链表的值，输入 -1 结束
    scanf("%d", &inputValue2);
    while (inputValue2 != -1) {
        if (list2 == NULL) {       // 如果链表为空，初始化头节点
            list2 = createNode(inputValue2);
            list2Tail = list2;
        } else {                   // 否则追加到链表末尾
            list2Tail->next = createNode(inputValue2);
            list2Tail = list2Tail->next;
        }
        scanf("%d", &inputValue2);
    }

    // 合并两个链表
    ListNode* mergedList = mergeList(list1, list2);

    // 打印合并后的链表
    printList(mergedList);

    // 释放合并链表的内存
    freeList(mergedList);

    return 0;
}

