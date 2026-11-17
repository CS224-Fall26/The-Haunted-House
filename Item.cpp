
#include "Item.hpp"

#include <iostream>
#include "GameState.hpp"

// Default constructor
Item::Item()
    : name("Unknown item"),
      description("Nothing special."),
      text(""),
      clueFlag("")
{
}

// Parameterized constructor
Item::Item(const std::string& name, const std::string& description,
           const std::string& text, const std::string& clueFlag)
    : name(name),
      description(description),
      text(text),
      clueFlag(clueFlag)
{
}

// Getters
const std::string& Item::getName() const
{
    return name;
}

const std::string& Item::getDescription() const
{
    return description;
}

const std::string& Item::getText() const
{
    return text;
}

const std::string& Item::getClueFlag() const
{
    return clueFlag;
}

// Displays the item text and records its clue if it is new.
void Item::read(GameState& state) const
{
    if (text == "")
    {
        std::cout << "There is nothing to read on " << name << ".\n";
    }
    else
    {
        std::cout << text << "\n";
    }

    if (clueFlag != "" && !state.hasFlag(clueFlag))
    {
        state.setFlag(clueFlag);
        std::cout << "[New clue recorded: " << name << "]\n";
    }
}

// Compares two items by name.
bool Item::operator==(const Item& other) const
{
    return name == other.name;
}

// Prints the item's name and description.
std::ostream& operator<<(std::ostream& out, const Item& item)
{
    out << item.name << " - " << item.description;
    return out;
}
