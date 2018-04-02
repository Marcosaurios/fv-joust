#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Game.h"


using namespace sf;
using namespace std;

int main() {
    
    /*
    int a = 12;
    int* b = &a;
    cout << "a: a " << a << endl;
    cout << "a: &a " << &a << endl;
    cout << "b: b " << b << endl;
    cout << "b: *b " << *b << endl;
    cout << "b: &b " << &b << endl;

    cout << "----" << endl;
    int c = 333;
    b = &c;
    cout << "&c = " << &c << endl;
    cout << "*b=2: b " << b << endl;
    cout << "*b=2: *b " << *b << endl;
    cout << "*b=2: &b " << &b << endl;
    cout << "----" << endl;
    a=0;
    cout << "a=0: b " << b << endl;
    cout << "a=0: *b " << *b << endl;
    cout << "a=0: &b " << &b << endl;
    cout << "----" << endl;
    // Esto de abajo NO VA
    *b=a;
    cout << "*b=a: b " << b << endl;
    cout << "*b=a: *b " << *b << endl;
    cout << "*b=a: &b " << &b << endl;
    cout << endl;
    */
    
    Game Joust(550,394,"P0_Joust_MarcosUrios");
    
    Joust.run();
    
    
    return 0;
}
