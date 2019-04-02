#include <iostream>
#include <vector>

using namespace std;

/* Question 1 - Smart Pointers in the standard library
    - std::unique_ptr:

    - std::shared_ptr:

    - std::weak_ptr:
*/


// Exceptions

class NegativeException: public exception {
    virtual const char* what() const throw() {
        return "Warning: negative number";
    }
};

class SizeException: public exception {
    virtual const char* what() const throw() {
        return "Warning: different sizes";
    }
};
class MissMatchException: public exception {
    virtual const char* what() const throw() {
        return "Warning: Miss match";
    }
};

NegativeException negNumExc;
SizeException diffSizes;
MissMatchException missMatch;

template <class T> class SmartPointer {
    private:
        T *p;
        T *arr;
        int size;
    
    public:
        SmartPointer();                     // Constructor int
        SmartPointer(T x);                  // Constructor int
        SmartPointer(bool flag, size_t s);  // Constructor array
        SmartPointer(int s, T values[]);    // Constructor array
        ~SmartPointer();                    // Destructor

        T getValue();                       // Int
        T getValue(int index);              // Array
        void printAllValues();              // Array
        void setValue(T x);                 // Int
        void setValue(int index, T val);    // Array


        // Operator overloading

        friend SmartPointer<T> operator+(const SmartPointer<T>& pointer1, const SmartPointer<T>& pointer2) {
            if(pointer1.p != nullptr && pointer2.p != nullptr) {
                SmartPointer<T> result;
                *result.p = *pointer1.p + *pointer2.p;
                return result;
            }
            else if(pointer1.arr != nullptr && pointer2.arr != nullptr) {
                if(pointer1.size != pointer2.size) throw diffSizes;
                SmartPointer<T> result(true, pointer1.size);
                for(int i = 0; i < pointer1.size; i++) {
                    result.arr[i] = pointer1.arr[i] + pointer2.arr[i];
                }
                return result;
            } 
            else {
                throw missMatch;
            }
        }
        friend SmartPointer<T> operator-(const SmartPointer<T>& pointer1, const SmartPointer<T>& pointer2) {
            if(pointer1.p != nullptr && pointer2.p != nullptr) {
                SmartPointer<T> result;
                *result.p = *pointer1.p - *pointer2.p;
                return result;
            }
            else if(pointer1.arr != nullptr && pointer2.arr != nullptr) {
                if(pointer1.size != pointer2.size) throw diffSizes;
                SmartPointer<T> result(true, pointer1.size);
                for(int i = 0; i < pointer1.size; i++) {
                    result.arr[i] = pointer1.arr[i] - pointer2.arr[i];
                }
                return result;
            } else {
                throw missMatch;
            }
        }
        friend SmartPointer<T> operator*(const SmartPointer<T>& pointer1, const SmartPointer<T>& pointer2) {
            if(pointer1.p != nullptr && pointer2.p != nullptr) {
                SmartPointer<T> result;
                *result.p = *pointer1.p * *pointer2.p;
                return result;
            }
            else if(pointer1.arr != nullptr && pointer2.arr != nullptr) {
                if(pointer1.size != pointer2.size) throw diffSizes;
                SmartPointer<T> result(true, pointer1.size);
                for(int i = 0; i < pointer1.size; i++) {
                    result.arr[i] = pointer1.arr[i] * pointer2.arr[i];
                }
                return result; 
            } 
            else {
                throw missMatch;
            }
        }
};


// Constructors

template <class T> SmartPointer<T>::SmartPointer() {
    p = new T(0);
    arr = nullptr;
}
template <class T> SmartPointer<T>::SmartPointer(T val) {
    if(val < 0) throw negNumExc;
    p = new T(val);
    arr = nullptr;
}
template <class T> SmartPointer<T>::SmartPointer(bool array, size_t s) {
    p = nullptr;
    arr = new T[s]();
    size = s;
}
template <class T> SmartPointer<T>::SmartPointer(int s, T values[]) {
    p = nullptr;
    size = s;
    arr = new T[s];
    for(int i = 0; i < s; i++) {
        arr[i] = values[i];
    }
}


// Destructor

template <class T> SmartPointer<T>::~SmartPointer() {
    if(p != nullptr) delete p;
    if(arr != nullptr) delete[] arr;
}


// Get values

