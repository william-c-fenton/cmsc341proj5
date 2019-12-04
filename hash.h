// CMSC 341 - Fall 2019 - Project 5
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************
  int findIndex(string key);
};

// *****************************************
// Templated function definitions go here! *
// *****************************************
template <class T>
HashTable<T>::HashTable(unsigned size, hash_fn hash){
  _N = size;
  _hash = hash;
  _table = new Heap<T>[_N];
  for (int i = 0; i < _N; i++){
    _table[i] = Heap<T>();
  }

}

template <class T>
int HashTable<T>::findIndex(string key){
  int ind = _hash(key) % _N;
  if(!_table[ind].used() ){
    return ind;
  }
  else{
    if (!_table[ind].empty()){
      int temp = ind;
      int count = 0;

      T obj = _table[ind].readTop();
      
      while(obj.key() != key && count <= _N){
        count++;
        ind = (ind + 1) % _N;
        try{
          obj = _table[ind].readTop();
        }
        catch(range_error &e){
        }
      } 
      
      if (count == _N){
        try{
          throw range_error("ERROR: LIST FULL AND ITEM NOT FOUND");
        }
        catch(range_error &e){
          std::cerr << e.what() << endl;
        }
        return -1;
      }
      return ind;
    }
    else{
      return ind;
    }
  }
}

template<class T>
HashTable<T>::~HashTable(){
  delete [] _table;
}

template <class T>
bool HashTable<T>::insert(const T& object){
  int index = findIndex(object.key());
  if (index != -1){
    _table[index].insert(object);

    return true;
  }
  else{
    return false;
  }
}

template<class T>
bool HashTable<T>::getNext(string key, T& obj){
  int index = findIndex(key);

  if (_table[index].empty()){
    return false;
  }
  else{
    obj = _table[index].readTop();
    _table[index].removeTop();
    return true;
  }
}

template<class T>
void HashTable<T>::dump() const{
  for(int i = 0; i < _N; i++){
    cout << "[" << i << "]:";
    try{
      _table[i].dump();
    }
    catch(range_error &e){
      cout << "No orders" << endl;
    }
  }
}

#endif
