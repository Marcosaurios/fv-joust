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
#include "Game.h"

#define kVel 0.03
#define jump 0.085
#define gravity 0.2

using namespace sf;
using namespace std;



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

void Game::inScreen(Sprite& sprite, RenderWindow& window)
{
    if(sprite.getPosition().x>window.getSize().x)
    {
        sprite.setPosition(0,sprite.getPosition().y);
    }
    else if(sprite.getPosition().x<0)
    {
        sprite.setPosition(window.getSize().x,sprite.getPosition().y);
    }
}

void Game::run()
{
    
    //Creamos una ventana (640x480) 550 394
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
    
    
    Texture tex_ini;
    if (!tex_ini.loadFromFile("resources/spritesheet.png")) {
        cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    //Y creo el spritesheet a partir de la imagen anterior
    Sprite sprite(tex_ini);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(8, 35, 16, 20));
    //Le pongo el centroide donde corresponde
    sprite.setOrigin({sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2});
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(rect5.getPosition().x+rect5.getGlobalBounds().width/2, rect5.getPosition().y);
    
    
    // Background setting:
    Texture bg;
    if (!bg.loadFromFile("resources/joust_bg.png")) {
        cerr << "Background not loaded!";
    }
    Sprite background(bg);
    
    //////////////////////////
    
    // Sprites
    int state = 0;
    // 0 walk
    // 1 fly
    int count_spw = 0;
    //int count_spf = 0;
    int count_sew = 0;
    int count_sef = 0;
    
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
    
    
    
     //COLISIONES
    
    Vector2f pos0 = sprite.getPosition();
    Vector2f pos1 = {0,0};    
    bool hit_x = false;    
    bool tierra = false;
    
    while (window.isOpen())
    {
        // Jump time stuff
        pt = ct;
        ct = clock.getElapsedTime();
        float dt = ct.asSeconds() - pt.asSeconds();
        
        // Check if player is inside the window
        inScreen(sprite,window);
        
        // COLISIONS
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
                sprite.setTextureRect(SP_fly.at(0));
            }
            
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        default:
                            std::cout << event.key.code << std::endl;
                            break;
                    }
            }
        }
         //jump
        if(isJumping)
        {
            // if is FLYING -> ADD gravity
            if(dt>0.15f) dt=0.15f;
            speed.y += (gravity * dt);
        }
        
        sprite.move(speed);
        hit_x = false;
        
        
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
    
        window.display();
    }

}
