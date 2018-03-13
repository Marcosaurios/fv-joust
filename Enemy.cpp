/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemy.cpp
 * Author: marcos
 * 
 * Created on 6 de marzo de 2018, 13:54
 */

#include "Enemy.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Enemy::Enemy(Vector2f p, Vector2f v, Sprite s) {
    pos = p;
    vel = v;
    sp=&s;
    
    sp->setTextureRect(sf::IntRect(8, 35, 16, 20));
    //Le pongo el centroide donde corresponde
    sp->setOrigin({0,0});
    // Lo dispongo en el centro de la pantalla
    sp->setPosition(p.x, p.y);
    
    sp->move(v);
    cout << "Posicion (x,y): " << v.x <<", " <<v.y << endl;
    
}

Enemy::Enemy(const Enemy& orig) {
}

Enemy::~Enemy() {
}

Sprite Enemy::getSprite() {
  return *sp;  
}

void Enemy::changeSprite(IntRect a){
    sp->setTextureRect(a);
}

