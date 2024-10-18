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
        //go through the list with for loop ad keep on incrementing right before it reaches the value 
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


        if (temp->prev) //if there is a previous value attached to the value we want to delete
            temp->prev->next = temp->next; //set the value after the deleted one equal to the previous next value
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}