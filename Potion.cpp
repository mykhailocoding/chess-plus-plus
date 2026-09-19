//---------------------------------------------------------------------------------------------------------------------
/// Base class for the potions. Contains constructor with essential members, default copy constructor, default virtual
/// destructor and pure virtual methods.
//---------------------------------------------------------------------------------------------------------------------
#include "Potion.hpp"

Potion::Potion(ItemId id, std::string name, std::string display_name) : Item(id, name, display_name) {}
