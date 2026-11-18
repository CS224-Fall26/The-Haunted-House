#ifndef PLAYER_HPP
#define PLAYER_HPP

using namespace std;
#include <string>
#include "Inventory.hpp"   // Player keeps an Inventory inside itself

class Room;   // forward declaration: Player points at a Room

// The Player class: who the player is, where they are standing, and what they carry.
class Player 
{
    private:
        string name;
        Room* currentRoom;     // points at the room the player is in currently
        Inventory inventory;   // the player's bag. It is created with the Player and destroyed with it.

    public:
        // overloaded constructors: 
        Player(); // empty constructor, player standing nowhere
        Player(const string& name, Room* startRoom); // player cosntructor with name and starting room

        string getName() const;
        Room* getCurrentRoom() const;
        void moveTo(Room* room);      // walk into another room

        Inventory& getInventory(); // lets us ADD items to the inventory, returns by reference
        
        Inventory viewInventory() const; // lets us VIEW the inventory.
};

#endif