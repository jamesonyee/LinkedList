#include "list.h"
#include "node.h"

#include <iostream>

using namespace std;

/********************************************************************************
 * Function: Linked_list()
 * Description: linked list constructor
 * Pre-conditions:
 * Post-conditions:
 * ******************************************************************************/
Linked_List::Linked_List(){
    head = NULL;
    length = 0;
}

/********************************************************************************
 * Function: isPrime(int listNum)
 * Description: checks if a number in the linked list is prime or not
 * source: https://www.tutorialspoint.com/count-number-of-primes-in-an-array-in-cplusplus
 * Pre-conditions: argument pasted in is a valid int
 * Post-conditions: returns a 1 or 0
 * ******************************************************************************/
bool Linked_List::isPrime(int listNum){
    if (listNum <= 1)
        return 0;
    for (int i = 2; i <= listNum/2; i++){
        if (listNum % i == 0){
            return 0;
      }
   }
   return 1;
}

/********************************************************************************
 * Function: get_num()
 * Description: gets int from user about which will be added to the linked list
 * Pre-conditions: none
 * Post-conditions: returns valid int and calls prime function
 * ******************************************************************************/
int Linked_List::get_num(){
    int listNum;
    do{
        if(cin.fail()==1){
            cin.clear();
            cin.ignore(256, '\n');
        }
        cout << "Please enter a number: ";
        cin >> listNum;
    }while(cin.fail()==1);
    isPrime(listNum);
    return listNum;
}

/********************************************************************************
 * Function: get_index()
 * Description: gets int from user which represents where in an array a number will be inserted 
 * Pre-conditions: none
 * Post-conditions: returns valid position that is not out of bounds of a given array
 * ******************************************************************************/
int Linked_List::get_index(){
    unsigned int pos;
    cout << "length: " << length << endl;
    do{
        if((cin.fail()==1) || (pos < 0 || pos > length)){
            cin.clear();
            cin.ignore(256, '\n');
        }
        cout << "Please enter the index in of the array where you want to insert a new num: ";
        cin >> pos;

    }while(cin.fail()==1 || (pos < 0 || pos > length));

    return pos;
}

/********************************************************************************
 * Function: get_length()
 * Description: function that determines size of linked list
 * Pre-conditions: none
 * Post-conditions: calls push function when the user wants to add a number
 * ******************************************************************************/
int Linked_List::get_length(){
    int action=1;
    char choice;
    do{
        cout << "Do you want another num to the end of the array (y or n): ";
        cin >> choice;
        if(choice == 'y'){
            int num = get_num(); //get an int from user, (error handled in get_num function)
            push_back(num);
            //push_front(num);
        }else if(choice == 'n'){
            action = 0;
        }
        else{
            cout << "input not recognized" << endl;
        }
    }while(action == 1);
    return length;
}

/********************************************************************************
 * Function: push_back(int num)
 * Description: adds user input number to the end of a linked list when called
 * Pre-conditions: user input is a valid int
 * Post-conditions: returns length of list after a number added
 * ******************************************************************************/
unsigned int Linked_List::push_back(int num){
   Node* temp = head;
   if(head == NULL){
       head = new Node;
       head->val = num;
       head->next = NULL;
    }else{
       for(unsigned int i=0; i<length; i++){
            if(temp->next == NULL){
                temp->next = new Node;
                temp->next->val = num;
                temp->next->next = NULL;
            }
            temp = temp->next;
        }
    }
    length++;
    cout << "length: " << length << endl;
    return length;
}

/********************************************************************************
 * Function: push_front()
 * Description: adds a number to the front of a linked list when called
 * Pre-conditions: user inputs valid int
 * Post-conditions: returns new length
 * ******************************************************************************/
unsigned int Linked_List::push_front(int num){
    length++;
    Node* temp = new Node;
    if(head == NULL){
        head = new Node;
        head->val = num;
        head->next = NULL;
    }else{
        temp->val = num;
        temp->next = head;
        head = temp;
    }
    return length;
}

/********************************************************************************
 * Function: insert(val, index)
 * Description: adds an int to the middle of the list depending on user input
 * Pre-conditions: user input is less than the value of the whole length list
 * Post-conditions: returns new length
 * ******************************************************************************/

unsigned int Linked_List::insert(int val, unsigned int index){
    Node* temp = head;
    Node* temp2 = head;
    Node* temp3 = head;
    int pos = index-1;
    if(index<0 || index>length){
        cout << "Position not in range of existing list" << endl;
    }else{
        //cout << "pos: " << pos << endl;
        //cout << "val: " << val << endl;
        for(int i=0; i<pos; i++){
            temp = temp->next;
        }
        //cout <<"out of loop" << endl;
        temp2 = temp->next;
        temp3 = new Node;
            temp3->val = val;
            temp->next = temp3;
        temp->next = temp3;
        temp3->next = temp2;
        length++;
    }
    return length;
}




