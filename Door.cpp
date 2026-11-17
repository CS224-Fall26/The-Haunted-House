// Door inherits from Interactable and handles moving between rooms.
// It checks if the player has the required key before unlocking a door.
// The front door allows the player to leave, while other doors lead to rooms.

#include "Door.hpp"
#include <iostream>
#include "Player.hpp"         
#include "Room.hpp"           
#include "Inventory.hpp"      
#include "GameState.hpp"     
#include "InputUtils.hpp"     
#include "GameConstants.hpp"  

// Default constructor sets the door's basic values.
Door::Door()
    : Interactable("Door", "A plain wooden door."),
      destination(nullptr),
      requiredItem(""),
      locked(false)
{
}

// Constructor sets the door details and the room it leads to.
Door::Door(const std::string& name, const std::string& description,
           Room* destination, const std::string& requiredItem, bool locked)
    : Interactable(name, description),
      destination(destination),
      requiredItem(requiredItem),
      locked(locked)
{
}

// Handles opening doors, unlocking them, or leaving the mansion.
void Door::interact(Player& player, GameState& state)
{
    // If there is no destination, this is the front door.
    if (destination == nullptr)
    {
        std::cout << "Leave Ashworth Manor? The mystery will stay unsolved.\n";
        std::cout << "   1. Yes\n";
        std::cout << "   2. No\n";
        int choice = readInt(1, 2);   // Accepts only 1 or 2

        if (choice == 1)
        {
            std::cout << "You step out into the cold night and do not look back.\n";
            // Save the player's choice so Game can handle the ending.
            state.setFinalChoice(CHOICE_RUN);
        }
        return;   // No room movement
    }

    // Check if the door is locked and the player has the key.
    if (locked)
    {
        // Search the player's inventory for the required item.
        if (player.getInventory().hasItem(requiredItem))
        {
            locked = false;   // Unlock the door permanently
            std::cout << "You unlock the " << getName()
                      << " with the " << requiredItem << ".\n";
        }
        else
        {
            std::cout << "The " << getName() << " is locked.\n";
            std::cout << getDescription() << "\n";
            return;           // Player cannot enter
        }
    }

    // Move the player to the destination room.
    std::cout << "You step into the " << destination->getName() << ".\n";
    player.moveTo(destination);
}

// Returns whether the door is locked.
bool Door::isLocked() const
{
    return locked;
}