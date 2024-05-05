#pragma once

struct heap_node
{
    unsigned char id;
    short int dist;
    bool operator<(const heap_node& other) const
    {
        return dist < other.dist;
    }
};

class MinHeap {

private:

    heap_node *heap;
    int size;
    int size_alloc;

    void expand();
    void swap(int id1, int id2);

    int getParentIdx(int id);
    int getLeftChildIdx(int id);
    int getRightChildIdx(int id);
    int getMinChildIdx(int id);

    void percolateUp(int id);
    void percolateDown(int id);

    heap_node deleteIdx(int id);

public:

    MinHeap();
    void push(heap_node node);
    heap_node pop();
    heap_node peek();
    int get_size();
    void terminate();

};