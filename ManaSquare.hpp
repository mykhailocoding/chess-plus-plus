//---------------------------------------------------------------------------------------------------------------------
/// Implements mana square. Gives mana to the player if their piece is on the square.
//---------------------------------------------------------------------------------------------------------------------
#ifndef MANA_SQUARE_HPP
#define MANA_SQUARE_HPP
#include "Square.hpp"
#include "Coordinates.hpp"

class ManaSquare: public Square
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor.
    /// @param coordinates coordinates of the square
    ManaSquare (Coordinates coordinates);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor. Calls the copy constructor of the base class.
    /// @param square square to copy
    ManaSquare(const ManaSquare& square) : Square(square) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~ManaSquare() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Sets the piece on the square and adds mana to the owner.
    /// @param piece piece to set
    void setPiece(std::unique_ptr<Piece> piece) override;
};

#endif 
