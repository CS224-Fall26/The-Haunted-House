#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>

class GameState
{
public:
    GameState();
    explicit GameState(int finalChoice);

    // Adds a flag or adds/removes it depending on the value.
    void setFlag(const std::string& name);
    void setFlag(const std::string& name, bool value);

    // Checks the stored flags and returns the current count.
    bool hasFlag(const std::string& name) const;
    int getFlagCount() const;

    // Stores and returns the player's final choice.
    void setFinalChoice(int choice);
    int getFinalChoice() const;

    // Clears all progress for a new game.
    void reset();

private:
    static const int MAX_FLAGS = 20; // Maximum number of flags that can be stored.

    std::string flags[MAX_FLAGS]; // Fixed-size array for storing clue flags.
    int flagCount;                // Number of flags currently stored.
    int finalChoice;
};

#endif
