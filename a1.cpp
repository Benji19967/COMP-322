#include <iostream>
#include <string>
#include <algorithm> // transform(), count()

using namespace std;

void countLetter() {

    string s;
    char c;

    cout << "Please enter a sentence:" << endl;    
    getline(cin, s);
    cout << "Please enter a letter:" << endl;
    cin >> c;
    c = tolower(c); 

    transform(s.begin(), s.end(), s.begin(), ::tolower); // all letters in sentence lowercase
    size_t n = count(s.begin(), s.end(), c); 

    cout << "The letter " << c << " is repeated " << n << " times in your sentence." << endl;
}

void convertPhonetic() {


}


int main() {
    //countLetter(); 
    convertPhonetic(); 
    //factorial(); 
    //enhancedFactorial(); 
    return 0;
}