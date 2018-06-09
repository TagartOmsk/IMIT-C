// ConsoleApplication7.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
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
        case 2:cout << "Value to add: "; cin >> a; list->push(a, iter); break;
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
        case 9:cout << "Value to add: "; cin >> a; list->push(a);
        }
    }
    /*list->push(1);
    list->push(2);
    list->push(3);
    list->clear();
    list->push(228);
    list->push(314159);
    list->push(5);
    iter = list->iterator();
    iter->start();
    cout << iter->get() << endl;
    while(!iter->finish())
    {
        iter->next();
        cout<<iter->get()<<endl;
    }    */
    system("pause");
    return 0;
}

