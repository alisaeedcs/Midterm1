//comsc-210 | Ali Saeed | Midterm 1
//ide used: vs code

#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // const elements to be used later

//class declaration to use linked list
class DoublyLinkedList {
private:
    //node declafration that stores one int and pointers to prev and next nodes
    struct Node {
        int data;
        Node* prev;
        Node* next;
        //constructor using parameters to store values within node
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; //pointer first node in list
    Node* tail; //pointer last node in list

public:
    //default constructor where head and tail are set to null or empty
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //function to insert node after given position
    void insert_after(int value, int position) {
        //make sure position is positive
        if (position < 0) {
            //call for the value of function to be changed if negative 
            cout << "Position must be >= 0." << endl;
            return; // and exit the function
        }

        //create new node with int value from parameter
        Node* newNode = new Node(value);
        //check if list is empty, no head node
        if (!head) {
            //if empty, set the new node equal to both the first and last node since its the only one
            head = tail = newNode;
            return; //exit function
        }

        //otherwise if there is a head node, set it equal to a temporary node that begins at the head
        Node* temp = head;
        //keep incrementing until the position is reached and while the temp node exists (not null)
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next; //keep on moving to next node

        //if position is out of bounds / goes past the range
        if (!temp) {
            //output that it the position is past the length of the lise
            cout << "Position exceeds list size. Node not inserted.\n";
            //delete the newNode
            delete newNode;
            return; //exit function
        }

        //input the new node right after the node that is found to be the position
        newNode->next = temp->next; //set newnode next val to value after temp
        newNode->prev = temp; //set newnode prev val to temp itself
        //if there was a next node for the temp
        if (temp->next)
            //set the node after the temp node's prev value = newNode
            temp->next->prev = newNode;
        else
        //otherwsie oif there was no next node or it was basically the last position
            tail = newNode; // set the tail of the list = to the new node
        temp->next = newNode; //and just set the next value 
    }

    //function to delete a specific node with "value" within the list
    void delete_val(int value) {
        //if the list is empty quit funct
        if (!head) return;

        //set the temp node to the head/first node
        Node* temp = head;
        
        //go through the list
        //while there is a temp variable and the value within it is not equal to parameter
        while (temp && temp->data != value)
            //go to the next node
            temp = temp->next;

        //if there is never a node with value that is found exit
        if (!temp) return; 


        if (temp->prev) //if there is a previous node attached to the node we want to delete
            temp->prev->next = temp->next; //set the node after the deleted one equal to the previous' next node
        else
        //else it would be the head node so set that equal to the node after the one we are going to delete
            head = temp->next; 

        //if there is a node after the one we want to delete
        if (temp->next)
        //set the node after the one we want to delete prev element to the element that was before the one we are going to delete
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; //or it will be the tail since there is no value after so set the element before the one we delete to the tail

        //delete the node that contains the value we put into function
        delete temp;
    }

    //function to delete node by position
    void delete_pos(int pos) {
        //if there is no head node
        if (!head) {
            //output list is empty and exit function
            cout << "List is empty." << endl;
            return;
        }
    
        //if the parameter is equal to 1
        if (pos == 1) {
            pop_front(); //remove the first node using other function
            return; //exit function
        }
    
        //set temporary node equal to the first element
        Node* temp = head;
    
        //for loop that stops at position of list
        for (int i = 1; i < pos; i++){
            //if position does not exist
            if (!temp) {
                cout << "Position doesn't exist." << endl; //output
                return; //exit function
            }
            else //if function exists
                temp = temp->next; // go to next node (until the position parameter)
        }
        //if no node exists at the position
        if (!temp) {
            cout << "Position doesn't exist." << endl; //output
            return; //exit function
        }
    
        //if it is the tail, or last node 
        if (!temp->next) {
            pop_back(); // use other function to delete
            return; //exit
        }
    
        //set pointers
        Node* tempPrev = temp->prev; //set a temporary previous node to the one before the deleted
        tempPrev->next = temp->next; //set this ^ node next value to the value after the one to be deleted
        temp->next->prev = tempPrev; //set the node after the one to be deleted previous element to the temporary node at the top of these pointer declarations
        delete temp; //delete the node
    }

    //add node at end of list
    void push_back(int v) {
        //craete new node with value v as data
        Node* newNode = new Node(v);
        //if the list is empty
        if (!tail)
            //set the head and tail equal to the new node
            head = tail = newNode;
        else {
            //set the value after the existing tail node equal to the new node
            tail->next = newNode;
            newNode->prev = tail; //set the new nodes previous node element equal to the existing tail node
            tail = newNode; //set the tail node within the class equal to the new node
        }
    }
    
