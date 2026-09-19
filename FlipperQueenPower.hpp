//---------------------------------------------------------------------------------------------------------------------
/// Flipper queen's special power. Validates bounce and target squares, validates path to the target square, moves the
/// queen there/captures the piece on the target square.
//---------------------------------------------------------------------------------------------------------------------
#ifndef FLIPPER_QUEEN_POWER_HPP
#define FLIPPER_QUEEN_POWER_HPP
#include "ActivePower.hpp"

class Game;

class FlipperQueenPower : public ActivePower
{
  protected:
    Coordinates square_;
    Coordinates target_square_;
    Coordinates bounce_square_;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 3;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor.
    FlipperQueenPower();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor.
    FlipperQueenPower(const FlipperQueenPower& power);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~FlipperQueenPower() override = default;

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
    /// @brief Validates bounce square.
    /// @return true if the square is incorrect, false if it is correct
    bool wrongBounceSquare();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Validates target square.
    /// @return true if the square is incorrect, false if it is correct
    bool wrongTargetSquare();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Identifies if it is a capture or a simple move, checks that it is possible to execute, initialises
    /// according variables.
    /// @param game pointer to the game object
    /// @param capture tells if it is a capture command
    /// @param move tells if it is a move command
    /// @return true if it is possible to execute either move or capture, false otherwise
    bool validateCaptureAndMove(Game* game, bool& capture, bool& move);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Validates path to the bounce square and then to the target square, executes move/capture.
    /// @param game pointer to the game object
    /// @param not_enough_mana tells if player does not have enough mana to execute the power
    /// @param capture tells if it is a capture command
    /// @param move tells if it is a move command
    void bounceExecution(Game* game, bool not_enough_mana, bool capture, bool move);

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
