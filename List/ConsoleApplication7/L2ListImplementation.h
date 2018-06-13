#pragma once
#include "L2List.h"
#include "Iterator.h"

template <typename T>
class L2Ring;

template <typename T>
class L2Iterator : public Iterator<T>
{
    L2Iterator(L2List<T> *list, Node<T>* node)
    {
        this->list = list;
        current = node;
    }
public:
    friend L2Ring<T>;

    L2Iterator(L2List<T> *list)
    {
        this->list = list;
        current = list->buffer;
    }

    ~L2Iterator()
    {
        current = nullptr;
        list = nullptr;
    }
    void start() override { current = list->buffer->next; }

    T get() override 
    {
        if(list->empty()) throw std::runtime_error("Empty list");
        if(finish()) throw std::runtime_error("End of list, please start iterator");
        return current->value; 
    }
    
    void next() override
    {
        if(list->empty()) throw std::runtime_error("Empty list");
        if(finish()) throw std::runtime_error("End of list, please start iterator");
        current = current->next;
    }
    
    bool finish() override
    {
        return  current == list->buffer;
    }
};

template <typename T>
class L2Ring : public L2List<T> 
{
public:
    friend L2Iterator<T>;

    L2Ring()
    {
        buffer = new Node<T>(nullptr, nullptr);
        buffer->next = buffer;
        buffer->prev = buffer;
    }

    ~L2Ring()
    {
        clear();
    }
    /*pushes backwards,
    no iterator needed*/
    void push(T value)
    {
        Node<T> *temp = buffer->prev, *cur = new Node<T>(value, buffer, temp);
        buffer->prev = cur;
        temp->next = cur;
        size++;
    }

    void push(T value, Iterator<T> *iter) override
    {
        if(iter == nullptr)throw std::runtime_error("No actual iterator");
        Node<T> * temp = iter->current->prev;
        iter->current->prev = new Node<T>(value, iter->current, temp);
        temp->next = iter->current->prev;
        size++;
    }

    void remove(Iterator<T> *iter) override
    {
        if(iter == nullptr)throw std::runtime_error("No actual iterator");
        if(size <= 0 ) throw std::runtime_error("Nothing to remove");
        if(iter->finish()) throw std::runtime_error("End of list, please start iterator");

        Node<T>* temp = iter->current->next, *del = iter->current;
        iter->current = iter->current->prev;
        temp->prev = iter->current;
        iter->current->next = temp;
        delete del;
        size--;
    }

    Iterator<T>* search(T value) override 
    { 
        Iterator<T> *res = iterator();
        res->start();
        while(!res->finish())
        {
            if(res->get() == value)return res;
            res->next();
        }
        return nullptr;
    }

    void clear() override {
        if(empty())return;
        Node<T> *temp = buffer;
        Node<T> *curr = nullptr;
        temp = temp->next;
        while(temp->next != buffer)
        {
            curr = temp->next;
            temp->prev = nullptr;
            temp->next = nullptr;
            delete temp;
            temp = curr;
        }
        delete temp;
        buffer->next = buffer;
        buffer->prev = buffer;
        size = 0;
    }

    Iterator<T>* iterator() override {
        Iterator<T>* temp =  new L2Iterator<T>(this);
        return temp;
    }

    L2Ring<T>& operator=(const L2List<T> &other)
    {
        L2Ring r;
        Iterator<T> iter = other.iterator();
        Iterator<T> c = r.iterator();
        while(!iter.finish())
        {
            r.push(iter.get());
            iter.next();
        }
        return r;
    }
};