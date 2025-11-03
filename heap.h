//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        //check if size is equal to data array maximum elements before pushing
        if (size == 64) {
            cout<<"Overflow"<<endl;
            return;
        }
        data[size] = idx;
        size++;
        //start with the last element of the data array before performing upheap
        upheap(size-1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        if (size > 0) {
            data[0] = data[size-1];
            size--;
            //start with the root index when downheaping
            downheap(0, weightArr);
            return data[0];
        }
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        int parent = pos - 1 / 2;
        //repeat until data pos index reaches the root or weightArr on data pos index is less than the parent weight
        while (data[pos] > data[0] or weightArr[data[pos]] >= weightArr[data[parent]]) {
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                int temp = data[pos];
                data[pos] = data[parent];
                data[parent] = temp;
                pos = parent;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        const int leftChild = pos * 2 + 1;
        const int rightChild = pos * 2 + 2;

        //repeat until weightArr of data pos index is less than or equal to both left and right child, or it reaches a leaf.
        while (weightArr[data[pos]] <= weightArr[data[leftChild]] && weightArr[data[pos]] <= weightArr[data[rightChild]] or data[leftChild] >= data[size]) {
            if (weightArr[data[rightChild]] < weightArr[data[pos]]) {
                const int temp = data[rightChild];
                data[rightChild] = data[pos];
                data[pos] = temp;
                pos = rightChild;

            } if (weightArr[data[leftChild]] < weightArr[data[pos]]) {
                const int temp = data[leftChild];
                data[leftChild] = data[pos];
                data[pos] = temp;
                pos = leftChild;
            }
        }
    }
};

#endif