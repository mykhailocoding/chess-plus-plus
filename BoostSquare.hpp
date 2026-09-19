//---------------------------------------------------------------------------------------------------------------------
/// Implements boost square. Gives additional turn to the current player.
//---------------------------------------------------------------------------------------------------------------------
#ifndef BOOST_SQUARE_HPP
#define BOOST_SQUARE_HPP
#include "Square.hpp"
#include "Coordinates.hpp"
#include "Game.hpp"

class BoostSquare : public Square
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor.
    /// @param coordinates coordinates of the square
    BoostSquare(Coordinates coordinates);
    
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor. Calls the copy constructor of the base class.
    /// @param square square to copy
    BoostSquare(const BoostSquare& square) : Square(square) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~BoostSquare() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Allows to execute additional move.
    /// @param game pointer to the game object
    void additionalTurn(Game &game);
};

#endif
