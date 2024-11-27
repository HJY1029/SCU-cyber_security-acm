#include <stdio.h> 
#include <stdlib.h>

// 定义链表节点的结构体
typedef struct ListNode {
    int val;              // 节点存储的值
    struct ListNode *next; // 指向下一个节点的指针
} ListNode;

// 创建新节点的函数
ListNode* createNode(int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); // 分配内存
    newNode->val = value;    // 初始化节点值
    newNode->next = NULL;    // 设置下一个节点为空
    return newNode;
}

// 从用户输入构造链表的函数
ListNode* readList() {
    int inputValue;
    ListNode *head = NULL, *current = NULL;

    // 循环读取输入，当输入值为 -1 时结束
    while (scanf("%d", &inputValue) && inputValue != -1) {
        ListNode* newNode = createNode(inputValue); // 创建新节点
        if (!head) {
            head = newNode;    // 初始化链表的头节点
            current = head;    // 设置当前节点为头节点
        } else {
            current->next = newNode; // 将新节点追加到链表末尾
            current = newNode;       // 更新当前指针
        }
    }

    return head; // 返回链表头节点
}

// 计算链表的二进制值并转换为十进制
int binaryToDecimal(ListNode* head) {
    int decimalValue = 0; // 用于存储十进制结果
    int length = 0;       // 链表长度
    ListNode* current = head;

    // 计算链表长度
    while (current != NULL) {
        length++;
        current = current->next;
    }

    current = head;       // 重置指针到链表头部
    int weight = length - 1; // 权重：最高位为链表长度减1

    // 遍历链表并计算十进制值
    while (current != NULL) {
        decimalValue += current->val * (1 << weight); // 使用位运算计算 2^weight
        current = current->next; // 移动到下一个节点
        weight--; // 权重递减
    }

    return decimalValue;
}

int main() {
    ListNode* list = readList(); // 读取链表
    int decimalValue = binaryToDecimal(list); // 计算十进制值
    printf("%d", decimalValue); // 输出结果
    return 0;
}

