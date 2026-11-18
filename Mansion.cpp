#include "Mansion.hpp"

#include "Room.hpp"
#include "Item.hpp"
#include "Door.hpp"            // Hijab's classes
#include "Mirror.hpp"
#include "RiddlePuzzle.hpp"
#include "CodePuzzle.hpp"
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

// Creates the rooms, items, puzzles and doors of the game.
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
    Room* bedroom = new Room("Bedroom",
                             "A faded four-poster bed sits under a layer of dust. A tall mirror\n"
                             "leans against the wall.");
    Room* basement = new Room("Basement",
                              "The air is cold and damp. A heavy chest sits at the foot of the\n"
                              "stairs, and the far wall looks newer than the rest.");
    //Add all rooms to Mansion                       
    storeRoom(hall);      
    storeRoom(library);
    storeRoom(bedroom);
    storeRoom(basement);

    // Items:
    // (Mansion owns the items, room only knows which ones lie in it)
    // Item(name, description, text, clueFlag)
    // empty clueFlag "" means the item is not a clue

    // Items the player picks up from the floor:
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
    Item* diary = new Item(ITEM_DIARY,
                           "leather, with a broken clasp",
                           "\"I shelved my life as I lived it: first the spring I came to this house,\n"
                           " then the winter I married, then the letters I never sent, and at last\n"
                           " the quiet year.\"\n"
                           "\"Thomas asked me at a quarter past three, and I made him stop the hall\n"
                           " clock at that very minute.\"",
                           FLAG_DIARY_READ);

    // Items the player only gets as a puzzle reward (they do not lie in any room):
    Item* brassKey = new Item(ITEM_BRASS_KEY, 
                              "a small brass key engraved with a rose", "", "");
    Item* ironKey = new Item(ITEM_IRON_KEY, 
                             "a heavy iron key, cold to the touch", "", "");
    Item* locket = new Item(ITEM_LOCKET, 
                            "a small silver locket", "", "");
    Item* confession = new Item(ITEM_CONFESSION,
                                "a folded letter in a man's handwriting",
                                "\"I never meant for her to fall. I was afraid, so I hid what happened\n"
                                " and sealed her things behind the basement wall. I could never bring\n"
                                " myself to send this.  - Thomas\"",
                                FLAG_CONFESSION_READ);

    //Add all items to Mansion 
    storeItem(letter);
    storeItem(photograph);
    storeItem(diary);
    storeItem(brassKey);
    storeItem(ironKey);
    storeItem(locket);
    storeItem(confession);

    // Items lying in the rooms:
    hall->addItem(letter);          // the letter lies in the hall
    library->addItem(photograph);   // the photograph lies in the library
    bedroom->addItem(diary);        // the diary lies in the bedroom

    // Objects:
    // Each Room takes ownership of the objects
    // Door(name, description, destination room, key needed, locked?)
    // empty key name "" means no key is needed.
    // Puzzle(name, description, prompt, hint, required flag, reward item, answer(s))
    // empty required flag "" means the puzzle needs no earlier clue.

    // Entrance Hall:
    hall->addObject(new Door("Library Door", "An old oak door leads to the Library.",
                             library, "", false));
    hall->addObject(new Door("Bedroom Door", "A small brass keyhole glints in the candlelight.",
                             bedroom, ITEM_BRASS_KEY, true));
    hall->addObject(new Door("Basement Door", "A heavy door with an iron lock.",
                             basement, ITEM_IRON_KEY, true));
    hall->addObject(new CodePuzzle("Grandfather Clock",
                                   "The clock stands frozen, its hands stuck in place.",
                                   "You can turn the clock's hands. Enter the time as digits (for example 1230): ",
                                   "Eleanor made Thomas stop the clock at the minute he proposed.",
                                   FLAG_DIARY_READ, locket, "315", "3:15"));

    // front door destination is nullptr (way out of the house)
    hall->addObject(new Door("Front Door", "The heavy front door of the manor.",
                             nullptr, "", false));

    // Library:
    library->addObject(new RiddlePuzzle("Writing Desk",
                                        "Words are carved into the lid.",
                                        "\"The more of me you take, the more you leave behind. What am I?\"",
                                        "Think about what you leave behind with every step you take.",
                                        "", brassKey, "footsteps"));
    library->addObject(new CodePuzzle("Bookshelf",
                                      "Four books lean in an uneven row.",
                                      "Four books lean in an uneven row:\n"
                                      "  1. A Winter Wedding     2. The Quiet Year\n"
                                      "  3. Letters Never Sent   4. Spring at Ashworth\n"
                                      "Enter the order of the books (for example 1234): ",
                                      "Eleanor shelved her books in the order of her life. Read her diary.",
                                      FLAG_DIARY_READ, ironKey, "4132", ""));
    library->addObject(new Door("Hall Door", "A door back to the Entrance Hall.",
                                hall, "", false));

    // Bedroom:
    bedroom->addObject(new Mirror("Mirror", "A tall mirror with a cracked frame.",
                                  "Your reflection is blurred by a grey fog. For a moment you think\n"
                                  "someone stands behind you.",
                                  "The fog parts. Letters appear in the dust, backwards:\n"
                                  "  DEHSINAV I YAD EHT SREBMEMER TSEHC EHT\n"
                                  "Read in reverse: \"THE CHEST REMEMBERS THE DAY I VANISHED\"",
                                  FLAG_DIARY_READ, FLAG_MIRROR_REVEALED));
    bedroom->addObject(new Door("Hall Door", "A door back to the Entrance Hall.",
                                hall, "", false));

    // Basement:
    basement->addObject(new CodePuzzle("Chest",
                                       "A heavy chest with a four-digit lock.",
                                       "The chest has a four-digit lock. Enter the code: ",
                                       "The photograph shows a date. The day and month make four digits.",
                                       FLAG_MIRROR_REVEALED, confession, "1704", ""));
    basement->addObject(new Door("Stairs Up", "The stairs lead back up to the Entrance Hall.",
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