#include "stdafx.h" 
#include "Vector.h" 

Vector::Vector ()
{
    this->size = 5;
    this->arr = new int[5];
    for (int i = 0; i < this->size; i++)
    {
        arr[i] = 0;
    }
}
Vector::Vector (int size)
{
    this->size = size;
    this->arr = new int[size];
    for (int i = 0; i < this->size; i++)
    {
        arr[i] = 0;
    }
}
Vector::Vector (int size, int value)
{
    this->size = size;
    this->arr = new int[size];
    for (int i = 0; i < this->size; i++)
    {
        arr[i] = value;
    }
}
Vector::Vector(int size, int value, int reserve)
{
    this->size = size;
    this->resSize = reserve;
    this->arr = new int[size + reserve];
    for(int i = 0; i < this->size; i++)
    {
        arr[i] = value;
    }
}

Vector::Vector (Vector& orig)
{
    this->size = orig.size;
    arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        this->arr[i] = orig.arr[i];
    }
}

Vector::Vector (Vector&& orig)
{
    if (this == &orig)
    {
        return;
    }
    this->size = orig.size;
    this->arr = orig.arr;
    orig.arr = nullptr;
    //delete &orig;
}

Vector::~Vector ()
{
    delete[] arr;
}


int& Vector::operator[](int pos)
{
    if(pos < 0 || pos >= size)throw Vector::OutOfBoundsException();
    return arr[pos];
}

int Vector::length ()
{
    return this->size;
}

void Vector::reSize (int newSize)
{
    int* temp;
    if(newSize <= size + resSize)
    {
        for(int i = size; i < newSize; i++)
        {
            arr[i] = 0;
        }
        resSize = size + resSize - newSize;
        size = newSize;
    }
    else
    {
        temp = this->arr;
        arr = new int[newSize];
        for(int i = 0; i < size; i++)
        {
            arr[i] = temp[i];
        }
        for(int i = size; i < newSize; i++)
        {
            arr[i] = 0;
        }
        size = newSize;
        resSize = 0;
        delete[] temp;
    }
}

Vector& Vector::operator=(Vector& orig)
{
    if (this == &orig)return *this;
    size = orig.size;
    arr = new int[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = orig.arr[i];
    }
    return *this;
}

Vector& Vector::operator=(Vector&& orig)
{
    if (this == &orig)return *this;
    size = orig.size;
    arr = orig.arr;
    orig.arr = nullptr;
    return *this;
}

bool operator==(const Vector& a, const Vector& b)
{
    if (a.size != b.size)throw Vector::UnmatchingSizesException();
    for (int i = 0; i < a.size; i++)
    {
        if (a.arr[i] != b.arr[i])return false;
    }
    return true;
}

bool operator!=(const Vector& a, const Vector& b)
{
    return !(a == b);
}

bool operator>(const Vector& a, const Vector& b)
{
    for (int i = 0; i < std::fmin(a.size, b.size); i++)
    {
        if (a.arr[i] < b.arr[i])return false;
        if (a.arr[i] > b.arr[i])return true;
    }
    if (a.size == b.size)
    {
        return false;
    }
    else
    {
        if (a.size < b.size)return false;
        else return true;
    }
    
}

bool operator<(const Vector& a, const Vector& b)
{
    return (b > a);
}

bool operator>=(const Vector& a, const Vector& b)
{
    return !(a < b);
}

bool operator<=(const Vector& a, const Vector& b)
{
    return !(a > b);
}

Vector operator+(Vector& a, Vector& b)
{
    Vector res (a.length() + b.length());
    for (int i = 0; i < res.length (); i++)
    {
        if (i < a.length ()) res[i] = a.arr[i];
        else res[i] = b.arr[i - a.length ()];
    }
    return res;
}

std::ostream& operator<<(std::ostream& stream, Vector& a)
{
    for (int i = 0; i < a.length (); i++)
    {
        stream << a[i] << " ";
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, Vector& a)
{
    for (int i = 0; i < a.length (); i++)
    {
        stream >> a[i];
    }
    return stream;
}

void Vector::reserve (int reservedSize)
{
    resSize = reservedSize;
    int*temp = arr;
    arr = new int[size + resSize];
    for (int i = 0; i < size + resSize; i++)
    {
        if (i < size) arr[i] = temp[i];
        else arr[i] = 0;
    }
    delete[] temp;
}

int Vector::capacity ()
{
    return resSize;
}

int Vector::popBack()
{
    if(size == 0) throw  Vector::ZeroSizeException();
    size--;
    resSize++;
    return arr[size];
}

void Vector::pushBack(int value)
{
    if(resSize <= 0)
    {
        this->reserve((size + 1) / 2);
    }
    arr[size] = value;
    size++;
    resSize--;
}