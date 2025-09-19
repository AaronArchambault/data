//
//  LinkedList.h
//
//  This file defines a Linked List class.
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

#ifndef linkedlist_hpp
#define linkedlist_hpp

#include "MemoryLeakDetector.h"
#include "Collection.h"
#include <cassert>//added

using namespace std;

namespace csi281 {
  template <typename T> class LinkedList : public Collection<T> {
    class Node;  // forward declaration
  public:
    // Erase all the nodes
    ~LinkedList() {
      Node *current = head;
      while (current != nullptr) {
        Node *last = current;
        current = current->next;
        delete last;
      }
      head = nullptr;
      tail = nullptr;
      count = 0;
    }

    // Find the index of a particular item
    // Return -1 if it is not found
    //pre: the linked list has to exist and item has to be passed in
    //post: if the item does not exist it returns -1, but if it does exist in the linked list then it will find it
    //and return its index
    //purpose: to find the index of an item
    int find(const T &item) {
      Node *current = head; //creates a node of a pointer current that is set to the value of head
      int index = 0; //creates an int indexs and sets it to be 0
      while (current != nullptr) { //it keeps looping until current does not = nullptr so until it reaches the end
        if (current->data == item) { //everytime it loops it tests if current next data is the same as the item
          return index; //if it is true, then it returns the index
        }
        current = current->next; //it set current to the value of the current next to the current current
        index++; //it adds one to the value of index
      }
      return -1; //it returns -1 if it can not find the item
    }

    // Get the item at a particular index
    //pre: the linked list has to exist and index is passed in
    //post: it returns the data/item of the index that was passed in
    //purpose: to get the item of a particualr index
    T &get(int index) {
      assert(index < count);  // can't insert off end
      assert(index >= 0);     // no negative indices

      Node *current = head;//creates a node of a pointer current that is set to the value of head
      for (int i = 0; i < index; i++) { //loops until i is not less than index and it adds 1 to i everytime it loops
        current = current->next; //everytime it loops it sets current to the vaule of the next current value of current
      }
      return current->data; //it returns current->data/ the value of that
    }

    // Insert at the beginning of the collection
    //pre: the linked list has to exist and item is passed in
    //post: it adds one to the front of the linked list and adds one to the count
    //purpose: to insert an item at the beginning of the linked list
    void insertAtBeginning(const T &item) {
      Node *newNode = new Node(item); //creates a node of a pointer of newNode that is set to the value of a new node with item passed in
      newNode->next = head;//then it sets the next value in the newNode to be the value of head
      head = newNode; //then it sets head to be the value of newNode

      if (count == 0) {//it tests if count is 0 and if it is then it sets tail to the value of newNode
        tail = newNode;
      }
      count++;//it adds one to the value of count
    }

    // Insert at the end of the collection
    //pre: the linked list has to exist and item is passes in
    //post: it goes to the end and adds a new item to the end of the list and increases the count by 1
    //purpose: to insert an item at the end of the linked list
    void insertAtEnd(const T &item) {
      Node *newNode = new Node(item);//creates a node of a pointer of newNode that is set to the value of a new node with item passed in

      if (head == nullptr) { //it tests if head is = to nullptr and if it is then it sets head and tail to be the value of newNode
        head = newNode;
        tail = newNode;
      }
      else {//if head is not = to nullptr then it sets the value next to tail to newNode and then it sets the value of tail to be the value of newNode
        tail->next = newNode;
        tail = newNode;
      }
     count++;//adds one to the value of count
    }


    // Insert at a specific index
    //pre: the linked list has to exist item and index are passed in, and insertAtBeginning insertAtEnd are implented
    //post: if index is 0 it adds to the beginning and if index and count are the same then it adds to the end
    //or it finds the location of the index passed in and inserts the item
    //purpose: to insert at a specific index
    void insert(const T &item, int index) {
      assert(index <= count);  // can't insert off end
      assert(index >= 0);      // no negative indices
      if (index == 0) {//tests if the value of index is 0 and if it is then it calls the insertAtBegining fuction and passes in item and then returns
        insertAtBeginning(item);
        return;
      }
      if (index == count) { //it test if the index is = to count then it calls the insertAtEnd funciton and passes the item and then it returns
        insertAtEnd(item);
        return;
      }
      int location = 0; //sets the location int to be 0
      for (Node *current = head; current != nullptr; current = current->next) { //loops untill curtent = a nullptr and everytime it loops it sets curent to the value of the
        //next current
        if (location == (index - 1)) { //test if the location is the same as the index -1 and if it is then it sets a node of *after to be the value of
          //the current next value and then it sets the node of *thing to the value of new Node with item passed in and then it sets the value of the next current to the
          //value of thing and then it sets the value of the next thing to the value of after and then it adds 1 to the value of count and then it returns
          Node *after = current->next;
          Node *thing = new Node(item);
          current->next = thing;
          thing->next = after;
          count++;
          return;
        }
        location++; //it adds one to the value of location
      }
    }

    // Remove the item at the beginning of the collection
    //pre: the linked list has to exist item
    //post: it removes and deletes the item at the beginning of the linked list and removes one from the count
    //purpose: to remove the item at the beginning of the collection
    void removeAtBeginning() {
      assert(count > 0);
      Node *current = head;//creates a node of a pointer current that is set to the value of head
      head = head->next; //sets the value of head to be the value of the next head value

      if (head == nullptr) { //tests if the value of head = nullptr and if it does then it sets tail to be nullptr
        tail = nullptr;
      }
      delete current; //deletes the current
      count--; //takes one away from the count
    }

    // Remove the item at the end of the collection
    //pre: the linked list has to exist
    //post: it removes and deletes the last item at the end by moving to the end which should be nullptr and -1 from count
    //purpose: to remove an item at the end of the linked list
    void removeAtEnd() {
      assert(count > 0);
      if (count == 1) { //tests if count is 1 and if it is then it deletes head and then it sets head and tail to be nullptr
        delete head;
        head = nullptr;
        tail = nullptr;
      }
      else {//if count it not 1 then it makes node *current and sets it to the value of head
        Node *current = head;
        while (current->next != tail) { //it loops unitl the next current = tail
          //every time it loops it sets current to the value of the next current
          current = current->next;
        }
        delete tail;//deletes tail
        tail = current; //sets tail to the value of current
        tail->next = nullptr; //sets the next value next tail to be nullptr
      }
      count--; //subtracts one from the count
    }

    // Remove the item at a specific index
    //pre: the linked list has to exist and index is passed in and removeAtBeginning and removeAtEnd are impleneted
    //post: it finds the index that was passed and then it moves to that index and deletes it and adds to the locaiton and removes form the count
    //purpose: to remove the item at a specific index
    void removeAt(int index) {
      assert(index >= 0);
      assert(index < count);
      assert(count > 0);
      if (index == 0) {//tests if the index is 0 and if it is then it calls removeAtBeginning and then returns
        removeAtBeginning();
        return;
      }
      if (index == (count - 1)) { //tests if index = count -1 and if it does then it calls the removeat end function and returns
        removeAtEnd();
        return;
      }

      int location = 0; //creates int location and sets it to 0
      for (Node *current = head; current != nullptr; current = current->next) { //loops until current - nullprt and every time it loops it sets current to the value of
        //the next current
        if (location == (index - 1)) { //tests if the location = index -1 and if it does then it makes node *after and it sets it to the next next current value
          //then it deletes the current next value and then it subtracts 1 from the count and returns
          Node *after = current->next->next;
          delete (current->next);
          current->next = after;
          count--;
          return;
        }
        location++; //adds one to the location value
      }
    }

  protected:
    using Collection<T>::count;

  private:
    Node *head = nullptr;
    Node *tail = nullptr;

    class Node {
      friend class LinkedList;

    public:
      Node(const T &thing) : data(thing), next(nullptr){};

    private:
      T data;
      Node *next;
    };
  };
}  // namespace csi281

#endif /* linkedlist_hpp */
