#include <iostream>
#include <vector>

using namespace std;

/* Question 1 - Smart Pointers in the standard library
    - std::unique_ptr:  Can point to one Object. As soon as the pointer goes out of scope the Object is was pointing to is deleted.

    - std::shared_ptr:  Pointer can be copied. There is a count for how many pointers point to an Object. If the count goes to 0, the Object is deleted.

    - std::weak_ptr:    Pointer to hold a non-owning reference to an object managed by shared_ptr. Can access object temporarily if it exists. 
*/


// Exceptions

class NegativeException: public exception {
    virtual const char* what() const throw() {
        return "Warning: negative number";
    }
};

class SizeException: public exception {
    virtual const char* what() const throw() {
        return "Warning: Arrays have different sizes";
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

    private:
        T *p;
        T *arr;
        int size;
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

    cout << endl;

    // For handling arrays
    cout << "Testing arrays -- Assume arrays can have negative values" << endl << endl;
    
    // New pointer to array
    cout << "New Array P1 of size 10. Initialized with 0's:" << endl;
    SmartPointer<int> ArrP1(true, 10);
    cout << "ArrP1: "; ArrP1.printAllValues();
    cout << "Set value at index 5 to 17:" << endl;
    ArrP1.setValue(5, 17);
    cout << "ArrP1: "; ArrP1.printAllValues();
    cout << endl;

    // New pointer to array
    cout << "New Array P1 of size 10. Set index 5 to 10, index 6 to 11. Get index 6:" << endl;
    SmartPointer<int> ArrP2(true, 10);
    ArrP2.setValue(5, 10);
    ArrP2.setValue(6, 11);
    cout << "ArrP2: "; ArrP2.printAllValues();
    cout << "ArrP2 index 6: " << ArrP2.getValue(6) << endl;
    cout << endl;

    // New pointers to arrays
    cout << "Arr 3 and Arr 4 are initialized to have values of other arrays: " << endl;
    int arr[5] = {1, 2, 3, 4, 5};
    SmartPointer<int> ArrP3(5, arr);
    cout << "ArrP3: "; ArrP3.printAllValues();
    int arr2[5] = {5, 5, 5, 5, 5};
    SmartPointer<int> ArrP4(5, arr2);
    cout << "ArrP4: "; ArrP4.printAllValues();
    cout << endl;

    // Operator Overloading

    cout << "Operator Overloading: " << endl;
    // Addition
    cout << "Addition: ArrP3 + ArrP4 = ";
    SmartPointer<int> ArrP5 = ArrP3 + ArrP4;
    ArrP5.printAllValues();

    // Subtraction
    cout << "Subtraction: ArrP3 - ArrP4 = ";
    SmartPointer<int> ArrP6 = ArrP3 - ArrP4;
    ArrP6.printAllValues();

    // Multiplication
    cout << "Multiplication: ArrP3 * ArrP4 = ";
    SmartPointer<int> ArrP7 = ArrP3 * ArrP4;
    ArrP7.printAllValues();
    cout << endl;

    cout << "Try to Add/Sub/Mult arrays with different sizes: " << endl;
    try {
        SmartPointer<int> ArrP8 = ArrP1 + ArrP4;
        ArrP5.printAllValues();
    } catch (exception& e) {            
        cout << e.what() << endl;
    }
    cout << endl;

    cout << "Try to Add/Sub/Mult array with single variable: " << endl;
    try {
        SmartPointer<int> ArrP8 = ArrP1 + SmartIntPointer1;
        ArrP5.printAllValues();
    } catch (exception& e) {            
        cout << e.what() << endl;
    }
}