#ifndef ROOM_HPP
#define ROOM_HPP

using namespace std;
#include <string>
#include "GameConstants.hpp"   // for the array sizes

//Forward declarations:
class Interactable;
class Item;

// A Room is one place in the mansion (Entrance Hall, Library, ...).
// It has a name, a description, some objects the player can use (doors,
// puzzles, the mirror) and some items lying on the floor.
class Room 
{
    private:
        string name;
        string description;

        // Room owns its objects: it deletes them when the Room itself is deleted 
        // (composition : array of pointers)
        Interactable* objects[MAX_OBJECTS_PER_ROOM];
        int objectCount; // tells us how many slots in obejects array are actually used.

        // The Room does not own its items (Owned by Mansion)
        // Room only knows which items it has (aggregation)
        Item* items[MAX_ITEMS_PER_ROOM];
        int itemCount; // tells us how many slots in items array are actually used.

    public:
        Room(); // empty room
        Room(const string& name, const string& description);  // named room

        // RULE OF THREE:
        ~Room();   // destructor (deletes the objects the Room owns)

        // Copying a Room is not allowed. If two Rooms were copies of each other,
        // both would think they own the same objects and both would delete them,
        // which crashes the program. "= delete" tells the compiler to refuse copies.
        Room(const Room& other) = delete;
        Room& operator=(const Room& other) = delete;

        string getName() const;
        string getDescription() const;

        void describe() const;      // prints the room screen (name, description, items, objects)
        void listObjects() const;   // prints a numbered list of the objects
        void listItems() const;     // prints a numbered list of the items on the floor

        void addObject(Interactable* object);   // the Room takes ownership of this object
        void addItem(Item* item);               // the Room just remembers where this item is

        int getObjectCount() const;
        Interactable* getObject(int index) const;   // index starts at 0
        int getItemCount() const;

        // Overloaded funtions: 
        Item* takeItem(int index);  // finds an item by its position
        Item* takeItem(const string& name); //finds an item by its name
};

#endif