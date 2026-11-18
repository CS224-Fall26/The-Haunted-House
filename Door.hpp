#ifndef DOOR_HPP
#define DOOR_HPP
#include <string>
#include "Interactable.hpp"

// Forward declaration since Door only stores a Room pointer.
class Room;

// Door inherits from Interactable and overrides interact().
// It checks for the required key and moves the player to another room.
// If destination is nullptr, it acts as the front door (exit).
class Door : public Interactable
{
public:
    Door();
    Door(const std::string& name, const std::string& description,
         Room* destination, const std::string& requiredItem, bool locked);

    // Handles door interaction using the overridden function.
    void interact(Player& player, GameState& state) override;

    bool isLocked() const;

    // No destructor needed since Mansion owns all the rooms.
    // Door only stores a pointer to its destination.

private:
    Room* destination;          // Destination room, nullptr for front door
    std::string requiredItem;   // Key needed to unlock the door
    bool locked;                // Whether the door is locked
};

#endif
