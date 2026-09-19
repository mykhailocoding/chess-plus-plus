//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Queen class and checks HungryQueen-specific movement 
/// and capture rules.
//----------------------------------------------------------------------------------------------------------------------


#include "HungryQueen.hpp"
#include "Square.hpp"
#include "Conditions.hpp"

HungryQueen::HungryQueen() : Queen("QHNGR", SpecialPowerType::Passive, "♛qh") {}

bool HungryQueen::isMoveValid(Board& board, Square* target_square)
{
  Piece* target_piece = target_square->getPiece();
  if(target_piece != nullptr && ((target_piece->getOwner() == this->getOwner() && target_piece->getId() == "K")
    || !target_piece->canBeCaptured(PieceType::Queen)))
  {
    return false;
  }
  int source_row = static_cast<int>(coordinates_.getRank()) -1;
  int source_column = static_cast<int>(coordinates_.getFile()) - 'A';

  int target_row = static_cast<int>(target_square->getCoordinates().getRank()) -1;
  int target_column = static_cast<int>(target_square->getCoordinates().getFile()) -'A';

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
   
  if(Conditions::isPathClear(board, board.getSquare(source_row , source_column ), target_square) != true)
  {
    return false;
  }
  return true;
}
  