// HashTable.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "HashTable.h"
#include <iostream>
using namespace std;

int hashFunc(int key, int a)
{
    return key % a;
}

void drawMenu()
{
    cout << "1.Exit" << endl;
    cout << "2.Put" << endl;
    cout << "3.Remove" << endl;
    cout << "4.Get value by key" << endl;
    cout << "5.Clear" << endl;
    cout << "6.Contains key" << endl;
    cout << "7.Contains value" << endl;
    cout << "8.Is empty" << endl;
    cout << "9.Switch iterator" << endl;
}

int main()
{
    bool ext = false;
    int a = 0;
    string str = "";
    HashTable<int, string> table = HashTable<int, string>(hashFunc, 16);
    while(!ext)
    {
        drawMenu();
        cin >> a;
        system("cls");
        switch(a)
        {
        case 1:ext = true; break;
        case 2:cout << "Insert key: "; cin >> a; cout << "Insert value: "; cin >> str; table.put(a, str); break;
        case 3:
            try
            {
                cout << "Insert key to remove: "; cin >> a;
                cout << "Removed value: " << table.remove(a) << endl;
            }
               catch(runtime_error e)
               {
                   cerr << e.what() << endl;
               }break;
        case 4:
            try
            {
                cout << "Insert key : "; cin >> a;
                cout << "Value: " << table.get(a) << endl;
            }
            catch(std::runtime_error e)
            {
                cerr << e.what() << endl;
            }break;
        case 5:table.clear(); cout << "Cleared successfully" << endl; break;
        case 6:cout << "Insert key: "; cin >> a;
            cout.setf(ios::boolalpha);
            cout << table.containsKey(a) << endl;
            cout.unsetf(ios::boolalpha);
            break;
        case 7:cout << "Insert value: "; cin >> str;
            cout.setf(ios::boolalpha);
            cout << table.containsValue(str) << endl;
            cout.unsetf(ios::boolalpha);
            break;
        case 8:cout.setf(ios::boolalpha);
            cout << table.isEmpty() << endl;
            cout.unsetf(ios::boolalpha);
            break;
        case 9:
        {
            bool stop = false;
            int choose = 0;
            HashTable<int, string>::Iterator iter = HashTable<int, string>::Iterator(table);
            while(!stop)
            {
                if(!iter.finish())cout << "Current key: " << iter.getKey() << endl; else cout << "Iteration is alredy finished" << endl;
                if(!iter.finish())cout << "Current value: " << iter.getValue() << endl;
                cout << "1.Stop" << endl;
                cout << "2.Move to next" << endl;
                cout << "3.Restart" << endl;
                cout << "4.Is iteration finished" << endl;
                cin >> choose;
                system("cls");
                switch(choose)
                {
                case 1:stop = true; break;
                case 2:if(!iter.finish())iter.next(); /*else cout << "Iteration is alredy finished" << endl;*/ break;
                case 3:iter.start(); break;
                case 4:cout.setf(ios::boolalpha);
                    cout << iter.finish() << endl;
                    cout.unsetf(ios::boolalpha);
                    break;
                }
            }
        }break;
        default: cout << "Size: " << table.getSize() << endl;
        }
    }
    system("pause");
    return 0;
}

