#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include "Registros.h"

class MaxHeap {
private:
    std::vector<Registros> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void maxHeapify(int i) {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < heap.size() && heap[left].getAccesos() > heap[largest].getAccesos())
            largest = left;
        if (right < heap.size() && heap[right].getAccesos() > heap[largest].getAccesos())
            largest = right;

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            maxHeapify(largest);
        }
    }

public:
    // Constructor
    MaxHeap() {}

    // Insertar un registro en el MaxHeap
    void insert(const Registros& registro) {
        heap.push_back(registro);

        int i = heap.size() - 1;
        while (i > 0 && heap[parent(i)].getAccesos() < heap[i].getAccesos()) {
            std::swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    // Extraer el registro con mayor cantidad de accesos
    Registros extractMax() {
        if (heap.size() == 0)
            throw std::runtime_error("Heap vacío, no se puede extraer el máximo");

        Registros max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        maxHeapify(0);

        return max;
    }

    // Obtener el tamaño del MaxHeap
    size_t size() const {
        return heap.size();
    }
};

#endif // MAXHEAP_H
