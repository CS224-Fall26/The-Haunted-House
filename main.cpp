#include "Game.hpp"


int main() 
{
    Game game;    // creates the Game, which creates the Mansion, Player and GameState inside it
    game.run();   // shows the main menu and keeps running until the player chooses Quit
    return 0;    
}