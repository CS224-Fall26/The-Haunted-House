
#include "GameState.hpp"
#include "GameConstants.hpp"

// Default constructor: starts with an empty list of flags and no final choice.
GameState::GameState()
    : flags(),
      finalChoice(CHOICE_NONE)
{
}

// Parameterized constructor: starts with a given final choice.
GameState::GameState(int finalChoice)
    : flags(),
      finalChoice(finalChoice)
{
}

// Function overload 1: adds a flag only if it does not already exist.
void GameState::setFlag(const std::string& name)
{
    if (!hasFlag(name))
    {
        flags.push_back(name);
    }
}

// Function overload 2: adds or removes a flag based on the Boolean value.
void GameState::setFlag(const std::string& name, bool value)
{
    if (value)
    {
        setFlag(name); // Reuses the first overload to avoid duplicate code.
        return;
    }

    // Search for the flag and remove it if it exists.
    for (int i = 0; i < (int)flags.size(); i++)
    {
        if (flags[i] == name)
        {
            flags.erase(flags.begin() + i);
            return;
        }
    }
}

// Checks whether a particular flag exists in the vector.
// const means this function does not modify GameState.
bool GameState::hasFlag(const std::string& name) const
{
    for (int i = 0; i < (int)flags.size(); i++)
    {
        if (flags[i] == name)
        {
            return true;
        }
    }

    return false;
}

// Returns the total number of recorded flags.
int GameState::getFlagCount() const
{
    return (int)flags.size();
}

// Saves the player's final decision.
void GameState::setFinalChoice(int choice)
{
    finalChoice = choice;
}

// Returns the player's final decision.
int GameState::getFinalChoice() const
{
    return finalChoice;
}

// Clears the previous progress when a new game starts.
void GameState::reset()
{
    flags.clear();
    finalChoice = CHOICE_NONE;
}
