#pragma once
#include "Iterator.h"

template <typename T>
class L2Ring;

template <typename T>
class L2List
{
protected:
    Node<T>* buffer = nullptr;
    int size = 0;
    bool wasCleared = false;
public:
    //friend L2Ring<T>;
    friend L2Iterator<T>;
    L2List()
    {
        buffer = new Node<T>(nullptr, nullptr);
        buffer->next = buffer;
        buffer->prev = buffer;
    }
    virtual ~L2List() = default;
    virtual void push(T value, Iterator<T>* iter) = 0;
    virtual void remove(Iterator<T>* iter) = 0;
    virtual void clear() = 0;
    virtual bool empty()
    {
        return buffer->next == buffer;
    }
    virtual int length() { return size; };
    virtual Iterator<T>* iterator() = 0;
    virtual Iterator<T>* search(T value) = 0;
};


