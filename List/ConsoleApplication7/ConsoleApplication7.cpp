// ConsoleApplication7.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "L2ListImplementation.h"
using namespace std;

void drawMenu()
{
    cout << "1.Exit" << endl;
    cout << "2.Push" << endl;
    cout << "3.Remove" << endl;
    cout << "4.Show" << endl;
    cout << "5.Next" << endl;
    cout << "6.Start Iterator" << endl;
    cout << "7.is Finish" << endl;
    cout << "8.Clear" << endl;
    cout << "9.No iterator push" << endl;
    cout << "10.Print list" << endl;
}

int main()
{
    L2Ring<int> *list = new L2Ring<int>();
    Iterator<int>* iter = nullptr;
    int a = 0;
    bool ext = false;
    while(!ext)
    {
        drawMenu();
        cin >> a;
        system("cls");
        switch(a)
        {
        case 1:ext = true; break;
        case 2:try
        {
            cout << "Value to add: "; cin >> a; list->push(a, iter);
        }
               catch(runtime_error e)
               {
                   cerr << e.what() << endl;
               }break;
        case 3:try
        {
            list->remove(iter);
        }
               catch(runtime_error e)
               {
                   cerr << e.what() << endl;
               }break;
        case 4:try
        {
            cout << "Current value: " << iter->get() << endl; 
        }
               catch(runtime_error e)
               {
                   cerr << e.what() << endl;
               }break;
        case 5:try
        {
            iter->next();
        }
               catch(std::runtime_error e)
               {
                   cerr << e.what() << endl;
               }break;
        case 6:try
        {
            if(iter == nullptr)iter = list->iterator();
            iter->start();
        }
               catch(std::runtime_error e)
               {
                   cerr << e.what() << endl;
               }break;
        case 7:cout << iter->finish()<<endl; break;
        case 8:list->clear(); break;
        case 9:cout << "Value to add: "; cin >> a; list->push(a); break;
        case 10:
        {
            Iterator<int> *it = list->iterator();
            it->start();
            while(!it->finish())
            {
                cout << it->get() << endl;
                it->next();
            }
        }
        default:cout << "List size: " << list->length() << endl;
        }
    }

    list->push(1);
    list->push(2);
    list->push(3);
    list->clear();
    list->push(228);
    list->push(314159);
    list->push(5);
    iter = list->iterator();
    iter->start();
    while(!iter->finish())
    {
        cout << iter->get() << endl;
        iter->next();
    }

    L2Ring<string>& list1 = L2Ring<string>();
    list1.push("First");
    list1.push("Second");
    list1.push("Third");
    L2Ring<string> list2 = list1;
    Iterator<string> *iter2 = list2.iterator();
    string str = "";
    iter2->start();
    while(!iter2->finish())
    {
        str = iter2->get();
        cout << str << endl;
        iter2->next();
    }
    
    L2Ring<int> list3 = L2Ring<int>();
    list3.push(1);
    list3.push(4);
    list3.push(22);
    list3.push(12);
    list3.push(41);
    list3.push(110);
    Iterator<int> *iter3 = list3.search(22);
    if(iter3 != nullptr)
    while(!iter3->finish())
    {
        cout << iter3->get() << endl;
        iter3->next();
    }
    system("pause");
    return 0;
}