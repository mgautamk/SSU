#include <iostream>
#include <string>

using namespace std;

class Node {

public:
  Node(int key1){
    key = key1;
    tag = 0;
    down = NULL;
    next = NULL;
  }

  Node(Node* dptr, Node* nptr) {
    tag = 1;
    down = dptr;
    next = nptr;
  }

  void setKey(int k) {
    key = k;
  }
  
  bool isNumber() {
    //boolean function IsNumber to find out numbers 
    //from other characters
    return tag == 0;
  }

  void setDown(Node* ptr) {
    down = ptr;
  }

  void setNext(Node* ptr) {
    next = ptr;
  }

  int getKey() {
    return key;
  }

  Node* getDown() {
    return down;
  }

  Node* getNext() {
    return next;
  }

  int size() {
    //size function to find out the size of the list
    if (this == NULL)
      return 0;
    else if (this->tag == 0) return 1;
    else
      return down->size() + next->size();
  }
  //update function which updates the list using values
  //j,k 
  void update(int j, int k) {
    if (this->isEmpty())
      {
	cout <<"Not valid to update empty list:" << endl;
	return;
      }
    else if(this->isNumber())
      {
	this->setKey(k);
	return;
      }
    else
      {
	int s = down->size();
	if (j <=s)
	  down->update(j,k);
	else
	  next->update(j-s, k);
      }
    
  } // end update
  
  bool isEmpty() {
    //boolean function to check if the list is Empty
    return this == NULL;
  }
  
  void print(int depth) {
    //print function, to print the contents of the list
    if (this == NULL) return;
    if (tag == 0) {
      cout << "<" << key << ":" << depth << ">  " ;
    }
    else {
      down->print(depth+1);
      next->print(depth);
    } // end else
  } // end print

private:
  int tag;
  int key;
  Node* down;
  Node* next;
};
