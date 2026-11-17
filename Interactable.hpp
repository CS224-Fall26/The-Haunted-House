#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include <string>

// Forward declarations to avoid unnecessary includes.
class Player;
class GameState;

// Abstract base class for Door, Mirror, Ghost, and Puzzle.
// Uses pure virtual interact() to allow polymorphism.
class Interactable
{
public:
    // Constructors initialize and count objects.
    Interactable();
    Interactable(const std::string& name, const std::string& description);

    // Virtual destructor ensures proper cleanup of derived objects.
    virtual ~Interactable();

    // Disable copying to avoid ownership and memory issues.
    Interactable(const Interactable& other) = delete;
    Interactable& operator=(const Interactable& other) = delete;

    // Pure virtual function implemented by each derived class.
    virtual void interact(Player& player, GameState& state) = 0;

    // Const getters return references without copying strings.
    const std::string& getName() const;
    const std::string& getDescription() const;

    // Static function returns the total number of existing objects.
    static int getObjectCount();

private:
    std::string name;          // Object name
    std::string description;   // Object description

    static int objectCount;    // Shared object counter
};

#endif
