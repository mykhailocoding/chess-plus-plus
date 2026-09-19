//---------------------------------------------------------------------------------------------------------------------
/// Jumpy queen's special power. Validates target square, identifies if the command is move or capture, executes the
/// command.
//---------------------------------------------------------------------------------------------------------------------
#ifndef JUMPY_QUEEN_POWER_HPP
#define JUMPY_QUEEN_POWER_HPP
#include "ActivePower.hpp"

class Game;

class JumpyQueenPower : public ActivePower
{
  protected:
    Coordinates square_;
    Coordinates target_square_;
    static constexpr std::size_t MANA_COST_ = 2;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 2;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor.
    JumpyQueenPower();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    JumpyQueenPower(const JumpyQueenPower& power) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~JumpyQueenPower() override = default;

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
    /// @brief Identifies if it is a capture or a simple move, checks that it is possible to execute, initialises
    /// according variables
    /// @param game pointer to the game object
    /// @param capture tells if it is a capture command
    /// @param move tells if it is a move command
    /// @return true if it is possible to execute either move or capture, false otherwise
    bool validateCaptureAndMove(Game* game, bool& capture, bool& move);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks that the target square is a valid knight move(from source square).
    /// @return true if that is the case, false otherwise
    bool validKnightJump();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Executes the knight like move.
    /// @param square source square
    /// @param target_square target square
    void QueenKnightMove(Square* square, Square* target_square);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Executes the knight like move and captures the piece on the target square/
    /// @param game pointer to the game object
    /// @param square source square
    /// @param target_square target square
    void QueenKnightCapture(Game* game, Square* square, Square* target_square);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the special power requires.
    /// @return number of the required parameters
    std::size_t getNumberExpectedParameters() override
    {
      return NUMBER_EXPECTED_PARAMETERS_;
    }
};

#endif
