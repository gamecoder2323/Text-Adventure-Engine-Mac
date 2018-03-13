//
//  Area.hpp
//  C++ Project
//
//  Created by Reuben Randell on 3/6/18.
//  Copyright © 2018 Stokesoft. All rights reserved.
//

#pragma once
#include <vector>
#include "Inventory.hpp"
#include "Interactables.hpp"

enum class Action { GRAB, GO, LIGHT, TOSS, NONE, ENTER, LEAVE }; // light is for stuff like 'light' a torch

class Area
{
public:
    Area();
    std::string name;
    void description(std::string describe, int x, int y);
    std::string areaDescription;
    //std::string buffer;
    void giveInteractions(Interactables interactable);
    std::vector<Interactables> interactables;
    std::string getHint();
    std::string generalDescription;
    int subareaID;
private:
    
    
    
};

//Give areas position and objects and/or interactions
