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
        if (idx < 0) {
            cout<<"Invalid Index"<<endl;
        }
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
            int min = data[0];
            data[0] = data[size-1];
            size--;
            //start with the root index when downheaping
            downheap(0, weightArr);
            return min;
        }
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        //repeat until data pos index reaches the root or weightArr on data pos index is less than the parent weight
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                swap(data[pos], data[parent]);
                pos = parent;
            } else {
                break;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            int parent = pos;
            int leftChild = 2 * pos + 1;
            int rightChild = 2 * pos + 2;

            if (leftChild < size && weightArr[data[leftChild]] < weightArr[data[parent]]) {
                parent = leftChild;
            }
            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[parent]]) {
                parent = rightChild;
            }
            if (parent != pos) {
                swap(data[pos], data[parent]);
                pos = parent;
            } else {
                break;
            }
        }
    }
};

#endif