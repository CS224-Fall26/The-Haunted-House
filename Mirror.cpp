// =====================================================================
// Mirror.cpp  -  written by Hijab Asif Malik (Member B)
// ---------------------------------------------------------------------
// VIVA SUMMARY
//  * Mirror IS-A Interactable and OVERRIDES interact() (polymorphism).
//  * It shows different text depending on the player's progress:
//      before the Diary is read   -> only fog
//      after the Diary is read    -> the hidden message, and the FIRST time
//                                    it records the clue "mirrorRevealed"
//  * It links the clue chain: Diary -> Mirror -> Chest. The Chest puzzle
//    needs the "mirrorRevealed" flag. Mirror and Chest never point to each
//    other; they only communicate through FLAGS in GameState. This keeps the
//    classes independent (Mirror does not need to know a Chest exists).
//  * No destructor: all four members are std::strings (they clean up
//    themselves). The inherited virtual ~Interactable() still runs, so the
//    object count goes down when Room deletes the Mirror.
//
// TRACE - player looks in the Mirror BEFORE reading the Diary:
//   Room calls objects[i]->interact(...) -> Mirror::interact runs
//   -> requiredFlag "diaryRead" is missing -> prints fogText -> return
//   (no flag is set, so the Chest still stays locked)
// =====================================================================
#include "Mirror.hpp"

#include <iostream>
#include "GameState.hpp"   // state.hasFlag(), state.setFlag()

// DEFAULT CONSTRUCTOR: base part first, then placeholder texts and no flags.
Mirror::Mirror()
    : Interactable("Mirror", "An old mirror covered in dust."),
      fogText("Your reflection is blurred by a grey fog."),
      hiddenText("Nothing appears in the glass."),
      requiredFlag(""),
      revealFlag("")
{
}

// PARAMETERIZED CONSTRUCTOR (Mansion uses this one with
// requiredFlag = "diaryRead" and revealFlag = "mirrorRevealed").
Mirror::Mirror(const std::string& name, const std::string& description,
               const std::string& fogText, const std::string& hiddenText,
               const std::string& requiredFlag, const std::string& revealFlag)
    : Interactable(name, description),
      fogText(fogText),
      hiddenText(hiddenText),
      requiredFlag(requiredFlag),
      revealFlag(revealFlag)
{
}

// The Player parameter has NO NAME because Mirror does not use it.
// It must still be there: to OVERRIDE, the parameters must match
// Interactable::interact(Player&, GameState&) exactly. Otherwise this would
// be a new function, interact() would stay pure virtual, Mirror would be
// abstract and "new Mirror(...)" would not compile.
// Leaving the name out tells the compiler "unused on purpose" (no warning).
void Mirror::interact(Player& /* player */, GameState& state)
{
    // NOT READY: the player has not found the clue yet ("" = no clue needed).
    if (requiredFlag != "" && !state.hasFlag(requiredFlag))
    {
        std::cout << fogText << "\n";
        return;
    }

    // READY: show the message every time the player looks...
    std::cout << hiddenText << "\n";

    // ...but record the clue only the FIRST time. The second time hasFlag()
    // is already true, so the clue is never recorded twice.
    if (revealFlag != "" && !state.hasFlag(revealFlag))
    {
        state.setFlag(revealFlag);
        std::cout << "[New clue recorded: Mirror message]\n";
    }
}
