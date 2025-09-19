//
//  DynamicArray.h
//
//  This file defines a Dynamic Array class.
//  You SHOULD modify this file.
//
//  Copyright 2019 David Kopec
//Aaron Archambault
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

#ifndef dynamicarray_hpp
#define dynamicarray_hpp

#include <algorithm>  // for copy(), min(), move_backward
                      // for assert()
#include <cassert>
#include "Collection.h"
#include "MemoryLeakDetector.h"

#define DEFAULT_CAPACITY 10

using namespace std;

namespace csi281 {
  template <typename T> class DynamicArray : public Collection<T> {
  public:
    // Initialize the dynamic array with a starting capacity
    DynamicArray(int cap = DEFAULT_CAPACITY) {
      capacity = cap;
      backingStore = new T[capacity];
    }

    // Erase the dynamic array
    ~DynamicArray() { delete[] backingStore; }

    // Find the index of a particular item
    // Return -1 if it is not found>
    //pre: t item must be passed in and the dynamic array must exits
    //post: if it finds item it will return the index that it is at and if it does not it will return -1
    //purpose: to find the index of a particular item
    int find(const T &item) {
      for (int i = 0; i < count; i++) { //it loops until i is not less than count and every time it loops is adds one to i
        if (item == backingStore[i]) { //it test if item is the same as the value of backingStore at the index of i and if that is true
          //it returns i
          return i;
        }
      }
    return -1; //returns -1 if it can not find the item
    }

    // Get the item at a particular index
    //pre: the dynamic array should exist, and the int index has to be passed in
    //post: it will return the backingStore at the index that was passed in if it passes the assert that is
    //purpose: to get the item at a particualr index
    T &get(int index) {
      assert(index >= 0 && index < this->count); //calls the assert with the infromation of index >= 0 and index < count passed in
      return backingStore[index];//returns the value of backingStore at the index index
    }

    // Insert at the beginning of the collection
    // Using setCapacity() if we are too small before
    // inserting
    // Hint: May want to use moveDownFrom()
    //pre:dynamic array must exist and the item must be passed in and also movedownfrom must be coded
    //post: it might increase the capaicty and or it will movedownfrom the 0 index and place the item at that place
    //and incease the count
    //purpose:to insert an item at the beginging
    void insertAtBeginning(const T &item) {
      if (this->count >= this->capacity) {//test if count is grater or = to the capacity and if it is then
        //it calls setCapacity function that sets the capacity with capaticy times 2 passed into the function
        setCapacity(capacity * 2);
      }
      moveDownFrom(0); //calls the moveDownFrom function and passes in 0
      backingStore[0] = item; //sets the value of backingStore at the index 0 to the value of item
      this->count++; //adds one to the value of count
    }

    // Insert at the end of the collection
    // Using setCapacity() if we are too small before
    // inserting
    //pre: the dynamic array has to exits and the item has to be passed in
    //post: it may increase the capacity and or then set the next backingStore to the item and increases the count
    //purpose: to insert the item at the end
    void insertAtEnd(const T &item) {
      if (this->count >= this->capacity) {//test if count is grater or = to the capacity and if it is then
        //it calls setCapacity function that sets the capacity with capaticy times 2 passed into the function
        setCapacity(capacity * 2);
      }
      backingStore[this->count] = item; //sets the value of backingStore at the index of count to the value of item
      this->count++;//add one to the value of count
    }

    // Insert at a specific index
    // Using setCapacity() if we are too small before
    // inserting
    // Hint: May want to use moveDownFrom()
    //pre: movedownfrom has to be coded/exist, the dynamic array must exist, and item and index must be passed in
    //post: the capacity may be inceassed if it is to small and then it will move down from the index and then it will
    //set the backingStore at index index to the item and then increases the count
    //purpose: to instert at a specific index
    void insert(const T &item, int index) {
      if (this->count >= this->capacity) {//test if count is grater or = to the capacity and if it is then
        //it calls setCapacity function that sets the capacity with capaticy times 2 passed into the function
        setCapacity(capacity * 2);
      }
      assert(index >= 0 && index <= this->count);//calls the assert with the infromation of index >= 0 and index <= count passed in
      moveDownFrom(index); //calls the moveDownFrom with index passed in
     backingStore[index] = item;//sets the value of backingStore at the index of index to the value of item
      this->count++;//adds one to the value of count
    }

    // Remove the item at the beginning of the collection
    //pre: the dynamic array has to exist
    //post: it will move to the start and get rid of it and then subract form the count
    //purpose: to revmove an item at the beginning
    void removeAtBeginning() {
      assert(this->count > 0);//calls assert and passes in count > 0
      move(backingStore + 1, backingStore + count, backingStore); //calls the move operation and it passes in the backingStore + 1, backingStore + count
      //and backingStore so it gets the range with backingStore + 1, backingStore + count and the it gets the destinaiton of backingStore and shifts all elements one postion
      //also this move function I think it intial came from auto fill, but then I looked it up to see what it did so that
      //I understood its implentation better
      this->count--; //subtracts one from the count
    }

    // Remove the item at the end of the collection
    // Hint: This might be very simple.
    //pre: the dynamic array has to exist
    //post: it removes one from the end and removes 1 from the count
    //purpose:to remove an item at the end of the collection
    void removeAtEnd() {
      assert(this->count > 0);//calls assert and passes in count > 0
      this->count--; //subtracts one form the count
    }

    // Remove the item at a specific index
    // Hint: Can be done by a combination of moving items
    // down and removing the starting beginning element
    //pre: the dynamic array has to exist and index must be passed in
    //post: it moves to the index passed in, and then it moves it to the "end/removes it" and then it subtracts the count
    //purpose: to remove an item at a specific index
    void removeAt(int index) {
      assert(index >= 0 && index < this->count);//calls the assert with the infromation of index >= 0 and index <= count passed in
      move(backingStore + index + 1, backingStore + count, backingStore + index);//calls the move operation and it passes in the backingStore + index + 1,
      //backingStore + count and backingStore + index so it gets the range with backingStore + index + 1, backingStore + count and
      ////then it gets the destinaiton of backingStore + index and shifts all elements index positions
      this->count--;//subtracts one from the value of count
    }

    // Change the capacity of the dynamic array
    // If it becomes less than count, just discard excess
    //pre: the dynamic array has to exist and int cap is passed in
    //post: it returns if the cap == the capcityc but if not it changes the capacity to be cap
    //purpose:to change the capacity of the dynaimc array
    void setCapacity(int cap) {
      assert(cap >= 0);  // can't have negative capacity
      // don't do anything if we're already correct
      if (cap == capacity) { //test if cap is = to capcity and if it is it returns
        return;
      }

      int numberToCopy = min(cap, count); //sets the numberToCopy to the value of min with cap and count passed in

      T *destination = new T[cap]; //makes T*destiation the value of new T at cap index

      copy(backingStore, backingStore + numberToCopy, destination); //calls copy with backingStore, backingStore + numberToCopy,
      //and destionation passed in
      delete[] backingStore; //deletes arrays backingStore
      backingStore = destination; //sets backingStore to the value of destination
      capacity = cap; //sets capacity to the value of cap
      if (capacity < count) { //tests if capacity is less than count and if it is then it sets count to the value of capacity
        count = capacity;
      }
    }

    // Return the current capacity
    int getCapacity() { return capacity; }

  protected:
    using Collection<T>::count;

  private:
    int capacity;
    int growthFactor = 2;
    T *backingStore;

    // Shift all of the items in backingStore starting at
    // index down by 1 place
    // Make sure you have capacity available to do this before
    // running this method
    void moveDownFrom(int index) {
      move_backward(backingStore + index, backingStore + count, backingStore + count + 1);
    }
  };

}  // namespace csi281

#endif /* dynamicarray_hpp */
