//
//  util.cpp
//
//  Implementation of Timing Tests
//  You SHOULD modify this file.
//
//  Copyright 2019 David Kopec
//  Aaron Archambault
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

#include "util.h"

#include <algorithm>
#include <iostream>
#include <random>

#include "search.h"

using namespace std;

namespace csi281 {

  // Returns a new int array of *length* and filled
  // with numbers between *min* and *max*
  // Suggest using the facilities in STL <random>

  //pre: the randomIntArray must exist, and the length, min, and max must be passed in
  //post: it will return the populated array that it made
  //purpose: to generate an array and populate it with random numbers that are in the min and max
  //ranges that are given
  int *randomIntArray(const int length, const int min, const int max) {
    //creates the array that will be on the heap
    int* array = new int[length];

    //calls and seeds the random number generator and gives it the range of the min and max values
      random_device rd;
      mt19937 gen(rd());
      uniform_int_distribution<> dist(min, max);
//loops until i is greater than length, and every time it loops it generates a random number and
    // it sets the value of the array of index i to that value and then it loops until i is greater than
    //length make it so that every index in the array of length is populated then when it exits the
    //loop it returns the array
    for (int i = 0; i < length; i++) {
      array[i] = dist(gen);
    }
    return array;
  }

  // Finds the speed of linear versus binary search
  // in a random int array of *length* size
  // by running *numTests* and averaging them
  // Returns a pair indicating the average time it took
  // to do linear search and binary search in nanoseconds
  // Linear search should be first in the pair, and binary search
  // should be second
  //
  // Suggest using the facilities in STL <chrono>
  // For example, you can start a timer using
  // using namespace std::chrono;
  // auto start = duration_cast< nanoseconds >(system_clock::now().time_since_epoch()).count();
  // and stop a timer using
  // auto end = duration_cast< nanoseconds >(system_clock::now().time_since_epoch()).count();
  // start, end will be results in nanoseconds

  //pre: the linear search, binary search, and int *randomIntArray have to exist and be coded right
  // also the length and numTests must be passed in
  //post: it will calculate the average speed of the linear search and binary search, and return
  //the averages back as a pair
  //purpose: to calculate the average speed of the linear search and binary search, and return
  //the averages
  pair<nanoseconds, nanoseconds> arraySearchSpeed(const int length, const int numTests) {
// calls the randomintarray and sets the test array and test key to that value created/gotten
    int *testArray = randomIntArray(length, 0, length);
    int *testKeys = randomIntArray(numTests, 0, length);

    using namespace std::chrono;

    // Do numTests linear searches and find the average time
    // Put the result in a variable linearSearchSpeed

    // sets the linearStart to the value of duration_cast
    auto linearStart  = duration_cast< nanoseconds >(system_clock::now().time_since_epoch()).count();

    //loops until i is greater than the numTests and every time it loops it sets the result to be the
    //value it gets from the linearSearch and its job is to run for all the num of test to see how long
    //sorting is after i is greater than numTests it sets linerEnd to the duration_cast then it sets
    //linearSearchSpeed to the value of linearEnd - linearStart / numTests
    for (auto i = 0; i < numTests; i++) {
    int result = linearSearch(testArray, length, testKeys[i]);
    }
    auto linearEnd = duration_cast< nanoseconds >(system_clock::now().time_since_epoch()).count();
    auto linearSearchSpeed = (linearEnd - linearStart) / numTests;
    // Do numTests binary searches and find the average time
    // Put the result in a variable binarySearchSpeed

    //sorts the testarray to be in the right order so that binary search can work
    sort(testArray, testArray + length);

    // sets the binaryStart to the value of duration_cast
    auto binaryStart  = duration_cast< nanoseconds >(system_clock::now().time_since_epoch()).count();

    //loops until i is greater than the numTests, and every time it loops it sets the result to be the
    //value it gets from the binarySearch, and its job is to run for all the number of test to see how long
    //sorting is after i is greater than numTests, it sets binaryEnd to the duration_cast, then it sets
    //binarySearchSpeed to the value of binaryEnd - binaryStart / numTests
    for (auto i = 0; i < numTests; i++) {
      int result = binarySearch(testArray, length, testKeys[i]);
    }

    auto binaryEnd = duration_cast< nanoseconds >(system_clock::now().time_since_epoch()).count();
    auto binarySearchSpeed = (binaryEnd - binaryStart) / numTests;
    //it then frees up the memory in the heap by deleting the test array and test keys

    //delete testArray;
    //delete testKeys;
    delete[] testArray;
    delete[] testKeys;

    return pair<nanoseconds, nanoseconds>(linearSearchSpeed, binarySearchSpeed);
  }
}  // namespace csi281
