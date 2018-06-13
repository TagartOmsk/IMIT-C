// BinaryTree.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "BinaryTree.h"
using namespace std;

void drawMenu()
{
    cout << "0.Exit" << endl;
    cout << "1.Add value" << endl;
    cout << "2.Clear tree" << endl;
    cout << "3.Print tree" << endl;
    cout << "4.Count of even values" << endl;
    cout << "5.If tree contains only positive values" << endl;
    cout << "6.Cut leaves" << endl;
    cout << "7.Average of tree values" << endl;
    cout << "8.Search" << endl;
    cout << "9.Is Binary Search tree" << endl;
}

int main()
{
    bool exit = false;
    int a = 0;
    string str = "";
    cout << "Initialize root: "; 
    cin >> a;
    BinaryTree tree = BinaryTree(a);
    while(!exit)
    {
        tree.levelPrint();
        drawMenu();
        cin >> a;
        system("cls");
        switch(a)
        {
        case 0:exit = true; break;
        case 1:
            cout << "Insert value: "; cin >> a;
            cout << "Insert binary way (note that tree level is " << tree.getLevel() << " now): ";
            cin >> str;
            try
            {
                tree.add(str.c_str(), a);
            }
            catch(runtime_error e)
            {
                cerr << e.what() << endl;
            }
            break;
        case 2:
            tree.clear(); break;
        case 3:
            cout << tree << endl;
            break;
        case 4: 
            cout << "There are " << tree.evenCount() << " even values." << endl;
            break;
        case 5:
            cout << "Tree contains only positive values: " << boolalpha << tree.containsOnlyPositive() << endl;
            break;
        case 6:
            tree.cutLeaves();
            break;
        case 7:
            cout << "Average: " << tree.getAverage() << endl; break;
        case 8:
            try
            {
                cout << "Input value to find: "; cin >> a;
                vector<bool> vect = tree.find(a);
                vector<bool>::iterator it = vect.begin();
                cout << "Value found by the binary address: ";
                while(it != vect.end())
                {
                    cout << *it;
                    it++;
                }
            }
            catch(runtime_error e)
            {
                cerr << e.what() << endl;
            }break;
        case 9:
            cout << boolalpha << tree.isBinarySearchTree() << endl;
            break;
        default:
            cout << "Tree level: " << tree.getLevel() << endl;
        }
    }
    system("pause");
    return 0;
}

