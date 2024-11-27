#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct ListNode {
    int val;                // 节点存储的值
    struct ListNode* next;  // 指向下一个节点的指针
} ListNode;

// 创建新节点的函数
ListNode* createNode(int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // 分配内存
    newNode->val = value;    // 初始化节点值
    newNode->next = NULL;    // 设置下一个节点为空
    return newNode;
}

// 从用户输入读取链表
ListNode* readList() {
    ListNode *head = NULL, *current = NULL;
    int value;

    // 循环读取输入，输入 -1 表示结束
    while (scanf("%d", &value) && value != -1) {
        ListNode* newNode = createNode(value); // 创建新节点
        if (!head) {
            head = newNode;    // 初始化链表头节点
            current = head;    // 设置当前指针为头节点
        } else {
            current->next = newNode; // 将新节点追加到链表末尾
            current = newNode;       // 更新当前指针
        }
    }
    return head; // 返回链表头节点
}

// 反转链表的指定区间 [a, b]
ListNode* reverseList(ListNode* head, int a, int b) {
    if (!head || a == b) return head; // 如果链表为空或不需要反转，直接返回原链表

    // 创建虚拟头节点，用于统一处理头节点的反转
    ListNode dummy;
    dummy.next = head;
    ListNode* prev = &dummy;

    // 找到反转部分的前一个节点
    for (int i = 1; i < a; i++) {
        prev = prev->next;
    }

    ListNode* start = prev->next; // 反转开始的节点
    ListNode* then = start->next; // 反转部分的第二个节点

    // 反转指定部分
    for (int i = 0; i < b - a; i++) {
        start->next = then->next; // 更新当前开始节点的 next 指针
        then->next = prev->next;  // 反转当前节点指向前驱的 next
        prev->next = then;        // 更新前驱的 next 为当前节点
        then = start->next;       // 移动到下一个要反转的节点
    }

    return dummy.next; // 返回新的头节点
}

// 打印链表
void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d", head->val); // 打印当前节点值
        head = head->next;
        if (head != NULL) {
            printf(" "); // 节点之间用空格分隔
        }
    }
}

// 主函数
int main() {
    ListNode* list = readList(); // 读取链表输入
    int a, b;
    scanf("%d %d", &a, &b); // 输入要反转的区间 [a, b]

    ListNode* head = reverseList(list, a, b); // 反转链表指定区间
    printList(head); // 输出结果链表

    return 0;
}

