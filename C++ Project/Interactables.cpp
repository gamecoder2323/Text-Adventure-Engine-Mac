//
//  Interactables.cpp
//  C++ Project
//
//  Created by Reuben Randell on 3/6/18.
//  Copyright © 2018 Stokesoft. All rights reserved.
//


#include "Interactables.hpp"



Interactables::Interactables()
{
    isTriggered = 0;
}


std::string Interactables::giveHint(std::string hintToUse) {
    if (!isTriggered) {
        hint = hintToUse;
        return hint;
    }
    else {
        hint = "";
        return hint;
    }
}

void Interactables::init(std::string name, Property match) {
    nameOfObj = name;
    interactMatch = match;
}
