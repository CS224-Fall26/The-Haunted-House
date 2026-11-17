// =====================================================================
// CodePuzzle.cpp  -  written by Hijab Asif Malik (Member B)
// ---------------------------------------------------------------------
// VIVA SUMMARY
//  * CodePuzzle IS-A Puzzle IS-A Interactable.
//  * Same procedure as every puzzle (inherited Template Method); only the
//    answer check differs: it compares a CODE.
//  * REUSE: ONE class serves THREE puzzles. Only their data is different:
//      Bookshelf          code "4132"                      reward Iron Key
//      Grandfather Clock  code "315", altCode "3:15"       reward Eleanor's Locket
//      Chest              code "1704"                      reward Thomas's Confession
//  * The code is stored as a STRING, not an int, so "3:15" works and a
//    leading zero (like "0412") would not be lost.
//  * No destructor: it owns nothing on the heap.
// =====================================================================
#include "CodePuzzle.hpp"
#include "InputUtils.hpp"   // cleanText()

// DEFAULT CONSTRUCTOR: Puzzle part first, then empty codes.
CodePuzzle::CodePuzzle()
    : Puzzle(),
      code(""),
      altCode("")
{
}

// PARAMETERIZED CONSTRUCTOR: six values go up to Puzzle, two are kept here.
CodePuzzle::CodePuzzle(const std::string& name, const std::string& description,
                       const std::string& prompt, const std::string& hint,
                       const std::string& requiredFlag, Item* reward,
                       const std::string& code, const std::string& altCode)
    : Puzzle(name, description, prompt, hint, requiredFlag, reward),
      code(code),
      altCode(altCode)
{
}

// OVERRIDES the pure virtual Puzzle::checkAnswer().
// Correct if the cleaned answer equals the code, OR equals the alternative
// code when there is one ("" means there is no alternative).
bool CodePuzzle::checkAnswer(const std::string& answer) const
{
    std::string cleaned = cleanText(answer);   // lower-case, spaces removed

    if (cleaned == cleanText(code))
    {
        return true;
    }
    if (altCode != "" && cleaned == cleanText(altCode))
    {
        return true;   // e.g. the clock accepts "3:15" as well as "315"
    }
    return false;
}
