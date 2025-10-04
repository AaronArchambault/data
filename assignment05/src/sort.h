//
//  sort.h
//
//  Functions for merge sort, quicksort, and a hybrid sort.
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

#ifndef sort_hpp
#define sort_hpp

#include <algorithm>  // for swap(), merge()
#include <random>

#include "MemoryLeakDetector.h"

using namespace std;

namespace csi281 {
  //use the inplace merge function call

  // Performs an in-place ascending sort of *array*
  // using the merge sort algorithm
  // *start* is the first element of the array to start sorting from
  // *end* is the end element for the elements to be sorted
  // *end* will be the length of the array - 1 for a first run
  // NOTE: Your solution MUST use std::inplace_merge
  // http://www.cplusplus.com/reference/algorithm/inplace_merge/
  //pre: the t array, int start, and int end values must be passed in
  //post: the array that was passed in is sorted using the mergesort
  //purpose: to create a funciton that sorts an array using the merge Short
  template <typename T> void mergeSort(T array[], const int start, const int end) {
    // YOUR CODE HERE
if (start >= end) //it test if start is grater than or = to end and it that is true it retunrs
  //becasue if that is true the array is most likely messed up due to their one being 1 element or more
  //more elements at the start than the end
{
  return;
}
    int middle = start + (end - start) / 2; //creates an in for the middle of the index that is the value
    //of start + (end - start) / 2 so that the program can get the middle of start and end

    mergeSort(array, start, middle); // it calls itself and passes in the middle for the end

    mergeSort(array, middle + 1, end); //it calls itself and passes middle + 1 as the start

    std::inplace_merge(array + start, array + middle + 1, array + end +1);
    //it calls the inplace merge sort and it passes in the array + the start as the first iterators
    // then it passs array + middle + 1 as the middle iterator, and then it passes array + end + 1 as the
    //final iterator
    //just a little note I looked this up using the website that was give and also some others so that I could better understand it
    //it works by taking the three iterators of first, middle, and last and then first and middle and middle last should be sorted
    //and then merges them into on sorted range of first, last

  }

  // inplace merge without extra space
  // this is less time efficient than the regular merge
  // but it is more space efficient
  // time complexity is O(n^2) in the worst case
  // space complexity is O(1)
  template <typename T>
  requires std::is_arithmetic<T>::value // C++20
  void mergeInplace(std::vector<T>& arr, const size_t start, size_t mid,  const size_t end) {
    size_t left = start;
    size_t right = mid + 1;

    while (left <= mid && right <= end) {
      if (arr[left] <= arr[right]) {
        left++;
      }
      else {
        T temp = arr[right];
        for (size_t i = right; i > left; i--) {
          arr[i] = arr[i - 1];
        }
        arr[left] = temp;
        left++;
        mid++;
        right++;
      }
    }
  }


  // setup random number generator
  static random_device rd;
  static mt19937 rng(rd());
  // you can use uniform_int_distribution and rng to create
  // a random int in a certain range

  // Performs an in-place ascending sort of *array*
  // using the quicksort algorithm
  // *start* is the first element of the array to start sorting from
  // *end* is the end element for the elements to be sorted
  // *end* will be the length of the array - 1 for a first run
  // NOTE: Your solution should use std::swap
  // http://www.cplusplus.com/reference/algorithm/swap/
  // NOTE: Your solution MUST use a random pivot
  // TIP: It may be helpful to swap the pivot to the end,
  // sort the center of the range, and then move the pivot back to
  // the appropriate place
  //pre: the array, start, and end values must be passed in
  //post: the array that was passed in is now sorted using the quick sort
  //purpose: to create a function that can take in an array and sort it using a quick sort
  template <typename T> void quickSort(T array[], const int start, const int end) {
    // YOUR CODE HERE
    if (start >= end)//it test if start is grater than or = to end and it that is true it retunrs
      //becasue if that is true the array is most likely messed up due to their one being 1 element or more
      //more elements at the start than the end
    {
      return;
    }
      std::uniform_int_distribution<int> dist(start, end); //generates a random number in the ranfe of start and end
      int pivotIndex = dist(rng); //sets the pivotIndex = dist(rng) or in other words it sets the pivotIndex to the random number
      std::swap(array[pivotIndex], array[end]); //it calls the swap function and it swaps
    //array at the pivotIndex and the array at index end

        T pivotValue = array[end]; //it creates a vareable of t type and sets it to be the value of
    //array at the index of end
        int i = start - 1;  // it sets the i int/index to be start - 1 so that the index is the smaller element

        //it goes through elements from start to end
        for (int j = start; j < end; j++) //it sets j to be the vale of start and then it loops until j is less than
          //end and everytime it loops it adds 1 to j
          {
          //it tests if the current element(of array at index j) is <= pivot(pivotValue)
          if (array[j] <= pivotValue)
            {
            i++; //adds 1 to the index of smaller element(of i)
            std::swap(array[i], array[j]); //it calls the swap function and passes in and swaps
            //the array at index i and the array at index j
          }
        }
              std::swap(array[i + 1], array[end]); //it calls the swap function and passes in and swaps
            //the array at index i + 1 and the array at index end
            int pivotPos = i + 1; //it sets an int pivotPos to be the value of i + 1 which stores the final postion
            //of where the pivot element ended up after the swap/partitioning

            quickSort(array, start, pivotPos - 1); //it calls itself and it passes in array, start and
            //pivotpos - 1 and it does this to recursively sort the left of the subarray that was created or
            //it recursivly sorts the elements that are smaller than the pivot
            quickSort(array, pivotPos + 1, end); //it calls itself and it passes in array, pivotPos + 1, and end
            //it does this to recursively sort the right of the subarray that was created or
            //it recursivly sorts the elements that are larger than the pivot
  }


