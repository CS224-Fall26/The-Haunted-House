#include "Game.hpp"

#include <iostream>
using namespace std;

#include "InputUtils.hpp"
#include "GameConstants.hpp"
#include "Room.hpp"
#include "Item.hpp"
#include "Interactable.hpp"

// default constructor:
Game::Game() : title("THE HAUNTED HOUSE"), mansion(), player(), state() {}

// parameterized constructor (lets us choose a different title)
Game::Game(const string& title): title(title), mansion(), player(), state() {}


// Main menu:
// keeps showing the welcome menu until the player chooses quit.
void Game::run() 
{
    bool running = true;
    while (running)
    {
        showWelcome();
        int choice = readInt(0, 3);

        if (choice == 1)
        {
            startNewGame();
        } 
        else if (choice == 2) 
        {
            showHowToPlay();
        } 
        else if (choice == 3) 
        {
            cout << "Load Game is not available yet."<<endl;
            waitForEnter();
        } 
        else 
        {
            running = false;   // choice 0 = Quit
        }
    }
    cout << "Goodbye."<endl;
}


void Game::showWelcome() const {
    cout << "\n======================================================\n";
    cout << "    __________\n";
    cout << "   /\\ ____ /\\      " << title << "\n";
    cout << "  /  \\/  \\/  \\     -----------------\n";
    cout << " /____|_[]_|____\\  A mystery at\n";
    cout << " | [] | | [] | |   " << mansion.getName() << "\n";
    cout << " |____|_/\\_|____|\n";
    cout << "======================================================\n";
    cout << " 1. New Game\n";
    cout << " 2. How to Play\n";
    cout << " 3. Load Game (optional feature)\n";
    cout << " 0. Quit\n";
    cout << "------------------------------------------------------\n";
    cout << "Enter your choice: ";
}

void Game::showHowToPlay() const {
    cout << "\n===================== HOW TO PLAY =====================\n";
    cout << "You have inherited Ashworth Manor. Find out what\n";
    cout << "happened to Eleanor Ashworth.\n";
    cout << "- Type the number of an option and press Enter.\n";
    cout << "- Look around each room and pick up useful items.\n";
    cout << "- Read the items you carry: clues hide in them.\n";
    cout << "- Locked doors need the right key.\n";
    cout << "- Some puzzles make sense only after you find a clue.\n";
    cout << "- Three wrong answers in a row will earn you a hint.\n";
    cout << "- You may leave by the front door at any time,\n";
    cout << "  but the mystery will stay unsolved.\n";
    cout << "=======================================================\n";
    waitForEnter();
}


//Starting a game:
void Game::startNewGame() 
{
    state.reset();     // remove all clues from any earlier game
    mansion.build();   // build a fresh world (also deletes the old one first)

    cout << "\nEnter your name: ";
    string name = readLine();
    if (name.empty()) 
    {
        name = "Traveller";   // sets default name if no input given
    }

    // replaces the old player with a new one standing in the Entrance Hall.
    player = Player(name, mansion.getStartRoom());

    cout << "\n" << name << ", the lawyer called the house \"simply old\".\n";
    cout << "As you step into the hall, the front door swings shut\n";
    cout << "behind you. Somewhere upstairs, a clock that has not\n";
    cout << "ticked in years strikes once.\n\n";
    waitForEnter();

    playGame();
}

// Ending game: (called when the player quits or reached an ending)
void Game::endSession() 
{
    mansion.clear();     // deletes every room, object and item

    player = Player(); //Replaces player with blank to avoid dangling room pointer after deletion

    cout << "\nReturning to the main menu...\n";

    //0 count shows everthing is deleted and no memory leaks
    std::cout << "[Check] Interactable objects still alive: "<< Interactable::getObjectCount() << " (should be 0)"<<endl;
}

