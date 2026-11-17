
#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <string>
#include <vector>

// Forward declarations: Inventory only needs pointers and references here.
class Item;
class GameState;

class Inventory
{
public:
    Inventory(); // Creates an inventory with a default capacity of 20.
    explicit Inventory(int capacity);

    // Adds an item if it is valid, not already carried, and space is available.
    bool add(Item* item);

    // Function overloading: search for an item by its name or by an Item object.
    bool hasItem(const std::string& name) const;
    bool hasItem(const Item& item) const;

    int getCount() const;

    // Operator overloading: allows us to access items using inventory[index].
    // Returns nullptr if the index is outside the valid range.
    Item* operator[](int index) const;

    // Displays the inventory menu and lets the player read an item.
    void openMenu(GameState& state) const;

private:
    // Stores pointers to Items. Inventory does not own or delete these objects.
    std::vector<Item*> items;

    int capacity; // Maximum number of items the player can carry.
};

#endif