/********************************************************************************
 * Function: print()
 * Description: displays the values in the link list
 * Pre-conditions: the list has stuff in it
 * Post-conditions: none
 * ******************************************************************************/
void Linked_List::print() {
    Node* current_node = head;
    cout << "Here is what your array looks like now: ";
    for (unsigned int i = 0; i<length; i++) { //interates through every node
        cout << current_node->val << " ";  
        current_node = current_node->next; //moves to next node in list
    }
    cout << endl;
}

/********************************************************************************
 * Function: split()
 * Description: recursively splits linked list into single elements and calls the sort function
 * Pre-conditions: list already exists
 * Post-conditions: 
 * source: shout out the homie Matthew for helping me with this one... this function was a pain
 * ******************************************************************************/
void Linked_List::split(Node*& head){
    int c=0;
    Node* temp = head;

    if(temp->next==NULL){ //base case
        return;
    }

    while(temp->next!=NULL){ 
        c++;
        temp = temp->next;
    }
    //cout << "c: "<< c << endl;

    int mid = c/2;
    //cout << mid << endl;
    Node* temp2 = head; 
    for(int i=0; i<mid; i++){ //points to the middle element in 
        temp2 = temp2->next;
    }

    Node* temp3 = temp2->next; 
    temp2->next = NULL;

    Node* left = head;
    Node* right = temp3;


    split(left);
    split(right);

    head = mergeDescending(left,right);
    //head = mergeAscending(left,right);
}

/********************************************************************************
 * Function: mergeAscending()
 * Description: compares values in linked list and sorts them from smallest to greatest
 * Pre-conditions: list is already split
 * Post-conditions: returns bigboi array
 * source: https://www.geeksforgeeks.org/merge-sort-for-linked-list/
 * ******************************************************************************/
Node* Linked_List::mergeAscending(Node* l, Node* r){
    //cout << "in merge" << endl;
    Node* bigboi = NULL;

    //base cases
    if(l==NULL) 
        return r;
    else if (r==NULL)
        return l;
    
    //compare values
    if(l->val <= r->val){
        bigboi = l;
        bigboi->next = mergeAscending(l->next,r);
    }else{
        bigboi=r;
        bigboi->next = mergeAscending(l,r->next);
    }

    return bigboi;
}

Node* Linked_List::mergeDescending(Node* l, Node* r){
    Node* bigboi = NULL;

    //base cases
    if(l==NULL) 
        return r;
    else if (r==NULL)
        return l;
    
    //compare values
    if(l->val >= r->val){
        bigboi = l;
        bigboi->next = mergeDescending(l->next, r);
    }else{
        bigboi = r;
        bigboi->next = mergeDescending(l, r->next);
    }
    return bigboi;
}

/********************************************************************************
 * Function: sort_ascending()
 * Description: calls to split the function which calls the merge 
 * Pre-conditions: list has elements in it
 * Post-conditions:
 * ******************************************************************************/

void Linked_List::sort_ascending(){
    cout << "sorting the list in ascending order..." << endl;
    split(head);
}

void Linked_List::sort_descending(){
    cout << "sorting the list in descending order..." << endl;
    split(head);

}

/********************************************************************************
 * Function: countPrimes()
 * Description: counts the number of prime numbers in linked list
 * Pre-conditions: valid ints in the list
 * Post-conditions: prints out how many prime numbers are in the list
 * ******************************************************************************/

//https://www.tutorialspoint.com/count-number-of-primes-in-an-array-in-cplusplus
void Linked_List::countPrimes(){
    int count=0;
    Node* current_node = head;
    for(unsigned int i=0; i<length; i++){
        //isPrime(current_node->val);
            if(isPrime(current_node->val) == 1)
            count++; //increase count if number is prime 
            current_node=current_node->next; //moves into the next node
    }
    cout << "You have " << count << " prime number(s) in your list" << endl;
}

/********************************************************************************
 * Function: clear()
 * Description: deletes memory of linked list and all pointers
 * Pre-conditions: link list exists
 * Post-conditions: linked list go bye bye
 * source: https://www.geeksforgeeks.org/write-a-function-to-delete-a-linked-list/
 * ******************************************************************************/
void Linked_List::clear(){
    Node* current_node = head;
    Node* next = NULL;

    while(current_node != NULL){
        next = current_node->next;
        delete current_node;
        current_node = next;
    }
    head = NULL;
}