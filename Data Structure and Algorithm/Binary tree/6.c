#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义二叉树节点结构体
struct Node {
    int val;               // 节点的值！！！
    struct Node* left;     // 左子节点指针
    struct Node* right;    // 右子节点指针
    struct Node* next;     // 指向同一层下一个节点的指针
};

// 创建一个新的节点，并初始化其各项属性
struct Node* createNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); // 动态分配内存
    node->val = val;  // 设置节点值
    node->left = NULL; // 左子节点为空
    node->right = NULL; // 右子节点为空
    node->next = NULL;  // 同层的下一个节点为空
    return node;
}

// 层次遍历二叉树，并填充每个节点的 next 指针
struct Node* connect(struct Node* root) {
    if (root == NULL) { // 如果树为空，直接返回
        return root;
    }

    struct Node* queue[5000];  // 使用队列进行层次遍历
    int left = 0, right = 0;   // 队列的左右指针
    queue[right++] = root;     // 将根节点入队列

    while (left < right) {
        int level_size = right - left;  // 当前层的节点个数

        for (int i = 0; i < level_size; i++) {
            struct Node* node = queue[left++];  // 出队当前节点

            // 设置当前节点的 next 指针
            if (i < level_size - 1) {
                node->next = queue[left];  // 指向同层下一个节点
            }

            // 将当前节点的左右子节点入队列
            if (node->left != NULL) {
                queue[right++] = node->left;
            }
            if (node->right != NULL) {
                queue[right++] = node->right;
            }
        }
    }

    return root; // 返回修改后的根节点
}

// 将输入的字符串解析为整数数组，返回数组的大小
int parse_input_to_array(char* input_string, int* numbers) {
    int count = 0;  // 数组元素计数
    char* token = strtok(input_string, ",");  // 按逗号分割输入字符串
    while (token != NULL) {
        numbers[count++] = atoi(token);  // 将字符串转换为整数并存入数组
        token = strtok(NULL, ",");  // 获取下一个子串
    }

    return count;  // 返回解析出的元素数量
}

// 根据整数数组构建二叉树
struct Node* buildTree(int* nums, int size) {
    if (size == 0) {
        return NULL;  // 如果数组为空，返回空树
    }

    struct Node* root = createNode(nums[0]);  // 创建根节点
    struct Node* queue[5000];  // 使用队列辅助构建树
    int front = 0, rear = 0;   // 队列的前后指针
    queue[rear++] = root;  // 根节点入队列

    int i = 1;  // 数组索引
    while (i < size) {
        struct Node* node = queue[front++];  // 出队一个节点
        if (i < size) {
            node->left = createNode(nums[i++]);  // 创建左子节点
            queue[rear++] = node->left;  // 左子节点入队
        }
        if (i < size) {
            node->right = createNode(nums[i++]);  // 创建右子节点
            queue[rear++] = node->right;  // 右子节点入队
        }
    }

    return root;  // 返回构建好的树的根节点
}

// 打印树的层次遍历结果，并输出每个节点的 next 指针
void printTree(struct Node* root) {
    if (!root) {  // 如果树为空，打印空数组并返回
        printf("[]");
        return;
    }

    struct Node* queue[10000];  // 使用队列进行层次遍历
    int front = 0, rear = 0;
    queue[rear++] = root;  // 将根节点入队列

    while (front < rear) {
        struct Node* node = queue[front++];  // 出队当前节点
        if (node) {
            queue[rear++] = node->left;  // 左子节点入队
            queue[rear++] = node->right; // 右子节点入队
        }
    }

    int last_non_null_index = rear - 1;  // 最后一个非空节点的索引
    int trailing_null_count = 0;  // 统计尾部连续的 NULL 节点数

    // 统计尾部连续的 NULL 节点
    while (queue[last_non_null_index--] == NULL) {
        trailing_null_count++;
    }

    // 输出所有节点的值
    for (int i = 0; i < rear - trailing_null_count; i++) {
        if (queue[i]->next) {  // 如果当前节点的 next 指针不为空
            printf("%d,", queue[i]->val);
        } else {
            printf("%d,#,", queue[i]->val);  // 否则输出 # 表示没有下一个节点
        }
    }

    // 最后一个节点处理
    if (queue[rear - trailing_null_count - 1]->next) {
        printf("%d", queue[rear - trailing_null_count - 1]->val);
    } else {
        printf("%d,#", queue[rear - trailing_null_count - 1]->val);
    }
}

int main() {
    char input_string[5000];  // 存储输入的字符串
    fgets(input_string, sizeof(input_string), stdin);  // 从标准输入读取一行
    int input_length = strlen(input_string);  // 获取字符串长度
    if (input_string[input_length - 1] == '\n') {
        input_string[input_length - 1] = '\0';  // 去掉末尾的换行符
    }

    int nums[5000];  // 存储解析后的数字
    int array_size = parse_input_to_array(input_string, nums);  // 解析输入字符串为数组

    struct Node* root = buildTree(nums, array_size);  // 构建二叉树
    connect(root);  // 填充每个节点的 next 指针
    printTree(root);  // 打印二叉树的层次遍历结果

    return 0;
}

