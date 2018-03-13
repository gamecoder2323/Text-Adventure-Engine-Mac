//
//  Inventory.cpp
//  C++ Project
//
//  Created by Reuben Randell on 3/6/18.
//  Copyright © 2018 Stokesoft. All rights reserved.
//

#include "Inventory.hpp"



Inventory::Inventory() {
    
}


Inventory::Inventory(std::string objName, Property propOne) {
    name = objName;
    itemProperty.push_back(propOne);
}

Inventory::Inventory(std::string objName, Property propOne, Property propTwo) {
    name = objName;
    itemProperty.push_back(propOne);
    itemProperty.push_back(propTwo);
}

Inventory::Inventory(std::string objName, Property propOne, Property propTwo, Property propThree) {
    name = objName;
    itemProperty.push_back(propOne);
    itemProperty.push_back(propTwo);
    itemProperty.push_back(propThree);
}

void Inventory::setProperty(Property prop) {
    itemProperty.push_back(prop);
}

bool Inventory::searchProperty(Property search) {
    for (unsigned int i = 0; i < sizeof(itemProperty); ++i) {
        if (itemProperty[i] == search) {
            return true;
        }
    }
    return false;
}
