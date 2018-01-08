#include <iostream>
#include <string>

#define SIZE 100

using namespace std;

class Stack {
  
private:
  int maxTop;// max stack size = size - 1
  int top;// current top of stack
  Node* values[SIZE];// element array
public:
  bool IsEmpty() { return top == -1; }
  bool IsFull() { return top == maxTop; }
  
  Stack() {
    top=-1;
    maxTop= SIZE - 1;
  }
  
  void Push(Node* x) {
    if (IsFull())  // if stack is full, print error
      cout << "Error: the stack is full." << endl;
    else {
      values[++top]= x;
    }
  }
  
  Node*  Pop() {
    if (IsEmpty()) { //if stack is empty, print error
      cout << "Error: the stack is empty." << endl;
      return NULL;
    }
    else {
      return values[top--];
    }
  }
  
  Node* Top() {
    if (IsEmpty()) {
      cout << "Error: the stack is empty." << endl;
      return NULL;
    }
    else
      return values[top];
  }
};