  // Performs an in-place ascending sort of *array*
  // using the insertion sort algorithm
  // *start* is the first element of the array to start sorting from
  // *end* is the end element for the elements to be sorted
  // *end* will be the length of the array - 1 for a first run
  // NOTE: You can modify your old implementation from assignment 4
  // OR if you believe yours was incorrect, email me and I will
  // send you mine, assuming you are done with assignment 4,
  // but you will still need to modify it for this assignment
  // as described below
  // NOTE: You will need to modify the implementation to only
  // sort part of the array as per the parameters of this version
  //pre: the array, start, and end values must be passed in
  //post: the array is sorted using the insertion sort
  //purpose: to create a funciton that sorts an array using insertion sort
  template <typename T> void insertionSort(T array[], const int start, const int end) {
    // YOUR CODE HERE
    if (start >= end)//it test if start is grater than or = to end and it that is true it retunrs
      //becasue if that is true the array is most likely messed up due to their one being 1 element or more
      //more elements at the start than the end
    {
      return;
    }
    for (int i = start + 1; i <= end; i++) { //loops until i is greater than or = to end and every time it loops it adds one
      //to the value of i
      T key = array[i]; //sets T key to the value of array at index i
      int j = i - 1; //sets j to be the value of i -1
      while (j >= start && array[j] > key) {//loops until either j is greater or = to start and array index j is greater than key
        array[j + 1] = array[j]; //sets array at index j+1 to the value of array at index j
        j = j - 1; //sets j to j-1
      }
      array[j + 1] = key; //sets array at index j+1 to the value of key
    }
  }

  // Performs an in-place ascending sort of *array*
  // using merge sort until there is less than 10 elements, and then
  // the insertion sort algorithm
  // *start* is the first element of the array to start sorting from
  // *end* is the end element for the elements to be sorted
  // *end* will be the length of the array - 1 for a first run
  // TIP: You can copy your implementation of merge sort in here, and
  // should be able to call the insertionSort above
  //pre: array, start, and end values must be passed in insertionSort and mergeshort must be implented
  //post: the array is sorted using the hybridsort
  //purpose: to create a function to short and array using a hybrid sort that uses other sorts to make it better
  template <typename T> void hybridSort(T array[], const int start, const int end) {
    // YOUR CODE HERE
    if (start >= end)//it test if start is grater than or = to end and it that is true it retunrs
      //becasue if that is true the array is most likely messed up due to their one being 1 element or more
      //more elements at the start than the end
    {
      return;
    }
    if (end - start + 1 < 10) //tests if the end - start + 1 is less than 10 and if it is then it calls the
      //insertionSort with the array, start, and end passed in
    {
      insertionSort(array, start, end); //calls the insertionSort function
    }
    else //if  end - start + 1 is not less than 10 then it does this other logic
      {
      int middle = start + (end - start) / 2; //it creates an int of middle and then it sets it to start + (end - start) / 2
      //and it does this to get the middle of the end and start of the subarray
      hybridSort(array, start, middle); //it calls the itself with the array, start, and middle passed in
      //and it calls itself recursively to sort the left half of the subarray
      hybridSort(array, middle + 1, end); //it calls the itself with the array, middle + 1, end passed in
      //and it calls itself recursively to sort the right half of the subarray
      
      std::inplace_merge(array + start, array + middle + 1, array + end +1);
      //it calls the inplace_merge funcion with array + start, array + middle + 1, and array + end +1 passed in
      //and it does this to merge the two sorted havles/subarrays back togther and it makes the two sorted subarrays
      //and combines them into one big sorted array
      //just a little note I looked this up using the website that was give and also some others so that I could better understand it and then the rest with it was logic and trial + error
    }


  }

}  // namespace csi281

#endif /* sort_hpp */
