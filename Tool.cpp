//---------------------------------------------------------------------------------------------------------------------
/// Base class for the tools. Contains constructor with essential members, default copy constructor, default virtual
/// destructor.
//---------------------------------------------------------------------------------------------------------------------
#include "Tool.hpp"

Tool::Tool(ItemId id, std::string name, std::string display_name) : Item(id, name, display_name) {}
