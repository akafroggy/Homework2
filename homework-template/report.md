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



(a)從空的二元搜尋樹（BST）開始，插入 n 個隨機值

(b)從 BST 中刪除 key 為 k 的節點
### 解題策略

設計一個 MinPQ 抽象類別，定義四個純虛擬函式：IsEmpty(), Top(), Push(), Pop()，用陣列（或 vector）實作 MinHeap，繼承 MinPQ，並完成所有函式。

2.二元搜尋樹:

(a)插入 n 個隨機值，用隨機演算法將數字順序打亂，確保插入順序隨機，計算樹高。

(b)從根節點開始，根據 BST 性質（小於往左，大於往右）遞迴搜尋 key 為 k 的節點
3. 主程式呼叫遞迴函式，並輸出計算結果。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
