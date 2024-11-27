#include<stdio.h>
#include<stdlib.h>

// 定义链表节点结构体
typedef struct ListNode {
    int val;  // 节点值
    struct ListNode* next;  // 指向下一个节点的指针
} ListNode; 

// 创建新节点并返回指向该节点的指针
ListNode* createNode(int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));  // 分配内存
    newNode->val = value;  // 设置节点值
    newNode->next = NULL;  // 新节点的next指针初始化为NULL
    return newNode;  // 返回新节点的指针
}

// 读取链表并返回头节点指针
ListNode* readList() {
    ListNode* head = NULL, *current = NULL, *newNode;
    int value;
    // 持续读取输入直到遇到-1
    while(scanf("%d", &value) && value != -1) {
        newNode = createNode(value);  // 创建新节点
        if (!head) {
            head = newNode;  // 如果是第一个节点，设置头节点
            current = head;  // 设置current指针指向头节点
        } else {
            current->next = newNode;  // 将当前节点的next指向新节点
            current = newNode;  // 更新current指针
        }
    }
    return head;  // 返回链表头节点的指针
}

// 找到链表的中间节点
ListNode* findMiddle(ListNode *head) {
    ListNode *slow = head;  // 慢指针，步长为1
    ListNode *fast = head;  // 快指针，步长为2
    // 快指针和慢指针同时移动，直到快指针到达链表末尾
    while (fast && fast->next) {
        slow = slow->next;  // 慢指针走一步
        fast = fast->next->next;  // 快指针走两步
    }
    return slow;  // 返回中间节点
}

// 反转链表并返回新的头节点
ListNode* reverseList(ListNode *head) {
    ListNode *prev = NULL;  // 上一个节点初始化为NULL
    while (head) {
        ListNode *next = head->next;  // 保存当前节点的下一个节点
        head->next = prev;  // 反转当前节点的next指针
        prev = head;  // 更新prev为当前节点
        head = next;  // 更新head为下一个节点
    }
    return prev;  // 返回反转后的链表头节点
}

// 重新排列链表，使得节点按要求的顺序排列
void reorderList(ListNode *head) {
    if (!head || !head->next) return;  // 如果链表为空或只有一个节点，直接返回

    // 1. 找到链表的中间节点
    ListNode *middle = findMiddle(head);
    ListNode *secondHalf = middle->next;  // 第二部分链表
    middle->next = NULL;  // 断开链表，分割成两部分

    // 2. 反转后半部分链表
    secondHalf = reverseList(secondHalf);

    // 3. 交替连接前后两部分
    ListNode *firstHalf = head;
    ListNode *temp1, *temp2;
    while (secondHalf) {
        temp1 = firstHalf->next;  // 保存前半部分的下一个节点
        temp2 = secondHalf->next;  // 保存后半部分的下一个节点

        firstHalf->next = secondHalf;  // 将前半部分的当前节点与后半部分的当前节点连接
        secondHalf->next = temp1;     // 将后半部分的当前节点与前半部分的下一个节点连接
        firstHalf = temp1;  // 移动到下一个前半部分的节点
        secondHalf = temp2; // 移动到下一个后半部分的节点
    }
}

// 打印链表
void printList(ListNode *head) {
    ListNode *current = head;
    while (current) {
        printf("%d ", current->val);  // 打印当前节点的值
        current = current->next;  // 移动到下一个节点
    }
}

int main() {
    ListNode* list;
    list = readList();  // 读取链表
    reorderList(list);  // 对链表进行重新排序
    printList(list);    // 打印重新排序后的链表
    return 0;
}

