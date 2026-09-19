//---------------------------------------------------------------------------------------------------------------------
/// Base class for the potions. Contains constructor with essential members, default copy constructor, default virtual
/// destructor and pure virtual methods.
//---------------------------------------------------------------------------------------------------------------------
#ifndef POTION_HPP
#define POTION_HPP
#include "Item.hpp"

class Potion : public Item
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor with essential parameters.
    /// @param id id of the item
    /// @param name full name of the item
    /// @param display_name character that is actually displayed on the board
    Potion(ItemId id, std::string name, std::string display_name);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    Potion(const Potion& potion) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    virtual ~Potion() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Validates the parameters required to use the potion.
    /// @param parameters vector of the string where the parameters are
    /// @param user_input_use struct where the parameters will be stored after validation
    /// @return true if the parameters are correct, false otherwise
    virtual bool validParameters(std::vector<std::string> parameters, UserInputUse& user_input_use) = 0;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Main method of the class. Executes the effects of the potion.
    /// @param game pointer to the game object
    /// @param input struct where the user intput is stored
    virtual void usePotion(Game* game, UserInputUse& input) = 0;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the potion requires.
    /// @return number of the required parameters
    virtual std::size_t getNumberExpectedParameters() = 0;
};

#endif
