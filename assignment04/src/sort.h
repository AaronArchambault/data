//
//  sort.h
//
//  Functions for bubble sort, selection sort, and insertion sort.
//  You SHOULD modify this file.
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

#ifndef sort_hpp
#define sort_hpp

#include <algorithm>  // for swap()

#include "MemoryLeakDetector.h"

using namespace std;

namespace csi281 {

  // Performs an in-place ascending sort of *array* of size *length*
  // using the bubble sort algorithm
  //pre: the array and length values must be made and passed in
  //post: it will loop doing a bubblesort and it will make the array that was passed in sorted
  //purpose: to use a bubble sort to sort the array that was passed in
  template <typename T> void bubbleSort(T array[], const int length) {
    for (int i = 0; i < length; i++) { //it loops until i is greater than length and every time it loops
      //it adds 1 to the value of i
      for (int j = i + 1; j < length; j++) {//it first set j to be the value of i + 1 and then it loops until
        //j is greater than length and every time it loops it adds one to the value of j
        if (array[j] < array[i]) { //it tests if the array of index j is less than the array of index i
          //and if it is it calls swap with array i index and array j index passed into it and it swaps them
          swap(array[i], array[j]);
        }
      }
    }
  }

  // Performs an in-place ascending sort of *array* of size *length*
  // using the selection sort algorithm
  //pre: the array and length values must be made and passed in
  //post: the array that was passed in will be sorted using a selection sort
  //purpose: to sort the array that is passed in using a slection sort
  template <typename T> void selectionSort(T array[], const int length) {
    for (int i = 0; i < length; i++) { //loops until i is greater than length and every time it loops it adds one to i
      int min = i; //sets int min to the value of i
      for (int j = i + 1; j < length; j++) {//sets j to be i+1 and then it loops until j is greater than length
      //and every time it loops it adds one to the value of j
        if (array[j] < array[min]) { //tests if array index j is less than the array index min and if it is then
          //it set min to the value of j
          min = j;
        }
      }
      swap(array[i], array[min]); //calls the swap with array at index i and array at index min passed in
      //then it swaps them
    }
  }

  // Performs an in-place ascending sort of *array* of size *length*
  // using the insertion sort algorithm
  //pre: the array and length values must be passed in
  //post: the array that was passed in is sorted using an insertion sort
  //purpose: to sort the array using an insertion sort 
  template <typename T> void insertionSort(T array[], const int length) {
    // YOUR CODE HERE
    for (int i = 1; i < length; i++) { //loops until i is greater than length and every time it loops it adds one
      //to the value of i
      T key = array[i]; //sets T key to the value of array at index i
      int j = i - 1; //sets j to be the value of i -1
      while (j >= 0 && array[j] > key) {//loops until either j is greater or = to 0 and array index j is greater than key
        array[j + 1] = array[j]; //sets array at index j+1 to the value of array at index j
        j = j - 1; //sets j to j-1
      }
      array[j + 1] = key; //sets array at index j+1 to the value of key
    }
  }
}  // namespace csi281

#endif /* sort_hpp */
