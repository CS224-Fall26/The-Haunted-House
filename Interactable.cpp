// Abstract base class for Door, Mirror, Ghost, and Puzzle.
// Uses virtual interact() for polymorphism and a virtual destructor
// for proper cleanup. A static counter tracks existing objects.
// Copying is disabled to avoid memory issues.

#include "Interactable.hpp"

// Shared counter for all Interactable objects.
int Interactable::objectCount = 0;

// Default constructor initializes values and counts the object.
Interactable::Interactable()
    : name("Unnamed object"),
      description("There is nothing special about it.")
{
    objectCount++;   // Increase object count
}

// Parameterized constructor uses const references to avoid copies.
Interactable::Interactable(const std::string& name, const std::string& description)
    : name(name),
      description(description)
{
    objectCount++;   // Increase object count
}

// Virtual destructor ensures proper cleanup of derived objects.
Interactable::~Interactable()
{
    objectCount--;   // Decrease object count
}

// Returns the name without modifying or copying it.
const std::string& Interactable::getName() const
{
    return name;
}

// Returns the description without modifying or copying it.
const std::string& Interactable::getDescription() const
{
    return description;
}

// Static function returns the number of existing objects.
int Interactable::getObjectCount()
{
    return objectCount;
}
