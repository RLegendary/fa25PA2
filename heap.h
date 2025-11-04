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
        if (size >= 1) {
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
        int parent = (pos - 1)/ 2;
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
        int parent = pos;
        int leftChild = pos * 2 + 1;
        int rightChild = pos * 2 + 2;
        while (weightArr[data[parent]] < weightArr[data[leftChild]] && weightArr[data[parent]] < weightArr[data[rightChild]]) {
            if (weightArr[data[rightChild]] < weightArr[data[parent]]) {
                swap(data[parent], data[rightChild]);
                rightChild = parent;
            }
            if (weightArr[data[leftChild]] < weightArr[data[parent]]) {
                swap(data[parent], data[leftChild]);
                leftChild = parent;
            } else {
              break;
            }
        }
    }
};

#endif