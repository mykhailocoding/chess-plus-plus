//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the base Piece class and implements checks for knight-specific movement 
/// and capture rules
//----------------------------------------------------------------------------------------------------------------------


#include "Knight.hpp"
#include "Board.hpp"
#include "Square.hpp"


Knight::Knight() : Piece(PieceType::Knight, "N", 3, SpecialPowerType::None, "♞n") {}

Knight::Knight(std::string id, SpecialPowerType special_power_type, std::string short_name)
  : Piece(PieceType::Knight, id, 3, special_power_type, short_name) {}

bool Knight::isMoveValid([[maybe_unused]] Board& board, Square* target_square)
{
  Piece* target_piece = target_square->getPiece();
  if(target_piece != nullptr &&
    (*(target_piece->getOwner()) == this->getOwner() || !target_piece->canBeCaptured(PieceType::Knight)))
  {
    return false;
  }
  int source_row = static_cast<int>(coordinates_.getRank()) - 1;
  int source_column = static_cast<int>(coordinates_.getFile()) - 'A';

  int target_row = static_cast<int>(target_square->getCoordinates().getRank()) - 1;
  int target_column = static_cast<int>(target_square->getCoordinates().getFile()) - 'A';

  int row_difference = std::abs(target_row - source_row);
  int column_difference = std::abs(target_column - source_column);
  
  return (column_difference == 1 && row_difference == 2) || 
         (column_difference == 2 && row_difference == 1);
}
