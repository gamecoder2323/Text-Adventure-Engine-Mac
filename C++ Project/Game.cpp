//
//  Game.cpp
//  C++ Project
//
//  Created by Reuben Randell on 3/6/18.
//  Copyright © 2018 Stokesoft. All rights reserved.
//

#include "Game.hpp"
#include "Inventory.hpp"
#include <iostream>
#include "Interactables.hpp"
#include <stdlib.h>
#include <time.h>
#include "Enemy.hpp"


//INSTRUCTIONS:
//
//To create a new Area, first you give a new interactable to an area. You go to initAreas to do this, then you give the item a hint. From there, you create an areaSetup.
//In the areaSetup, you specify the (x, y) coordinates and give it a name, and a description of it when there aren't any interacts there.
//After that, you're done with creating an area.
//
//
//That is, unless you wanted to create a new interactable for the area. Now, to do this, you go to initInteractables, and then type Interactables followed by a space,
//and then the name of your interactable. In the initialization list, you type:
//
//name.init("name", Property::*whatever the name of the property that you want to trigger it is*);
//
//
//If you wish to make a new item, follow the same steps as you would an interactable, except every time you see 'interactable' replace it with 'Inventory' (Names included)
//
//
//To create a new property, click on Area.h and make a new name for it.
//
//
//I have placed all the tools you will need to use near the top. This is the basic engine. All that I'll be doing now is expanding it, and adding new features.





Game::Game()
{
    x = 5;
    y = 5;
    initInteractables();
    initInventory();
    initAreas();
    itemSlotIterator = 0;
    isInSubarea = false;
    
    srand(time(NULL) % BATTLE_CHANCES);

}





//Start of Game setup


void Game::initAreas() {
    
    //initialization list for map interacts.
    map[5][5].giveInteractions(allInteracts[2]); // The 'allInteracts' here is a list of interactables that I put in a certain order. The order is in initInteractables.
    map[5][5].interactables[0].giveHint("It seems there is an old sword lying in the ground."); // This is what appears if you haven't interacted with something in an area.
    map[5][4].giveInteractions(allInteracts[4]);
    map[5][4].interactables[0].giveHint("There are stones in the wall that appear to be loose.");
    map[6][5].giveInteractions(allInteracts[0]);
    
    map[6][6].giveInteractions(allInteracts[1]);
    map[4][5].giveInteractions(allInteracts[0]);
    map[5][6].giveInteractions(allInteracts[5]);
    map[5][6].interactables[0].giveHint("There are crystals on the ground. It looks like you can carry them.");
    map[4][6].giveInteractions(allInteracts[0]);
    map[4][7].giveInteractions(allInteracts[6]);
    map[4][7].interactables[0].giveHint("There is a shovel on the ground.");
    map[3][5].giveInteractions(allInteracts[8]);
    
    
    
    
    //Basic Setup: Do this first.
    
    areaSetUp(5, 5, "Mountains 1", "You are standing on a tall mountain. It is very snowy here. You look around. You appear to be on a large island. You can see miles of shoreline at the edges of the island. ");
    areaSetUp(5, 4, "Mountain Ravine", "You walk through a narrow ravine in the mountains. Erosion has worn down the stones of an unknown civilization. To the south, there appears to be a bridge. ");
    areaSetUp(6, 5, "Mountains 2", "You cross into rocky terrain. The mountain range stretches far to the east. To the north of you appears to be a weathered stone tower. It looks like it could reveal some clues about this island. ");
    
    areaSetUp(6, 6, "Stone Tower", "You have come across an ancient tower. It's stone bricks look weathered from hundreds of years of erosion. It looks very unstable. In front of the tower, there is an old door.");
    
    map[6][6].subareaID = 0; //Stone Tower has subarea.
    subareas[0].description("You have entered the stone tower. It is dark, but you can still see. There is a winding staircase to the right.", 6, 6); //Set the coords to map coords.
    subareas[0].name = "Inside Stone Tower";
    subareas[0].giveInteractions(allInteracts[0]); //replace with something else
    subareas[0].giveInteractions(allInteracts[7]);
    subareas[0].interactables[1].giveHint(" An axe is on a wooden table in the center of the room.");
    
    
    areaSetUp(4, 5, "Grasslands 1", "You have come to the boundary of the Grasslands. It is very flat and has a cool breeze that comes from the North. From here, you can see mountains to the East.");
    areaSetUp(5,6, "Glacial 1", "There is a layer of ice on the ground. You are in a wide ravine, the walls shimmer like crystals in the sun. ");
    areaSetUp(4,6, "Glacial 2", "You are walking into mountainous terrain. Snow is starting to fall, dusting the area. To the far north, there appears to be a small village in the snow. Just north of here, the snow thickens. ");
    areaSetUp(4,7, "Glacial 3", "You are knee deep in snow, every step you take drains your energy. To the north, there is a small village. Maybe it could help you discover more about this island.");
    areaSetUp(3, 5, "Grasslands 2", "You have come across a hill. At the top of it, there is a stone. It looks like you could climb the hill.");
    
    map[3][5].subareaID = 1; //Hill subarea
    subareas[1].description("You are standing atop a hill. To the Northeast, you can see a glacial land. To the East, you can see the Mountains from whence you came.", 3, 5);
    subareas[1].name = "Grassland Hill";
    
    
    
    
}


