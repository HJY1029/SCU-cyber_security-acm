#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����������ڵ�ṹ��
struct Node {
    int val;               // �ڵ��ֵ
    struct Node* left;     // ���ӽڵ�ָ��
    struct Node* right;    // ���ӽڵ�ָ��
    struct Node* next;     // ָ��ͬһ����һ���ڵ��ָ��
};

// ����һ���µĽڵ㣬����ʼ�����������
struct Node* createNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); // ��̬�����ڴ�
    node->val = val;  // ���ýڵ�ֵ
    node->left = NULL; // ���ӽڵ�Ϊ��
    node->right = NULL; // ���ӽڵ�Ϊ��
    node->next = NULL;  // ͬ�����һ���ڵ�Ϊ��
    return node;
}

// ��α����������������ÿ���ڵ�� next ָ��
struct Node* connect(struct Node* root) {
    if (root == NULL) { // �����Ϊ�գ�ֱ�ӷ���
        return root;
    }

    struct Node* queue[5000];  // ʹ�ö��н��в�α���
    int left = 0, right = 0;   // ���е�����ָ��
    queue[right++] = root;     // �����ڵ������

    while (left < right) {
        int level_size = right - left;  // ��ǰ��Ľڵ����

        for (int i = 0; i < level_size; i++) {
            struct Node* node = queue[left++];  // ���ӵ�ǰ�ڵ�

            // ���õ�ǰ�ڵ�� next ָ��
            if (i < level_size - 1) {
                node->next = queue[left];  // ָ��ͬ����һ���ڵ�
            }

            // ����ǰ�ڵ�������ӽڵ������
            if (node->left != NULL) {
                queue[right++] = node->left;
            }
            if (node->right != NULL) {
                queue[right++] = node->right;
            }
        }
    }

    return root; // �����޸ĺ�ĸ��ڵ�
}

// ��������ַ�������Ϊ�������飬��������Ĵ�С
int parse_input_to_array(char* input_string, int* numbers) {
    int count = 0;  // ����Ԫ�ؼ���
    char* token = strtok(input_string, ",");  // �����ŷָ������ַ���
    while (token != NULL) {
        numbers[count++] = atoi(token);  // ���ַ���ת��Ϊ��������������
        token = strtok(NULL, ",");  // ��ȡ��һ���Ӵ�
    }

    return count;  // ���ؽ�������Ԫ������
}

// �����������鹹��������
struct Node* buildTree(int* nums, int size) {
    if (size == 0) {
        return NULL;  // �������Ϊ�գ����ؿ���
    }

    struct Node* root = createNode(nums[0]);  // �������ڵ�
    struct Node* queue[5000];  // ʹ�ö��и���������
    int front = 0, rear = 0;   // ���е�ǰ��ָ��
    queue[rear++] = root;  // ���ڵ������

    int i = 1;  // ��������
    while (i < size) {
        struct Node* node = queue[front++];  // ����һ���ڵ�
        if (i < size) {
            node->left = createNode(nums[i++]);  // �������ӽڵ�
            queue[rear++] = node->left;  // ���ӽڵ����
        }
        if (i < size) {
            node->right = createNode(nums[i++]);  // �������ӽڵ�
            queue[rear++] = node->right;  // ���ӽڵ����
        }
    }

    return root;  // ���ع����õ����ĸ��ڵ�
}

// ��ӡ���Ĳ�α�������������ÿ���ڵ�� next ָ��
void printTree(struct Node* root) {
    if (!root) {  // �����Ϊ�գ���ӡ�����鲢����
        printf("[]");
        return;
    }

    struct Node* queue[10000];  // ʹ�ö��н��в�α���
    int front = 0, rear = 0;
    queue[rear++] = root;  // �����ڵ������

    while (front < rear) {
        struct Node* node = queue[front++];  // ���ӵ�ǰ�ڵ�
        if (node) {
            queue[rear++] = node->left;  // ���ӽڵ����
            queue[rear++] = node->right; // ���ӽڵ����
        }
    }

    int last_non_null_index = rear - 1;  // ���һ���ǿսڵ������
    int trailing_null_count = 0;  // ͳ��β�������� NULL �ڵ���

    // ͳ��β�������� NULL �ڵ�
    while (queue[last_non_null_index--] == NULL) {
        trailing_null_count++;
    }

    // ������нڵ��ֵ
    for (int i = 0; i < rear - trailing_null_count; i++) {
        if (queue[i]->next) {  // �����ǰ�ڵ�� next ָ�벻Ϊ��
            printf("%d,", queue[i]->val);
        } else {
            printf("%d,#,", queue[i]->val);  // ������� # ��ʾû����һ���ڵ�
        }
    }

    // ���һ���ڵ㴦��
    if (queue[rear - trailing_null_count - 1]->next) {
        printf("%d", queue[rear - trailing_null_count - 1]->val);
    } else {
        printf("%d,#", queue[rear - trailing_null_count - 1]->val);
    }
}

int main() {
    char input_string[5000];  // �洢������ַ���
    fgets(input_string, sizeof(input_string), stdin);  // �ӱ�׼�����ȡһ��
    int input_length = strlen(input_string);  // ��ȡ�ַ�������
    if (input_string[input_length - 1] == '\n') {
        input_string[input_length - 1] = '\0';  // ȥ��ĩβ�Ļ��з�
    }

    int nums[5000];  // �洢�����������
    int array_size = parse_input_to_array(input_string, nums);  // ���������ַ���Ϊ����

    struct Node* root = buildTree(nums, array_size);  // ����������
    connect(root);  // ���ÿ���ڵ�� next ָ��
    printTree(root);  // ��ӡ�������Ĳ�α������

    return 0;
}

