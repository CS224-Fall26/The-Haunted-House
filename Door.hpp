// Door.hpp  -  written by Hijab Asif Malik (Member B). See Door.cpp for the full viva notes.
#ifndef DOOR_HPP
#define DOOR_HPP

#include <string>
#include "Interactable.hpp"

// Forward declaration: Door only stores a POINTER to a Room, so the header
// does not need the full Room class. Room.hpp is included in Door.cpp.
class Room;

// Door IS-A Interactable (inheritance). It inherits name, description,
// getName(), getDescription() and the object counter, and it gives its own
// version of interact(): unlock if possible, then move the player.
//
// A Door with destination == nullptr is the FRONT DOOR: using it asks the
// player whether to leave the house (this ends the game).
class Door : public Interactable
{
public:
    Door();
    Door(const std::string& name, const std::string& description,
         Room* destination, const std::string& requiredItem, bool locked);

    // "override" asks the compiler to check that this really replaces the
    // pure virtual Interactable::interact(). A typo in the parameters would
    // then be a compile error instead of a silent bug.
    void interact(Player& player, GameState& state) override;

    bool isLocked() const;

    // No destructor needed: Door owns nothing on the heap.
    // ASSOCIATION, not ownership: Door only POINTS to its destination Room.
    // Mansion owns every Room and deletes it, so Door must never delete it.

private:
    Room* destination;          // where the door leads; nullptr = front door
    std::string requiredItem;   // exact item name of the key, e.g. "Brass Key"
    bool locked;                // true until the player uses the right key
};

#endif
