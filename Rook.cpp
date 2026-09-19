//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the base Piece class and implements checks for rook-specific movement 
/// and capture rules
//----------------------------------------------------------------------------------------------------------------------

#include "Rook.hpp"
#include "Board.hpp"
#include "Square.hpp"
#include "Conditions.hpp"

Rook::Rook() : Piece(PieceType::Rook, "R", 5, SpecialPowerType::None, "♜r") {}

Rook::Rook(std::string id, SpecialPowerType special_power_type, std::string short_name)
  : Piece(PieceType::Rook, id, 5, special_power_type, short_name) {}

bool Rook::isMoveValid(Board& board, Square* target_square)
{
  if(target_square->getPiece() != nullptr && (*(target_square->getPiece()->getOwner()) == this->getOwner()
    || !target_square->getPiece()->canBeCaptured(PieceType::Rook)))
  {
    return false;
  }

  int source_row = static_cast<int>(coordinates_.getRank()) - 1;
  int source_column = static_cast<int>(coordinates_.getFile()) - 'A';

  int target_row = static_cast<int>(target_square->getCoordinates().getRank()) - 1;
  int target_column = static_cast<int>(target_square->getCoordinates().getFile()) - 'A';

  int row_difference = std::abs(target_row - source_row);
  int column_difference = std::abs(target_column - source_column);

  if(row_difference == 0 && column_difference == 0)
  {
    return false;
  }

  if(row_difference != 0 && column_difference != 0)
  {
    return false;
  }

  if(Conditions::isPathClear(board, board.getSquare(source_row, source_column), target_square) != true)
  {
    return false;
  }
  return true;
}
