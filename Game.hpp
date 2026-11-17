#ifndef GAME_HPP
#define GAME_HPP

using namespace std;
#include <string>

#include "Mansion.hpp"
#include "Player.hpp"
#include "GameState.hpp"   // Zoha's class

// The Game class runs everything the main menu and the room-by-room loop.
// It owns a Mansion, a Player and a GameState
// which are created when the Game is created and destroyed when it is destroyed (composition)
class Game {
private:
    string title;
    Mansion mansion;
    Player player;
    GameState state;

    // Private helpers:
    void showWelcome() const;   // displays welcome screen
    void showHowToPlay() const; //displays instructions
    void startNewGame();   // resets and starts new game
    void playGame();             // the loop that repeats the turns inside the house
    void showRoomMenu() const;  //displayes reoom menu upon entering
    void interactWithObject();  //player interats with object
    void pickUpItem();         //allows player to add item to inventory
    void showMapAndHelp() const;  //displays help notes
    bool confirmReturnToMenu() const; //returns player to main menu
    void showEnding() const;     // placeholder for now
    void endSession();           // cleans up and goes back to the main menu

public:
    Game();
    Game(const string& title);

    void run();   // shows the main menu and keeps going until the player quits
};

#endif