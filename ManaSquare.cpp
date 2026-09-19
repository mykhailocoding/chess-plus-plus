//---------------------------------------------------------------------------------------------------------------------
/// Implements mana square. Gives mana to the player if their piece is on the square.
//---------------------------------------------------------------------------------------------------------------------
#include "ManaSquare.hpp"
#include "Coordinates.hpp"
#include "Piece.hpp"

ManaSquare::ManaSquare(Coordinates coordinates): Square(SquareType::MANA_SQUARE, coordinates){}

void ManaSquare::setPiece(std::unique_ptr<Piece> piece)
{
  piece_ = std::move(piece);
  if (piece_->getOwner() != nullptr) // only if pieces has an owner already
  {
    piece_->getOwner()->addMana(1);
  }
}
