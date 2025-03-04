#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node*& head, Node* & smaller, Node*& larger, int pivot) {
  if (head == nullptr) { // base case
    smaller = nullptr;
    larger = nullptr;
    return;
  }
  // Detatch first node
  Node* curr = head;
  head = head->next;
  curr->next = nullptr;

 // recursively split remainder of list
  Node* recSmall = nullptr;
  Node* recLarge = nullptr;
  llpivot(head, recSmall, recLarge, pivot);

  if(curr->val <= pivot) {
    curr->next = recSmall; // Attatch curr at front of smaller list
    smaller = curr;
    larger = recLarge;
  }
  else {
    curr->next = recLarge; // Attatch curr at front of larger list
    smaller = recSmall;
    larger = curr;
  }
}