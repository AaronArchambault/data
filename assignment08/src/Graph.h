//
//  Graph.h
//
//  Defines the Graph class.
//  You SHOULD modify this file.
//  You should not add any additional methods to this class.
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

#ifndef graph_hpp
#define graph_hpp

#include <iostream>
#include <list>
#include <optional>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "MemoryLeakDetector.h"

using namespace std;

namespace csi281 {

  template <typename V> class Graph {
  public:
    // Add a vertex to the graph
    void addVertex(V vertex) { adjacencyList.emplace(vertex, unordered_set<V>()); }

    // Add an edge to the graph
    // *from* is the starting vertex
    // *to* is the ending vertex
    // *bidirectional* is whether the edge should be in both directions
    // If *from* and/or *to* do not exist, they are added as vertices
    void addEdge(V from, V to, bool bidirectional = true) {

      adjacencyList[from].emplace(to);
      if (bidirectional) {
        adjacencyList[to].emplace(from);
      } else {  // ensure the *to* vrtex is in the graph
        if (adjacencyList.find(to) == adjacencyList.end()) {
          addVertex(to);
        }
      }
    }

    // Return the neighbors (as an unordered_set) for a vertex
    const unordered_set<V> &neighbors(const V &vertex) {
      // ensure we actually have this vertex in the graph
      assert(adjacencyList.find(vertex) != adjacencyList.end());
      return adjacencyList[vertex];
    }

    // Determines whether there is an edge between *from* and *to*
    // if either is not in the graph, return false
    //pre: the graph should exist and the from and to need to be passed in
    //post: it will test whether there is an edge between *from* and *to* and it will return something differnt depeding
    //it will reutrn false if the the egeds don't exist it will reutrn true if to and from are connect and it will reutrn false if it can find
    //them being connected
    //purpose: to have a funciton that tests/determies and returns ture or false whether there is an edge between *from* and *to* and
    //if either is not in the graph, return false
    bool edgeExists(const V &from, const V &to) {
      // YOUR CODE HERE

      if (adjacencyList.find(from) == adjacencyList.end()) //it checks/test if form exists in the graph
        //if it does not exist, there can't be an edge from it
      {
        return false;
      }

      for (const auto &edge : adjacencyList[from]) //loops through all edges neighbors form the 'from' vertex
        //to check if 'to' is connected to 'from'
        {
        if (to == edge) //test if it finds the 'to' vertex in the adjecency list of 'from' then
          //an edge exists between them
          {
          return true;
        }
      }
      return false; //if all the edges are checked and edges did not find to it returns false
    }

    using Path = list<V>;
    // Figure out a path from a goal node back to
    // a start node using a map keeping track of each node and the
    // node that got to it (your explored map)
    Path pathMapToPath(unordered_map<V, V> &previousMap, V &goal) {
      Path path = Path();
      V *current, *previous = nullptr;
      current = &goal;
      do {
        path.push_front(*current);
        previous = current;
        current = &previousMap[*current];
      } while (*current != *previous);
      return path;
    }

    // Perform a depth-first search from *start*, looking for *goal*
    // Return a path if one is found using pathMathToPath (with explored)
    // or return nullopt if no path is found
    //pre: the graph should exist and the stat and goal need to be passed in
    //post: th goal/path to the goal should be found and returned as a path using pathMapToPath unsing dpeth-first search or if it can't
    //find the goal/path to the goal then it will return nullopt
    //purpose: to create a function that uses depth-first search to find/try and find the path to the goal that it was given using the start
    //it was given and to return that path
    optional<Path> dfs(const V &start, const V &goal) {
      // how did we get to each node, and which ones have already been visited (dual purpose)
      unordered_map<V, V> explored = unordered_map<V, V>();
      // the start node came from nowhere, so we mark its parent as itself
      explored[start] = start;

      stack<V> front; //creates the satck front that DFS can explore before backtracking
      front.push(start); //adds the start node to the front so that DFS can start to explore

      while (!front.empty()) //it loops wilhe the front is not empty so that it keeps exploring
      //while there are still nodes in the fornt
        {
        V current = front.top(); //gets the top/most recoently added node to explore from the top of the stack
        front.pop();

        if (current == goal) //tests if it has reached/found the goal
        {
          V goalCopy = goal; //crates a copy of goal to pass to pathMapToPath
          return pathMapToPath(explored, goalCopy); //when it is found, it converts it to an expleoted map to a path and returns it
        }
        for (const auto &edge : adjacencyList[current]) //it loops to explore all the neighbors edged of the current node
          {
          const V &to = edge;
          if (explored.find(to) == explored.end()) //tests if the neighbor has not been explored yet
            {
            explored[to] = current; //marks it as explored and record that it has reached it form the curent thing/node
            front.push(to); //adds this neighbor to the frontier for future exploraiton if needed
          }
        }
      }
      return nullopt; //if nothing has been found/reached from all possible nodes and it does not find the goal it returns null
      //to say that no path exists
      // YOUR CODE HERE
      // TIP: Start by defining a frontier and putting start onto it.
      // TIP: Follow the pseudocode from the slides from class
    }

    // Perform a breadth-first search from *start*, looking for *goal*
    // Return a path if one is found using pathMathToPath (with explored)
    // or return nullopt if no path is found
    //pre: the graph should exits and the start and goal should be passed in
    //post: it will either return the path that it found to the goal using pathMathToPath or nullopt if it could
    //not find the path
    //purpose: to create a function to used breadth-first search to find the path to the goal that was passed in and starting
    //from the start that was passed in and either return the path to the goal if it finds it or nullpot if it can't find it
    optional<Path> bfs(const V &start, const V &goal) {
      // how did we get to each node, and which ones have already been visited (dual purpose)
      unordered_map<V, V> explored = unordered_map<V, V>();
      // the start node came from nowhere, so we mark its parent as itself
      explored[start] = start;

      queue<V> front; //creates the queue front so that BFS can explore level by level
      front.push(start); //adds the start node to the front to start the exploration

      while (!front.empty()) //it loops so that it can continue to explore while there are nodes in the fort
        {
        V current = front.front(); //gets oldest node form the front of the queue and it does this to
        //make sure that it explores the nodes in the oder they were discoverd
        front.pop();

        if (current == goal) //tests if it has reached/found the goal
        {
          V goalCopy = goal;// makes a copy of the goal to pass to the pathMapToPath
          return pathMapToPath(explored, goalCopy); //when it is found it converts it to expleoted map to a path and returns it
        }

        for (const auto &edge : adjacencyList[current]) //it loops so that it explores all of the neighbors/edges of the current node
          {
          const V &to = edge;
          if (explored.find(to) == explored.end()) //checks if this node/neighbor has not been explored yet
            {
            explored[to] = current; //marks it as explored and records that it reached it form the curent
            front.push(to); //adds this neighbor to the back of the queue for future exploration
          }
        }
      }
     return nullopt; //if it has done all of the reachable node without finding the goal it returns null to tell
      //that it could not find the path
      // YOUR CODE HERE
      // TIP: Start by defining a frontier and putting start onto it.
      // TIP: Follow the pseudocode from the slides from class
      // TIP: This should be very similar to dfs
    }

    // Utility function if you need it
    void printExplored(unordered_map<V, V> um) {
      for (auto const &p : um) {
        cout << p.first << " : " << p.second;
        cout << endl;
      }
    }

    // Debug print out the contents of the graph
    void debugPrint() {
      for (auto const &p : adjacencyList) {
        cout << p.first << ": ";
        for (auto const &v : p.second) {
          cout << v << ", ";
        }
        cout << endl;
      }
    }

  private:
    unordered_map<V, unordered_set<V>> adjacencyList = unordered_map<V, unordered_set<V>>();
  };
}  // namespace csi281

#endif /* graph_hpp */
