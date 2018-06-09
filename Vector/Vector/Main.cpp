#include "stdafx.h" 
#include "Vector.h"
#include <iostream>
#include <conio.h> 
using namespace std;

int main ()
{
    /*int siz;
    cout << "A size: ";
    cin >> siz;
    Vector a (siz);
    cout << "B size: ";
    cin >> siz;
    Vector b (siz);
    cout << "initialize A: ";
    cin >> a;
    cout << "initialize B: ";
    cin >> b;
    cout << (a + b) << endl;
    cout << a << endl << b << endl;*/
    bool ext = false;
    int siz = 0, sh,n;
    cout << "A size: ";
    cin >> siz;
    Vector A(siz);
    cout << "Insert A: ";
    cin >> A;
    cin.clear();
    while(!ext)
    {
        cout << "1.Exit" << endl;
        cout << "2.Resize Vector" << endl;
        cout << "3.Fill in Vector " << endl;
        cout << "4.Show Vector" << endl;
        cout << "5.Reserve" << endl;
        cout << "6.Show sizes" << endl;
        cout << "7.Pop" << endl;
        cout << "8.Push" << endl;
        cin >> sh;
        switch(sh)
        {
        case 1: ext = true; break;
        case 2: cout << "Insert new size: "; cin >> n; A.reSize(n); break;
        case 3: cout << "Insert A: "; cin >> A; break;
        case 4: cout << "Gotcha: " << A << endl; break;
        case 5: cout << "Insert reserve size: "; cin >> n; A.reserve(n); break;
        case 6: cout << "Vector size: " << A.length() << endl << "Reserve size: " << A.capacity() << endl;break;
        case 7: cout << A.popBack() << endl; break;
        case 8: cout << "Insert Value: "; cin >> n; A.pushBack(n); break;
        }
    }
    _getch ();
    return 0;
}