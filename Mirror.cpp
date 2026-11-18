// Mirror inherits from Interactable and overrides interact().
// It shows fog before the Diary is read and reveals a hidden message
// afterward. GameState flags connect the Diary, Mirror, and Chest.

#include "Mirror.hpp"

#include <iostream>
#include "GameState.hpp"   // Handles game flags

// Default constructor initializes the mirror with basic values.
Mirror::Mirror()
    : Interactable("Mirror", "An old mirror covered in dust."),
      fogText("Your reflection is blurred by a grey fog."),
      hiddenText("Nothing appears in the glass."),
      requiredFlag(""),
      revealFlag("")
{
}

// Constructor sets the mirror's messages and required flags.
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

// Overrides interact(). Player is unused but required by the function signature.
void Mirror::interact(Player& /* player */, GameState& state)
{
    // Show fog if the required clue hasn't been found.
    if (requiredFlag != "" && !state.hasFlag(requiredFlag))
    {
        std::cout << fogText << "\n";
        return;
    }

    // Show the hidden message once the clue is found.
    std::cout << hiddenText << "\n";

    // Record the mirror clue only if it hasn't been recorded yet.
    if (revealFlag != "" && !state.hasFlag(revealFlag))
    {
        state.setFlag(revealFlag);
        std::cout << "[New clue recorded: Mirror message]\n";
    }
}
