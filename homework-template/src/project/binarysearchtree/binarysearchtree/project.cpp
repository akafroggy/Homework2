#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// 插入節點
void insert(Node*& root, int val) {
    if (!root) {
        root = new Node(val);
        return;
    }
    if (val < root->val) insert(root->left, val);
    else insert(root->right, val);
}

// 計算樹高
int height(Node* root) {
    if (!root) return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

// 釋放樹記憶體
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Fisher-Yates 洗牌
void shuffle(int* arr, int n) {
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

int main() {
    int ns[] = { 100, 500, 1000, 2000, 3000, 10000 };
    int num_ns = sizeof(ns) / sizeof(ns[0]);

    srand(time(0)); // 初始化亂數種子

    for (int idx = 0; idx < num_ns; ++idx) {
        int n = ns[idx];
        int* vals = new int[n];
        for (int i = 0; i < n; ++i) vals[i] = i;
        shuffle(vals, n);

        Node* root = nullptr;
        for (int i = 0; i < n; ++i) insert(root, vals[i]);

        int h = height(root);
        double log2n = log2(n);
        double ratio = h / log2(n);

        std::cout << "n = " << n
            << ", height = " << h
            << ", log2(n) = " << log2n
            << ", height/log2(n) = " << ratio << std::endl;

        freeTree(root);
        delete[] vals;
    }
    return 0;
}
