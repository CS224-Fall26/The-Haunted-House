
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>
#include <vector>

// Stores the player's progress, including discovered clues and final choice.
class GameState
{
public:
    GameState(); // Starts with no flags and CHOICE_NONE.
    explicit GameState(int finalChoice);

    // Function overloading: add a flag or add/remove it using a bool value.
    void setFlag(const std::string& name);
    void setFlag(const std::string& name, bool value);

    // Checks whether a clue or progress flag has been recorded.
    bool hasFlag(const std::string& name) const;

    int getFlagCount() const;

    void setFinalChoice(int choice);
    int getFinalChoice() const;

    // Clears all progress and resets the final choice for a new game.
    void reset();

private:
    // Stores discovered clues, such as "diaryRead" and "letterRead".
    std::vector<std::string> flags;

    // Stores the player's ending choice.
    int finalChoice;
};

#endif
