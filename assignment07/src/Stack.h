//
//  Stack.h
//
//  This file defines a Stack class.
//  You SHOULD modify this file.
//  You may not add any instance variables to this class.
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

#ifndef stack_hpp
#define stack_hpp

#include "SequentialCollection.h"


using namespace std;

namespace csi281 {
  template <typename T> class Stack : public SequentialCollection<T> {
  public:

    //pre: item has to be passed in
    //post: the item is added to the top of the stack
    //purpose: it is to add an element to the top of the stack
    void push(const T &item) override
    {
      this->backingStore.push_back(item); //it pushes back the backingStore by pushing back the item passed in
      //it adds the item to the end of the backing store
    }

    //pre: nothing except the exception throws if the stack is empty
    //post: the top element is removed from the stack and it is returned unless the stack is empty, then the throws an exception
    //purpose: it is to remove and return the most recently added element from the stack
    T pop() override {
        if (this->backingStore.empty()) //it test if the backingStore is empty and if it is then it throws a runtime error
        {
          throw std::runtime_error("Can't pop back into empty Stack"); //throws a runtime error with the message
          //Can't pop back into empty Stack
        }
        T item = this->backingStore.back(); //get the top element asn sets item to that
        this->backingStore.pop_back(); //it removes the element from the backing store
        return item; //it returns the removed item
      }

    //pre: nothing except the exception throws if the stack is empty
    //post: the stack stays the same and it just returns the back of the backingStore
    //purpose: it returns a reference to the top element without removing it
    T& peek() override {
      if (this->backingStore.empty()) //it test if the backingStore is empty and if it is then it throws a runtime error
        {
        throw std::runtime_error("Can't peek into empty Stack"); //throws a runtime error with the message
        //Can't peek into empty Stack
      }
      return this->backingStore.back(); //it returns a reference to the top/bakc element of the backingStore
    }

  protected:
    //brings the backingStore from the parent class
    using SequentialCollection<T>::backingStore;

  };
}  // namespace csi281

#endif /* stack_hpp */
