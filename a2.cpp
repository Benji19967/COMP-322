#include <iostream>
#include <stdlib.h>

using namespace std;

struct ticket {
    unsigned int numbers[6];
    ticket* next;
};

class SuperDraw {
    public:
        SuperDraw();                            // Constructor
        SuperDraw(int n);                       // Constructor
        SuperDraw(const SuperDraw & obj);       // Constructor
        ~SuperDraw();                           // Destructor
        
        void newTicket(int verbose);            // class methods
        void printAllTicketNumbers();
        void verifySequence(int numbers[6]); 
        void deleteSequence(int numbers[6]); 
    
    private:
        ticket* ticketListHead;
        ticket* ticketListTail;
};

SuperDraw::SuperDraw() {
    this->ticketListHead = NULL;
    this->ticketListTail = NULL;
}

// Method to add a new Ticket to the Linked List
void SuperDraw::newTicket(int verbose = 0) {
    ticket* tick = new ticket;                  // allocate memory for a new ticket
    
    for(int i = 0; i < 6; i++) {                // generate 6 random numbers between 0-99
        int num = rand() % 100;
        tick->numbers[i] = num;
    }
    
    sort(tick->numbers, tick->numbers + 6);     // sort in increasing order
    
    tick->next = NULL;
    if(ticketListHead == NULL) {
        ticketListHead = tick;
    } 
    else {
        ticketListTail->next = tick;
    }
    ticketListTail = tick;

    if(verbose == 1) {
        cout << "A new ticket was successfully generated. The numbers are: ";
        for(int i = 0; i < 6; i++) {
            cout << tick->numbers[i] << ", ";
        }
        cout << endl;
    }
}

// Constructor to create the requested number of tickets
SuperDraw::SuperDraw(int n) {
    cout << n << " new ticket were successfully generated." << endl;
    cout << "The numbers are: ";
    
    // Create n new tickets and print the numbers
    for(int i = 0; i < n; i++) {
        SuperDraw sd;
        sd.newTicket(0);
        for(int i = 0; i < 6; i++) {
            cout << sd.ticketListTail->numbers[i];
            if(i != 5) cout << ", ";
            else cout << " ";
        }
        if(i == n-2) cout << "and ";
    }
    cout << endl;
}

// Method to print all Ticket Numbers
void SuperDraw::printAllTicketNumbers() {
    ticket* curr = this->ticketListHead;
    
    // Find number of tickets
    int count = 0;
    while(curr != NULL) {
        count++;
        curr = curr->next;
    }

    // Print the numbers of each ticket
    curr = this->ticketListHead;
    cout << "We found " << count << " generated tickets:" << endl;
    while(curr != NULL) {
        for(int i = 0; i < 6; i++) {
            cout << curr->numbers[i];
            if(i != 5) cout << ", ";
            else cout << " " << endl;
        }
        curr = curr->next;
    }
}

// Method to check if a Ticket was already generated
void SuperDraw::verifySequence(int numbers[6]) {
    ticket* curr = this-> ticketListHead;
    
    // For each ticket check if all 6 numbers match
    while(curr != NULL) {
        int count = 0;
        for(int i = 0; i < 6; i++) {
            if(curr->numbers[i] == numbers[i]) count++;
            if(count == 6) {
                cout << "The provided sequence of numbers was already generated." << endl;
                return;
            }
        }
        curr = curr->next;
    }
    cout << "The provided sequence of numbers was never generated before" << endl;
}

// Method to delete a sequence
void SuperDraw::deleteSequence(int numbers[6]) {
    ticket* curr = this->ticketListHead;
    ticket* prev = this->ticketListHead;
    
    // Go through each ticket, delete it if found one that matches given sequence and update pointers
    while(curr != NULL) {
        int count = 0;
        for(int i = 0; i < 6; i++) {
            if(curr->numbers[i] == numbers[i]) count++;
            if(count == 6) {
                if(curr == this->ticketListHead && curr == this->ticketListTail) {
                    this->ticketListHead = NULL;
                    this->ticketListTail = NULL;
                } 
                else if (curr == this->ticketListHead) {
                    this->ticketListHead = curr->next;
                }
                else if (curr == this->ticketListTail) {
                    this->ticketListTail = prev;
                    prev->next = NULL;
                } 
                else prev->next = curr->next;
                
                // Delete allocated memory to avoid memory leaks
                delete[] curr;
                cout << "The provided sequence of numbers was successfully deleted." << endl;
                return;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "The provided sequence of numbers was never generated before" << endl;
}

// Destructor to delete all tickets to ensure we don't have memory leaks
SuperDraw::~SuperDraw() { 
    ticket* curr = this->ticketListHead;
    while(curr != NULL) {
        ticket* temp = curr->next;
        delete[] curr;
        curr = temp;
    }
}

// Copy Constructor to make a deep copy an Object into another
SuperDraw::SuperDraw(const SuperDraw & obj) {
    ticket* curr = obj.ticketListHead;
    ticket* prev = NULL;

    this->ticketListHead = new ticket;

    while(curr != NULL) {
        ticket* tick = new ticket;
        for(int i = 0; i < 6; i++) {
            tick->numbers[i] = curr->numbers[i];
        }
        if(curr == obj.ticketListHead) {
            this->ticketListHead = tick;
        } 
        if(curr == obj.ticketListTail) {
            this->ticketListTail = tick;
        }
        if(prev != NULL) {
            prev->next = tick;
        }
        prev = tick;
        curr = curr->next;
    }
}

int main() {
    // SuperDraw sd;
    // sd.newTicket(1);

    // SuperDraw sd(2);

    // SuperDraw sd;
    // sd.newTicket();
    // sd.newTicket();
    // sd.newTicket();
    // sd.newTicket();
    // sd.printAllTicketNumbers();
   
    // SuperDraw sd;
    // sd.newTicket();
    // // as many sd.newTicket() as you like
    // int myNumbers[6] = {2, 4, 17, 29, 31, 34};
    // sd.verifySequence(myNumbers);

    // SuperDraw sd;
    // sd.newTicket();
    // // as many sd.newTicket() as you like
    // int myNumbers[6] = {2, 4, 17, 29, 31, 34};
    // sd.deleteSequence(myNumbers);


    SuperDraw sd;
    sd.newTicket();
    // as many sd.newTicket() as you like
    SuperDraw sd2(sd);
    sd2.printAllTicketNumbers();
}