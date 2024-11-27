#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <unordered_map>
using namespace std;

// 定义二叉树节点结构体
struct Node {
    int data;       // 节点的数据
    Node* left;     // 左子节点
    Node* right;    // 右子节点
    Node(int x) : data(x), left(NULL), right(NULL) {}  // 构造函数
};

// 根据给定的字符串数组构建二叉树
Node* BuildTree(const vector<string>& arr) {
    if (arr.empty()) {
        return NULL;  // 如果数组为空，返回空树
    }

    // 创建根节点
    Node* root = new Node(stoi(arr[0]));
    queue<Node*> nodeQueue;  // 队列用于层次遍历
    nodeQueue.push(root);    // 将根节点入队列

    int i = 1;
    while (!nodeQueue.empty() && i < arr.size()) {
        Node* currentNode = nodeQueue.front();  // 获取队头节点
        nodeQueue.pop();  // 出队

        // 处理左子节点
        if (arr[i] != "null") {
            currentNode->left = new Node(stoi(arr[i]));
            nodeQueue.push(currentNode->left);  // 左子节点入队
        }
        i++;

        // 处理右子节点
        if (i < arr.size() && arr[i] != "null") {
            currentNode->right = new Node(stoi(arr[i]));
            nodeQueue.push(currentNode->right);  // 右子节点入队
        }
        i++;
    }

    return root;  // 返回构建好的树的根节点
}

// 遍历树并记录每个节点的父节点
void RecordParents(Node* root, unordered_map<int, Node*>& parentMap) {
    if (root == NULL) {
        return;  // 如果节点为空，直接返回
    }

    // 递归处理左子节点
    if (root->left) {
        parentMap[root->left->data] = root;  // 记录左子节点的父节点
        RecordParents(root->left, parentMap);
    }

    // 递归处理右子节点
    if (root->right) {
        parentMap[root->right->data] = root;  // 记录右子节点的父节点
        RecordParents(root->right, parentMap);
    }
}

// 根据节点的值查找该节点
Node* FindNodeByValue(Node* root, int val) {
    if (root == NULL) {
        return NULL;  // 如果节点为空，返回空
    }

    // 如果当前节点值匹配，直接返回节点
    if (root->data == val) {
        return root;
    }

    // 递归查找左子树
    Node* leftSearch = FindNodeByValue(root->left, val);
    if (leftSearch != NULL) {
        return leftSearch;
    }

    // 递归查找右子树
    return FindNodeByValue(root->right, val);
}

// 查找两个节点的最近公共祖先
Node* FindNearestAncestor(Node* root, Node* p, Node* q) {
    unordered_map<int, Node*> parentMap;
    RecordParents(root, parentMap);  // 记录每个节点的父节点

    unordered_map<int, bool> ancestorMap;  // 用于记录p的所有祖先
    while (p != NULL) {
        ancestorMap[p->data] = true;  // 将p的祖先加入集合
        p = parentMap[p->data];  // 更新p为其父节点
    }

    // 查找q的祖先，如果存在p的祖先，说明是最近公共祖先
    while (q != NULL) {
        if (ancestorMap.find(q->data) != ancestorMap.end()) {
            return q;  // 返回最近公共祖先
        }
        q = parentMap[q->data];  // 更新q为其父节点
    }

    return NULL;  // 如果没有找到公共祖先，返回NULL
}

int main() {
    string input;
    int p_val, q_val;

    // 获取树节点的值（以逗号分隔的字符串）
    getline(cin, input);
    stringstream ss(input);
    vector<string> nodes;
    string token;

    // 将输入的节点值按逗号拆分并存储
    while (getline(ss, token, ',')) {
        nodes.push_back(token);
    }

    // 获取p和q的值
    cin >> p_val >> q_val;

    // 根据节点值构建二叉树
    Node* root = BuildTree(nodes);

    // 查找节点p和q
    Node* p = FindNodeByValue(root, p_val);
    Node* q = FindNodeByValue(root, q_val);

    // 查找p和q的最近公共祖先
    Node* result = FindNearestAncestor(root, p, q);

    // 输出结果
    cout << result->data << endl;

    return 0;
}
