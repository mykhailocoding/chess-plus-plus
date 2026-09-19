//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the base Piece class and implements checks for queen-specific movement 
/// and capture rules
//----------------------------------------------------------------------------------------------------------------------

#include "Queen.hpp"
#include "Board.hpp"
#include "Square.hpp"
#include "Conditions.hpp"

Queen::Queen() : Piece(PieceType::Queen, "Q", 9, SpecialPowerType::None, "♛q") {}

Queen::Queen(std::string id, SpecialPowerType special_power_type, std::string short_name)
  : Piece(PieceType::Queen, id, 9, special_power_type, short_name) {}

bool Queen::isMoveValid(Board& board, Square* target_square)
{
  if(target_square->getPiece() != nullptr && (*(target_square->getPiece()->getOwner()) == this->getOwner()
    || !target_square->getPiece()->canBeCaptured(PieceType::Queen)))
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

  if(!(row_difference == 0 || column_difference == 0 || row_difference == column_difference))
  {
    return false;
  }
   
  if(Conditions::isPathClear(board, board.getSquare(source_row, source_column), target_square) != true)
  {
    return false;
  }
  return true;
}
