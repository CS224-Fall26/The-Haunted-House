// Interactable.hpp  -  written by Hijab Asif Malik (Member B). See Interactable.cpp for the full viva notes.
#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include <string>

// Forward declarations: interact() only takes these by reference, so the
// header does not need their full definitions. The real #includes go in the
// .cpp files of the derived classes that actually use Player and GameState.
class Player;
class GameState;

// Interactable is the ABSTRACT BASE CLASS of everything the player can
// interact with in a room: Door, Mirror, Ghost and Puzzle.
// It is abstract because interact() is a PURE VIRTUAL function (= 0):
// "an object you can interact with" is only an idea, so nobody can create a
// plain Interactable. Only the derived classes can be created.
class Interactable
{
public:
    // Constructors (both use member initializer lists and both count the object)
    Interactable();
    Interactable(const std::string& name, const std::string& description);

    // VIRTUAL destructor: Room deletes its objects through Interactable*
    // pointers. Without "virtual", deleting a Door through an Interactable*
    // would run only this destructor, not Door's (undefined behaviour).
    virtual ~Interactable();

    // Copying is switched off. Every Interactable is created once by Mansion
    // and owned by exactly one Room; a copy would make a second object that
    // nobody owns, and it would not be counted correctly.
    Interactable(const Interactable& other) = delete;
    Interactable& operator=(const Interactable& other) = delete;

    // THE common interface. Each derived class overrides this with its own
    // behaviour, and Room/Game call it through an Interactable* pointer
    // (runtime polymorphism). "= 0" makes it pure virtual.
    virtual void interact(Player& player, GameState& state) = 0;

    // Getters are const: reading the name never changes the object.
    // They return a const reference so the string is not copied.
    const std::string& getName() const;
    const std::string& getDescription() const;

    // STATIC: belongs to the class, not to one object. It reports how many
    // Interactables exist right now. After the game returns to the main menu
    // it should be 0, which proves every object was deleted (no leaks).
    static int getObjectCount();

private:
    std::string name;          // e.g. "Bedroom Door"
    std::string description;   // e.g. "A heavy oak door with a brass keyhole."

    static int objectCount;    // ONE shared counter for all Interactables
};

#endif
