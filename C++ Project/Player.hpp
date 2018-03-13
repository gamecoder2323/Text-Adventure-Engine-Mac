//
//  Player.hpp
//  C++ Project
//
//  Created by Reuben Randell on 3/13/18.
//  Copyright © 2018 Stokesoft. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#pragma once
#include <stdio.h>
#include <string>

class Player {
public:
    Player();
    ~Player();
    int hp, attack, fragments;
    std::string name;
    
};
#endif /* Player_hpp */
