// CMSC 341 - Spring 2020 - Project 2
#ifndef _RMQLIST_H
#define _RMQLIST_H

#include <iostream>
#include <stdexcept>
#include <cmath>

using std::swap;
using std::ostream;
using std::cout;
using std::endl;
using std::sqrt;
using std::range_error;
using std::invalid_argument;


// Macro for a two-argument min function
#define MIN(a, b)  ((a) < (b) ? (a) : (b))

// forward declarations
template <class K, class V> class RMQList;
template <class K, class V> class Node;
template <class K, class V> ostream& operator<<(ostream &sout, const Node<K,V> &x);

// *********************************************
// Node - node class for the RMQList linked list
//   key and value are templated (types K and V)
// *********************************************

template <class K, class V>
class Node {
  friend RMQList<K, V>;
public:
  Node(K key = K(), V value = V(), Node<K, V> *next = nullptr) {
    _key = key;
    _value = value;
    _next = next;
  }
  friend ostream& operator<< <K,V>(ostream &sout, const Node<K,V> &x);
private:
  K _key;
  V _value;
  Node *_next;
};

// Overloaded insertion operator for Node
template <class K, class V>
ostream& operator<<(ostream &sout, const Node<K,V> &x) {
  sout << "Key: " << x._key << ", Value: " << x._value;
  return sout;
}

// *******************************************************
// RMQList - list container (linked list) with RMQ support
//   key and value are templated (types K and V)
// *******************************************************

template <class K, class V>
class RMQList {
public:
  // Create an empty RMQList object
  RMQList();
  
  // Destructor, Copy Constructor, Assignment Operator
  ~RMQList();
  RMQList(const RMQList<K,V> &rhs);
  const RMQList<K,V>& operator=(const RMQList<K,V> &rhs);
  
  // In-line function. Returns the size (number of elements).
  int size() const { return _listSize; } 

  // In-line function. Returns true if the list is empty; false
  // otherwise.
  bool empty() const { return _head == nullptr; }
  
  // Insert an element into the list; list must be kept in increasing
  // order by key; duplicate keys are not allowed, so return false if
  // there is already an entry with the specified key, true otherwise.
  // Should check if key > largest current key and, if so, append to
  // the end of the list without iteration.
  bool insert(const K& key, const V& value);

  // Remove an element from the list; return false if no element
  // exists with the specified key value, true otherwise
  bool remove(const K& key);

  // Update value for the element with given key; return false if
  // there is no element with the given key, true otherwise
  bool update(const K& key, const V& value);
  
  // RMQ Query for k1 to k2.  Throws exceptions (see documentation).
  V query(const K& k1, const K& k2);

  // Dump the list entries
  void dumpList() const;
  
  // Dump the RMQ info and table.  What gets dumped depends on which
  // RMQ method is used.
  void dumpTable() const;

  // Clear the data data strucures
  void clear();
  
 private:
  Node<K,V> *_head;
  Node<K,V> *_tail;
  int _listSize;

  // **********************************
  // Private variables for RMQ go here!
  // **********************************

  // *******************************************
  // Declarations for private functions go here!
  // *******************************************
};
 

template <class K, class V>
RMQList<K,V>::RMQList() {
  _head = nullptr;
  _tail = nullptr;
  _listSize = 0;
}

template <class K, class V>
RMQList<K,V>::~RMQList() {
  clear();
}

template <class K, class V>
RMQList<K,V>::RMQList(const RMQList<K,V> &rhs) {
  if (rhs._head == nullptr){
    _head == nullptr;
    _tail == nullptr;
  }
  else{
    _head = new Node<K,V> (rhs._head->_key, rhs._head->_value, rhs._head->_next);
    Node<K,V> *current = _head;
    Node<K,V> *rhsHead = rhs._head;
    Node<K,V> *temp = rhsHead;
    while (temp->_next != nullptr){
      current->_next = new Node<K,V>(temp->_next->_key, temp->_next->_value, temp->_next->_next);
      temp = temp->_next;
      current = current->_next;      
    }
    _tail = current;
  }
}

template <class K, class V>
const RMQList<K,V>& RMQList<K,V>::operator=(const RMQList<K,V> &rhs) {
  if (this != &rhs){
    //destructor
    clear();
    
    //copy constructor
    Node<K,V> *current = _head;
    Node<K,V> *rhsHead = rhs._head;
    Node<K,V> *ptr = rhsHead;
    while (ptr->_next != nullptr){
      current->_next = new Node<K,V>(ptr->_next->_key, ptr->_next->_value, ptr->_next->_next);
      ptr = ptr->_next;
      current = current->_next;      
    }
    _tail = current;
  }
  
  else{
    cout << "no self-assignment!" << endl;
  }
  return *this;
    
}

