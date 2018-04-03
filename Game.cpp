/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: marcos
 * 
 * Created on 13 de febrero de 2018, 17:14
 */
#include <iostream>
#include <vector> // Storing sprites
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Game.h"
#include <fstream>

#define kVel 0.018
#define jump 0.04
#define gravity 0.2

using namespace sf;
using namespace std;

struct nivel{
    int round = 0;
    int enemies = 0;
    int killed = 0;
    int tdelay = 0; /* seconds */
    
    bool win = false;
    int points = 0;
    
    nivel(int r, int e, int k, int t){
        round = r;
        enemies = e;
        killed = k;
        tdelay = t;
        points = 0;
    }
    
    
    
};


Game::Game(int w, int h, string t) {
    width = w;
    height = h;
    title = t;
}



Game::Game(const Game& orig) {
}

Game::~Game() {
}

bool Game::collision(Sprite& sprite, RectangleShape& rect6, bool& hit_x, bool& isJumping, bool& tierra,Vector2f& speed){
    bool x = false;
    if(sprite.getGlobalBounds().intersects(rect6.getGlobalBounds()))
    {
        // from LEFT face
        if(sprite.getPosition().x <= rect6.getPosition().x
           && sprite.getPosition().y > rect6.getPosition().y) 
        {
            speed.x=speed.x*-1;
            sprite.setPosition(sprite.getPosition().x-sprite.getGlobalBounds().width/2,sprite.getPosition().y);
            hit_x = true;
        }
        // from RIGHT face
        else if(sprite.getPosition().x >= rect6.getPosition().x+rect6.getGlobalBounds().width
           && sprite.getPosition().y > rect6.getPosition().y)
        {
            speed.x=speed.x*-1;
            sprite.setPosition(sprite.getPosition().x+sprite.getGlobalBounds().width/2,sprite.getPosition().y);
            hit_x = true;
        }

        // from UPPER face
        else if(sprite.getPosition().y <= rect6.getPosition().y+rect6.getGlobalBounds().height)
        {
            sprite.setPosition(sprite.getPosition().x,rect6.getPosition().y-sprite.getGlobalBounds().height/2);
            isJumping = false;
            tierra = true;
        } 
        // from LOWER face
        else if(sprite.getPosition().y >= rect6.getPosition().y+rect6.getGlobalBounds().height)
        {
            speed.y = speed.y*-1;
            sprite.setPosition(sprite.getPosition().x,sprite.getPosition().y+sprite.getGlobalBounds().height/2);
        }
        x = true;
    }
    return x;
}

void Game::inScreen(Sprite& sprite, RenderWindow& window, Vector2f speed )
{
    if(sprite.getPosition().x>window.getSize().x)
    {
        
        // If sprite goes right
        sprite.setPosition(0,sprite.getPosition().y);
    }
    else if(sprite.getPosition().x<0)
    {
        // If sprite goes left
        sprite.setPosition(window.getSize().x,sprite.getPosition().y);
    }
    else if(sprite.getPosition().y<0)
    {
        // If sprite goes up
        speed.y *= -1;
        sprite.setPosition(sprite.getPosition().x,sprite.getPosition().y+sprite.getGlobalBounds().height);
        
    }
}

void Game::moveEnemies(vector<Enemy*> v1, vector<Enemy*> v2){
    for(int i=0; i<v1.size();i++){
        Vector2f speed = v1.at(i)->vel;
        v1.at(i)->setMove(speed);
    }
}

