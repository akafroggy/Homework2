#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cmath>

// 1. MinPQ 抽象類別（依 ADT 5.2 格式）
template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}                                 // virtual destructor
    virtual bool IsEmpty() const = 0;                   // return true iff the priority queue is empty
    virtual const T& Top() const = 0;                   // return reference to min element
    virtual void Push(const T&) = 0;                    // add an element to the priority queue
    virtual void Pop() = 0;                             // delete element with min priority
};

// 2. MinHeap 實作（繼承 MinPQ）
template <class T>
class MinHeap : public MinPQ<T> {
private:
    std::vector<T> heap;

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
    }

public:
    virtual ~MinHeap() {}

    virtual bool IsEmpty() const override {
        return heap.empty();
    }

    virtual const T& Top() const override {
        if (IsEmpty()) throw std::runtime_error("Heap is empty");
        return heap[0];
    }

    virtual void Push(const T& x) override {
        heap.push_back(x);
        HeapifyUp(heap.size() - 1);
    }

    virtual void Pop() override {
        if (IsEmpty()) throw std::runtime_error("Heap is empty");
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) HeapifyDown(0);
    }
};

// 3. main() 測試 MinHeap
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
    return 0;
}
