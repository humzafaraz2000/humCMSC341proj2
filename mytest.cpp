#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <functional>
#include <algorithm>
#include "rmqlist.h"

using namespace std;

int main(){
  RMQList <double,double> rmq;
  vector<double> vals = {4, 8, 16, 5, 10, 15, 14, 19, 2, 81, 9, 6};
  
  //check insert
  bool insertCheck;  
  cout << "Insert data" << endl;
  for (int i = 0; i < (int)vals.size(); i++){
    cout << "  key = " << vals[i] << ", value = " << i << endl;
    insertCheck = rmq.insert(vals[i], i);    
  }
  cout << "Check bool of insert" << endl;
  cout << insertCheck << endl;  
  
  cout << "Dump list (should be ordered by key value)" << endl;
  rmq.dumpList();
  
  //check remove
  bool removeCheck;
  cout << "Remove first, last, and middle entry" << endl;
  cout << "Remove 2 (beginning)" << endl;
  removeCheck = rmq.remove(2.0);
  cout << "Remove 9 (middle)" << endl;
  rmq.remove(9.0);
  cout << "Remove 81 (end)" << endl;
  rmq.remove(81.0);
  rmq.dumpList();
  cout << "Check bool of remove" << endl;
  cout << removeCheck << endl;  
  
  //check constructors
  cout << "Check copy constructor" << endl;
  RMQList <double, double> copy(rmq);
  copy.dumpList();
  cout << "Check assignment operator" << endl;
  RMQList<double, double> assign = rmq;
  assign.dumpList();
  
  //check update
  bool updateCheck;
  cout << "Update first, last, and middle entry" << endl;
  cout << "Update 4 (beginning)" << endl;
  updateCheck = rmq.update(4.0, 15.0);
  cout << "Update 10 (middle)" << endl;
  rmq.update(10.0, 5.0);
  cout << "Update 19 (end)" << endl;
  rmq.update(19.0, 1.0);
  rmq.dumpList();
  cout << "Check bool of update" << endl;
  cout << updateCheck << endl;
  cout << "after update check" << endl;
  
  //test clear
  rmq.clear();
  rmq.dumpList();
  
  //test assigning to empty list
  cout << "Test assign and copy empty list" << endl;
  RMQList <double, double> emptyTest(rmq);
  emptyTest.dumpList();
  RMQList <double, double> assignEmpty = rmq;
  assignEmpty.dumpList();
  
  //--------------------------------------------------------------------------------------------
  //QUERY TESTS
  RMQList<double,double> newQ;
  vector<double> doubles = {3.2, 4.3, 8.9, 5.4, 11.3, 6.7, 8.2, 9.9, 10.1};
  for (int i = 0; i < (int)doubles.size(); i++){
    newQ.insert(doubles[i], i);
  }
  //compare query to brute force method
  //test beginnig
  cout << "\nTotal of " << newQ.size() << " key/value pairs inserted.\n";
  int min = 0;
  int queryCheck = newQ.query(3.2, 8.9); 
  if (min == queryCheck){
    cout << "Good" << endl;
  }
  else{
    cout << "Wrong" << endl;
  }
  
  //test end
  min = (int)doubles.size() - 1;
  queryCheck = newQ.query(10.1, 10.1);
  if (min == queryCheck){
    cout << "Good" << endl;
  }
  
  //test middle
  min = 3;
  queryCheck = newQ.query(5.4, 6.7);
  if (min == queryCheck){
    cout << "Good" << endl;
  }
  return 0;
}