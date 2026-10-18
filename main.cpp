#include <iostream>
#include "Game.h"
#include <vector>
#include <stack>
using namespace std;

/*description of code (might move this to README file instead of here)
 * this is a recreation of a classic space shooter arcade game but with c++ (kinda like Galaga, Space Invaders, etc.)
 * I decided to make the entire game in the terminal and to be sort of turn based, it's easier to code it that way
 * and adds a layer of strategy to the game. I may add to this game in the future, or maybe make a more traditional
 * version that plays in real time
 */


int main() {
    Game arcadeGame;
    arcadeGame.run();
    return 0;
}

