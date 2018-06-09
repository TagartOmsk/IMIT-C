#pragma once
template <typename T>
class RingBuffer
{
private:
    T* queue;
    int length, fullness, head = 0, back = 0;
public:
    class Iterator
    {
    private:
        RingBuffer* buffer;
        int count = 0, current = 0;
    public:
        Iterator(RingBuffer<T> *queue)
        {
            count = 0;
            current = -1;
            buffer = queue;
        }
        ~Iterator()
        {
            buffer = nullptr;
        }
        void start()
        {
            if(buffer->fullness == 0) throw std::runtime_error("Buffer is empty. Please, fill it.");
            count = 0;
            current = buffer->head;
        }
        void next()
        {
            if(finish()) throw std::runtime_error("Iteration is already finished");
            current = ++current % buffer->fullness;
            count++;
        }
        bool finish()
        {
            return count == buffer->length - 1;
        }
        T getValue()
        {
            return buffer->queue[current];
        }
        int position()
        {
            return current + 1;
        }
    };

    RingBuffer(int size)
    {
        queue = new T[size];
        this->length = size;
        this->fullness = 0;
    }
    ~RingBuffer()
    {
        delete[] queue;
    }

    void push(T value)
    {
        if(fullness == length) throw std::runtime_error("Buffer is full");
        queue[back] = value;
        if(back < length)back++;
        else back = 0;
        fullness++;
    }
    T pop()
    {
        if(this->empty()) throw std::runtime_error("Buffer is empty");
        T temp = queue[head];
        if(head < length)head++;
        else head = 0;
        fullness--;
        return temp;
    }
    T top()
    {
        if(this->empty()) throw std::runtime_error("Buffer is empty");
        return queue[head];
    }
    int size()
    {
        return length;
    }
    void clear()
    {
        head = 0;
        back = 0;
        fullness = 0;
    }
    bool empty()
    {
        return head == back;
    }
};