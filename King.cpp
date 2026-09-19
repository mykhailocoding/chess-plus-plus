//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the base Piece class and implements checks for king-specific movement
/// and capture rules
//----------------------------------------------------------------------------------------------------------------------

#include "King.hpp"
#include "Board.hpp"
#include "Square.hpp"
#include "Conditions.hpp"

King::King() : Piece(PieceType::King, "K", 0, SpecialPowerType::None, "♚k") {}

King::King(std::string id, SpecialPowerType special_power_type, std::string short_name)
    : Piece(PieceType::King, id, 0, special_power_type, short_name) {}

bool King::isMoveValid(Board &board, Square *target_square)
{
  int source_row = static_cast<int>(coordinates_.getRank()) - 1;
  int source_column = static_cast<int>(coordinates_.getFile()) - 'A';
  int target_row = static_cast<int>(target_square->getCoordinates().getRank()) - 1;
  int target_column = static_cast<int>(target_square->getCoordinates().getFile()) - 'A';
  int row_difference = std::abs(target_row - source_row);
  int column_difference = std::abs(target_column - source_column);

  if (target_square->getPiece() != nullptr && (*(target_square->getPiece()->getOwner()) == this->getOwner() ||
      !target_square->getPiece()->canBeCaptured(PieceType::King)))
  {
    // caslting move to a square where a rook is standing
    if (!(row_difference == 0 && column_difference == 2) || target_square->getPiece()->getType() != PieceType::Rook)
    {
      return false;
    }
  }
  // king does not move
  if (row_difference == 0 && column_difference == 0)
  {
    return false;
  }
  /// king moves exaclty one square
  if (row_difference <= 1 && column_difference <= 1)
  {
    return true;
  }
  // entered move was a castling move
  if (row_difference == 0 && column_difference == 2)
  {
    if (first_move_ == false)
    {
      return false;
    }
    Square *kings_square = board.getSquare(source_row, source_column);
    if (Conditions::checkIsSquareUnderAttack(board, kings_square) == true)
    {
      return false;
    }
    return checkCastlingConditions(board, source_row, source_column, target_column);
  }
  return false;
}

bool King::checkCastlingConditions(Board &board, int source_row, int source_column, int target_column)
{
  int direction;
  if (target_column > source_column)
  {
    direction = 1;
  }
  else
  {
    direction = -1;
  }
  // are the squares between rook and king empty
  Square *pass_through_square = board.getSquare(source_row, (source_column + direction));
  if (Conditions::isEmptySquareUnderAttack(board, pass_through_square, this->getOwner()) == true)
  {
    return false;
  }
  // search for the rook to castle with
  Square *square_of_rook = nullptr;
  int rook_column = -1;
  
  for (int current_column = source_column + direction;
    current_column >= 0 && current_column < 8; current_column += direction)
  {
    Square *current_square = board.getSquare(source_row, current_column);
    Piece *current_piece = current_square->getPiece();
    if (current_piece != nullptr)
    {
      if (current_piece->getType() == PieceType::Rook && current_piece->getOwner() == this->getOwner())
      {
        if (current_piece->isFirstMove() == true)
        {
          square_of_rook = current_square;
          rook_column = current_column;
        }
      }
      break;
    }
  }

  if (square_of_rook == nullptr)
  {
    return false;
  }
  int distance_king_to_rook = std::abs(rook_column - source_column);
  // special if rook adjacent to king check if the square behind rook is free
  if (distance_king_to_rook == 1)
  {
    int column_behind_rook = rook_column + direction;
    if (column_behind_rook >= 0 && column_behind_rook < 8)
    {
      if (board.getSquare(source_row, column_behind_rook)->getPiece() != nullptr)
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  return true;
}

void King::move(Game &game, bool is_capture, Square *target_square, std::optional<char> promote_to)
{
  int source_row = static_cast<int>(coordinates_.getRank()) - 1;
  int source_column = static_cast<int>(coordinates_.getFile()) - 'A';
  int target_column = static_cast<int>(target_square->getCoordinates().getFile()) - 'A';
  Board &board = game.getBoard();
  // entered move is a castling move
  if (std::abs(target_column - source_column) == 2)
  {
    int direction;
    if (target_column > source_column)
    {
      direction = 1;
    }
    else
    {
      direction = -1;
    }
    Square *square_of_rook = nullptr;
    for (int current_column = source_column + direction; current_column >= 0 && current_column < 8; current_column += direction)
    {
      Square *current_square = board.getSquare(source_row, current_column);
      if (current_square != nullptr && current_square->getPiece() != nullptr)
      {
        square_of_rook = current_square;
        break;
      }
    }
    if (square_of_rook != nullptr && square_of_rook->getPiece() != nullptr)
    {
      int target_column_of_rook = direction + source_column;
      Square *target_square_of_rook = board.getSquare(source_row, target_column_of_rook);
      // move rook
      auto rook_pointer = square_of_rook->releasePiece();
      rook_pointer->setCoordinates(target_square_of_rook->getCoordinates());
      target_square_of_rook->setPiece(std::move(rook_pointer));
    }
  }
  Piece::move(game, is_capture, target_square, promote_to);
}
