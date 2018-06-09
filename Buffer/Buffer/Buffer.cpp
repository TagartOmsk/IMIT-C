#include "stdafx.h" 
#include <iostream>
#include <ctime>
#include "ringbuffer.h"


int main()
{
    srand(time(0));
    int a = 0, b = 0;
    bool exit = false, ext1 = false;;
    std::cout << "Insert size: ";
    std::cin >> a;
    RingBuffer<int> *que = new RingBuffer<int>(a);
    RingBuffer<int>::Iterator iter(que);
    while(!exit)
    {
        std::cout << "1.Push" << std::endl;
        std::cout << "2.Pop" << std::endl;
        std::cout << "3.Top" << std::endl;
        std::cout << "4.Random filling" << std::endl;
        std::cout << "5.Exit" << std::endl;
        std::cout << "6.Clear" << std::endl;
        std::cout << "7.Switch Iterator" << std::endl;
        std::cin >> a;
        system("cls");
        switch(a)
        {
        case 1: std::cout << "Insert value: ";
            std::cin >> b;
            try 
            { 
                que->push(b);
            }
            catch(std::exception e)
            {
                std::cerr << e.what() << std::endl;
            }break;
        case 2: 
            try 
            { 
                std::cout << "Head value: " << que->pop() << std::endl; 
            }
            catch(std::runtime_error e) 
            {
                std::cerr << e.what() << std::endl;
            } 
            break;
        case 3: 
            try
            {
            std::cout << "Head value: " << que->top() << std::endl;
            }
            catch(std::runtime_error e)
            {
                std::cerr << e.what() << std::endl;
            }
            break;
        case 4: 
            while(true)
            {
                try 
                { 
                    que->push(rand());
                }
                catch(std::runtime_error e)
                {
                    std::cout << "Filled succsessfully" << std::endl;
                    break;
                }; 
            }; 
            break;
        case 5: exit = true; break;
        case 6: que->clear(); break;
        case 7: 
            system("cls");
            ext1 = false;
            try { iter.start(); }
            catch(std::runtime_error e)
            {
                std::cerr << e.what() << std::endl;
                break;
            }
            while(!ext1)
            {
                std::cout << "At: "<< iter.position() << std::endl;
                std::cout << "Value: " << iter.getValue() << std::endl;
                std::cout << "1.Exit" << std::endl;
                std::cout << "2.Move to next element" << std::endl;
                std::cout << "3.Get current value" << std::endl;
                std::cout << "4.Is iteration finished" << std::endl;
                std::cout << "5.Restart" << std::endl;
                std::cin >> a;
                system("cls");
                switch(a)
                {
                case 1: ext1 = true; break;
                case 2:
                    try
                    {
                        iter.next();
                    }
                    catch(std::runtime_error e)
                    {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case 3:std::cout << iter.getValue() << std::endl; break;
                case 4:iter.finish() ? std::cout << "Yes" << std::endl  : std::cout << "No" << std::endl; break;
                case 5:iter.start(); break;
                }
            }
            break;
        }
    }
    system("pause");
    return 0;
}