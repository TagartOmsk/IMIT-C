// Dictionary.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FrequencyDictionary.h"
using namespace std;

void drawMenu()
{
    cout << "0.Exit" << endl;
    cout << "1.Search" << endl;
    cout << "2.Add" << endl;
    cout << "3.Words summary" << endl;
    cout << "4.Remove" << endl;
    cout << "5.Print dictionary" << endl;
}

int main()
{
    bool exit = false;
    int a = 0;
    FrequencyDictionary &dic = FrequencyDictionary();
    string str = "";
    /*str = "0070";
    dic.add(str);
    str = "0060";
    dic.add(str);
    str = "0050";
    dic.add(str);
    str = "0055";
    dic.add(str);
    str = "0051";
    dic.add(str);
    str = "0065";
    dic.add(str);
    str = "0060";
    cout << dic << endl;
    //dic.remove(str);*/
    while(!exit)
    {
        drawMenu();
        cin >> a;
        system("cls");
        switch(a)
        {
        case 0:
            exit = true; break;
        case 1:
            cout << "Input word: ";
            cin >> str;
            cout << "There are " << dic.search(str) << " occurances of this word" << endl;
            break;
        case 2:
            cout << "Input word to add: ";
            cin >> str;
            dic.add(str);
            break;
        case 3:
            cout << "There are " << dic.wordsCount() << " words" << endl; break;
        case 4:
            cout << "Input word to remove: ";
            cin >> str;
            dic.remove(str);
            break;
        case 5:
            cout << dic;
            break;
        }
    }
    system("pause");
    return 0;
}

