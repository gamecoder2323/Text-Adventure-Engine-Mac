//
//  Interactables.hpp
//  C++ Project
//
//  Created by Reuben Randell on 3/6/18.
//  Copyright © 2018 Stokesoft. All rights reserved.
//

#pragma once
#include <string>
#include "Inventory.hpp"



class Interactables
{
public:
    Interactables();
    std::string nameOfObj;
    Property interactMatch;
    
    std::string giveHint(std::string hintToUse);
    bool isTriggered;
    std::string hint;
    void init(std::string name, Property match);
private:
    
};

