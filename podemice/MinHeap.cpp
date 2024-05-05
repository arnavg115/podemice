#include <stdio.h> // NULL
#include <stdlib.h> // malloc, free

#include "MinHeap.h"

MinHeap::MinHeap()
{
    size = 0;
    size_alloc = 128;
    heap = (heap_node *)malloc(size_alloc * sizeof(heap_node));
}

void MinHeap::push(heap_node obj)
{
    if (size == size_alloc)
        expand();

    *(heap+size) = obj;
    percolateUp(size);
    size++;
}

void MinHeap::expand()
{
    heap_node *ptr = (heap_node *)malloc(size_alloc * sizeof(heap_node) * 2);

    for (int i=0; i<size_alloc; ++i)
        *(ptr+i) = *(heap+i);

    free(heap);

    size_alloc *= 2;
    heap = ptr;
}

void MinHeap::swap(int id1, int id2)
{
    heap_node temp = *(heap+id1);
    *(heap+id1) = *(heap+id2);
    *(heap+id2) = temp;
}

int MinHeap::getParentIdx(int id)
{
    return (id-1)/2;
}

int MinHeap::getLeftChildIdx(int id)
{
    return id*2+1;
}

int MinHeap::getRightChildIdx(int id)
{
    return id*2+2;
}

int MinHeap::getMinChildIdx(int id)
{
    int left = getLeftChildIdx(id);
    int right = getRightChildIdx(id);

    if (left < size) {
        if (right < size) {
            if (*(heap+left) < *(heap+right))
                return left;
            else 
                return right;
        }

        return left;
    }

    return -1;
}

void MinHeap::percolateUp(int id)
{
    int parent = getParentIdx(id);

    while (*(heap+id) < *(heap+parent)) {
        swap(id, parent);

        id = parent;
        if (id == 0) return;
        parent = getParentIdx(id);
    }
}

void MinHeap::percolateDown(int id)
{
    int child = getMinChildIdx(id);

    while (child > 0 && *(heap+child) < *(heap+id)) {
        swap(id, child);

        id = child;
        child = getMinChildIdx(id);
    }
}

heap_node MinHeap::deleteIdx(int id)
{
    if (id == size-1)
        return *(heap+(--size));

    swap(id, size-1);
    heap_node ret = *(heap+(--size));

    if (size == 0)
        return ret;

    if (getParentIdx(id) >= 0 && *(heap+id) < *(heap+getParentIdx(id)))
        percolateUp(id);
    else
        percolateDown(id);

    return ret;
}

heap_node MinHeap::pop()
{
    return deleteIdx(0);
}

heap_node MinHeap::peek()
{
    return *heap;
}

int MinHeap::get_size()
{
    return size;
}

void MinHeap::terminate()
{
    free(heap);
    heap = NULL;
    size = 0;
}