// Game loop: (one while loop is one turn)
void Game::playGame() 
{
    bool playing = true;
    bool needToDescribe = true;   // flag to show the room screen when player walks into a room

    while (playing) 
    {
        Room* roomBefore = player.getCurrentRoom();   // remember where we were

        if (needToDescribe) 
        {
            roomBefore->describe();
            needToDescribe = false;
        }

        showRoomMenu();
        int choice = readInt(0, 5);

        if (choice == 1) 
        {
            roomBefore->describe();
        } 
        else if (choice == 2) 
        {
            interactWithObject();
        }
        else if (choice == 3)
        {
            pickUpItem();
        }
        else if (choice == 4)
        {
            player.getInventory().openMenu(state);
        }
        else if (choice == 5)
        {
            showMapAndHelp();
        } 
        else
        {
            if (confirmReturnToMenu()) 
            {
                playing = false;
            }
        }

        // Game ending decided on the final choice (set by doors and the ghost)
        if (state.getFinalChoice() != CHOICE_NONE)
        {
            showEnding();
            playing = false;
        }
        else if (playing && player.getCurrentRoom() != roomBefore) 
        {
            //player is standing in a different room than before the turn,
            //so describe the new room at the start of the next turn.
            needToDescribe = true;
        }
    }

    endSession(); //ends game
}

void Game::showRoomMenu() const {
    std::cout << "-------------------------------------------------------\n";
    std::cout << " 1. Look around\n";
    std::cout << " 2. Interact with an object\n";
    std::cout << " 3. Pick up an item\n";
    std::cout << " 4. Open inventory\n";
    std::cout << " 5. Map and help\n";
    std::cout << " 0. Return to main menu\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << "Choice: ";
}

// What each menu option does:
void Game::interactWithObject() 
{
    Room* room = player.getCurrentRoom();

    if (room->getObjectCount() == 0) 
    {
        cout << "There is nothing to interact with here."<<endl;
        return;
    }

    cout << "What do you want to interact with?"<<endl;
    room->listObjects();
    cout << "  0. Back"<<endl;
    cout << "Choice: ";
    int choice = readInt(0, room->getObjectCount());

    if (choice > 0) 
    {
        // POLYMORPHISM: 
        // the Game class only knows this is an Interactable* it does
        // not know whether it is a Door, a Mirror or a Puzzle. The right
        // interact() is picked when the program runs. 
        Interactable* object = room->getObject(choice - 1);   // array starts at 0
        object->interact(player, state);
    }
}

void Game::pickUpItem() 
{
    Room* room = player.getCurrentRoom();

    if (room->getItemCount() == 0) 
    {
        cout << "There is nothing to pick up here."<<endl;
        return;
    }

    cout << "What do you want to pick up?"<<endl;
    room->listItems();
    cout << "  0. Back"<<endl;
    cout << "Choice: ";
    int choice = readInt(0, room->getItemCount());

    if (choice > 0) 
    {
        Item* item = room->takeItem(choice - 1);   // item pointer removed from the room and added into the inventory
        if (player.getInventory().add(item))   
        {     
            cout << "You picked up: " << item->getName() << endl;
        }
        else
        {
            room->addItem(item);                   // inventory refused it so puts it back
            cout << "You cannot carry that."<<endl;
        }
    }
}

void Game::showMapAndHelp() const
 {
    cout << "\nYou are in: " << player.getCurrentRoom()->getName() << "\n";
    cout << "Doors are listed under \"Objects here\". Use option 2 to use a door.\n";
    cout << "Items you can take are listed under \"Items here\". Use option 3.\n";
    cout << "Read the items you carry through option 4: clues hide in them.\n";
    waitForEnter();
}

// Returns true if the player wants to go back to the main menu.
bool Game::confirmReturnToMenu() const 
{
    cout << "Return to the main menu? Your progress will be lost."<<cout;
    cout << " 1. Yes\n 2. No\nChoice: ";
    int choice= readInt(1, 2);
    return choice == 1;
}

// placeholder for now (four real endings and the summary built later)
void Game::showEnding() const 
{
    cout << "\n=================== THE GAME ENDS ===================\n";
    if (state.getFinalChoice() == CHOICE_RUN) 
    {
        cout << "Ending: Walk Away. You are safe, but the mystery remains unsolved."<<endl;
    } 
    else 
    {
        cout << "(Full ending screens will be added in a later stage.)"<<endl;
    }
    cout << "=====================================================\n";
    waitForEnter();
}