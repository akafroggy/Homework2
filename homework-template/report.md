 41243252
# 41243249 
作業一

## 解題說明

1.Max/Min Heap

要C++ 抽象類別設計、繼承與 heap 的基本操作，並且讓介面和複雜度都和 max priority queue 一致

### 解題策略

設計一個 MinPQ 抽象類別，定義四個純虛擬函式：IsEmpty(), Top(), Push(), Pop()，用陣列（或 vector）實作 MinHeap，繼承 MinPQ，並完成所有函式。

## 程式實作

以下為主要程式碼：

###minheap
```cpp
#include <iostream>

class MinPQ {
public:
    virtual ~MinPQ() {}                                 
    virtual bool IsEmpty() const = 0;                   
    virtual const T& Top() const = 0;                  
    virtual void Push(const T&) = 0;                   
    virtual void Pop() = 0;                           
};
void HeapifyUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[idx] < heap[parent]) {
            std::swap(heap[idx], heap[parent]);
            idx = parent;
        }
        else break;
    }
}

void HeapifyDown(int idx) {
    int n = heap.size();
    while (true) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;
        if (left < n && heap[left] < heap[smallest]) smallest = left;
        if (right < n && heap[right] < heap[smallest]) smallest = right;
        if (smallest != idx) {
            std::swap(heap[idx], heap[smallest]);
            idx = smallest;
        }
        else break;
    }
int main() {
    MinHeap<int> minHeap;
    minHeap.Push(3);
    minHeap.Push(1);
    minHeap.Push(4);
    minHeap.Push(2);

    while (!minHeap.IsEmpty()) {
        std::cout << minHeap.Top() << " ";
        minHeap.Pop();
    }
    std::cout << std::endl;
```

2.二元搜尋樹:

(a)從空的二元搜尋樹（BST）開始，插入 n 個隨機值

(b)從 BST 中刪除 key 為 k 的節點
### 解題策略



設計一個 MinPQ 抽象類別，定義四個純虛擬函式：IsEmpty(), Top(), Push(), Pop()，用陣列（或 vector）實作 MinHeap，繼承 MinPQ，並完成所有函式。

2.二元搜尋樹:

(a)插入 n 個隨機值，用隨機演算法將數字順序打亂，確保插入順序隨機，計算樹高。

(b)從根節點開始，根據 BST 性質（小於往左，大於往右）遞迴搜尋 key 為 k 的節點
3. 主程式呼叫遞迴函式，並輸出計算結果。

## 程式實作

以下為主要程式碼：

###minheap
```cpp
#include <iostream>

void HeapifyUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[idx] < heap[parent]) {
            std::swap(heap[idx], heap[parent]);
            idx = parent;
        }
        else break;
    }
}

void HeapifyDown(int idx) {
    int n = heap.size();
    while (true) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;
        if (left < n && heap[left] < heap[smallest]) smallest = left;
        if (right < n && heap[right] < heap[smallest]) smallest = right;
        if (smallest != idx) {
            std::swap(heap[idx], heap[smallest]);
            idx = smallest;
        }
        else break;
    }
int main() {
    int h = 0;
int size = n;
while (size > 0) {
    size /= 2;
    ++h;
}
double ratio = h / std::log2(n);

std::cout << "n = " << n
    << ", heap height (log2 n rounded up) = " << h
    << ", h/log2(n) = " << ratio << std::endl;
}
```
###binarysearchtree(a)
```cpp
#include <iostream>
using namespace std;

int height(Node* root) {
    if (!root) return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

void shuffle(int* arr, int n) {
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
int main() {
    for (int idx = 0; idx < num_ns; ++idx) {
    int n = ns[idx];
    int* vals = new int[n];
    for (int i = 0; i < n; ++i) vals[i] = i;
    shuffle(vals, n);

    Node* root = nullptr;
    for (int i = 0; i < n; ++i) insert(root, vals[i]);

    int h = height(root);
    double ratio = h / log2(n);

    std::cout << "n = " << n
        << ", height = " << h
        << ", height/log2(n) = " << ratio << std::endl;
}
```

## 效能分析

1. 時間複雜度
| 操作     | 時間複雜度     |說明 |
|----------|--------------|----------------------------------------------------------------------|
| IsEmpty()| O(1)         | 判斷容器是否為空，直接檢查陣列或 vector 長度                            |
| Top()    | O(1)         | 取得最小元素，直接回傳根節點（heap）                                    |
| Push(x)  | O(logn)      | 插入新元素後進行 Heapify Up，最多移動樹高次（log n）                    |
| Pop()    | O(logn)      | 移除最小元素（根），用最後一個元素補上後 Heapify Down，最多移動樹高次      |

2. 空間複雜度：整體空間複雜度為O(n)，因為所有元素都儲存在一個陣列（vector）中。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $n = 0$      | 0        | 0        |
| 測試二   | $n = 1$      | 1        | 1        |
| 測試三   | $n = 3$      | 6        | 6        |
| 測試四   | $n = 5$      | 15       | 15       |
| 測試五   | $n = -1$     | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

### 結論

1. 程式能正確計算 $n$ 到 $1$ 的連加總和。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
