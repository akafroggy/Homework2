#include <iostream>

// 節點結構
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

// 尋找最小值節點
Node* findMin(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

// 刪除 key 為 k 的節點
Node* deleteNode(Node* root, int k) {
    if (!root) return nullptr;
    if (k < root->val) {
        root->left = deleteNode(root->left, k);
    }
    else if (k > root->val) {
        root->right = deleteNode(root->right, k);
    }
    else {
        // 找到要刪除的節點
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }
        else if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            Node* succ = findMin(root->right);
            root->val = succ->val;
            root->right = deleteNode(root->right, succ->val);
        }
    }
    return root;
}

// 中序走訪（印出樹內容）
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    std::cout << root->val << " ";
    inorder(root->right);
}

// 釋放樹記憶體
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;
    // 插入一些數字
    insert(root, 5);
    insert(root, 3);
    insert(root, 8);
    insert(root, 1);
    insert(root, 4);
    insert(root, 7);
    insert(root, 9);

    std::cout << "原始樹（中序）：";
    inorder(root);
    std::cout << std::endl;

    // 刪除一個節點
    root = deleteNode(root, 3);

    std::cout << "刪除輸入節點後（中序）：";
    inorder(root);
    std::cout << std::endl;

    // 釋放記憶體
    freeTree(root);
    return 0;
}
