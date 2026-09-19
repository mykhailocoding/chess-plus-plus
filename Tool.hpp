//---------------------------------------------------------------------------------------------------------------------
/// Base class for the tools. Contains constructor with essential members, default copy constructor, default virtual
/// destructor.
//---------------------------------------------------------------------------------------------------------------------
#ifndef TOOL_HPP
#define TOOL_HPP
#include "Item.hpp"

class Tool : public Item
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor with essential parameters.
    /// @param id id of the item
    /// @param name full name of the item
    /// @param display_name character that is actually displayed on the board
    Tool(ItemId id, std::string name, std::string display_name);
    
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    Tool(const Tool& tool) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    virtual ~Tool() override = default;
};

#endif
