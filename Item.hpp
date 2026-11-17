#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <ostream>

class GameState; // Forward declaration

class Item{
public:
    Item();

    Item(const std::string& name, const std::string& description,
         const std::string& text, const std::string& clueFlag);

    // Getters
    const std::string& getName() const;
    const std::string& getDescription() const;
    const std::string& getText() const;
    const std::string& getClueFlag() const;

    // Reads the item and records its clue in GameState.
    void read(GameState& state) const;

    // Compares items by name and prints item details.
    bool operator==(const Item& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Item& item);

private:
    std::string name;
    std::string description;
    std::string text;
    std::string clueFlag;
};

#endif
