#ifndef MAX_HEAP_H  // Verifica si MAX_HEAP_H no está definido
#define MAX_HEAP_H  // Define MAX_HEAP_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

class MaxHeap {
public:
    std::vector<std::pair<int, std::string>> heap;

    bool empty() {
        return heap.empty();
    }

    void push(std::pair<int, std::string> element) {
        heap.push_back(element);
        std::push_heap(heap.begin(), heap.end());
    }

    std::pair<int, std::string> top() {
        return heap.front();
    }

    void pop() {
        std::pop_heap(heap.begin(), heap.end());
        heap.pop_back();
    }
};

#endif  // Cierra el guardia de inclusión