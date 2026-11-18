
#include "GameState.hpp"
#include "GameConstants.hpp"

// Starts with no flags and no final choice.
GameState::GameState()
    : flags(),
      flagCount(0),
      finalChoice(CHOICE_NONE)
{
}

// Starts with no flags and the given final choice.
GameState::GameState(int finalChoice)
    : flags(),
      flagCount(0),
      finalChoice(finalChoice)
{
}

// Adds a flag only if it is not already stored.
void GameState::setFlag(const std::string& name)
{
    if (hasFlag(name))
    {
        return;
    }

    // Do not add more flags once the array is full.
    if (flagCount >= MAX_FLAGS)
    {
        return;
    }

    flags[flagCount] = name;
    flagCount++;
}

// Adds or removes a flag depending on the Boolean value.
void GameState::setFlag(const std::string& name, bool value)
{
    if (value)
    {
        setFlag(name);
        return;
    }

    // Find the flag that needs to be removed.
    for (int i = 0; i < flagCount; i++)
    {
        if (flags[i] == name)
        {
            // Shift the remaining flags one position to the left.
            for (int j = i; j < flagCount - 1; j++)
            {
                flags[j] = flags[j + 1];
            }

            flagCount--;
            flags[flagCount] = "";
            return;
        }
    }
}

// Checks whether a flag exists in the array.
bool GameState::hasFlag(const std::string& name) const
{
    for (int i = 0; i < flagCount; i++)
    {
        if (flags[i] == name)
        {
            return true;
        }
    }

    return false;
}

// Returns the number of flags currently stored.
int GameState::getFlagCount() const
{
    return flagCount;
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

// Removes all stored flags and resets the final choice.
void GameState::reset()
{
    for (int i = 0; i < flagCount; i++)
    {
        flags[i] = "";
    }

    flagCount = 0;
    finalChoice = CHOICE_NONE;
}