void Game::initInteractables() {
    //Interactables to be used
    //They won't work because they are local variables, so you put them in a class-wide Interactables container, allInteracts.
    Interactables none;
    Interactables door;
    Interactables sword;
    Interactables explodable;
    Interactables stone;
    Interactables crystals;
    Interactables shovel;
    Interactables axe;
    Interactables hill;
    
    //Initialize the properties of interactables
    //The 'Property' is pretty much the verb that makes you interact with the interactable. For item props, go to Inventory section.
    none.init("none", Property::NONE);
    door.init("door", Property::OPEN);
    sword.init("sword", Property::GRAB);
    explodable.init("gunpowder", Property::FLAMMABLE);
    stone.init("stone", Property::HARD);
    crystals.init("crystals", Property::GRAB);
    shovel.init("shovel", Property::GRAB);
    axe.init("axe", Property::GRAB);
    hill.init("hill", Property::CLIMB);
    
    //
    allInteracts.push_back(none); //0
    allInteracts.push_back(door); //1
    allInteracts.push_back(sword); //2
    allInteracts.push_back(explodable); //3
    allInteracts.push_back(stone); //4
    allInteracts.push_back(crystals); //5
    allInteracts.push_back(shovel); //6
    allInteracts.push_back(axe); //7
    allInteracts.push_back(hill); //8
    
    //Add new interacts above this line: put them at the bottom!
}

void Game::initInventory() {
    //init all game Items
    Inventory key("key", Property::UNLOCK, Property::METAL);
    Inventory sword("sword", Property::SHARP, Property::METAL);
    Inventory torch("torch", Property::WOOD, Property::FLAMMABLE);
    Inventory stone("stone", Property::HARD, Property::HEAVY);
    Inventory crystals("crystals", Property::COLD, Property::HARD);
    Inventory shovel("shovel", Property::HARD, Property::HEAVY, Property::DIG);
    Inventory axe("axe", Property::HARD, Property::SHARP, Property::HEAVY);
    
    sword.giveAttack(15);
    //Add them to the list of items in the game
    allItems.push_back(key);
    allItems.push_back(sword);
    allItems.push_back(torch);
    allItems.push_back(stone);
    allItems.push_back(crystals);
    allItems.push_back(shovel);
    allItems.push_back(axe);
    
    for (int i = 0; i < 16; ++i) {
        inventory[i].name = "none";
        inventory[i].giveAttack(player.attack);
    }
    
}





//End of Game setup






















//Start of Engine

