 41243252
 41243249 

## 1.Max/Min Heap

## 解題說明

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

## 效能分析

1. 時間複雜度

| 操作         | 時間複雜度         | 說明                                                                 |
|--------------|--------------------|----------------------------------------------------------------------|
| `IsEmpty()`  | \(O(1)\)           | 判斷容器是否為空，直接檢查陣列或 vector 長度。                        |
| `Top()`      | \(O(1)\)           | 取得最小元素，直接回傳根節點（heap）。                                |
| `Push(x)`    | \(O(\log n)\)      | 插入新元素後進行 Heapify Up，最多移動樹高次（log n）。                 |
| `Pop()`      | \(O(\log n)\)      | 移除最小元素（根），用最後一個元素補上後 Heapify Down，最多移動樹高次。|


2. 空間複雜度：整體空間複雜度為O(n)，因為所有元素都儲存在一個陣列（vector）中。

## 測試與驗證
插入多個亂序數字（例如 3, 1, 4, 2）。

每次呼叫 Top() 應該得到目前 heap 中的最小值。

依序呼叫 Pop()，印出每次 Top() 結果，應該是由小到大輸出（1 2 3 4）。

測試 IsEmpty()，確保 heap 清空後會回傳 true。
### 測試案例

| 測試編號 | 操作序列                         | 預期 Top() 結果序列 | 預期 IsEmpty() 結果 | 說明                    |
|----------|----------------------------------|---------------------|---------------------|-------------------------|
| 1        | Push(3), Push(1), Push(4), Push(2) | 1, 2, 3, 4          | false, ..., true    | 正常插入與遞增取出      |
| 2        | Push(5), Pop(), Pop()              | 5, (例外)           | false, true         | Pop 到空 heap 應丟例外  |
| 3        | Push(2), Push(2), Push(1), Pop()   | 1, 2, 2             | false, false, true  | 重複元素處理            |
| 4        | 無操作                             | (例外)              | true                | 空 heap 呼叫 Top() 應例外|




### 結論
此時作成功完成了最小優先佇列（Min Priority Queue, MinPQ）之 C++ 抽象類別設計，並以 vector 實作了二元 min-heap（MinHeap）
1. MinHeap 能夠正確維護最小優先佇列的性質，無論資料插入順序如何，依序取出的元素皆為遞增排序，符合 min-heap 的預期行為。  
2. 所有操作的時間複雜度也均達到理論標準，插入與刪除的最壞情況為O(logn)。  
3. 本次實作不僅達成了題目的所有功能與效能要求，亦展現了物件導向設計、抽象資料型態與 heap 結構實作的能力。

## 申論及開發報告
1.資料結構的抽象設計與物件導向實作是提升程式可維護性與可重用性的關鍵，優先佇列（Priority Queue）是一種常見的抽象資料型態，廣泛應用於排序、排程、圖論演算法等場景。本題要求以 C++ 撰寫一個最小優先佇列（Min 

Priority Queue, MinPQ）的抽象類別，並以二元堆積（MinHeap）方式實作，這不僅能鞏固資料結構理論，也能實踐物件導向程式設計中的繼承與多型。

2.透過實驗測試，無論資料插入順序如何，從 MinHeap 依序取出的元素皆為遞增排序，證明 min-heap 性質正確維護。對空 heap 執行 Top() 或 Pop() 操作時，程式會丟出例外，提升了系統的健壯性

---
## 第二題binarysearchtree

## 解題說明

(a)從從一棵空的二元搜尋樹（Binary Search Tree, BST）開始，隨機插入n個節點。每個n需進行多次實驗，並計算最終樹的高度。
-隨機插入：利用亂數產生器產生 n 個不同的值，並依序插入 BST，確保插入順序隨機
-計算樹高：插入完畢後，計算 BST 的高度
-計算比值：將高度除以 log2n
(b)從 BST 中刪除 key 為 k 的節點
### 解題策略
-資料結構選擇：使用指標實作 BST，每個節點包含值、左子樹、右子樹指標。
-隨機性：產生 0~n−1的隨機排列，保證插入順序隨機
-高度計算：用遞迴方式計算 BST 高度。
-多組測試：用 for 迴圈依序測試不同 n。


## 程式實作
```cpp
#include <iostream>

void insert(Node*& root, int val) {
    if (!root) {
        root = new Node(val);
        return;
    }
    if (val < root->val) insert(root->left, val);
    else insert(root->right, val);
}

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
}

int main(){
 double ratio = h / log2(n);

 std::cout << "n = " << n
     << ", height = " << h
     << ", log2(n) = " << log2n
     << ", height/log2(n) = " << ratio << std::endl;
}
```

## 效能分析

| 函數/步驟         | 時間複雜度（期望） | 時間複雜度（最壞） | 空間複雜度 | 說明                                                         |
|-------------------|-------------------|---------------------|------------|--------------------------------------------------------------|
| shuffle           | O(n)              | O(n)                | O(1)       | 確保插入順序隨機                          |
| insert            | O(log n)          | O(n)                | O(h)       | 單次插入，h為樹高，隨機插入期望為O(log n)，最壞O(n)         |
| n次insert         | O(n log n)        | O(n^2)              | O(n)       | n個節點依序插入BST                                           |
| height            | O(n)              | O(n)                | O(h)       | 遞迴遍歷所有節點計算樹高                                     |
| freeTree          | O(n)              | O(n)                | O(h)       | 遞迴釋放所有節點記憶體                                       |
| 總體              | O(n log n)        | O(n^2)              | O(n)       | 主要由插入操作主導，空間由n個節點主導                        |

1.期望情況下，隨機插入BST的高度約為O(logn)，因此總插入複雜度為O(nlogn)。

2.最壞情況（極度不平衡時）會退化為O(n^2)。

3.空間複雜度主要來自於節點儲存，為O(n)。

4.height 與 freeTree 的遞迴堆疊深度為樹高h，期望O(logn)，最壞O(n)。

## 測試與驗證

每組 n 執行完畢後，輸出：

1.執行程式，收集每組 n 的輸出結果

2.檢查 height/log₂(n) 是否隨 n 增大而趨於穩定，且接近理論常數

3.若要更精確，可對每個 n 執行多次（如 10 次），取平均高度再計算比值

### 測試案例

| n     | height | log₂(n)  | height/log₂(n) |
|-------|--------|----------|----------------|
| 100   | 15     | 6.64386  | 2.25772        |
| 500   | 18     | 8.96578  | 2.00763        |
| 1000  | 20     | 9.96578  | 2.00687        |
| 2000  | 24     | 10.9658  | 2.18863        |
| 3000  | 25     | 11.5507  | 2.16436        |
| 10000 | 32     | 13.2877  | 2.40824        |

![height/log2n_關係圖](https://github.com/akafroggy/Homework2/blob/main/homework-template/src/images/7136d516_ejpnng.png)

### 結論
-隨機插入 n 個節點後的二元搜尋樹，其高度與 log2n 的比值（height/log₂n）會隨著 n 增大而趨於穩定
-實驗中，當 n 逐漸變大時，height/log₂(n) 的比值會趨近於理論常數，通常在 2~4.3 之間。這說明隨機插入下 BST 的高度確實為 O(logn)
