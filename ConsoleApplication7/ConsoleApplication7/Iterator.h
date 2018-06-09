#pragma once
#include "L2ListImplementation.h"

template <typename T>
class L2List;

template <typename T>
class L2Ring;

template <typename T>
class Iterator;

template <typename T>
class L2Iterator;

template <typename T>
struct Node
{
    friend Iterator<T>;
    friend L2Iterator<T>;
    friend L2Ring<T>;
    T value;
    Node *next, *prev;
    Node(T value, Node *next, Node *prev)
    {
        this->value = value;
        this->next = next;
        this->prev = prev;
    }
    Node(Node *next, Node *prev) :Node(0, next, prev) {}
};

template <typename T>
class Iterator
{
    Node<T> *current = nullptr;
    L2List<T> *list = nullptr;
public:
    friend L2Ring<T>;
    friend L2Iterator<T>;
    virtual void start() = 0;
    virtual T get() = 0;
    virtual void next() = 0;
    virtual bool finish() = 0;
};
