#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "DLL.h"

using namespace std;

DLL::DLL(){
   head = nullptr;
   tail = nullptr;
}
/*
Adds the positive integer passed as a parameter to the head of the list. 
Returns false if the integer parameter is not positive, or cannot be added to the list. 
This function should allow duplicate elements to be added to the list.
*/
bool DLL::prepend(int val){
   if (val >= 0) {
      Node* nodeToPreprend = new Node(val);

      if (this->head != nullptr) {
         nodeToPreprend->next = this->head;
         this->head->prev = nodeToPreprend;
      }
      this->head = nodeToPreprend;

      if (this->tail == nullptr) {
         this->tail = this->head;
      }
      return true;
   }
   cout << "The value: " << val << " cannot be added to the list" << endl;
   return false;
}

/*
Adds the positive integer passed as a parameter to the tail of the list. 
Returns false if the integer parameter is not positive, or cannot be added to the list. 
This function should allow duplicate elements to be added to the list.
*/
bool DLL::append(int val){
   if (val >= 0) {
      Node *nodeToAppend = new Node(val);

      if (this->tail != nullptr)
      {
         nodeToAppend->prev = this->tail;
         this->tail->next = nodeToAppend;
      }
      this->tail = nodeToAppend;

      if (this->head == nullptr)
      {
         this->head = this->tail;
      }
      return true;
   }
   cout << "The value: " << val << " cannot be added to the list" << endl;
   return false;
}

   /*
   Adds the vals of the DLL passed (by reference) as a parameter, to the end of the list, 
   leaving "other" empty. Returns true. 
   If an object is merged into itself, then these instructions are contradictory, 
   so the function should not take any action. "list += list;" should therefore leave list unchanged.
   */
bool DLL::merge(DLL &other){
   if (this == &other)
      return true;
     
   if (this->head != nullptr){
      if (other.head != nullptr){
         this->tail->next = other.head;
      } else if (this->tail != nullptr && other.head != nullptr){
         other.head->prev = this->tail;
      } else if (other.tail != nullptr){
         this->tail = other.tail;
      }
   } else{
      if (other.head != nullptr && other.tail != nullptr){
         this->head = other.head;
         this->tail = other.tail;
      }
   }
   other.head = nullptr;
   other.tail = nullptr;
   return true;
}

DLL& DLL::operator+=(const DLL& other){
   // Guard self assignment
   if (this == &other)
      return *this;

   Node* temp = other.head;

   while (temp != nullptr){
      this->append(temp->data); 
      temp = temp->next;
   }

   return *this;

}
/*Adds the vals of the DLL passed (by reference) as a parameter, to the end of the list, leaving "other" intact. 
Returns a reference to the current object (i.e. the object that is called... use "return *this;"). Calling "list += list;" 
cannot both add the list to the left hand side and leave that same list in tact, so this operation should instead leave list unchanged. 
You may simply implement this as "if (this == &other) return *this;" */

DLL& DLL::operator-=(const DLL &other){

   if (this == &other)
      return *this;
   //if this->data in the other list, remove that node
   Node* one = other.head;
   Node* two = this->head;
   Node* del;
   while (other.head != nullptr){
      one = other.head;
      while(one != nullptr){
         two = this->head;
         while(two != nullptr){
            if (one->data == two->data){
               del = two;
               two = two->next;
               deleteNode(del);
            } else{
               two = two->next;
            }
         }
         one = one->next;
      }
      return *this;
   }
   return *this;
}
/*
Removes all vals that are contained in other, from the list that is called, leaving other intact. 
Returns a reference to the current object (i.e. the object that is called). 
Passing an object to its own -= operator should not change the object (because it cannot simultaneously remove elements from the list and leave that same list intact.)*/

void DLL::deleteNode(Node* nodeToDelete) {
   if (nodeToDelete == head && nodeToDelete == tail) {
      head = nullptr;
      tail = nullptr;
   } else if (nodeToDelete == head) {
      head = head->next;
      head->prev = nullptr;
      nodeToDelete->next = nullptr;
   } else if (nodeToDelete == tail) {
      tail = tail->prev;
      tail->next = nullptr;
      nodeToDelete->prev = nullptr;
   } else {
      nodeToDelete->prev->next = nodeToDelete->next;
      nodeToDelete->next->prev = nodeToDelete->prev;
      //cout << "Neither" << endl;

      nodeToDelete->next = nullptr;
      nodeToDelete->prev = nullptr;
   }
   delete nodeToDelete;
}

/*Returns the maximum val in the DLL, leaving it in the DLL. If the list is empty before the call, returns 0.*/
int DLL::getMax(){
   Node* tempNode = head;
   Node* maxNode = head;
   int maxValue = head->data;

   while (tempNode != nullptr) {
      if (tempNode->data > maxValue) {
         maxNode = tempNode;
         maxValue = tempNode->data;
      }
      tempNode = tempNode->next;
   }
   return maxValue;
}

/*Returns the maximum integer in the DLL, and removes it from the DLL. If the list is empty, returns 0.
If there are multiple instances of the same maximum val, only the first one in the list should be removed.*/
int DLL::extractMax(){
   Node* tempHead = this->head;
   Node* maxNode = this->head;

   if (tempHead == nullptr){
      return 0;
   }
   while (tempHead != nullptr){
      if (tempHead->data > maxNode->data){
         maxNode = tempHead;
      }
      tempHead = tempHead->next;
   }
   int result = maxNode->data;
   deleteNode(maxNode);
   return result;
}

DLL DLL::extractOdds(){
   Node* temp = this->head;
   Node* oddNode = this->head;
   DLL odds;
   while (temp != nullptr){
      if (temp->data % 2 != 0){
         oddNode = temp;
         odds.append(oddNode->data);
         temp = temp->next;
         deleteNode(oddNode);
      } else{
         temp = temp->next;
      }
      //cout << "ODD NUM: " << oddNode->data << endl;
      //deleteNode(oddNode);
   }
   return odds;
/*Returns a DLL containing the odd numbers of the original list. Leaves only the even numbers in the list that is called.*/
}

DLL DLL::extractEvens(){
   Node* temp = this->head;
   Node* evenNode = this->head;
   DLL evens;
   while (temp != nullptr){
      if (temp->data % 2 == 0){
         evenNode = temp;
         evens.append(evenNode->data);
         temp = temp->next;
         deleteNode(evenNode);
      } else{
         temp = temp->next;
      }
      //cout << "ODD NUM: " << oddNode->data << endl;
      //deleteNode(oddNode);
   }
   return evens;
/*Returns a DLL containing the even numbers of the original list. Leaves only the odd numbers in the list that is called.
Finally, your DLL should support the concept (but only the concept) of an "iterator", via the following operations.*/
}

bool DLL::reset(){
//Sets a "pointer" within the object to the first node of the linked list. This operation returns true if the list is non-empty, and false otherwise.
   currentNode = head;
   //cout << currentNode->data << endl;
   if (currentNode == nullptr){
      return false;
   }
   return true;
}

int DLL::getNext(){
/*Returns the "next" integer from the linked list. 
So a call to reset() followed by a call to getNext() returns the first element of a (non-empty) DLL. 
Subsequent calls to getNext() return the subsequent integers in the list. 
When it becomes true that the tail integer was returned on the previous call to getNext(), 
and no subsequent "reset()" is performed, then getNext() should return 0.*/
   if (currentNode != nullptr) {
      int data = currentNode->data;
      currentNode = currentNode->next;
      return data;
   }
   return 0;
}

