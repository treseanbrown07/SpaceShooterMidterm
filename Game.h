#include <vector>
#include <iostream>
#include "entities.h"
using namespace std;

class Game {

private:
    int playerPos; //players position on bottom row
    int score; //keeps score
    int turnCount; //number of turns present
    bool isRunning; //checks if game is still running

    //stores every active shot the player shoots
    vector<Bullet> bullets;

    //stores the amount of enemies present
    vector<Enemy> enemies;

    //helper functions

    //helps clear screen after every turn
    void clearScreen();

    //helps with printing the grid out
    void makeGrid();

    //helps with keyboard inputs
    void handleInput();

    //updates world
    void updateWorld();


public:

    //constructor
    Game();
    void run();


};



