//
//  Area.cpp
//  C++ Project
//
//  Created by Reuben Randell on 3/6/18.
//  Copyright © 2018 Stokesoft. All rights reserved.
//

#include "Area.hpp"
#include "Interactables.hpp"
#include <string>



Area::Area()
{
    
}

void Area::description(std::string describe, int x, int y) {
    generalDescription = "    " + name + ":   " + std::to_string(x) + ", " + std::to_string(y) + "\n" + describe + " ";
    //for (int i = 0; i < 1; ++i) {
    //areaDescription = getHint();
    //std::cout << finalDescription;
    //}
}

void Area::giveInteractions(Interactables interactable) {
    interactables.push_back(interactable);
}

std::string Area::getHint() {
    //if (sizeof(interactables) > 0) {
    for (unsigned int i = 0; i < sizeof(interactables); ++i) {
        if (!interactables[i].isTriggered) {
            
            return interactables[i].hint;
        }
    }
    return "";
    //}
}