template <class K, class V>
bool RMQList<K,V>::insert(const K& key, const V& value) {
  //if empty
  if (_head == nullptr){
    Node<K,V> *newNode = new Node<K,V>(key, value, nullptr);
    _head = newNode;
    _listSize++;
    _tail = newNode;
    return true;
  }
  
  //check if key > tail's key
  if (key > _tail->_key){
    Node<K,V> *newNode = new Node<K,V>(key, value, nullptr);
    _tail->_next = newNode;
    _tail = newNode;
    _listSize++;
    return true;
  }
  
  //check if key < head's key
  if (key < _head->_key){
    Node<K,V> *newNode = new Node<K,V>(key, value, _head);
    _head = newNode;
    _listSize++;
    return true;
  }
  
  //check if it exists
  Node <K,V> *temp = _head;
  while (temp != _tail->_next){
    if (temp->_key == key){
      cout << "Already exists!" << endl;
      return false;
    }
    temp = temp->_next;
  }
  
  //insert the Node
  Node <K,V> *ptr = _head;
  while (ptr->_next != nullptr and ptr->_next->_key < key){
    ptr = ptr->_next;
  }
  Node <K,V> *newNode = new Node<K,V>(key, value, ptr->_next); 
  ptr->_next = newNode;
  if(!newNode->_next){
    _tail = newNode;
  }
  _listSize++;
  return true;
}

template <class K, class V>
bool RMQList<K,V>::remove(const K& key) {
  //check if valid key
  bool k1Check = false;
  Node<K,V> *check = _head;
  while (check != nullptr){
    if (check->_key == key){
      k1Check = true;
    }
    check = check->_next;
  }
  if (k1Check != true){
    throw invalid_argument ("Key 1 not valid");
  }  
  Node<K,V> *temp = _head;
  //remove head
  if (_head->_key == key){
    _head = temp->_next;
    delete temp;
    _listSize--;
    return true;
  }
  //remove tail
  if (_tail->_key == key){
    Node<K,V> *del = _head;
    while (del->_next != _tail){
      del = del->_next;
    }
    Node<K,V>* ptr = _tail;
    delete ptr;
    del->_next = nullptr;
    _tail = del;
    _listSize--;
    return true;
  }
  //remove from middle
  while (temp->_next->_key != key){
    temp = temp->_next;
    if (temp->_next->_key == key){
      Node<K,V> *ptr;
      ptr = temp->_next;
      temp->_next = ptr->_next;
      delete ptr;
      _listSize--;
      return true; 
    }
    if (temp == _tail){
      if(temp->_key != key){
        return false;
      }
    }
  }
  return false;
}

template <class K, class V>
bool RMQList<K,V>::update(const K& key, const V& value) {
  Node<K,V> *temp = _head;
  while (temp != _tail->_next){
    if (temp->_key == key){
      temp->_value = value;
      return true;
    }
    temp = temp->_next;
  }
  return false;
}

template <class K, class V>
V RMQList<K,V>::query(const K& k1, const K& k2) {
  //throw range_error if list is empty
  if (_listSize == 0){ 
    throw range_error ("List is empty");
  }
  
  //check if valid keys
  bool k1Check = false;
  bool k2Check = false;
  Node<K,V> *check = _head;
  while (check != nullptr){
    if (check->_key == k1){
      k1Check = true;
    }
    if (check->_key == k2){
      k2Check = true;
    }
    check = check->_next;
  }
  if (k1Check != true or k2Check != true){
    throw invalid_argument ("Key 1 and/or 2 not valid");
  }
  
  //preprocess
  //i Node
  Node<K,V> *temp = _head;
  //j Node
  Node<K,V> *ptr = _head;
  //= {0}
  V lookup[_listSize][_listSize] = {0};
  V min = temp->_value;
  for (int i = 0; i < _listSize; i++){
    for (int j = i; j < _listSize; j++){
      min = MIN(min, ptr->_value);
      lookup[i][j] = min;
      //cout << min << endl;
      ptr = ptr->_next;
    }
    temp = temp->_next;
    if (temp == nullptr){
      break;
    }    
    min = temp->_value;
    ptr = temp;
    //am I 1 short in adding to array?
    //output should be 766 but is 76 for cout << min
  }
  //cout << "after break" << endl;
  //find indexes
  int k1Count = 0;
  int k2Count = 0;
  int count = 0;
  Node<K,V> *find = _head;
  while (find != nullptr){
    if (find->_key == k1){
      k1Count = count;
    }
    if (find->_key == k2){
      k2Count = count;
    }
    find = find->_next;
    count++;
  }
  return lookup[k1Count][k2Count];
}

template <class K, class V>
void RMQList<K,V>::dumpList() const { 
  if (_head == nullptr){
    return; 
  }
  Node<K,V> *temp = _head;
  while (temp != _tail->_next){
    cout << *temp << endl;
    temp = temp->_next;
  }
}

template <class K, class V>
void RMQList<K,V>::dumpTable() const {
  if (_head == nullptr){
    return;
  }  
  //i Node
  Node<K,V> *temp = _head;
  //j Node
  Node<K,V> *ptr = _head;
  //= {0}
  V lookup[_listSize][_listSize] = {0};
  V min = temp->_value;
  for (int i = 0; i < _listSize; i++){
    for (int j = i; j < _listSize; j++){
      min = MIN(min, ptr->_value);
      lookup[i][j] = min;
      //cout << min << endl;
      ptr = ptr->_next;
    }
    temp = temp->_next;
    if (temp == nullptr){
      break;
    }    
    min = temp->_value;
    ptr = temp;
  }
  for (int i = 0; i < _listSize; i++){
    for (int j = i; j < _listSize; j++){
      cout << lookup[i][j] << " ";
    }
    cout << endl;
  }  
}

template <class K, class V>
void RMQList<K,V>::clear() {
  Node <K,V> *temp = _head;
  while (_head != nullptr){
    temp = _head->_next;
    delete _head;
    _head = temp;
  }
  _head = nullptr;
  _tail = nullptr;
  _listSize = 0;  
}

#endif
