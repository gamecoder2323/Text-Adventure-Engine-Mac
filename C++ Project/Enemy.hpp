//
//  Enemy.hpp
//  C++ Project
//
//  Created by Reuben Randell on 3/13/18.
//  Copyright © 2018 Stokesoft. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Inventory.hpp"
#include <string>

class Enemy {
public:
    Enemy();
    ~Enemy();
    int hp, attack;
    std::string name;
    int lootDropID; //The array index value of an Inventory-type item. Access the vector of allItems[lootDropID] in the Game.cpp file
    int fragmentDrop; //fragments are the game's currency.
private:
    
};

#endif /* Enemy_hpp */
