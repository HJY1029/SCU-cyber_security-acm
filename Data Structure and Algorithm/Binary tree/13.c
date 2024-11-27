#include <stdio.h>
#include <stdlib.h>

// ������С�ѽṹ��
typedef struct {
    int *data;  // �洢�����ݵ�����
    int size;   // ��ǰ�ѵĴ�С
    int capacity; // �ѵ��������
} MinHeap;

// ��ʼ����С��
MinHeap *initMinHeap(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));  // ����ѿռ�
    heap->data = (int*)malloc((capacity + 1) * sizeof(int));  // Ϊ�����ݷ���ռ�
    heap->size = 0;  // ��ʼ���ѵĴ�СΪ0
    heap->capacity = capacity;  // ���öѵ��������
    return heap;
}

// ����С���в���һ��Ԫ��
void insert(MinHeap *heap, int value) {
    heap->size++;  // �ѵĴ�С��1
    int i = heap->size;  // �Ӷѵ�ĩβ��ʼ����
    // ���ϵ����ѣ��Ա�֤��С�ѵ�����
    while (i > 1 && heap->data[i / 2] > value) {
        heap->data[i] = heap->data[i / 2];  // �����ڵ��³�
        i /= 2;  // �����ƶ������ڵ�
    }
    heap->data[i] = value;  // ����ǰֵ���뵽���ʵ�λ��
}

// ����С����ɾ����������Сֵ
int deleteMin(MinHeap *heap) {
    int minValue = heap->data[1];  // ��ȡ��Сֵ���Ѷ�Ԫ�أ�
    int lastValue = heap->data[heap->size--];  // ɾ���Ѷ�Ԫ�ز���ȡ���һ��Ԫ��
    int i = 1, child;
    // ���µ����ѣ��Ա�����С�ѵ�����
    while (i * 2 <= heap->size) {
        child = i * 2;  // ��ȡ���ӽڵ�
        // ������ӽڵ������С�����ӽڵ㣬ѡ�����ӽڵ�
        if (child < heap->size && heap->data[child] > heap->data[child + 1]) {
            child++;
        }
        // ������һ��ֵ�Ѿ������ӽڵ�С������
        if (lastValue <= heap->data[child]) {
            break;
        }
        heap->data[i] = heap->data[child];  // ����С���ӽڵ�����
        i = child;  // �����ƶ����ӽڵ�
    }
    heap->data[i] = lastValue;  // �����һ��ֵ������ʵ�λ��
    return minValue;  // ���ضѶ�����Сֵ
}

// �����������㷨
int huff(int n, int *weights) {
    MinHeap *heap = initMinHeap(n);  // ��ʼ����
    // ������Ȩֵ�������
    for (int i = 0; i < n; i++) {
        insert(heap, weights[i]);
    }
    int totalCost = 0;  // ���յı���ɱ�
    // ֱ������ֻʣһ��Ԫ��
    while (heap->size > 1) {
        int firstMin = deleteMin(heap);  // ɾ����Сֵ
        int secondMin = deleteMin(heap); // ɾ���ڶ�Сֵ
        totalCost += firstMin + secondMin;  // �����ܳɱ�
        insert(heap, firstMin + secondMin);  // ������֮�Ͳ������
    }
    return totalCost;  // �����ܳɱ�
}

int main() {
    int n;  // Ԫ������
    scanf("%d", &n);  // ����Ԫ������
    int *weights = (int*)malloc(n * sizeof(int));  // ��̬��������洢Ȩֵ
    // ����ÿ��Ԫ�ص�Ȩֵ
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }
    // ���������������ܳɱ�
    int result = huff(n, weights);
    printf("%d", result);  // ������
    return 0;
}

