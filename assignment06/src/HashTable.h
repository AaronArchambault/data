//
//  HashTable.h
//
//  This file defines a Hash Table class.
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

#ifndef hashtable_hpp
#define hashtable_hpp

#include <algorithm>   // find_if(), remove_if()
#include <functional>  // for hash()
#include <iostream>
#include <list>
#include <optional>
#include <utility>  // for pair

#include "MemoryLeakDetector.h"

#define DEFAULT_CAPACITY 10
#define MAX_LOAD_FACTOR 0.7

using namespace std;

namespace csi281 {
  template <typename K, typename V> class HashTable {
  public:
    // Initialize the array with a starting capacity
    HashTable(int cap = DEFAULT_CAPACITY) {
      if (cap < 1) {
        cap = 1;
      }  // cannot have < 1 capacity
      resize(cap);
    }

    // Erase the array
    ~HashTable() { delete[] backingStore; }

    // Put the key value pair in the hash table
    // If *key* is already present, change its
    // associated value to *value*
    // If the load factor exceeds the MAX_LOAD_FACTOR
    // then resize the table
    // TIP: Be careful to get a reference to the list at each
    // location in the backing store, so you're modifying
    // the original and not a copy
    //pre: the k key and v value must be passed in and the hash must "exist" also resize has to be implemented
    //post:it puts the k key valuing in the hash table  and if the load factor exceeds the max load factor it rizes the table
    //purpose: to create a fuction that puts the key value pair in the hash table and if the *key* is already there then it changes its
    //associated value to *value* and if the load factor exceeds the MAX_LOAD_FACTOR to resize the table
    void put(const K key, const V value) {
      // YOUR CODE HERE
      size_t index = hashKey(key); //sets size_t index to the value of hashKey(key) and that gets the buckets index for the key
      //that the key is using for the hash
      auto& bucket = backingStore[index]; //it sets the auto ref buket to the value of backingSotre at index index
      //it does that to get a refereance to the bucket in/of list at the index and then it uses the refrecne to modify the original and not a copy

      for (auto& pair : bucket) //it loops and check the bucket to see if their is a key that already exists in the bucket
        {
        if (key == pair.first) //it test if it found the key and updates based on that
          {
          pair.second = value; //if it found it then it sets pair.second to be the value of value
          return; //returns
          }
      }
      bucket.emplace_back(key, value); //if it did not find the key then it adds a new key value pair to the end of the bucket
      //the emplace_back I think came either from auto fill and or it is from when I looked up hash table and fuctions to
      //see what I could do with them
      count++; //it adds one to the count so that the count of the list is increased by one

      float loadFactor = getLoadFactor(); //sets loadfactor to theh value of getloadfactor and then it checks if
      //that loadfactor is grater than the max load factor and if it is then it calls resize to resize the bucket
      if (loadFactor > MAX_LOAD_FACTOR)
        {
        resize(capacity * growthFactor); //calls the resize fuction and passes in capacity times growthFactor
        }

    }

    // Get the item associated with a particular key
    // return an empty optional (nullopt) if the item is not found
    // and returns an optional with the value associated with key
    // if key is found
    // TIP: read the documentation on optional
    // https://en.cppreference.com/w/cpp/utility/optional
    // TIP: Be careful to get a reference to the list at each
    // location in the backing store, so you're modifying
    // the original and not a copy
    //pre: the k key has to be passes in
    //post: the hash tancle is not changed the item is just retrived
    //purpose: it gets the values of it by the keys without chaning the table
    optional<V> get(const K &key) {
      // YOUR CODE HERE
      size_t index = hashKey(key); //sets size_t index to the value of hashKey(key) and that gets the buckets index for the key
      //that the key is using for the hash
      auto& bucket = backingStore[index]; //it sets the auto ref buket to the value of backingSotre at index index
      //it does that to get a refereance to the bucket in/of list at the index and then it uses the refrecne to modify the original and not a copy

      for (auto& pair : bucket) //it loops looking through the bucket for the key
        {
        if (key == pair.first) //tests if it finds the key and if it does then it returns the value in the value of the key
          {
          return pair.second; //reutrns the associated value of the key
          }
      }
      return nullopt; //returns a null if it can not find the key

    }

    // Remove a key and any associated value from the hash table
    // TIP: I suggest using remove_if()
    // https://en.cppreference.com/w/cpp/algorithm/remove
    // TIP: Be careful to get a reference to the list at each
    // location in the backing store, so you're modifying
    // the original and not a copy
    //pre: k key has to be passed in
    //post: the key value is removed from the table if it is their and count is lowered
    //purpose: to create a function that removes from the hash/table
    void remove(const K &key) {
      // YOUR CODE HERE
      size_t index = hashKey(key); //sets size_t index to the value of hashKey(key) and that gets the buckets index for the key
      //that the key is using for the hash
      auto& bucket = backingStore[index]; //it sets the auto ref buket to the value of backingSotre at index index
      //it does that to get a refereance to the bucket in/of list at the index and then it uses the refrecne to modify the original and not a copy

      size_t last = bucket.size(); //it sets size_t last to be the value of bucket.size and it does this to store the
      //original size to help with the removal

      bucket.remove_if([&key](const pair<K, V>& pair) //it removes all of the pairs with matching keys from the bucket
        //and it gets keys by the rfeereances and checks them and thier first element
      {
        return pair.first == key; //returns if the pair.firt is the same as the key
      });

      size_t size = bucket.size(); //it sets size_t size to be the value of bucket.size so that it can check if something
      //was removed
      if (size < last) //checks if size is less than last and if it is then something was removed so it subbtracts one from count
        {
        count--; //subtracts 1 from the value of count
        }
    }

    // Calculate and return the load factor
    float getLoadFactor() { return ((float)count) / ((float)capacity); }

    // Get the count
    int getCount() { return count; }

    // Get the capacity
    int getCapacity() { return capacity; }

    // Print out the contents of the hash table
    void debugPrint() {
      for (int i = 0; i < capacity; i++) {
        cout << i << ":";
        for (auto p : backingStore[i])
          {
          cout << " -> (" << p.first << ", " << p.second << ")";
          }
        cout << endl;
      }
    }

  private:
    int capacity = 0;
    int growthFactor = 2;
    int count = 0;
    hash<K> key_hash;
    list<pair<K, V>> *backingStore = nullptr;

    // Shift all of the items in backingStore into a
    // new backing store of size cap, or create
    // the backingStore for the first time
    //pre: the cap has to be passed in and cap > 0
    //post: the capacity is updated and all items are rehased into new backing store
    //purpose: to resize the hash table to help maintain the preformance
    void resize(int cap) {
      // YOUR CODE HERE
      list<pair<K, V>>* oldhash = backingStore; //it sets list<pair<K, V>>* oldhash to the value of backingStore
      //to save the pointer to the old backing store and its capacity
      int oldcapacity = capacity; //sets the oldcapacity to the value of capacity

      capacity = cap; //sets the value of capacity to the value of cap and it does this to update the cpacity
      //and create the new backing store
      backingStore = new list<pair<K, V>>[capacity]; //creates the new backingStore and sets it to the value of
      //new list<pair<K, V>>[capacity]

      count = 0; //sets count to 0/resets the count so that it can be changed later

      if (oldhash != nullptr) //tests if oldhash is not null and this is to check if there was an old backing store
        //then it rehashes all of the old items
        {
        for (int i = 0; i < oldcapacity; i++) //it loops through the list by testing if i is less than oldcapcity
        //and adding 1 to i every time it loops and it goes throgh the bucket and the old backing
          {
          for (auto &pair : oldhash[i]) //it loops through each of the key-values pairs and rehashes them in the new capacity
            {
            put(pair.first, pair.second);
            }
        }
        delete[] oldhash; //frees up the old backing store from the memory
      }
    }

    // hash anything into an integer appropriate for
    // the current capacity
    // TIP: use the std::hash key_hash defined as a private variable
    size_t hashKey(const K &key) { return key_hash(key) % capacity; }
  };

}  // namespace csi281

#endif /* hashtable_hpp */
