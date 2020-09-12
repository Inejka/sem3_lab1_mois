#include <iostream>
#include "binary_normal.h"

using namespace std;
//011001
int main() { //13,25
    binary_normal a(13), b(25);
    b=b*binary_normal(2);
    cout << "float_x1+float_x2=" ;
    cout << endl << "Straight Binary\n" ;
    (a+b).print(); cout << "*2E00000100";



/*
    for (int i = -1000; i < 1000; i++)
        for (int j = -1000 ; j < 1000; j++)
            if ((binary_normal(i) * binary_normal(j)).to_int()!= i * j)//cout << "FUUCK";
                cout << (binary_normal(i) *binary_normal(j)).to_int() << "         " << i << "       " << j << endl;
*/


// (binary_normal(i)+binary_normal(j)).print();
}
