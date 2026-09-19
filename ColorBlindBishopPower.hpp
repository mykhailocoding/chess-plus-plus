//---------------------------------------------------------------------------------------------------------------------
/// Color blind bishop's special power. Checks that the target square is adjacent, moves the bishop and if target
/// square has piece captures it, identifies and sets new movement color.
//---------------------------------------------------------------------------------------------------------------------
#ifndef COLOR_BLIND_BISHOP_POWER_HPP
#define COLOR_BLIND_BISHOP_POWER_HPP
#include "ActivePower.hpp"

class Game;
class ColorBlindBishop;
enum class MovementColor;

class ColorBlindBishopPower : public ActivePower
{
  protected:
    Coordinates square_;
    Coordinates target_square_;
    ColorBlindBishop* owner_;
    static constexpr std::size_t MANA_COST_ = 3;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 2;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor.
    ColorBlindBishopPower(ColorBlindBishop* owner);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor.
    ColorBlindBishopPower(const ColorBlindBishopPower& power);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~ColorBlindBishopPower() override = default;

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
    /// @brief Checks that the target square is adjacent to the source square.
    /// @return true if that is the case, false otherwise
    bool isAdjacent();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Identifies new movement color of the bishop.
    /// @param game pointer to the game object
    /// @return new movement color of the bishop
    MovementColor identifyMovementColor(Game* game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the special power requires.
    /// @return number of the required parameters
    std::size_t getNumberExpectedParameters() override
    {
      return NUMBER_EXPECTED_PARAMETERS_;
    }
};

#endif
