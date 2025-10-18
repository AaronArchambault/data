//
//  test.cpp
//
//  Tests to prove your code works.
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

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#define SECTION(name) DOCTEST_SUBCASE(name)
#undef TEST_CASE
#define TEST_CASE(name, tags) DOCTEST_TEST_CASE(tags " " name)
using doctest::Approx;

#include <string>

#include "Queue.h"
#include "Stack.h"

using namespace std;
using namespace csi281;

TEST_CASE("Queue Tests", "[queue]") {
  SECTION("Queue w/ int tests") {
    //it creates an empty queue of ints
    Queue<int> q1 = Queue<int>();
    // Ensure that push(), pop(), and peek()
    // work properly in concert with getCount()
    // and remove()
    //test that the new queue is empty
    REQUIRE(q1.getCount() == 0);
    //test the first push and adds 10 to the queue
    q1.push(10);
    REQUIRE(q1.getCount() == 1);
    REQUIRE(q1.peek() == 10); //test to see if the front is 10 like is should be

    //tests the second push and adds 20 to the queue
    q1.push(20);
    REQUIRE(q1.getCount() == 2);
    REQUIRE(q1.peek() == 10); //checks/tests if the front element is still 10 like it should be

    //test a third push and adds 30 to the queue
    q1.push(30);
    REQUIRE(q1.getCount() == 3);
    REQUIRE(q1.peek() == 10); //checks/test if the front is still 10 like it should be

    //test the first pop and it should remove 10
    REQUIRE(q1.pop() == 10);
    REQUIRE(q1.getCount() == 2);
    REQUIRE(q1.peek() == 20); //now it checks and test if the front is 20 like it now should be after the pop

    //tests the second pop and it should remove the 20
    REQUIRE(q1.pop() == 20);
    REQUIRE(q1.getCount() == 1);
    REQUIRE(q1.peek() == 30); //it checks/tests if the front is now 30 like it should be

    //it adds/pushes 3 elements with two 20's as duplicates
    q1.push(20);
    q1.push(20);
    q1.push(30);
    REQUIRE(q1.getCount() == 4); //test to see if it has a count of 4 that should be 30, 20, 20, 30

    //it tests the remove() and it should remove all the instances of 20
    q1.remove(20);
    REQUIRE(q1.getCount() == 2); //now it tests that it should have a count of 2 and only be 30, 30
    REQUIRE(q1.peek() == 30); //it tests to see if the frount is still 30 like it should be

    //tests a push after the remove
    q1.push(40);
    REQUIRE(q1.getCount() == 3);
    REQUIRE(q1.peek() == 30); //tests if the front is still 30 like it should be
  }

  SECTION("Queue w/ string tests") {
    //creates an empty queue of strings
    Queue<string> q2 = Queue<string>();
    // Ensure that push(), pop(), and peek()
    // work properly in concert with getCount()
    // and remove()
    //it tests that the new queue is empty
    REQUIRE(q2.getCount() == 0);

    //it tests the first push and adds "first" to the queue
    q2.push("First");
    REQUIRE(q2.getCount() == 1);
    REQUIRE(q2.peek() == "First"); //it checks/tests if the front is first like it should be

    //it tests the second push and adds "second" to the queue
    q2.push("Second");
    REQUIRE(q2.getCount() == 2);
    REQUIRE(q2.peek() == "First"); //it check/tests if the front is still "first" like it should be

    //it test the third push and adds "third" to the queue
    q2.push("Third");
    REQUIRE(q2.getCount() == 3);
    REQUIRE(q2.peek() == "First"); //it tests if the front is still "first" like it should be

    //it tests the first pop and it should remove "first"
    REQUIRE(q2.pop() == "First");
    REQUIRE(q2.getCount() == 2);
    REQUIRE(q2.peek() == "Second"); //it checks/tests if "second" is at the front like it should be

    //it tests the second pop and it should remove the "second"
    REQUIRE(q2.pop() == "Second");
    REQUIRE(q2.getCount() == 1);
    REQUIRE(q2.peek() == "Third"); //it checks/test if third is at the front like it should be

    //it adds a few elemnets ith push with some duplicates
    q2.push("Second");
    q2.push("Second");
    q2.push("Third");
    REQUIRE(q2.getCount() == 4); //it tests if the count is now 4 like it should be with third, second second, third

    //it tests remove() and it removes all the "second"
    q2.remove("Second");
    REQUIRE(q2.getCount() == 2); //it checks and tests if their are only 2 elements and they should be third and third
    REQUIRE(q2.peek() == "Third"); //it checks/test if the front is still third like it should be

    //it tests push after the remove
    q2.push("New Guy");
    REQUIRE(q2.getCount() == 3);
    REQUIRE(q2.peek() == "Third"); //test if the front is still third like it should be
  }

  SECTION("Queue edge cases and error handling") {
    Queue<int> q;

    //it tests popping from empty queue throws exception
    REQUIRE_THROWS_AS(q.pop(), std::runtime_error);

    //it tests peeking into empty queue throws exception
    REQUIRE_THROWS_AS(q.peek(), std::runtime_error);

    //it tests removing from empty queue and it should not throw
    q.remove(10);
    REQUIRE(q.getCount() == 0);

    //it tests removing non-existent element in the queue
    q.push(5);
    q.push(10);
    q.push(15);
    q.remove(100);  //it checks if the element doe not exist
    REQUIRE(q.getCount() == 3);  //checks to see if the count is unchanged

    //it tests removing all elements leaves the queue working
    q.remove(5);
    q.remove(10);
    q.remove(15);
    REQUIRE(q.getCount() == 0);
    q.push(20);  //test/checks that it should still work
    REQUIRE(q.getCount() == 1);
    REQUIRE(q.peek() == 20);
  }

  SECTION("Queue debugPrint test") {
    Queue<int> q;

    //it checks/tests debugPrint on empty queue it should work
    cout << "Empty queue debug print: ";
    q.debugPrint();

    //it tests the debugPrint with elements in the queue
    q.push(1);
    q.push(2);
    q.push(3);
    cout << "Queue with elements debug print: ";
    q.debugPrint();
  }
}

