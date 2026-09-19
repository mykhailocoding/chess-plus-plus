//---------------------------------------------------------------------------------------------------------------------
/// Base class for the items. Contains constructor with essential members, default copy constructor, default virtual
/// destructor and getters.
//---------------------------------------------------------------------------------------------------------------------
#include "Item.hpp"
#include "Game.hpp"
#include "UseCommand.hpp"

Item::Item(ItemId id, std::string name, std::string display_name) :
  id_(id), name_(name), display_name_(display_name) {}
