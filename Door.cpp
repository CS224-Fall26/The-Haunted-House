// =====================================================================
// Door.cpp  -  written by Hijab Asif Malik (Member B)
// ---------------------------------------------------------------------
// VIVA SUMMARY
//  * INHERITANCE: Door IS-A Interactable. It inherits name, description,
//    getName(), getDescription() and the object counter.
//  * POLYMORPHISM: Door OVERRIDES interact(). Room calls it through an
//    Interactable* and C++ runs this version because interact() is virtual.
//  * ASSOCIATION (not ownership): Door only POINTS to its destination Room.
//    Mansion owns every Room. Many doors lead to the same room (the Hall), so
//    if each door deleted its room the Hall would be deleted several times
//    (double delete -> crash). That is why Door has NO destructor.
//  * ENCAPSULATION: "locked" is private. The only way to unlock is to call
//    interact() while carrying the right key.
//  * A door whose destination is nullptr is the FRONT DOOR (leave the house).
//
// TRACE - locked Bedroom Door, player WITHOUT the Brass Key:
//   Room calls objects[i]->interact(player, state) -> Door::interact runs
//   -> destination is not nullptr (not the front door)
//   -> locked is true -> hasItem("Brass Key") is false
//   -> prints "The Bedroom Door is locked." + description -> return
//   -> moveTo() is never called, so the player stays in the same room.
// TRACE - same door WITH the Brass Key:
//   -> hasItem("Brass Key") is true -> locked = false -> prints unlock line
//   -> continues to step 3 -> prints "You step into the Bedroom."
//   -> player.moveTo(destination). The key stays in the inventory and the
//      door stays unlocked, so next time it goes straight to step 3.
// =====================================================================
#include "Door.hpp"

// The header only needed "class Room;" (a forward declaration) because it
// stores a pointer. Here we CALL functions on these classes, so we need their
// full definitions.
#include <iostream>
#include "Player.hpp"         // player.getInventory(), player.moveTo()
#include "Room.hpp"           // destination->getName()
#include "Inventory.hpp"      // getInventory().hasItem(...)
#include "GameState.hpp"      // state.setFinalChoice(...)
#include "InputUtils.hpp"     // readInt()
#include "GameConstants.hpp"  // CHOICE_RUN

// DEFAULT CONSTRUCTOR
// ": Interactable(...)" calls the BASE CLASS constructor first, because name
// and description are private in Interactable and only it can set them.
// destination = nullptr means "leads nowhere" (so it acts like a front door).
Door::Door()
    : Interactable("Door", "A plain wooden door."),
      destination(nullptr),
      requiredItem(""),
      locked(false)
{
}

// PARAMETERIZED CONSTRUCTOR (this is the one Mansion uses)
// name and description go up to Interactable; the rest is Door's own data.
// "Room* destination" is only a pointer copy: no new Room is created.
Door::Door(const std::string& name, const std::string& description,
           Room* destination, const std::string& requiredItem, bool locked)
    : Interactable(name, description),
      destination(destination),
      requiredItem(requiredItem),
      locked(locked)
{
}

// interact() OVERRIDES the pure virtual Interactable::interact().
// Three steps, in this order:
void Door::interact(Player& player, GameState& state)
{
    // STEP 1 - FRONT DOOR: no destination room, so ask before leaving.
    if (destination == nullptr)
    {
        std::cout << "Leave Ashworth Manor? The mystery will stay unsolved.\n";
        std::cout << "   1. Yes\n";
        std::cout << "   2. No\n";
        int choice = readInt(1, 2);   // Jazib's helper: only accepts 1 or 2

        if (choice == 1)
        {
            std::cout << "You step out into the cold night and do not look back.\n";
            // Door only RECORDS the choice in GameState. It does not print an
            // ending: Game checks getFinalChoice() after every interaction and
            // shows the ending itself (one place decides endings).
            state.setFinalChoice(CHOICE_RUN);
        }
        return;   // the front door never moves the player
    }

    // STEP 2 - LOCKED DOOR: open only if the player carries the matching key.
    if (locked)
    {
        // getInventory() returns a REFERENCE to the player's own Inventory,
        // so we search the real inventory, not a copy.
        if (player.getInventory().hasItem(requiredItem))
        {
            locked = false;   // stays unlocked from now on; the key is kept
            std::cout << "You unlock the " << getName()
                      << " with the " << requiredItem << ".\n";
        }
        else
        {
            std::cout << "The " << getName() << " is locked.\n";
            std::cout << getDescription() << "\n";
            return;           // stop here: the player does not move
        }
    }

    // STEP 3 - OPEN DOOR: move the player. "->" because destination is a
    // pointer. Game prints the new room's description afterwards.
    std::cout << "You step into the " << destination->getName() << ".\n";
    player.moveTo(destination);
}

// const getter: only reads "locked", never changes it.
bool Door::isLocked() const
{
    return locked;
}
