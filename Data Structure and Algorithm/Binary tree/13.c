#include <stdio.h>
#include <stdlib.h>

// 定义最小堆结构体
typedef struct {
    int *data;  // 存储堆数据的数组
    int size;   // 当前堆的大小
    int capacity; // 堆的最大容量
} MinHeap;

// 初始化最小堆
MinHeap *initMinHeap(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));  // 分配堆空间
    heap->data = (int*)malloc((capacity + 1) * sizeof(int));  // 为堆数据分配空间
    heap->size = 0;  // 初始化堆的大小为0
    heap->capacity = capacity;  // 设置堆的最大容量
    return heap;
}

// 向最小堆中插入一个元素
void insert(MinHeap *heap, int value) {
    heap->size++;  // 堆的大小加1
    int i = heap->size;  // 从堆的末尾开始插入
    // 向上调整堆，以保证最小堆的性质
    while (i > 1 && heap->data[i / 2] > value) {
        heap->data[i] = heap->data[i / 2];  // 将父节点下沉
        i /= 2;  // 向上移动到父节点
    }
    heap->data[i] = value;  // 将当前值插入到合适的位置
}

// 从最小堆中删除并返回最小值
int deleteMin(MinHeap *heap) {
    int minValue = heap->data[1];  // 获取最小值（堆顶元素）
    int lastValue = heap->data[heap->size--];  // 删除堆顶元素并获取最后一个元素
    int i = 1, child;
    // 向下调整堆，以保持最小堆的性质
    while (i * 2 <= heap->size) {
        child = i * 2;  // 获取左子节点
        // 如果右子节点存在且小于左子节点，选择右子节点
        if (child < heap->size && heap->data[child] > heap->data[child + 1]) {
            child++;
        }
        // 如果最后一个值已经不比子节点小，跳出
        if (lastValue <= heap->data[child]) {
            break;
        }
        heap->data[i] = heap->data[child];  // 将较小的子节点上移
        i = child;  // 向下移动到子节点
    }
    heap->data[i] = lastValue;  // 将最后一个值放入合适的位置
    return minValue;  // 返回堆顶的最小值
}

// 霍夫曼编码算法
int huff(int n, int *weights) {
    MinHeap *heap = initMinHeap(n);  // 初始化堆
    // 将所有权值插入堆中
    for (int i = 0; i < n; i++) {
        insert(heap, weights[i]);
    }
    int totalCost = 0;  // 最终的编码成本
    // 直到堆中只剩一个元素
    while (heap->size > 1) {
        int firstMin = deleteMin(heap);  // 删除最小值
        int secondMin = deleteMin(heap); // 删除第二小值
        totalCost += firstMin + secondMin;  // 更新总成本
        insert(heap, firstMin + secondMin);  // 将两者之和插入堆中
    }
    return totalCost;  // 返回总成本
}

int main() {
    int n;  // 元素数量
    scanf("%d", &n);  // 输入元素数量
    int *weights = (int*)malloc(n * sizeof(int));  // 动态分配数组存储权值
    // 输入每个元素的权值
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }
    // 计算霍夫曼编码的总成本
    int result = huff(n, weights);
    printf("%d", result);  // 输出结果
    return 0;
}

