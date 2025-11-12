//
//  bst.h
//
//  Defines a class for a binary search tree.
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

#ifndef bst_hpp
#define bst_hpp

#include <list>
#include <optional>
#include <random>

#include "MemoryLeakDetector.h"

using namespace std;

namespace csi281 {

  template <typename T> class BST {
  public:
    // *Node* represents one node in the tree
    struct Node {
      Node(T k, Node *l, Node *r) : key(k), left(l), right(r) {}
      T key;
      Node *left;
      Node *right;
    };

    // Delete a node and all of its children
    void deleteHelper(Node *node) {
      if (node == nullptr) {
        return;
      }
      deleteHelper(node->left);
      deleteHelper(node->right);
      delete node;
    }

    // Delete all nodes
    ~BST() { deleteHelper(root); }

    // Add a new node to the tree with *key*
    // Make sure to insert it into the correct place
    // NOTE: We are allowing duplicates, so, <= and >, or < and >=
    // for traversing left and right should be used
    // TIP: If the tree is empty, remember that you
    // need to initialize root
    void insert(T key) {
      // YOUR CODE HERE
      //it checks if the tree is empty and if it is then it creates a root node
      if (root == nullptr) //checks if the root is null and if it is then it crates the new root node
        //and adds to the count
        {
        root = new Node(key, nullptr, nullptr);
        count++;
        return;
      }
      //it starts at the root and goes through/down the tree
      Node *current = root; //sets the node pointer current to be the value of root
      while (true) //loops while it is true
        {
        if (key <= current->key) //it checks if the key is less than or = to the current key so that if the key is
            //less than or = to the current it goes left
          {
          //move left
          if (current->left == nullptr) //it checks if the current left is null so that if the left child is empty it inserts the new node here
            {
            current->left = new Node(key, nullptr, nullptr);
            count++; //adds one to the count
            return;
          }
          current = current->left; //it sets current to be the current left so that it moves to the left child and continues
        }
        else //if the key is grater than the current then it goes right
          {
          //go right
          if (current->right == nullptr) //it checks if the current right is null so that if the right child is empty
          //it inserts a new node there
            {
            current->right = new Node(key, nullptr, nullptr); //it inserts the new node at the current right
            count++; //it adds one to the count
            return;
          }
          current = current->right; //it seets current to the value of current right so that it moves to the right
          //child and continues
        }
      }
    }

    // Do a search through the tree and return
    // whether or not it contains *key*
    bool contains(const T &key) {
      // YOUR CODE HERE
      Node *current = root; //it sets the node pointer current to the root so that it stats at the root
      while (current != nullptr) //it loops while the current is not null so that it moves down the tree untill
        //it finds the key or reaches a null node
        {
        if (current->key == key) //checks if the current key is the same as the key so it checks if it is hte key
          {
          return true; //if the key is found it returns true
        }
        else if (key < current->key) //it checks if the key is less than the current key so that it can see if the key
          //is smaller so it can search the left subtree
          {
          current = current->left; //sets the current to tbe the currents left so that it searches the left subtree
        }
        else// if the key is larger it searches the right subtree
          {
          current = current->right; //sets current to the value of curent right to search the right sub tree
        }
      }
      return false; //it returns false if it can not find the key
    }

    // Helper for inOrderWalk() to call for entire bst
    void inOrderWalk(list<T> &accumulated) { inOrderWalk(accumulated, root); }

    // Walk through the entire tree in ascending order, starting
    // from *current*, and accumulate the values in the
    // list *accumulated*
    // TIP: See page 288 of Chapter 12 of Introduction to Algorithms
    void inOrderWalk(list<T> &accumulated, Node *current) {
      // YOUR CODE HERE
      if (current == nullptr) //it checks if current is null so that if the current node is null it returns
      {
        return; //returns
      }
      //it recursively visits the left subtree first by calling inOrderWalk with accumulated and current left passed in
      inOrderWalk(accumulated, current->left);
      //it visits the current node adds to list it calls accumulated and pushes it back using the current key
      accumulated.push_back(current->key);
      //it recursivly visists the right subtree last by calling inOrderWalk and passing in the accumlated and the current right
      inOrderWalk(accumulated, current->right);

    }

    // Find the minimum key in the tree
    // If the tree is empty, return nullopt
    optional<T> minimum() {
      // YOUR CODE HERE
      if (root == nullptr) //checks if the root is null so that if the empty tree has no minimum it checks that and returns null
      {
        return nullopt; //returns null
      }

      Node *current = root; //it sets the pointer current to the value of root and so that the minimum is the left most
      //node and it keeps goinh left unitll it can not
      while (current->left != nullptr) //it loops while the current left is not null so that it keeps going untill it can't
      {
        current = current->left; //it sets current to be the current left
      }
      return current->key; //it returns the key of the left most node
    }

    // Find the maximum key in the tree
    // If the tree is empty, return nullopt
    optional<T> maximum() {
      // YOUR CODE HERE
      if (root == nullptr) //it checks if the root is null so that the empty tree has not maxium it returns null
      {
        return nullopt; //returns null
      }
      Node *current = root; //it sets the current pointer to be the value of root so that the maximum is hte rightmost
      //node and os it keeps going right untill it can not
      while (current->right != nullptr) //it keeps looping while the current right is not null so that it keeps going right untill it can not
        {
        current = current->right; //sets current to be the current right
      }
      return current->key; //it returns the key of the right most node
    }

    // How many nodes are in the tree?
    int getCount() { return count; }

  private:
    Node *root = nullptr;
    int count = 0;
  };

}  // namespace csi281

#endif /* bst_hpp */
