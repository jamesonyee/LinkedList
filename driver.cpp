/******************************************************
** Program Filename: driver.cpp
** Author: Jameson Yee
** Date: 6/7/2021
** Description: main file that creates a linked list object
** Input: integers from user
** Output: Sorted linked list and number of prime numbers in the list
******************************************************/

#include "list.h"
#include "node.h"
#include <iostream>

using namespace std;

int main(){
    Linked_List l1;
    int first = l1.get_num();
    l1.push_back(first);
    l1.get_length();
    l1.print();

    int index = l1.get_index();
    int insert_num = l1.get_num();

    l1.insert(insert_num,index);
    l1.print();
    //l1.sort_ascending();
    //l1.print();
    l1.sort_descending();
    l1.print();
    l1.countPrimes();
    l1.clear();

    return 0;
}