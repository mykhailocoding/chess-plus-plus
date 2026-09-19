//---------------------------------------------------------------------------------------------------------------------
/// Base class for the items. Contains constructor with essential members, default copy constructor, default virtual
/// destructor and getters.
//---------------------------------------------------------------------------------------------------------------------
#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>
#include <map>
#include <memory>
#include <functional>
#include "Coordinates.hpp"

class Game;
struct UserInputUse;

enum class ItemId
{
  FREEZE,
  TP,
  EVENODD,
  LUKE,
  SHIELD,
  CLOAK,
  REPEL
};

enum class Parity
{
  NONE,
  EVEN,
  ODD
};

class Item
{
  protected:
    ItemId id_;
    std::string name_;
    std::string display_name_;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor with essential parameters.
    /// @param id id of the item
    /// @param name full name of the item
    /// @param display_name character that is actually displayed on the board
    Item(ItemId id, std::string name, std::string display_name);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    Item(const Item& item) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    virtual ~Item() = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Getter for the item's id.
    /// @return id of the item
    ItemId getId() const
    {
      return id_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Getter for the item's name.
    /// @return name of the item
    std::string getName() const
    {
      return name_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Getter for the item's display name.
    /// @return display name of the item
    std::string getDisplayName() const
    {
      return display_name_;
    }
};

#endif
