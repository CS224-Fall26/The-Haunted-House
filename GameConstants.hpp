#ifndef GAMECONSTANTS_HPP
#define GAMECONSTANTS_HPP

#include <string>
using namespace std;



// Progress flags:
// A flag is an indicator the game stores when the player finds something out.
// GameState stores these strings in memory and classes Mirror, Puzzle, and Item check them.
// Set as Global constants so that typos are avoided in other files.
const string FLAG_LETTER_READ = "letterRead";           // player has read Eleanor's Letter
const string FLAG_DIARY_READ = "diaryRead";             // player has read the Diary (unlocks a lot of clues)
const string FLAG_PHOTO_READ = "photoRead";             // player has read the back of the Old Photograph
const string FLAG_MIRROR_REVEALED = "mirrorRevealed";   // the Mirror showed its hidden message
const string FLAG_CONFESSION_READ = "confessionRead";   // player has read Thomas's Confession

// Item Names:
// The game finds items by their names so to avoid typos constants are set.
const string ITEM_LETTER = "Eleanor's Letter";
const string ITEM_BRASS_KEY = "Brass Key";            // opens the Bedroom
const string ITEM_IRON_KEY = "Iron Key";              // opens the Basement
const string ITEM_DIARY = "Eleanor's Diary";
const string ITEM_PHOTOGRAPH = "Old Photograph";
const string ITEM_LOCKET = "Eleanor's Locket";        // decides which good ending the player gets
const string ITEM_CONFESSION = "Thomas's Confession"; // opens the hidden wall in the basement

// Final choices: 
// At the end of the game the player's decision is saved as a number in GameState.
// Setting constants to explicitly display which choice corresponds to which decision making code easier to understand
const int CHOICE_NONE = 0;     // no decision yet, the game keeps going
const int CHOICE_TRUTH = 1;    // tell Eleanor the truth
const int CHOICE_BURN = 2;    // burn the confession
const int CHOICE_RUN = 3;     // run away (leave by the front door)

#endif