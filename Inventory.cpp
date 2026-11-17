
#include "Inventory.hpp"

#include <iostream>
#include "Item.hpp"
#include "GameState.hpp"
#include "InputUtils.hpp"

Inventory::Inventory()
    : items(),
      capacity(20)
{
}

// Creates an inventory with a custom capacity.
Inventory::Inventory(int capacity)
    : items(),
      capacity(capacity)
{
}

bool Inventory::add(Item* item)
{
    // Reject invalid items.
    if (item == nullptr)
    {
        return false;
    }

    // Prevent the player from carrying duplicate items.
    if (hasItem(item->getName()))
    {
        return false;
    }

    // Check whether the inventory has reached its capacity.
    if ((int)items.size() >= capacity)
    {
        return false;
    }

    // Store the pointer, not a copy of the Item object.
    items.push_back(item);
    return true;
}

// Overload 1: checks whether an item with this name exists.
bool Inventory::hasItem(const std::string& name) const
{
    for (int i = 0; i < (int)items.size(); i++)
    {
        if (items[i]->getName() == name)
        {
            return true;
        }
    }

    return false;
}

// Overload 2: compares Item objects using Item's operator==.
bool Inventory::hasItem(const Item& item) const
{
    for (int i = 0; i < (int)items.size(); i++)
    {
        // items[i] is a pointer, so *items[i] accesses the actual Item.
        if (*items[i] == item)
        {
            return true;
        }
    }

    return false;
}

// Returns the number of items currently stored.
int Inventory::getCount() const
{
    return (int)items.size();
}

// Allows access to an item using its position in the inventory.
Item* Inventory::operator[](int index) const
{
    // Check the index to avoid accessing an invalid position.
    if (index < 0 || index >= (int)items.size())
    {
        return nullptr;
    }

    return items[index];
}

void Inventory::openMenu(GameState& state) const
{
    if (items.empty())
    {
        std::cout << "Your inventory is empty.\n";
        return;
    }

    while (true)
    {
        std::cout << "=== INVENTORY (" << items.size() << " items) ===\n";

        for (int i = 0; i < (int)items.size(); i++)
        {
            // Uses Item's operator<< to display its name and description.
            std::cout << "   " << (i + 1) << ". " << *items[i] << "\n";
        }

        std::cout << "   0. Back\n";
        std::cout << "Read which item? ";

        // Menu choices start at 1, while vector indexes start at 0.
        int choice = readInt(0, (int)items.size());

        if (choice == 0)
        {
            return;
        }

        // Read the selected item and update GameState if it contains a new clue.
        items[choice - 1]->read(state);

        waitForEnter();
    }
}
