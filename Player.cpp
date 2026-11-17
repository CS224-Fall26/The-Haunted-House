#include "Player.hpp"

using namespace std;
#include <string>

// empty default constructor:
Player::Player() : name("Traveller"), currentRoom(nullptr), inventory() {}

// Parameterized constructor used when a new game starts:
Player::Player(const string& name, Room* startRoom) : name(name), currentRoom(startRoom), inventory() {}

string Player::getName() const 
{
    return name;
}

Room* Player::getCurrentRoom() const 
{
    return currentRoom;
}

// Player walks into a new room so change room pointer
void Player::moveTo(Room* room) 
{
    currentRoom = room;
}

Inventory& Player::getInventory() //returns by reference allowing to add to inventory
{
    return inventory;              
}

Inventory Player::viewInventory() const 
{
    return inventory;
}