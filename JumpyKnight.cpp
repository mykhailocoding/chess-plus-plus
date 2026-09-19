//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Knight class and checks JumpyKnight-specific movement 
/// and capture rules.
//----------------------------------------------------------------------------------------------------------------------


#include "JumpyKnight.hpp"
#include "Square.hpp"

JumpyKnight::JumpyKnight() : Knight("NJMP", SpecialPowerType::Passive, "♞nj") {}

bool JumpyKnight::isMoveValid([[maybe_unused]] Board& board, Square* target_square)
{
  Piece* target_piece = target_square->getPiece();
  if(target_piece != nullptr &&
    (target_piece->getOwner() == this->getOwner() || !target_piece->canBeCaptured(PieceType::King)))
  {
    return false;
  }
  int source_row = static_cast<int>(coordinates_.getRank() );
  int source_column = static_cast<int>(coordinates_.getFile());
  int target_row = static_cast<int>(target_square->getCoordinates().getRank());
  int target_column = static_cast<int>(target_square->getCoordinates().getFile());

  int row_difference = std::abs(target_row - source_row);
  int column_difference = std::abs(target_column - source_column);
  
  return (column_difference == 2 && row_difference == 3) || 
         (column_difference == 3 && row_difference == 2);
}
