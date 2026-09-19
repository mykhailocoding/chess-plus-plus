//---------------------------------------------------------------------------------------------------------------------
/// Explosive pawn's special power. Checks that the target square is correct, captures the piece on the on the target 
/// square, identifies neighboring pieces that are not pawns, blows them up!
//---------------------------------------------------------------------------------------------------------------------
#ifndef EXPLOSIVE_PAWN_POWER_HPP
#define EXPLOSIVE_PAWN_POWER_HPP
#include "ActivePower.hpp"

class Game;
struct UserInputSpecial;

class ExplosivePawnPower : public ActivePower
{
  protected:
    Coordinates pawn_square_;//where the pawn initially stands
    Coordinates target_square_;
    static constexpr std::size_t MANA_COST_ = 3;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 2;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor.
    ExplosivePawnPower();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor.
    ExplosivePawnPower(const ExplosivePawnPower& power);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~ExplosivePawnPower() override = default;

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
    /// @brief Checks that the target square is a valid pawn capture square.
    /// @param game pointer to the game object
    /// @return true if that is the case, false otherwise
    bool wrongTargetSquare(Game* game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the special power requires.
    /// @return number of the required parameters
    std::size_t getNumberExpectedParameters() override
    {
      return NUMBER_EXPECTED_PARAMETERS_;
    }
};

#endif
