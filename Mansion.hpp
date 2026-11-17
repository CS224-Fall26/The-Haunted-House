#ifndef MANSION_HPP
#define MANSION_HPP

#include <string>
using namespace std;

#include "GameConstants.hpp"   // for the array sizes MAX_ROOMS and MAX_WORLD_ITEMS

//Forward declarations:
class Room;
class Item;

// The Mansion builds the whole game world and owns every Room and every Item.
class Mansion 
{
    private:
        string name;

        Room* rooms[MAX_ROOMS];        // every room in the game (Mansion creates and deletes these)
        int roomCount;                 // number of slots of the rooms array used

        Item* items[MAX_WORLD_ITEMS];  // every item in the game (Mansion creates and deletes these)
        int itemCount;                 // number of slots of the items array used

        // Private helpers fucntions used by build () 
        // save a new room or item in the next free slot respectively
        void storeRoom(Room* room);
        void storeItem(Item* item);

    public:
        Mansion(); // default constructor with name "Ashworth Manor"
        Mansion(const string& name);
        ~Mansion(); // destroys the whole world

        // RULE OF THREE
        // The Mansion owns heap memory, so copying it is not allowed
        // (two Mansions would both try to delete the same rooms and items).
        Mansion(const Mansion& other) = delete;
        Mansion& operator=(const Mansion& other) = delete;

        string getName() const;

        void build();   // creates a fresh world (deletes the old one first)
        void clear();   // deletes every room and item
        Room* getStartRoom() const;   // the Entrance Hall, or nullptr if nothing is built
};

#endif