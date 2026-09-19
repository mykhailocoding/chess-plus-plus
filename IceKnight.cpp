//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Knight class and excecutes IceKnight-specific movement 
/// and capture rules.
//----------------------------------------------------------------------------------------------------------------------


#include "IceKnight.hpp"
#include "Square.hpp"

IceKnight::IceKnight() : Knight("NICE", SpecialPowerType::Passive, "♞ni") {}

void IceKnight::move(Game& game, bool is_capture, Square *target_square , [[maybe_unused]] std::optional<char> promote_to)
{
  int source_row = static_cast<int>(coordinates_.getRank()) - 1;
  int source_column = static_cast<int>(coordinates_.getFile()) - 'A';

  int target_row = static_cast<int>(target_square->getCoordinates().getRank()) - 1;
  int target_column = static_cast<int>(target_square->getCoordinates().getFile()) - 'A';

  int row_difference = target_row - source_row;
  int column_difference = target_column - source_column;

  // setFrozen(2) because we are not counting the turn the piece became frozen
  
  if (row_difference == 2)
  {
    if (game.getBoard().getSquare(source_row + 1, source_column)->hasPiece())
    {
      game.getBoard().getSquare(source_row + 1, source_column)->getPiece()->setFrozen(2);
    }
    if (game.getBoard().getSquare(source_row + 2, source_column)->hasPiece())
    {
      game.getBoard().getSquare(source_row + 2, source_column)->getPiece()->setFrozen(2);
    }
  }
  else if (row_difference == -2)
  {
    if (game.getBoard().getSquare(source_row - 1, source_column)->hasPiece())
    {
      game.getBoard().getSquare(source_row - 1, source_column)->getPiece()->setFrozen(2);
    }
    if (game.getBoard().getSquare(source_row - 2, source_column)->hasPiece())
    {
      game.getBoard().getSquare(source_row - 2, source_column)->getPiece()->setFrozen(2);
    }
  }
  else if (column_difference == 2)
  {
    if (game.getBoard().getSquare(source_row, source_column + 1)->hasPiece())
    {
      game.getBoard().getSquare(source_row, source_column + 1)->getPiece()->setFrozen(2);
    }
    if (game.getBoard().getSquare(source_row, source_column + 2)->hasPiece())
    {
      game.getBoard().getSquare(source_row, source_column + 2)->getPiece()->setFrozen(2);
    }
  }
  else if (column_difference == -2)
  {
    if (game.getBoard().getSquare(source_row, source_column - 1)->hasPiece())
    {
      game.getBoard().getSquare(source_row, source_column - 1)->getPiece()->setFrozen(2);
    }
    if (game.getBoard().getSquare(source_row, source_column - 2)->hasPiece())
    {
      game.getBoard().getSquare(source_row, source_column - 2)->getPiece()->setFrozen(2);
    }
  }

  if (is_capture)
  {
    game.getCurrentPlayer()->addPieceToPrison(target_square->releasePiece());
  }

  auto current_piece = game.getBoard().getSquare(coordinates_)->releasePiece();
  coordinates_ = target_square->getCoordinates();
  first_move_ = false;
  game.getBoard().getSquare(target_row, target_column)->setPiece(std::move(current_piece));
}
