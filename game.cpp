#include <stack>
#include <iostream>
#include "Game.h"
using namespace std;

//constructor
Game::Game() {
    playerPos = width / 2;
    score = 0;
    turnCount = 0;
    isRunning = true;

    for (int r = 0; r <2; ++r) {
        for (int c = 1; c < width-1; ++c) {
            enemies.push_back({c,r});
        }
    }

}

//clears console screen between turns
    void Game::clearScreen() {
    //prints empty liness

    for (int i = 0; i < 50; i++) {
        cout << "\n";
    }
}

    void Game::makeGrid() {
    //makes 2d character representation of board
    vector<string> board(height, string(width, '.'));

    //Place player on bottom row
    if (playerPos >= 0 && playerPos < width) {
        board[height-1][playerPos] = '^';
    }

    //places bullets
    for (const auto& b : bullets) {

        //makes sure bullet isn't out of bounds
        if (b.x >= 0 && b.x < width && b.y >= 0 && b.y < height) {
            board[b.y][b.x] = '|';
        }
    }

    //place enemies
    for (const auto& e : enemies) {
        if (e.x >=0 && e.x < width && e.y >= 0 && e.y < height) {
            board[e.y][e.x] = 'X';
        }
    }

        //print board and border
        cout << "Score ~ " << score << " | Turn ~ " << turnCount << "\n";
        cout << string(width + 2, '-') << "\n";
        for (int r = 0; r < height; ++r) {
            cout << "|";
            for (int c = 0; c < width; ++c) {
                cout << board[r][c];
            }
            cout << "|\n";
        }
        cout << string(width + 2, '-') << "\n";
        cout << "Controls ~ [a] Left, [d] Right, [s] Shoot, [q] Quit\n";
        cout << "Click a Key ~  ";
    }

    //keyboard inputs
    void Game::handleInput(){
        char input;
        cin >> input;
        cin.ignore(10000, '\n');

        if (input == 'a' || input == 'A') {
            if (playerPos > 0)
                playerPos--;
        }
        else if (input == 'd' || input == 'D') {
            if (playerPos < width - 1)
                playerPos++;
        }
        else if (input == 's' || input == 'S') {
            // Spawn a bullet just above the player
            bullets.push_back({playerPos, height - 2});
        }
        else if (input == 'q' || input == 'Q') {
            isRunning = false;
        }
    }

    void Game::updateWorld(){
        turnCount++;

        //move bullets up
        vector<Bullet> nextBullets;
        for (auto& b : bullets) {
            b.y--;
            if (b.y >= 0) {
                nextBullets.push_back(b);
            }
        }
        bullets = nextBullets;

        vector<Enemy> survivingEnemies;
        for (auto& e : enemies) {
            bool hit = false;
            for (auto it = bullets.begin(); it != bullets.end(); ++it) {
                if (it->x == e.x && it->y == e.y) {
                    hit = true;
                    score+=100;
                    bullets.erase(it);
                    break;
                }
            }
            if (!hit) {
                survivingEnemies.push_back(e);
            }
        }
        enemies = survivingEnemies;

        //simple enemy movement
        if (turnCount % 3 == 0) {
            for (auto& e : enemies) {
                e.y++;

                //check to see if enemy has touched the bottom
                if (e.y >= height - 1) {
                    isRunning = false;
                }
            }
        }

        //checks win condition
        if (enemies.empty()) {
            isRunning = false;
        }
    }
    // Main game loop
    void Game::run(){
        clearScreen();
        makeGrid();

        while (isRunning) {
            //clearScreen(); ~ was causing errors
            //makeGrid();
            handleInput();
            if (!isRunning) break;
                updateWorld();
            clearScreen();
            makeGrid();
        }

        clearScreen();
        cout << "Game Over!\nFinal Score: " << score << "\n";

    }
