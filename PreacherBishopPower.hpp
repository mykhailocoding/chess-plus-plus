//---------------------------------------------------------------------------------------------------------------------
/// Preacher bishop's special power. Validates that the bishop can capture opponent's piece on the target square,
/// changes the owner of the targeted piece to the current player.
//---------------------------------------------------------------------------------------------------------------------
#ifndef PREACHER_BISHOP_POWER_HPP
#define PREACHER_BISHOP_POWER_HPP
#include "ActivePower.hpp"

class Game;

class PreacherBishopPower : public ActivePower
{
  protected:
    Coordinates square_;
    Coordinates target_square_;
    std::size_t targeted_piece_value_;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 2;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor.
    PreacherBishopPower();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    PreacherBishopPower(const PreacherBishopPower& power) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~PreacherBishopPower() override = default;

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
    /// @brief Returns number of parameters that the special power requires.
    /// @return number of the required parameters
    std::size_t getNumberExpectedParameters() override
    {
      return NUMBER_EXPECTED_PARAMETERS_;
    }
};

#endif
