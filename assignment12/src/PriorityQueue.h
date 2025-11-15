//
//  PriorityQueue.h
//
//  Defines a binary heap based priority queue class.
//  It is a max-heap.
//  You SHOULD modify this file.
//
//  IMPORTANT NOTE: For this particular assignment you may not add
//  any additional utility functions.
//
//  Copyright 2019 David Kopec
//  Aaron Archambault
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation files
//  (the "Software"), to deal in the Software without restriction,
//  including without limitation the rights to use, copy, modify, merge,
//  publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice
//  shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.

#ifndef pq_hpp
#define pq_hpp

#include <algorithm>  // for swap()
#include <iostream>
#include <random>
#include <vector>

#include "MemoryLeakDetector.h"

using namespace std;

// Convenience macros; Note that we are using -1, +1, and +2 as modifiers here
// versus the pseudocode in Introduction to Algorithms Chapter 6 to allow
// our heap to start at location 0
#define parent(i) ((i - 1) / 2)
#define left(i) (2 * i + 1)
#define right(i) (2 * i + 2)

namespace csi281 {

  template <typename T> class PriorityQueue {
  public:
    // What is the maximum value in the priority queue?
    // In other words, what is the next value that would be popped?
    // TIP: See pseudocode in Introduction to Algorithm Chapter 6 page 163
    // for HEAP-MAXIMUM()
    // NOTE: Our heap starts at 0, not 1
    T peek() {
      // YOUR CODE HERE
      if (heap.size() == 0) //it checks if the heaps size is 0 and if it is it throws a runtime error
      {
        throw std::runtime_error("empty Priority queue");
      }
      return heap[0];//the max element is/should always be at the root and it returns the heap at index 0
    }

    // Remove the next element (max element) in the heap and return it
    // TIP: See pseudocode in Introduction to Algorithm Chapter 6 page 163
    // for HEAP-EXTRACT-MAX()
    // NOTE: Our heap starts at 0, not 1
    // NOTE: Do not worry about contracting the size of the backing vector
    // after a pop.
    T pop() {
      // YOUR CODE HERE
      if (heap.size() == 0) //it checks if the heap size is 0 and if it is then it throws a runtime error
      {
        throw std::runtime_error("empty Priority queue");
      }

      T max = heap[0]; //it saves the max element by setting max to be the value of heap at index 0
      heap[0] = heap[heapSize - 1];//it moves to the last element to root by setting the heap at index 0 to be the value of
      //the heap at index of the heapsize - 1
      heapSize--; //it decreased the heap size by one
      maxHeapify(0); //restores the max-heap property

      return max; //returns the max

    }

    // Put a new element into the priority queue
    // TIP: A combination of HEAP-INCREASE-KEY() and MAX-HEAP-INSERT()
    // in Intro to Algorithms Chapter 6; they set the last element to
    // -infinity; we will set our last element to *key*, and then float it up
    // as is done in HEAP-INCREASE-KEY()
    // NOTE: macro parent() is defined at the top of this file
    // NOTE: our last element is at heapSize after being push_back()ed onto
    // the end of the vector heap
    void push(T key) {
      // YOUR CODE HERE
      heap.push_back(key); //add to the end of the vector by calling push back on the heap and pushing back the key
      heapSize++; //it increases the size by 1

      int i = heapSize - 1; //it makes the index of the newly added elements by setting i to the value of heapsize - 1

      //it floats the element up to maintain the max-heap property
      while (i > 0 && heap[parent(i)] < heap[i]) //it loops while i it grater than 0 and heap at parent(i) index is less than
        //heap at index i and everytime it loops it swaps the heap at index i and the heap at parent(i) and then sets
          //i to be the value of parent(i)
        {
        swap(heap[i], heap[parent(i)]);//it swaps the heap at index i and the heap at parent(i)
        i = parent(i); //sets i to be the value of parent(i)
      }
    }

    // How many items are in the priority queue?
    int getCount() { return heapSize; }

    // A debut print ouf of the contents of the heap
    void debugPrint() {
      for (auto item : heap) {
        cout << item << " ";
      }
      cout << endl;
    }

  private:
    // Push down the element at *i* to maintain the max-heap property
    // TIP: See pseudocode in Introduction to Algorithm Chapter 6 page 154
    // NOTE: Macros left() and right() are defined at the top of this file
    void maxHeapify(int i) {
      // YOUR CODE HERE
      int lefts = left(i); //it create a varerable for the left and it sets it to be the vlaue of left(i)
      int rights = right(i); ///it create a varerable for the right and sets it to be the value of right(i)
      int largest = i; ///it create a varerable for the largest and it sets it to the vlaue of i

      //it finds the largets among the node, left cilde and the right child
      if (lefts < heapSize && heap[lefts] > heap[largest]) //it checks if the lefts is less than the heapsize and if the
        //heap at index lefts is grater than the largest and if that is true it sets the lagest to be the value of lefts
      {
        largest = lefts; //sets the largest to be the value of lefts
      }
      if (rights < heapSize && heap[rights] > heap[largest]) //it checks to see if the rights is less than the heap size and
        //if the heap at index rights is grater than the heap at the largest index and if that is true then it sets the largest
          //to be the value of the rights
      {
        largest = rights; //sets largest to the value of rights
      }

      //it checks if the largest is not the current node, and it swpas and recuses
      if (largest != i) //it checks if the largest is not the same as the i and if that is true then it swaps the heap at
        //index i and the heap at the index largest and then it calls max heapifty and passes in largest
      {
        swap(heap[i], heap[largest]); //swaps the heap at index i and the heap at index largest
        maxHeapify(largest); //calls the maxHeapify and passes in the largest
      }

    }

    vector<T> heap;
    int heapSize = 0;
  };

}  // namespace csi281

#endif /* pq_hpp */
