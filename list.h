#ifndef LIST_H
#define LIST_H
#include "node.h"
class Linked_List {
private:
   unsigned int length; // the number of nodes contained in the list
   Node *head; // a pointer to the first node in the list
   // anything else you need...
public:
   Linked_List();
   int get_length();
   // note: there is no set_length(unsigned int) (the reasoning should be intuitive)
   void print(); // output a list of all integers contained within the list
   void clear(); // delete the entire list (remove all nodes and reset length to 0)
   unsigned int push_front(int); // insert a new value at the front of the list (returns the new length of the list)
   unsigned int push_back(int); // insert a new value at the back of the list (returns the new length of the list)
   unsigned int insert(int val, unsigned int index); // insert a new value in the list at the specified index (returns the new length of the list)
   void sort_ascending(); // sort the nodes in ascending order. You must implement the recursive Merge Sort algorithm
   // Note: it's okay if sort_ascending() calls a recursive private function to perform the sorting.
   void sort_descending(); // sort the nodes in descending order
   // you can add extra member variables or functions as desired
   int get_num();
   int get_index();
   bool isPrime(int);
   void countPrimes();
   void split(Node*&);
   Node* mergeAscending(Node*, Node*);
   Node* mergeDescending(Node*, Node*);
};

#endif
