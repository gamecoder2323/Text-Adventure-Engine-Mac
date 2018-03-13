//
//  Game.hpp
//  C++ Project
//
//  Created by Reuben Randell on 3/6/18.
//  Copyright © 2018 Stokesoft. All rights reserved.
//

#pragma once
#include <vector>
#include "Inventory.hpp"
#include "Area.hpp"
#include "Player.hpp"

class Game
{
public:
    Game();
    void start();
    
private:
    const int BATTLE_CHANCES = 7;
    void initInventory();
    std::vector<Inventory> allItems;
    Inventory inventory[16];
    int itemSlotIterator;
    void print(std::string string);
    void confirm();
    std::string name;
    void initAreas();
    void recognize(std::string input);
    void mainGame();
    int x;
    int y;
    void eventCheck(std::string verb, std::string noun);
    void grab(std::string noun);
    Action checkAction(std::string verb);
    void initInteractables();
    void areaSetUp(int posX, int posY, std::string name, std::string areaDesc);
    Area map[10][10];
    std::vector<Interactables> allInteracts;
    Area currentArea;
    void go(std::string noun);
    void enter(std::string noun);
    bool isInSubarea;
    std::string checkInventory(Property property);
    void checkBattle();
    void leave();
    void battle();
    Player player;
    Area subareas[50];
    void cls();
};