void Game::run()
{
    
    // Window (640x480) 550 394
    RenderWindow window(sf::VideoMode(width, height), title);
    
    // Vector to store sprites pixel positions
    vector<IntRect> SP_walk;
    vector<IntRect> SP_fly;
    vector<IntRect> SE_walk;
    vector<IntRect> SE_fly;
    vector<IntRect> boss;
    SP_walk.push_back(IntRect(8,35,16,20));
    SP_walk.push_back(IntRect(28,35,16,20));
    SP_walk.push_back(IntRect(48,35,16,20));
    SP_walk.push_back(IntRect(69,35,16,20));
    SP_fly.push_back(IntRect(8,14,16,13));
    SP_fly.push_back(IntRect(30,14,16,13));
    SE_walk.push_back(IntRect(303,38,16,20));
    SE_walk.push_back(IntRect(324,38,16,20));
    SE_walk.push_back(IntRect(345,38,16,20));
    SE_walk.push_back(IntRect(368,38,16,20));
    SE_fly.push_back(IntRect(217,38,16,13));
    SE_fly.push_back(IntRect(241,38,16,13));
    boss.push_back(IntRect(8,177,28,11));
    boss.push_back(IntRect(43,180,25,7));
    boss.push_back(IntRect(74,175,24,10));
    
    
    // Rectangles and bounding boxes for collisions
    RectangleShape rect1({60,10});
    rect1.setPosition({0,120});
    rect1.setFillColor(Color(255,255,255,0));
    
    RectangleShape rect2({160,17});
    rect2.setPosition({180,140});
    rect2.setFillColor(Color(255,255,255,0));
    
    RectangleShape rect3({75,10});
    rect3.setPosition({475,120});
    rect3.setFillColor(Color(255,255,255,0));
    
    RectangleShape rect4({110,15});
    rect4.setPosition({0,235});
    rect4.setFillColor(Color(255,255,255,0));
    
    RectangleShape rect5({110,15});
    rect5.setPosition({205,265});
    rect5.setFillColor(Color(255,255,255,0));
    
    RectangleShape rect6({110,15});
    rect6.setPosition({380,220});
    rect6.setFillColor(Color(255,255,255,0));
    
    RectangleShape rect7({75,10});
    rect7.setPosition({475,235});
    rect7.setFillColor(Color(255,255,255,0));
    
    RectangleShape base({550,50});
    base.setPosition({0,344});
    base.setFillColor(Color(255,255,255,0));
    
    ////////////////////////////////////////
    // LOADING RESOURCES
    ////////////////////////////////////////
    
    // SPRITES
    Texture tex_ini;
    if (!tex_ini.loadFromFile("resources/spritesheet.png")) {
        cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    // BACKGROUND
    Texture bg;
    if (!bg.loadFromFile("resources/joust_bg.png")) {
        cerr << "Background not loaded!";
    }
    Sprite background(bg);
    
    // FONT
    sf::Font font;
    if (!font.loadFromFile("resources/ARCADECLASSIC.TTF"))
    {
        cerr << "Font not loaded!!" << endl;
    }
    
    ////////////////////////////
    // Timers init
    ////////////////////////////
    Clock c1; // 5s clock to check enemies etc
    Clock enemychange; // change enemy flying sprite
    Clock enemyspawn; // whenever enemy spawns
    int count = 0;
    
    
    //////////////////////////
    
    // ======= Main player sprite =======
    
    //Y creo el spritesheet a partir de la imagen anterior
    Sprite sprite(tex_ini);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(8, 35, 16, 20));
    //Le pongo el centroide donde corresponde
    sprite.setOrigin({sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2});
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(rect5.getPosition().x+rect5.getGlobalBounds().width/2, rect5.getPosition().y);
    
    
    // Sprites
    int state = 0;
    // 0 walk
    // 1 fly
    int count_spw = 0;
    //int count_spf = 0;
    
    // Jump
    bool isJumping = false;
    Vector2f speed{0,-0.10};
    Clock clock;
    Time ct = clock.getElapsedTime();
    Time pt;
    
    /*
     Loop:
     * 1. Update
     * 2. Draw
     * 3. Repeat
     */
    
    /* Round values */
    int points = 0;
    bool endround = false;
    //bool win = false;
    
    /* Loading round settings */
    nivel nivel0(0 /* round */, 5 /* enemies */, 0 /* killed */, 4/* time delay */);
    nivel nivel1(1,10,0,2);
    
    /* round 0 */
    vector<Enemy*> v_enemies_0;
    vector<bool> shows;
    Vector2f enepos1 = {-10,10};
    Vector2f enev1 = {0.0,0.0};

    /* fill enemies vector */
    for(int i=0;i<nivel0.enemies;i++)
    {
        Enemy* ene = new Enemy(enepos1, enev1, tex_ini, SE_fly.at(0));
        v_enemies_0.push_back(ene);
        int randnumb = rand()%(10-0 + 1) + 0;
        enepos1.y += enepos1.y+randnumb;
        shows.push_back(false);
    }
        

    vector<Enemy*> v_enemies_1;
    
     //COLISIONS
    
    Vector2f pos0 = sprite.getPosition();
    Vector2f pos1 = {0,0};    
    bool hit_x = false;    
    bool tierra = false;
    
    
    int index=0;
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    //               GAME LOOP
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////

    while (window.isOpen())
    {
        
        // Jump time stuff
        pt = ct;
        ct = clock.getElapsedTime();
        float dt = ct.asSeconds() - pt.asSeconds();
        
        
        
        ////////////////////////////
        // TIMERS
        ////////////////////////////
        // 5s checker
        float s5 = c1.getElapsedTime().asSeconds();
        if(s5>5){
            c1.restart();
        }
        
        ///////////////////////////
        // Enemy spawner LVL 0
        ///////////////////////////
        if(!nivel0.win){
            // Spawn
            if(enemyspawn.getElapsedTime().asSeconds()>nivel0.tdelay && count<nivel0.enemies)
            {
                float max = 0.03;
                float min = 0.01;
                //int randvx = rand()%(max-min + 1) + min;
                //int randvy = rand()%(max-min + 1) + min;
                Vector2f velocity = {max, min};
                v_enemies_0.at(count)->setPosition({v_enemies_0.at(count)->pos.x+15,v_enemies_0.at(count)->pos.y});
                v_enemies_0.at(count)->setMove(velocity);
                enemyspawn.restart();
                cout << "pre shows[" << count << "]: " << shows[0] << shows[1] << shows[2] << shows[3] << shows[4] << endl;
                shows[count] = true;
                cout << "true shows[" << count << "]: " << shows[0] << shows[1] << shows[2] << shows[3] << shows[4] << endl;
                count++;
            }
            // Moves
            for(int a=0;a<v_enemies_0.size();a++)
            {
                // If it can be displayed
                if(shows[a])
                {
                    v_enemies_0.at(a)->setMove(v_enemies_0.at(a)->getVel());
                    inScreen(*v_enemies_0.at(a)->sp,window,v_enemies_0.at(a)->vel);
                }
            }
            // Enemy sprites
            if(enemychange.getElapsedTime().asSeconds()>1.5)
            {
                for(int i=0; i<v_enemies_0.size();i++)
                {
                    index++;
                    if(index>=2)index=0;
                    v_enemies_0.at(i)->changeSprite(SE_fly.at(index));
                    v_enemies_0.at(i)->setMove({v_enemies_0.at(i)->vel.x,v_enemies_0.at(i)->vel.y * -1});
                }
                enemychange.restart();
            }
        }
        
        
        
        
        //////////////////////////////////////
        // IN SCREEN WINDOW?
        //////////////////////////////////////
        inScreen(sprite,window,speed);
        
        /////////////////////////////////////
        // COLISIONS
        /////////////////////////////////////
        bool crec1 = collision(sprite,rect1,hit_x,isJumping,tierra,speed);
        bool crec2 = collision(sprite,rect2,hit_x,isJumping,tierra,speed);
        bool crec3 = collision(sprite,rect3,hit_x,isJumping,tierra,speed);
        bool crec4 = collision(sprite,rect4,hit_x,isJumping,tierra,speed);
        bool crec5 = collision(sprite,rect5,hit_x,isJumping,tierra,speed);
        bool crec6 = collision(sprite,rect6,hit_x,isJumping,tierra,speed);
        bool crec7 = collision(sprite,rect7,hit_x,isJumping,tierra,speed);
        
        // Base surface collision
        if(sprite.getPosition().y+sprite.getGlobalBounds().height/2>base.getPosition().y)
        {
            sprite.setPosition(sprite.getPosition().x,base.getPosition().y-sprite.getGlobalBounds().height/2);
            isJumping = false;
            tierra = true;
        }
        
        // collide with surfaces 
        else if( !(crec1 || crec2 || crec3 || crec4 || crec5 || crec6 || crec7) && !tierra)
        {
            isJumping = true;
        }
        
        // collide with enemies
        
        
        
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
           
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                if(state==0 && !hit_x) // walks and didn't hit any object in X axis
                {
                    speed.x=kVel;
                }
                
            }
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                if(state==0 && !hit_x) // walks and didn't hit any object in X axis
                {
                    speed.x=-kVel;
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Space) )
            {
                // ADD jump
                speed.y=-jump;
                isJumping = true;
                tierra = false;
                sprite.setTextureRect(SP_fly.at(1));
            }
            
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Q:
                            window.close();
                            break;
                        default:
                            std::cout << event.key.code << std::endl;
                            break;
                            
                    }
            }
        }
        
        //////////////////////////////
        // JUMP
        /////////////////////////////
        if(isJumping)
        {
            // if is FLYING -> ADD gravity
            if(dt>0.15f) dt=0.15f;
            speed.y += (gravity * dt);
        }
        // Colision in X-axis
        sprite.move(speed);
        hit_x = false;
        
        
        //////////////////////////////
        // P1 SPRITE MOVEMENT
        //////////////////////////////
        // Check pixels position to change sprites while walks
        pos1 = sprite.getPosition();
        if(pos1.x-pos0.x > 0)
        {
            // if moves to the RIGHT 
            if(isJumping)
            {
                sprite.setTextureRect(SP_fly.at(0));
            }
            else
            {
                // walking
                if(count_spw == 4)count_spw = 0;
                sprite.setTextureRect(SP_walk.at(count_spw));
                count_spw++;
            }
            sprite.setScale(1,1);
        }
        else if(pos1.x - pos0.x < 0)
        {
            // if moves to the LEFT
            if(isJumping)
            {
                sprite.setTextureRect(SP_fly.at(0));
            }
            else
            {
                if(count_spw == 4)count_spw = 0;
                sprite.setTextureRect(SP_walk.at(count_spw));
                count_spw++;
            }
            sprite.setScale(-1,1);
        }
        pos0 = pos1;   
        
        
        
       
        
        
        ///////////////////////////////
        // DRAW
        //////////////////////////////
        window.clear();
        window.draw(background);
        window.draw(sprite);
        window.draw(rect1);
        window.draw(rect2);
        window.draw(rect3);
        window.draw(rect4);
        window.draw(rect5);
        window.draw(rect6);
        window.draw(rect7);
        window.draw(base);
        
       
        for(int i=0;i<v_enemies_0.size();i++)
        {
            window.draw(v_enemies_0.at(i)->getSprite());
        }
        
        window.display();
    }

}
