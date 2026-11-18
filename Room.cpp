#include "Room.hpp"

#include <iostream>
using namespace std;


#include "Interactable.hpp"   
#include "Item.hpp"           
#include <cctype>     // needed for toupper


Room::Room(): name("Empty room"),description(""),objectCount(0),itemCount(0) 
{
    // Start every slot as nullptr
    for (int i = 0; i < MAX_OBJECTS_PER_ROOM; i++)
    {
        objects[i] = nullptr;
    }
    for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++)
    {
        items[i] = nullptr;
    }
}

Room::Room(const string& name, const string& description): name(name), description(description), objectCount(0), itemCount(0)
{
    for (int i = 0; i < MAX_OBJECTS_PER_ROOM; i++) 
    {
        objects[i] = nullptr;
    }
    for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++)
    {
        items[i] = nullptr;
    }
}

// Destructor: 
// The Room owns its objects, so it deletes each one.
// "delete" on an Interactable* still runs the right cleanup for the real type
// (Door, Mirror, ...) because Interactable has a virtual destructor.
Room::~Room() 
{
    for (int i = 0; i <objectCount; i++) 
    {
        delete objects[i];
        objects[i] = nullptr;   //avoids dangling pointers
    }
    objectCount = 0;
}

string Room::getName() const 
{
    return name;
}

string Room::getDescription() const 
{
    return description;
}

// Prints the whole room screen: title, description, items and objects.
void Room::describe() const 
{
    // Make a copy of the name in capital letters for the title.
    string title = name;
    for (int i=0; i < (int)title.size(); i++) 
    {
        title[i] = toupper(title[i]);
    }

    cout << "\n==================== " << title << " ====================\n";
    cout << description << endl;

    cout << "Items here: ";
    if (itemCount == 0) 
    {
        cout << "none";
    }
    else
    {
        for (int i = 0; i < itemCount; i++) 
        {
            if (i > 0) 
            {
                cout << ", ";   // comma sepearated list of item names (not before the first)
            }
            cout << items[i]->getName();
        }
        cout << endl;
    }

    cout << "Objects here: ";
    if (objectCount == 0) 
    {
        cout << "none";
    }
    else
    {
        for (int i = 0; i < objectCount; i++) 
        {
            if (i > 0) 
            {
                cout << ", ";   // comma sepearated list of object names (not before the first)
            }
            cout << objects[i]->getName();
        }
        cout<<endl;
    }
}

// Prints list of objects
void Room::listObjects() const 
{
    for (int i = 0; i < objectCount; i++) 
    {
        cout << "  " << (i + 1) << ". " << objects[i]->getName() << endl;
    }
}

// Prints list of items
void Room::listItems() const 
{
    for (int i = 0; i < itemCount; i++) 
    {
        cout << "  " << (i + 1) << ". " << items[i]->getName() << endl;
    }
}


void Room::addObject(Interactable* object) 
{
    if (object != nullptr && objectCount < MAX_OBJECTS_PER_ROOM) //check for free slots in objects array and to store valid object
    {
        objects[objectCount] = object;  // object added to the next free slot 
        objectCount++;                  // count incremented
    }
}


void Room::addItem(Item* item) 
{
    if (item != nullptr && itemCount < MAX_ITEMS_PER_ROOM) //check for free slots in items array and to store valid item
     {
        items[itemCount] = item;    // item added to the next free slot
        itemCount++;                // count incremented
    }
}

int Room::getObjectCount() const 
{
    return objectCount;
}

// Gives back the object at that position or nullptr if the position is invalid
Interactable* Room::getObject(int index) const 
{
    if (index < 0 || index >= objectCount) 
    {
        return nullptr;
    }
    return objects[index];
}

int Room::getItemCount() const 
{
    return itemCount;
}

// Taking the item at a position
// returns the item's pointer and slides every item after it one place to the left so that there is no gap in the array
// The item is not copied or deleted.
Item* Room::takeItem(int index)
{
    if (index < 0 || index >= itemCount) 
    {
        return nullptr;   // nothing at that position
    }
    Item* item = items[index];

    for (int i = index; i < itemCount - 1; i++) 
    {
        items[i] = items[i + 1];   // shift every item left to close the gap
    }
    itemCount--;
    items[itemCount] = nullptr;    // the last slot is now marked nullptr

    return item;
}

// Taking the item with a given name.
// Finds the item in the array using name, then calls overload 1 at that index
Item* Room::takeItem(const string& name) 
{
    for (int i = 0; i < itemCount; i++) 
    {
        if (items[i]->getName() == name) 
        {
            return takeItem(i);
        }
    }
    return nullptr;   // no item found with that name
}