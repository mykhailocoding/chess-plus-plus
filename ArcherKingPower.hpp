//---------------------------------------------------------------------------------------------------------------------
/// Archer king's special power. Validates path of the arrow, freezes the target piece.
//---------------------------------------------------------------------------------------------------------------------
#ifndef ARCHER_KING_POWER_HPP
#define ARCHER_KING_POWER_HPP
#include "ActivePower.hpp"

class Game;

class ArcherKingPower : public ActivePower
{
  protected:
    Coordinates square_;
    Coordinates target_square_;
    static constexpr std::size_t FROZEN_FOR_ = 2;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 2;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor.
    ArcherKingPower();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    ArcherKingPower(const ArcherKingPower& power) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~ArcherKingPower() override = default;

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
    /// @brief Validates the trajectory of the arrow.
    /// @param game pointer to the current game state
    /// @return true if the path is clear, false otherwise
    bool validateFlightWay(Game* game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the special power requires.
    /// @return number of the required parameters
    std::size_t getNumberExpectedParameters() override
    {
      return NUMBER_EXPECTED_PARAMETERS_;
    }
};

#endif