void Game::mainGame() {
    std::string areaHint = "";
    while (true) {
        checkBattle();
        cls();
        if (!isInSubarea) {
            currentArea = map[x][y];
        } else {
            currentArea = subareas[map[x][y].subareaID];
        }
        for (int i = 0; i < sizeof(currentArea.interactables); ++i) {
            
        }
        print(player.name + ":\n=============================================\n HP: " + std::to_string(player.hp) + "\n Fragments: *" + std::to_string(player.fragments) + "\n=============================================\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        areaHint = currentArea.getHint();
        currentArea.areaDescription = currentArea.generalDescription + areaHint;
        print(currentArea.areaDescription + "\n");
        std::string in;
        std::getline(std::cin, in);
        recognize(in);
        //print (std::to_string(map[5][5].interactables[0].isTriggered));
    }
}


void Game::start() {
    initAreas();
    print("\n\n\n\n\n\n\n\n                             WELCOME TO ARONTANIA\n\n\n\n             Type in 2-word commands, in the form of VERB-NOUN.\n\n\n\n\n\n\n\n");
    confirm();
    print("What is your name?");
    std::getline(std::cin, player.name);
    print("Hello " + player.name + "!");
    confirm();
    cls();
    mainGame();
}

void Game::print(std::string string) {
    std::cout <<std::endl << string;
}

void Game::confirm() {
    std::cin.ignore();
}


void Game::recognize(std::string input) {
    unsigned long space = input.find(" ");
    //int nounLength = input.length() - space;
    std::string verb = input.substr(0, space);
    std::string noun = input.substr(space + 1, input.length() - space);
    eventCheck(verb, noun);
}

void Game::areaSetUp(int posX, int posY, std::string name, std::string areaDesc) {
    
    //basic area set up
    map[posX][posY].name = name;
    map[posX][posY].description(areaDesc, posX, posY);
}



void Game::eventCheck(std::string verb, std::string noun) {
    Action action;
    action = checkAction(verb);
    switch (action) {
        case Action::GO:
            go(noun);
            break;
        case Action::GRAB:
            grab(noun);
            break;
            
        case Action::NONE:
            print("You can't " + verb + ".");
            break;
        case Action::ENTER:
            enter(noun);
            break;
        case Action::LEAVE:
            leave();
            break;
        default:
            print("Something went wrong!");
            break;
    }
    
    return;
}

void Game::grab(std::string noun) {
    //return the inventory item for an interact.
    for (int i = 0; i < sizeof(currentArea.interactables); ++i) {
        
        for (int j = 0; j < sizeof(allItems); ++j) {
            if (currentArea.interactables[i].nameOfObj == noun) {
                if (itemSlotIterator > 15) {
                    print("You can't hold anymore items! Type 'toss' and then the item you would like to discard to remove an item.");
                    return;
                }
                else if (allItems[j].name == currentArea.interactables[i].nameOfObj) {
                    if (!map[x][y].interactables[i].isTriggered && map[x][y].interactables[i].interactMatch == Property::GRAB) {
                        inventory[itemSlotIterator] = allItems[j];
                        print("You grabbed the " + inventory[itemSlotIterator].name + "!");
                        itemSlotIterator++;
                        map[x][y].interactables[i].isTriggered = true;
                        return;
                    }
                    else {
                        print("You can't grab that.");
                        return;
                    }
                }
            }
            
            else {
                print("You can't grab a " + noun + " here.");
                return;
            }
        }
    }
}

Action Game::checkAction(std::string verb) {
    //synonyms
    if (verb == "grab" || verb == "take") {
        return Action::GRAB;
    }
    else if (verb == "go" || verb == "travel" || verb == "walk" || verb == "hike" || verb == "trek") {
        return Action::GO;
    }
    else if (verb == "toss" || verb == "remove" || verb == "discard" || verb == "trash") {
        return Action::TOSS;
    }
    else if (verb == "enter" || verb == "open" || verb == "climb") {
        return Action::ENTER;
    }
    else if (verb == "leave" || verb == "exit") {
        return Action::LEAVE;
    }
    else {
        return Action::NONE;
    }
    
}


void Game::go(std::string noun) {
    if (noun == "north" || noun == "n") {
        ++y;
    }
    else if (noun == "south" || noun == "s") {
        --y;
        
    }
    else if (noun == "east" || noun == "e") {
        ++x;
    }
    else if (noun == "west" || noun == "w") {
        --x;
    }
    else {
        print("You can't go " + noun + "!");
    }
}

void Game::enter(std::string noun) {
    for (int i = 0; i < sizeof(currentArea.interactables); ++i) {
        if (currentArea.interactables[i].interactMatch == Property::OPEN) {
            print("You entered the door.");
            isInSubarea = true;
            return;
        }
        else if (currentArea.interactables[i].interactMatch == Property::UNLOCK) {
            std::string itemUsed = checkInventory(Property::UNLOCK);
            if (itemUsed != "") {
                print("You used the " + itemUsed + " to unlock it!");
                
                //Make a function that will be used to remove an item from the inventory after you use it, for example, a key.
                
                confirm();
                isInSubarea = true;
                return;
            }
        }
        else if (currentArea.interactables[i].interactMatch == Property::CLIMB) {
            if (!isInSubarea) {
                isInSubarea = true;
                return;
            } else {
                isInSubarea = false;
                return;
            }
        }
    }
}

std::string Game::checkInventory(Property property) {
    for (int i = 0; i < 16; ++i) {
        if (inventory[i].searchProperty(property)) {
            return inventory[i].name;
        }
    }
    return "";
}
void Game::checkBattle() {
    static int i;
    i = rand() % BATTLE_CHANCES;
    if (i == 5) { //the 5 is just a number I pulled from my head. It could be anything.
        battle();
    }
}
void Game::battle() {
    Enemy enemy;
    cls();
    print("Enemy encountered! ");
    confirm();
    while(enemy.hp > 0) {
        cls();
        std::string battleText = "\nEnemy:\n=============================================\n HP: " + std::to_string(enemy.hp) + "\n Attack: " + std::to_string(enemy.attack) + "\n=============================================\n\n" + player.name + ":\n=============================================\n HP: " + std::to_string(player.hp) + "\n=============================================\n";
        print(battleText);
        for (int i = 0; i < 16; ++i) { //16 is the size of the Inventory.
            print(std::to_string(i) + ": " + inventory[i].name + " - " + std::to_string(inventory[i].attack) + " attack power");
        }
        print("\nWhat would you like to use? (Type the corresponding number of the item you wish to use)\n");
        int in;
        std::cin >> in;
        player.attack = inventory[in].attack;
        enemy.hp -= player.attack;
        player.hp -= enemy.attack;
        print("Enemy took: " + std::to_string(player.attack) + " damage.\n\n" + player.name + " took: " + std::to_string(enemy.attack) + "\n");
    }
    print("\nEnemy defeated!");
    confirm();
    player.fragments += enemy.fragmentDrop;
}

void Game::leave() {
    if (isInSubarea) {
        isInSubarea = false;
    } else {
        print("You can't leave. MWUHAHAHAHAHAHAHAHAHAHA");
    }
    
}

//End of Engine





























void Game::cls() {
    std::cout << std::string(100, '\n');
}
