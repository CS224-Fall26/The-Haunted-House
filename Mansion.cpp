#include "Mansion.hpp"

#include "Room.hpp"
#include "Item.hpp"
#include "Door.hpp"            // Hijab's class
#include "GameConstants.hpp"

// Default constructor:
Mansion::Mansion(): name("Ashworth Manor"), roomCount(0), itemCount(0) 
{
    //starts with an empty world
    for (int i = 0; i < MAX_ROOMS; i++) 
    {
        rooms[i] = nullptr;
    }
    for (int i = 0; i < MAX_WORLD_ITEMS; i++) 
    {
        items[i] = nullptr;
    }
}

// Parameterized constructor: (name of our choice)
Mansion::Mansion(const std::string& name): name(name), roomCount(0), itemCount(0) 
{
    for (int i = 0; i < MAX_ROOMS; i++) 
    {
        rooms[i] = nullptr;
    }
    for (int i = 0; i < MAX_WORLD_ITEMS; i++)
    {
        items[i] = nullptr;
    }
}

// Calls clear to delete everthing the Mansion has created
Mansion::~Mansion() 
{
    clear();
}

string Mansion::getName() const 
{
    return name;
}

// Puts a room in the next free slot of the rooms array.
void Mansion::storeRoom(Room* room) 
{
    if (room != nullptr && roomCount < MAX_ROOMS) 
    {
        rooms[roomCount] = room;
        roomCount++;
    }
}

// Puts an item in the next free slot of the item array
void Mansion::storeItem(Item* item) 
{
    if (item != nullptr && itemCount < MAX_WORLD_ITEMS) 
    {
        items[itemCount] = item;
        itemCount++;
    }
}

// Deletes everything the Mansion created
void Mansion::clear() 
{
    for (int i = 0; i < roomCount; i++) 
    {
        delete rooms[i];       // Deleting a Room also deletes the objects inside it
        rooms[i] = nullptr;
    }
    roomCount = 0;  //sets counts back to zero

    for (int i = 0; i < itemCount; i++)
    {
        delete items[i];
        items[i] = nullptr;
    }
    itemCount = 0;   //sets counts back to zero
}

// Creates the rooms, items and doors of the game.
void Mansion::build() 
{
    clear();   // delete the old world first so starting second game does not cause memory leaks

    // Rooms:
    Room* hall = new Room("Entrance Hall",
                          "Dust covers a grand staircase. A grandfather clock stands silent,\n"
                          "its hands frozen in place.");
    Room* library = new Room("Library", 
                             "Tall shelves lean over a heavy writing desk. The air smells of\n"
                             "old paper, and a pale light flickers near the window.");
    //Add both rooms to Mansion                       
    storeRoom(hall);      
    storeRoom(library);

    // Items:
    // (Mansion owns the items, room only kniows which ones lie in it)
    // Item(name, description, text, clueFlag)
    Item* letter = new Item(ITEM_LETTER, //name constant
                            "addressed to \"whoever comes next\"",
                            "\"To whoever comes next: if you are reading this, I never got to leave.\n"
                            " This house keeps its secrets well, but it remembers. Look closely at\n"
                            " what I left behind.  - Eleanor\"",
                            FLAG_LETTER_READ); // Flag
    Item* photograph = new Item(ITEM_PHOTOGRAPH,
                                "a faded photograph of a woman in a garden",
                                "On the back, in faded ink: \"Our last spring - 17/04/1987\"",
                                FLAG_PHOTO_READ);
    //Add both items to Mansion 
    storeItem(letter);
    storeItem(photograph);

    hall->addItem(letter);          // the letter lies in the hall
    library->addItem(photograph);   // the photograph lies in the library

    // Objects:
    // Each Room takes ownership of the objects
    // Door(name, description, destination room, key needed, locked?)
    // empty key name "" means no key is needed.
    hall->addObject(new Door("Library Door", "An old oak door leads to the Library.",
                             library, "", false));

    // front door destination is nullptr (way out of the house)
    hall->addObject(new Door("Front Door", "The heavy front door of the manor.",
                             nullptr, "", false));

    library->addObject(new Door("Hall Door", "A door back to the Entrance Hall.",
                                hall, "", false));
}

// returns the first room we stored which is the Entrance Hall (Player starts here)
Room* Mansion::getStartRoom() const 
{
    if (roomCount == 0) 
    {
        return nullptr;   // the world has not been built yet
    }
    return rooms[0];
}