//---------------------------------------------------------------------------------------------------------------------
/// Painter rook's special power. Validates target square, moves the rook there, identifies all squares on the path
/// including the starting one, changes their type to the basic square with accoriding earlier identified color.
//---------------------------------------------------------------------------------------------------------------------
#ifndef PAINTER_ROOK_POWER_HPP
#define PAINTER_ROOK_POWER_HPP
#include "ActivePower.hpp"
#include "Square.hpp"
#include <vector>

class Game;

class PainterRookPower : public ActivePower
{
  protected:
    Coordinates square_;
    Coordinates target_square_;
    SquareType square_type_new_;
    std::vector<Coordinates> squares_to_paint_;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 2;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor.
    PainterRookPower();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    PainterRookPower(const PainterRookPower& power) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~PainterRookPower() override = default;

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
    /// @brief Identifies a new color for the squares and initialises respective variable.
    /// @param game pointer to the game object
    void identifyColor(Game* game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Identifies squares that are on the path including the starting one, pushes their coordinates to the
    /// vector.
    void identifySquaresToPaint();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Changes the type of the collected squares to the basic one with appropriate color.
    /// @param game pointer to the game object
    void paintSquares(Game* game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the special power requires.
    /// @return number of the required parameters
    std::size_t getNumberExpectedParameters() override
    {
      return NUMBER_EXPECTED_PARAMETERS_;
    }
};

#endif
