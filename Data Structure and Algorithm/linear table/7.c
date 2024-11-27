#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct ListNode {
    int val;               // 节点存储的值
    struct ListNode* next; // 指向下一个节点的指针
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
            head = newNode;    // 初始化链表的头节点
            current = head;    // 设置当前指针为头节点
        } else {
            current->next = newNode; // 将新节点追加到链表末尾
            current = newNode;       // 更新当前指针
        }
    }
    return head; // 返回链表头节点
}

// 反转链表
ListNode* reverseList(ListNode* head) {
    ListNode *prev = NULL, *current = head;

    // 遍历链表并反转指针方向
    while (current) {
        ListNode* nextNode = current->next; // 暂存下一个节点
        current->next = prev;              // 当前节点的 next 指向前一个节点
        prev = current;                    // 更新 prev 为当前节点
        current = nextNode;                // 移动到下一个节点
    }
    return prev; // 返回新的头节点
}

// 两数相加并返回结果链表
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int num1 = 0, num2 = 0;

    // 将链表 l1 表示的数转换为整数
    while (l1) {
        num1 = num1 * 10 + l1->val; // 按位累加构造数字
        l1 = l1->next;
    }

    // 将链表 l2 表示的数转换为整数
    while (l2) {
        num2 = num2 * 10 + l2->val;
        l2 = l2->next;
    }

    int total = num1 + num2; // 计算两个数的和
    ListNode *head = NULL, *current = NULL;

    // 如果总和为 0，直接返回一个节点值为 0 的链表
    if (total == 0) {
        return createNode(0);
    }

    // 将总和拆分为链表
    while (total > 0) {
        ListNode* newNode = createNode(total % 10); // 取余生成节点值
        total /= 10;                                // 去掉最低位

        if (!head) {
            head = newNode;    // 初始化链表头节点
            current = head;    // 设置当前指针
        } else {
            current->next = newNode; // 将新节点追加到链表末尾
            current = newNode;       // 更新当前指针
        }
    }

    return reverseList(head); // 结果链表需要反转回正确顺序
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

int main() {
    ListNode* l1 = readList(); // 读取第一个链表
    ListNode* l2 = readList(); // 读取第二个链表

    ListNode* result = addTwoNumbers(l1, l2); // 计算两数之和
    printList(result); // 输出结果链表

    return 0;
}

