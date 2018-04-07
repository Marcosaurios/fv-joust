/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: marcos
 *
 * Created on 13 de febrero de 2018, 17:14
 */

#ifndef GAME_H
#define GAME_H

using namespace std;
using namespace sf;

class Game {
public:
    Game(int w, int h, string t);
    Game(const Game& orig);
    virtual ~Game();
    void run();
    bool collision(Sprite& sprite, RectangleShape& rectangle, bool& hit_x, bool& isJumping, bool& tierra, Vector2f& speed);
    void inScreen(Sprite& sprite, RenderWindow& window, Vector2f speed);
    void moveEnemies(vector <Enemy*> v1, vector <Enemy*> v2);
    bool fight(Sprite &sprite, Sprite enemy, Clock c);
    float get_random(float a, float b);
private:
    int height;
    int width;
    string title;
    vector<IntRect> SP_walk;
    vector<IntRect> SP_fly;
    vector<IntRect> SE_walk;
    vector<IntRect> SE_fly;
    vector<IntRect> boss;
    bool die;

};

#endif /* GAME_H */

