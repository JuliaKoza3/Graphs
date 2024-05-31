// Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

template<typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t length;

    //resize vector by allocating new array
    void resize(size_t newCapacity)
    {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < length; ++i)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:

    //constructor
    Vector()
    {
        this->data = NULL;
        this->capacity = 0;
        this->length = 0;
    } 

    //adding element to the vector on the back
    void push_back(int& value) 
    {
        if (length >= capacity)
        {
            size_t newCapacity;
            if (capacity == 0)
            {
                newCapacity = 1;
            }
            else
            {
                newCapacity = capacity * 2;
            }
            resize(newCapacity);
        }
        data[length++] = value;
    }

    //returning the reference to the specific element in the vector
    T& operator[](size_t index) 
    {
        if (index >= length)
        {
            exit(1);
        }
        return data[index];
    }

    //checaking if vector is empty
    bool empty() const
    {
        return length == 0;
    }

    //resizing vector
    void resizeNow(size_t newSize)
    {
        if (newSize > capacity)
        {
            resize(newSize);
        }
        length = newSize;
    }

    //clearing vector
    void clear() 
    {
        delete[] data;
        data = nullptr;
        capacity = 0;
        length = 0;
    }

    //return pointer to first elemnt of the vector, can be modified
    T* begin()
    { 
        return data; 
    }

    //return pointer to last elemnt of the vector, can be modified
    T* end() 
    { 
        return data + length; 
    }

    //return pointer to fisrt elemnt of the vector, can not be modified
    const T* begin() const
    { 
        return data; 
    }

    //return pointer to last elemnt of the vector, can not be modified
    const T* end() const 
    { 
        return data + length; 
    }

};




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
