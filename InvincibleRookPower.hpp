//---------------------------------------------------------------------------------------------------------------------
/// Invincible rook's special power. Makes the rook invincible for a specified number of turns not including the
/// current one.
//---------------------------------------------------------------------------------------------------------------------
#ifndef INVINCIBLE_ROOK_POWER_HPP
#define INVINCIBLE_ROOK_POWER_HPP
#include "ActivePower.hpp"

class Game;

class InvincibleRookPower : public ActivePower
{
  protected:
    std::size_t turn_count_;
    Coordinates square_;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 2;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor.
    InvincibleRookPower();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    InvincibleRookPower(const InvincibleRookPower& power) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~InvincibleRookPower() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Main method of the class. Executes the special power.
    /// @param game pointer to the game object
    /// @param user_input_special struct with the necessary information from user
    void usePower(Game* game, UserInputSpecial& user_input_special) override;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Identifies amount of mana needed for the power.
    /// @return amount of required mana
    std::size_t distinguishManaCost() override;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets the information from the struct and sets it to the internal variables of the class.
    /// @param user_input_special struct the information is taken from
    void setContext(UserInputSpecial& user_input_special);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks that the turn cound is bigger than zero.
    /// @return false if that is the case, true otherwise
    bool wrongTurnCount();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the special power requires.
    /// @return number of the required parameters
    std::size_t getNumberExpectedParameters() override
    {
      return NUMBER_EXPECTED_PARAMETERS_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Validates the parameters required for the power.
    /// @param parameters vector with parameters as strings
    /// @param user_input_special struct where the parameters will be saved after validation
    /// @param error_messages map of the error messages
    void checkParameters(std::vector<std::string> parameters, UserInputSpecial& user_input_special,
      std::map<ErrorType, std::string>& error_messages) override;
};

#endif
