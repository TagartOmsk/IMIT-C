#pragma once 
#include <Exception>
#include <iostream>

class Vector
{
private:
    int* arr;
    int size = 0, resSize = 0;
public:
    struct UnmatchingSizesException 
    {
        
    };
    struct ZeroSizeException
    {

    };
    struct OutOfBoundsException
    {

    };
    ~Vector ();
    Vector ();
    Vector (int);
    Vector (int, int);
    Vector (int, int, int);
    Vector (Vector&);
    Vector (Vector&&);

    //methods 
    int length ();
    int& operator [](int pos);
    void reSize (int newSize);
    Vector& operator =(Vector&);
    Vector& operator =(Vector&&);
    friend bool operator ==(const Vector&, const Vector&);
    friend bool operator !=(const Vector&, const Vector&);
    friend bool operator >(const Vector&, const Vector&);
    friend bool operator <(const Vector&, const Vector&);
    friend bool operator >=(const Vector&, const Vector&);
    friend bool operator <=(const Vector&, const Vector&);
    friend Vector operator +(Vector&, Vector&);
    friend std::ostream& operator<<(std::ostream& , Vector&);
    friend std::istream& operator>>(std::istream&, Vector&);
    void reserve (int);
    int capacity ();
    void pushBack (int);
    int popBack ();
};