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
        //check if the index is valid
        if (idx < 0) {
            cout<<"Invalid Index"<<endl;
        }
        //check if size is equal to data array maximum elements before pushing
        if (size == 64) {
            cout<<"Overflow"<<endl;
            return;
        }
        //put the new index to the first available index
        data[size] = idx;
        size++;
        //start with the last element of the data array before performing upheap
        upheap(size-1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        //check that the heap is not empty before popping
        // Replace root with last element, then call downheap()
        if (size > 0) {
            int min = data[0];
            data[0] = data[size-1];
            size--;
            //start with the root index when downheaping
            downheap(0, weightArr);
            //return original minimum value that was popped
            return min;
        }
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        //repeat until data pos index reaches the root or weightArr on data pos index is less than the parent weight
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            //compare the weight of parent and the position or current node
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                swap(data[pos], data[parent]);
                //update to continue moving and comparing
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
            //check if leftChild is less than the parent, then update parent if true
            if (leftChild < size && weightArr[data[leftChild]] < weightArr[data[parent]]) {
                parent = leftChild;
            }
            //check if rightChild is less than the parent, then update parent if true
            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[parent]]) {
                parent = rightChild;
            }
            //check if the current position is not the smallest value
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