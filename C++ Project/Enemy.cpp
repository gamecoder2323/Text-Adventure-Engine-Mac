//
//  Enemy.cpp
//  C++ Project
//
//  Created by Reuben Randell on 3/13/18.
//  Copyright © 2018 Stokesoft. All rights reserved.
//

#include "Enemy.hpp"

Enemy::Enemy() {
    hp = (rand() % 40) + 5;
    attack = (rand() % 10) + 4;
    fragmentDrop = (rand() % 24) + 1;
}

Enemy::~Enemy() {
    
}
