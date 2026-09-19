//---------------------------------------------------------------------------------------------------------------------
/// Base class for the special powers. It includes two constructors: with mana cost and without, virtual
/// destructor, and a default copy constructor. It contains several essential (pure) virtual functions that are used 
/// in the subclasses, as well as getter and setter.
//---------------------------------------------------------------------------------------------------------------------
#ifndef ACTIVE_POWER_HPP
#define ACTIVE_POWER_HPP
#include <cstddef>//size_t
#include "Coordinates.hpp"
#include "SpecialCommand.hpp"

class Game;

class ActivePower
{
  protected:
    std::size_t mana_cost_;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructs an active power with default mana cost.
    ActivePower() : mana_cost_(0) {};

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructs an active power with a specified mana cost.
    /// @param mana_cost The initial mana cost value.
    ActivePower(std::size_t mana_cost);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    ActivePower(const ActivePower& other) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    virtual ~ActivePower() = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Main method of the class. Executes the special power.
    /// @param game pointer to the game object
    /// @param user_input_special struct with the necessary information from user
    virtual void usePower(Game* game, UserInputSpecial& user_input_special) = 0;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Identifies amount of mana needed for the power.
    /// @return amount of required mana
    virtual std::size_t distinguishManaCost() = 0;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Sets mana.
    /// @param amount amount of mana
    void setMana(std::size_t amount);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns mana cost of the power.
    /// @return mana cost of the power
    std::size_t getManaCost() const;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks that player has enough mana to execute the special power.
    /// @param player_mana current amount of the player's mana
    /// @return true if there is enough mana, false if not
    virtual bool validateMana(std::size_t player_mana);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the special power requires.
    /// @return number of the required parameters
    virtual std::size_t getNumberExpectedParameters() = 0;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Validates the parameters required for the power.
    /// @param parameters vector with parameters as strings
    /// @param user_input_special struct where the parameters will be saved after validation
    /// @param error_messages map of the error messages
    virtual void checkParameters(std::vector<std::string> parameters, UserInputSpecial& user_input_special,
      std::map<ErrorType, std::string>& error_messages);
};

#endif