    //function to add node at beginning of list
    void push_front(int v) { 
        Node* newNode = new Node(v); //create new node with data v
        //if list empty
        if (!head)
            //set the head and tail equal to the new node
            head = tail = newNode;
        //if list not empty
        else {
            //set the new nodes next element to the existing head node
            newNode->next = head;
            //set existing head node previous node equal to the new node
            head->prev = newNode;
            //set head node equal to new node
            head = newNode;
        }
    }
    
    //function to remove node at beginning of list
    void pop_front() {
        //if list empty
        if (!head) {
            cout << "List is empty." << endl; //output
            return; //exit function
        }

        Node * temp = head; //set temp node equal to current head or first node

        //if node after the first node
        if (head->next) {
            //set the head to the second node or node after
            head = head->next;
            head->prev = nullptr; //set the new head existing previous element to empty since its the first
        }
        else //its just one node in the list
            //set head and tail equal to null since it will be empty
            head = tail = nullptr;
        delete temp; //delete the temporary node 
    }

    //function to delete node at end of list
    void pop_back() {
        //if list empty
        if (!tail) {
            cout << "List is empty." << endl; //output
            return; //exit function
        }
        Node * temp = tail; //set temp node equal to last node in list / tail node

        //if there is a node prior to the tail basically meaning its not the only node in the list
        if (tail->prev) {
            tail = tail->prev; //set the node tail equal to the node before the existing tail node
            tail->next = nullptr; //set the next element of the new tail equal to null since it is now the tail
        }
        //if it is only one node in list
        else
            head = tail = nullptr; //set both head and tail to null since list is empty
        delete temp; //delete temp node
    }

    //destructor (clears memory)
    ~DoublyLinkedList() {
        while (head) { //while there is a node in the list specifically the first node
            Node* temp = head; //set a temp node equal to the first node
            head = head->next; //set the existing head node to the one after it
            delete temp; //delete the temp node
        }
    }
    //method to print / output list
    void print() {
        Node* current = head; //set iterator node to first node in list
        if (!current) { //if there is no head  node or list is empty essentially
            cout << "List is empty." << endl; //output
            return; //exit fucntion
        }
        while (current) { //while a node exists after being incremented
            cout << current->data << " "; //output the int stored in the node
            current = current->next; //move on to the next node in list
        }
        cout << endl; //output an empty line
    }

    //method to print / output list but backwards
    void print_reverse() {
        Node* current = tail; //set iterator node to the last node / tail
        if (!current) {  //if the list is empty / there is not tail node (has to exist if its not empty)
            cout << "List is empty." << endl; //output
            return; //exit function
        }
        while (current) { //while there is a node at current
            cout << current->data << " "; //output the int stored in this node
            current = current->prev; //move on to the previous node in list
        }
        cout << endl; //output empty line
    }

    //function that outputs every like odd element in the list (starts at 1 and skips 2 outputs 3 ...)
    void every_other_element() {
        Node* current = head; //set iterator node to first node in list
        if (!current) { //if there is no head  node or list is empty essentially
            cout << "List is empty." << endl; //output
            return; //exit function
        }
        //all code above is good

        while (current) { //while there is a node at current
            cout << current->data << " "; //output the int stored in the node
             //current = current->next->next; //move on to the node after the next node in list (got rid of cuz faults)
            //debugging: only line different from other functions is the one above, and segmentation
            //faults are correlated to accessing memeory that does not exist?
            //maybe check if there is a next variable that exists before calling it?
            if (current->next) { //if there is a node after the current
                current = current->next->next; //set the iterator node to the node after that
            }
            else { //if there is not
                return; //exit function
            }
        }
        cout << endl; //clear line
    }
};

//
int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning
    cout << endl; //clear line between this
    //testing the new class function
    //first make a list using the class declaration
    DoublyLinkedList numbers;

    //use .push_back for ease of use
    numbers.push_back(2);
    numbers.push_back(4);
    numbers.push_back(6);
    numbers.push_back(8);
    numbers.push_back(10);
    //list of 5 numbers
    // 2 4 6 8 10

    //now call for every other element function
    // expecting list below
    // 2 6 10

    numbers.every_other_element(); //call function through the list
    //first attempt: getting segmentation fault?
    //second attempt: still
    //going to quit my terminal and see if it helps (didnt help) 
    //lets look back at my function i made
    //fourth attempt (after fixing function) started outputting in infinite loop
    //lets see if regular print methods work (they do)
    // got it to work after adding the else method to stop it from keeping on output after there is like not another value :)
    return 0;
}