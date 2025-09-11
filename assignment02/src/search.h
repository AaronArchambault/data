//
//  search.h
//
//  Functions for doing linear search and binary search on an
//  arbitrary array.
//  You SHOULD modify this file.
//  Aaron Archambault
//  Copyright 2019 David Kopec
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

#ifndef search_hpp
#define search_hpp

#include "MemoryLeakDetector.h"

namespace csi281 {

  // Returns the first location of the found key
  // or -1 if the key is never found
  template <typename T> int linearSearch(T array[], const int length, const T key) {
    //this loops until i is grater than length/the length that was passed in and everytime it loops
    //it checks to see if the array value of the i index is the same value as key/the thing that is
    //being looked for and if that is true it return i but if it is not true it add 1 to the value of
    // i until i is grater than length and if that is true and it never finds and arry i index that is
    //the value of key it returns -1
    for (int i = 0; i < length; i++) {
      if (array[i] == key) {
        return i;
      }
    }
    return -1;
  }

  // Returns the first location of the found key
  // or -1 if the key is never found; assumes a sorted array
  template <typename T> int binarySearch(T array[], const int length, const T key) {
    //it creates a low and high int that are set to 0 and the length passed in - 1
    int low = 0;
    int high = length - 1;
//it loops while low is less than or = high and everytime it loops it create a middle int and sets it to
    //the value of low+high / 2 to find the middle vale of the "values" then it tests if the array of middle
    //index is the same as the value of key and if it is true then it returns middle, but if it is false it
    //check to see if array middle index is less than the key value and if that is ture it sets the value of low
    //to be the middle value + 1, but if it is false then it knows that array middle index is grater than key value so
    //it sets the high value to be middle - 1 and if it can not find when array middle index = key/when the loop ends
    //it returns -1 to show that it could not find it
    while (low <= high) {
      int middle = (low + high) / 2;

      if (array[middle] == key) {
        return middle;
      }
      else if (array[middle] < key) {
        low = middle + 1;
      }
      else {
        high = middle - 1;
      }
    }
    return -1;
  }

}  // namespace csi281

#endif /* search_hpp */