template <class T> T SmartPointer<T>::getValue() {
    return *p;
}
template <class T> T SmartPointer<T>::getValue(int index) {
    return arr[index];
}
template <class T> void SmartPointer<T>::printAllValues() {
    int n = size;
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


// Set values

template <class T> void SmartPointer<T>::setValue(T x) {
    *p = x;
}
template <class T> void SmartPointer<T>::setValue(int index, T val) {
    arr[index] = val;
}


int main() {

    // For SmartPointer class
    cout << "Testing SmartPointer class" << endl;

    // Testing Constructors
    cout << "Creating a SmartPointer of type int with value 11" << endl;
    SmartPointer<int> SmartIntPointer1(11);
    cout << "SmartIntPointer1 = " << SmartIntPointer1.getValue() << endl;

    cout << "Creating a SmartPointer of type int with value -1" << endl;
    try {
        SmartPointer<int> SmartIntPointer(-1);
    } catch (exception& e) {            
        cout << e.what() << endl;
    }

    cout << "Creating a SmartPointer of type int with no value provided" << endl;
    SmartPointer<int> SmartIntPointer2;
    cout << "SmartIntPointer2 = " << SmartIntPointer2.getValue() << endl;

    // Testing Setter & Getter
    cout << "Setting value of SmartIntPointer2 to 5" << endl;
    SmartIntPointer2.setValue(5);
    cout << "SmartIntPointer2 = " << SmartIntPointer2.getValue() << endl;

    cout << "Creating a SmartPointer of type float with no value provided" << endl;
    SmartPointer<float> SmartFloatPointer1;
    cout << "SmartFloatPointer1 = " << SmartFloatPointer1.getValue() << endl;

    cout << "Setting value of SmartFloatPointer1 to 1.5" << endl;
    SmartFloatPointer1.setValue(1.5);
    cout << "SmartFloatPointer1 = " << SmartFloatPointer1.getValue() << endl;

    cout << "Creating a SmartPointer of type float with no value provided" << endl;
    SmartPointer<float> SmartFloatPointer2;
    cout << "SmartFloatPointer2 = " << SmartFloatPointer2.getValue() << endl;

    cout << "Setting value of SmartFloatPointer2 to 2.5" << endl;
    SmartFloatPointer2.setValue(2.5);
    cout << "SmartFloatPointer2 = " << SmartFloatPointer2.getValue() << endl;

    SmartPointer<float> SmartFloatPointer3 = SmartFloatPointer1 + SmartFloatPointer2;
    cout << "SmartFloatPointer1 + SmartFloatPointer2 = " << SmartFloatPointer3.getValue() << endl;

    SmartPointer<float> SmartFloatPointer4 = SmartFloatPointer2 - SmartFloatPointer1;
    cout << "SmartFloatPointer2 - SmartFloatPointer1 = " << SmartFloatPointer4.getValue() << endl;

    SmartPointer<float> SmartFloatPointer5 = SmartFloatPointer1 * SmartFloatPointer2;
    cout << "SmartFloatPointer1 * SmartFloatPointer2 = " << SmartFloatPointer5.getValue() << endl;

    // For handling arrays
    cout << "Testing arrays" << endl;

    // New pointer to array
    SmartPointer<int> ArrP1(true, 10);
    ArrP1.setValue(5, 17);
    cout << "ArrP1: "; ArrP1.printAllValues();

    // New pointer to array
    SmartPointer<int> ArrP2(true, 10);
    ArrP2.setValue(5, 10);
    ArrP2.setValue(6, 11);
    cout << "ArrP2: "; ArrP2.printAllValues();


    int arr[5] = {1, 2, 3, 4, 5};
    SmartPointer<int> ArrP3(5, arr);
    cout << "ArrP3: "; ArrP3.printAllValues();
    int arr2[5] = {5, 5, 5, 5, 5};
    SmartPointer<int> ArrP5(5, arr2);
    cout << "ArrP5: "; ArrP5.printAllValues();


    // Add two arrays
    cout << "ArrP1 + ArrP2:" << endl;
    SmartPointer<int> ArrP4 = ArrP1 + ArrP2;
    ArrP4.printAllValues();

    // Mult
    cout << "ArrP3 * ArrP5:" << endl;
    SmartPointer<int> ArrP6 = ArrP3 * ArrP5;
    ArrP6.printAllValues();

    // add the needed code that shows how you use your class to create an array of multiple elements of a certain type.
    // provide all the necessary test code that shows the different use cases of your code
    
}