TEST_CASE("Stack Tests", "[stack]") {
  SECTION("Stack w/ int tests") {
    //creates an empty stack of ints
    Stack<int> s1 = Stack<int>();
    // Ensure that push(), pop(), and peek()
    // work properly in concert with getCount()
    // and remove()
    //test if the it is an empty stack of ints
    REQUIRE(s1.getCount() == 0);

    //it test the first push and adds 10 to the stack
    s1.push(10);
    REQUIRE(s1.getCount() == 1);
    REQUIRE(s1.peek() == 10); //it checks/tests to see if the top is 10 like it should be

    //it tests the second push and adds 20 to the stack
    s1.push(20);
    REQUIRE(s1.getCount() == 2);
    REQUIRE(s1.peek() == 20); //it checks/tests if the top is 20 now like it should be

    //it test the third push and adds 30 to the stack
    s1.push(30);
    REQUIRE(s1.getCount() == 3);
    REQUIRE(s1.peek() == 30); //it tests if the top is now 30 like it should be

    //it tests the first pop and it should remove 30
    REQUIRE(s1.pop() == 30);
    REQUIRE(s1.getCount() == 2);
    REQUIRE(s1.peek() == 20); //it checks/tests if the top is 20 like it should be

    //it tests the second pop and it should remove 20
    REQUIRE(s1.pop() == 20);
    REQUIRE(s1.getCount() == 1);
    REQUIRE(s1.peek() == 10); //it checks/tests if the top is 10 like it should be

    //it adds several elements with push and it includes duplicates
    s1.push(20);
    s1.push(20);
    s1.push(30);
    REQUIRE(s1.getCount() == 4); //checks to see if the count is 4 like it should be of 10, 20, 20, 30

    //it tests the remove() and it should remove all instances of 20
    s1.remove(20);
    REQUIRE(s1.getCount() == 2); //it checks/tests if there are 2 in the count and they should be 10, 30
    REQUIRE(s1.peek() == 30); //checks/tests if the top is still 30 like it should be

    //it tests the push after the remove
    s1.push(40);
    REQUIRE(s1.getCount() == 3);
    REQUIRE(s1.peek() == 40); //it tests if the top is now 40 like it should be
  }

  SECTION("Stack w/ string tests") {
    //it creates an empty stack of strings
    Stack<string> s2 = Stack<string>();
    // Ensure that push(), pop(), and peek()
    // work properly in concert with getCount()
    // and remove()
    //it tests to see if the empty stack that was crated is empty
    REQUIRE(s2.getCount() == 0);

    //it tests the first push and it adds "first" to the stack
    s2.push("First");
    REQUIRE(s2.getCount() == 1);
    REQUIRE(s2.peek() == "First"); //it tests to see if "first" it at the top like it should be

    //it tests the second push and adds "second" to the stack
    s2.push("Second");
    REQUIRE(s2.getCount() == 2);
    REQUIRE(s2.peek() == "Second"); //it tests if the top is "second" like it should be

    //it tests the third push and it adds "third" to the stack
    s2.push("Third");
    REQUIRE(s2.getCount() == 3);
    REQUIRE(s2.peek() == "Third"); //it tests if the top is "third" like it should be

    //it tests the first pop and it should remove the "third"
    REQUIRE(s2.pop() == "Third");
    REQUIRE(s2.getCount() == 2);
    REQUIRE(s2.peek() == "Second"); //it tests to see if the top is "second" like it should be

    //it tests the second pop and it should remove "second"
    REQUIRE(s2.pop() == "Second");
    REQUIRE(s2.getCount() == 1);
    REQUIRE(s2.peek() == "First"); //it tests if the top is "first" like it should be

    //it adds several elements including duplicates
    s2.push("Second");
    s2.push("Second");
    s2.push("Third");
    REQUIRE(s2.getCount() == 4); //it tests if the count is 4 like it should be and it shound be first, second, second, thrid

    //it tests the remove() and it should remove all instances of "Second"
    s2.remove("Second");
    REQUIRE(s2.getCount() == 2); //it checks if the count is 2 like it should be with first, third
    REQUIRE(s2.peek() == "Third"); //it tests if the top is still third like it should be

    //it test push after the remove
    s2.push("New Guy");
    REQUIRE(s2.getCount() == 3);
    REQUIRE(s2.peek() == "New Guy"); //it tests if the top is new guy like it should be
  }

  SECTION("Stack edge cases and error handling") {
    Stack<int> s;

    //it tests popping from empty stack throws exception
    REQUIRE_THROWS_AS(s.pop(), std::runtime_error);

    //it tests peeking into an empty stack throws an exception
    REQUIRE_THROWS_AS(s.peek(), std::runtime_error);

    //it checks/tests removing from empty stack should not throw
    s.remove(10);
    REQUIRE(s.getCount() == 0);

    //it tests removing non-existent element
    s.push(5);
    s.push(10);
    s.push(15);
    s.remove(100);  //tests if element doesn't exist
    REQUIRE(s.getCount() == 3);  //checks to see if the count is unchanged

    //it tests removing all elements leaves the stack working
    s.remove(5);
    s.remove(10);
    s.remove(15);
    REQUIRE(s.getCount() == 0);
    s.push(20);  //cheks if it should still work
    REQUIRE(s.getCount() == 1);
    REQUIRE(s.peek() == 20);
  }

  SECTION("Stack debugPrint test") {
    Stack<int> s;

    //it tests the debugPrint on empty stack shoudl work fine
    cout << "Empty stack debug print: ";
    s.debugPrint();

    //it tests the debugPrint with elements
    s.push(1);
    s.push(2);
    s.push(3);
    cout << "Stack with elements debug print: ";
    s.debugPrint();
  }
}
