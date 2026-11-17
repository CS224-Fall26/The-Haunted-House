// =====================================================================
// Interactable.cpp  -  written by Hijab Asif Malik (Member B)
// ---------------------------------------------------------------------
// VIVA SUMMARY
//  * Interactable is the ABSTRACT BASE CLASS of Door, Mirror, Ghost, Puzzle.
//  * Abstract = it has a pure virtual function (interact() = 0), so you can
//    never write "new Interactable". You can only create the derived classes.
//  * Room keeps a vector<Interactable*>. Calling objects[i]->interact(...)
//    runs Door's, Mirror's or Puzzle's version = RUNTIME POLYMORPHISM.
//  * The destructor is VIRTUAL so that "delete basePointer" runs the derived
//    destructor first (e.g. ~Door) and then ~Interactable. Without virtual,
//    only ~Interactable would run -> undefined behaviour.
//  * objectCount is STATIC: one counter shared by the whole class, not one
//    per object. +1 in every constructor, -1 in the destructor. If it is 0
//    when we return to the main menu, every object was deleted (no leaks).
//  * Copy constructor and copy assignment are "= delete": an object cannot be
//    copied by mistake (a copy would have no owner -> leak or double delete).
// =====================================================================
#include "Interactable.hpp"

// A static data member is only DECLARED inside the class (in the .hpp).
// It must be DEFINED exactly once in a .cpp file. This line creates the one
// shared counter and starts it at 0. Without it the program does not link
// ("undefined reference to Interactable::objectCount").
int Interactable::objectCount = 0;

// DEFAULT CONSTRUCTOR
// The part after ":" is the MEMBER INITIALIZER LIST. It sets the members
// directly when the object is created (better than assigning in the body).
// Every constructor must count the object, so objectCount++ is here too.
Interactable::Interactable()
    : name("Unnamed object"),
      description("There is nothing special about it.")
{
    objectCount++;   // one more Interactable exists now
}

// PARAMETERIZED CONSTRUCTOR
// Derived classes call this one, e.g. Door's constructor does
// ": Interactable(name, description)". The base part is always built FIRST.
// Parameters are "const std::string&": passed by reference (no copy) and
// const (this function promises not to change the caller's string).
Interactable::Interactable(const std::string& name, const std::string& description)
    : name(name),
      description(description)
{
    objectCount++;   // one more Interactable exists now
}

// DESTRUCTOR (virtual, see the .hpp)
// Order when Room does "delete objects[i]" and the object is a Door:
//   1. ~Door() runs (Door has none of its own, so the compiler's empty one)
//   2. then ~Interactable() runs automatically -> objectCount--
//   3. then the memory is freed.
// Interactable owns no heap memory, so updating the counter is its only job.
Interactable::~Interactable()
{
    objectCount--;   // one Interactable fewer
}

// GETTERS
// "const" at the end = this function does not change the object, so it can
// be called on a const object. Returning "const std::string&" gives read-only
// access to the member without making a copy. The data stays PRIVATE
// (encapsulation): derived classes can read the name but not change it.
const std::string& Interactable::getName() const
{
    return name;
}

const std::string& Interactable::getDescription() const
{
    return description;
}

// STATIC FUNCTION
// It belongs to the class, so it is called with the class name and needs no
// object:  Interactable::getObjectCount()
// A static function can only use static members (it has no "this").
int Interactable::getObjectCount()
{
    return objectCount;
}
