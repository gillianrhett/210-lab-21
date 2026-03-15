// COMSC-210 | Lab 21 | Gillian Rhett

#include <iostream>
#include <array>
using namespace std;
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // constants from the original file
const int NAMES_SIZE = 15, COLORS_SIZE = 15, AGE_MIN = 1, AGE_MAX = 20; // my new constants for Goat class
class DoublyLinkedList {
    private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };
    Node* head;
    Node* tail;
    public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }
    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail) // if there's no tail, the list is empty
        head = tail = newNode;
        else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        }
    }
    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head) // if there's no head, the list is empty
        head = tail = newNode;
        else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        }
    }
    void insert_after(int value, int position) {
        if (position < 0) {
        cout << "Position must be >= 0." << endl;
        return;
        }
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
        temp = temp->next;
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }
    void delete_node(int value) {
        if (!head) return; // Empty list
        Node* temp = head;
        while (temp && temp->data != value)
        temp = temp->next;
        if (!temp) return; // Value not found
        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }
        delete temp;
    }
    void print() {
        Node* current = head;
        if (!current) return;
            while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class Goat {
    int age;
    string name;
    string color;
    string names[NAMES_SIZE] {"Craig", "Katina", "Mike", "Blair", "Lorene", "Sol", "Ken", "Tony",
                        "Haley", "Leslie", "Harrison", "Tyler", "Carlene", "Sanford", "Whitney"};
    string colors[COLORS_SIZE] = {"light brown", "red", "light gray", "medium gray", "dark gray", 
                        "black", "white", "medium brown", "dark brown", "tan", "yellow", "orange",
                        "spotted", "striped", "beige",}; 

    public:
    // default constructor
    Goat() {
        /*
        The default constructor will randomly assign:
        an age, 1-20
        a name, randomly selected from the 15-element names[] array
        a color, randomly selected from the 15-element colors[] array
        The parameter constructor will be a typical 3-element parameter setup.
        */
        srand(time(0)); // set the seed for rand()
        age = (rand() % (AGE_MIN - AGE_MAX + 1)) + AGE_MIN;
        // set the name by randomly selecting from names array
        int i = (rand() % (NAMES_SIZE));
        name = names[i];
        // set the name by randomly selecting from colors array
        i = (rand() % (COLORS_SIZE));
        color = colors[i];
    }

    // parameter constructor
    Goat(int a, string n, string c) {
        age = a;
        name = n;
        color = c;
    }
};

// Driver program
int main() {
    /*
    _ Task. Modify the DoublyLinkedList class's push_front() and push_back() functions such 
    that it has a Goat object as a parameter, rather than an int. 

    _ Task. In main(), create a DoublyLinkedList object. Append to it a random number of Goat 
    objects, range 5-20 or so.

    _ Task. In main(), call your methods to print both forward and backward to show the proper 
    traversals.

    _ Task. Use srand(time(0)); as one of your first lines in main() to randomize your random 
    numbers.

    _ Task. Update both of the print() methods that are in the class. Both should display the 
    text "List is empty" if the list is empty; otherwise, output the list as shown in the sample output below.
    */
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();
    cout << "List backward: ";
    list.print_reverse();
    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();
    return 0;
}
