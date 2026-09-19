//---------------------------------------------------------------------------------------------------------------------
/// Stubborn pawn's special power. Validates the target square, captures the piece direct infront of the stubborn pawn.
//---------------------------------------------------------------------------------------------------------------------
#ifndef STUBBORN_PAWN_POWER_HPP
#define STUBBORN_PAWN_POWER_HPP
#include "ActivePower.hpp"

class Game;
struct UserInputSpecial;

class StubbornPawnPower : public ActivePower
{
  protected:
    Coordinates square_;
    Coordinates target_square_;
    char piece_color_;
    static constexpr std::size_t MANA_COST_ = 5;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 1;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor.
    StubbornPawnPower();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    StubbornPawnPower(const StubbornPawnPower& power) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~StubbornPawnPower() override = default;

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
    /// @param game pointer to the game object
    /// @param user_input_special struct the information is taken from
    void setContext(Game* game, UserInputSpecial& user_input_special);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks the target square.
    /// @param game pointer to the game object
    /// @param target_square target square
    /// @return false if the target square is correct, true otherwise
    bool wrongTargetSquare(Game* game, Square* target_square);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the special power requires.
    /// @return number of the required parameters
    std::size_t getNumberExpectedParameters() override
    {
      return NUMBER_EXPECTED_PARAMETERS_;
    }
};

#endif
