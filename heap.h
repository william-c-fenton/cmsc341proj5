// CMSC 341 - Fall 2019 - Project 5
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.

  // *********************************************
  // Private helper function declarations go here!
  // *********************************************
  int getHighestChild(int root);
};

// ***************************************
// Templated function definitions go here!
// ***************************************
template<class T>
int Heap<T>::getHighestChild(int root){
  if (root * 2 < _heap.size()){
    int curr = root;
    bool leftHighest = curr * 2 < _heap.size();
    if ((curr * 2) + 1 >= _heap.size()){
      leftHighest = true;
    }
    else if (_heap.at((curr * 2) + 1).priority() > _heap.at(curr * 2).priority()){
      leftHighest = false;
    }
    if (leftHighest)
      return curr * 2;
    else
      return (curr * 2) + 1;
  }
  else{
    return root;
  }
}

template<class T>
Heap<T>::Heap(){
  _heap.resize(1);
}

template<class T>
void Heap<T>::insert(const T& object){
  if(!_used){
    _heap.push_back(object);
    _used = true;
  }
  else{
    int curr = _heap.size();
    int parent = curr / (int) 2;
    _heap.push_back(object);

    //curr always approaches one with integer division by 2. 
    //iterate until either curr is one or the heap-order property is 
    //satisfied
    while(curr != 1 && (_heap.at(curr).priority() > _heap.at(parent).priority())){
      //swap values of curr and parent
      T temp = _heap.at(parent);
      _heap[parent] = _heap[curr];
      _heap[curr] = temp;

      //update markers
      curr = parent;
      parent = (int)(curr / 2);
    }
  }
}

template<class T>
T Heap<T>::readTop() const{
    if(!empty())
      return _heap.at(1);
    else{
      throw range_error("ERROR: ATTEMPT TO READ EMPTY HEAP");
      return _heap.at(0);
    }
    
}

template<class T> 
void Heap<T>::removeTop(){
  if(_heap.size() == 1){
    cout << "Heap is empty" << endl;
  }
  else{
    //swap top with last node added
    T temp = _heap.at(_heap.size() - 1);
    _heap[_heap.size() - 1] = _heap[1];
    _heap[1] = temp;
    //(aka, node at size() - 1)
    //delete the last node 
    _heap.erase(_heap.begin() + _heap.size() - 1);
    //down-heap
    int curr = 1;
    int highest = getHighestChild(curr);
    while(curr < _heap.size() && (_heap.at(highest).priority() > _heap.at(curr).priority())){
      T temp = _heap.at(highest);
      _heap[highest] = _heap[curr];
      _heap[curr] = temp;

      //update markers
      curr = highest;
      highest = getHighestChild(curr);
    }
  }
}

template<class T>
void Heap<T>::dump() const{  
    if(!empty()){
      cout << "\n";
      for(int i = 1; i < _heap.size(); i++){
        cout << _heap.at(i) << endl;
      }
    }
    else{
      throw range_error("ERORR: ATTEMPT TO READ AN EMPTY HEAP");
    }

}


#endif
