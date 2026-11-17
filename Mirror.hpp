// Mirror.hpp  -  written by Hijab Asif Malik (Member B). See Mirror.cpp for the full viva notes.
#ifndef MIRROR_HPP
#define MIRROR_HPP

#include <string>
#include "Interactable.hpp"

// Mirror IS-A Interactable. Its interact() shows different text depending on
// the player's progress:
//   - before the required clue is found it only shows fog,
//   - after it, it shows the hidden message and records a new clue.
// In the game: requiredFlag = "diaryRead", revealFlag = "mirrorRevealed".
// "mirrorRevealed" is the clue the Chest puzzle needs, so the Mirror is the
// link between the Diary and the Chest.
class Mirror : public Interactable
{
public:
    Mirror();
    Mirror(const std::string& name, const std::string& description,
           const std::string& fogText, const std::string& hiddenText,
           const std::string& requiredFlag, const std::string& revealFlag);

    void interact(Player& player, GameState& state) override;

    // No destructor needed: Mirror owns nothing on the heap.

private:
    std::string fogText;        // shown before the clue is found
    std::string hiddenText;     // the message shown after it
    std::string requiredFlag;   // clue needed to see the message ("" = none)
    std::string revealFlag;     // clue recorded when the message is first seen
};

#endif
