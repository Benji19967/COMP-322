#include <iostream>
#include <string>
#include <algorithm> // transform(), count()
#include <map>
#include <regex>

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

void convertPhonetic() { // validate string <------------------- !! ----------------------->

    map<char, string> m = {
        { 'A', "Alfa" },
        { 'B', "Bravo" },
        { 'C', "Charlie" },
        { 'D', "Delta" },
        { 'E', "Echo" },
        { 'F', "Foxtrot" },
        { 'G', "Golf" },
        { 'H', "Hotel" },
        { 'I', "India" },
        { 'J', "Juliett" },
        { 'K', "Kilo" },
        { 'L', "Lima" },
        { 'M', "Mike" },
        { 'N', "November" },
        { 'O', "Oscar" },
        { 'P', "Papa" },
        { 'Q', "Quebec" },
        { 'R', "Romeo" },
        { 'S', "Sierra" },
        { 'T', "Tango" },
        { 'U', "Uniform" },
        { 'V', "Victor" },
        { 'W', "Whiskey" },
        { 'X', "X-ray" },
        { 'Y', "Yankee" },
        { 'Z', "Zulu" }
    };

    string s;
    cout << "Please enter a word:" << endl;
    cin.ignore(256, '\n'); // flush '\n' ingnored by cin in previous function
    
    while(true) {
        getline(cin , s);
        if(!regex_match(s, regex("^[A-Za-z]+$"))) { // make sure input only contains characters. '^': start of line. '[A-Za-z]+': one or more letter
            cout << "Please only enter alphabetical characters. Try again:" << endl;
        } 
        else break;
    }

    transform(s.begin(), s.end(), s.begin(), ::toupper);

    for(char& c : s) {
            cout << m.find(c)->second << " ";
    }
    cout << endl;

}

/* Question 3:
    Tail recursion is a model to optimize standard recursion. 
    We calculate intermediate results and keep track of it through an accumulator before calling the next recursion.
    We avoid getting a stack overflow as we can get rid of the current frame once we're ready to perform the next step.

    Standard recursion:
        fact(4)
        4 * fact(3)
        4 * (3 * fact(2))
        4 * (3 * (2 * fact(1)))
        24

    Tail recursion:
        fact(4, 1)
        fact(3, 4)
        fact(2, 12)
        fact(1, 24)
        24
*/

int fact(int n, int acc) {
    if(n == 1) return acc;

    return fact(n-1, n * acc);
}

void factorial() {
    int n;
    int acc = 1;
    
    cout << "Please enter a number:" << endl;
    cin >> n;

    cout << "The factorial of " << n << " is " << fact(n, acc) << endl;
}

int enhancedFact(int n, int acc, int (&first_six)[6]) {
    if(n <= 6) return first_six[n-1];

    return fact(n-1, n * acc);
}

void enhancedFactorial() {
    int n;
    int acc = 1;
    int first_six[6] = {1, 2, 6, 24, 120, 720};

    cout << "Please enter a number:" << endl;
    cin >> n;

    cout << "The factorial of " << n << " is " << enhancedFact(n, acc, first_six) << endl;
}

int main() {
    countLetter(); 
    convertPhonetic(); 
    factorial(); 
    enhancedFactorial(); 
    return 0;
}