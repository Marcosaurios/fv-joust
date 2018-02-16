#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;
using namespace std;

int main() {
    
    Game Joust(550,394,"P0_Joust_MarcosUrios");
    
    Joust.run();
    
    return 0;
}
