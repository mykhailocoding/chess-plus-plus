//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the base Piece class and implements checks for pawn-specific movement 
/// and capture rules.
//----------------------------------------------------------------------------------------------------------------------


#include "Pawn.hpp"
#include "Player.hpp"
#include "Square.hpp"
#include "Board.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"

Pawn::Pawn() : Piece(PieceType::Pawn, "P", 1, SpecialPowerType::None, "♟p") {}

Pawn::Pawn(std::string id, SpecialPowerType special_power_type, std::string short_name)
    : Piece(PieceType::Pawn, id, 1, special_power_type, short_name) {}

bool Pawn::isMoveValid(Board &board, Square *target_square)
{
  if(target_square->getPiece() != nullptr && (*(target_square->getPiece()->getOwner()) == this->getOwner()
    || !target_square->getPiece()->canBeCaptured(PieceType::Pawn)))
  {
    return false;
  }

  int source_row = static_cast<int>(coordinates_.getRank()) - 1;
  int source_column = static_cast<int>(coordinates_.getFile()) - 'A';

  int target_row = static_cast<int>(target_square->getCoordinates().getRank()) - 1;
  int target_column = static_cast<int>(target_square->getCoordinates().getFile()) - 'A';

  int row_difference = target_row - source_row;
  int column_difference = target_column - source_column;

  int direction;
  if (this->getOwner()->getId() == WHITE_ID)
  {
    direction = 1;
  }
  else if (this->getOwner()->getId() == BLACK_ID)
  {
    direction = -1;
  }

  // move 1 forward
  if (column_difference == 0)
  {
    if (target_square->getPiece() != nullptr)
    {
      return false;
    }

    if (row_difference == direction)
    {
      return true;
    }
    if (row_difference == 2 * direction && first_move_ == true)
    {
      if (board.getSquare(source_row + direction, source_column)->getPiece() == nullptr)
      {
        return true;
      }
    }
  }
  // capture
  if (column_difference == 1 || column_difference == -1)
  {
    if (row_difference == direction)
    {
      if (target_square->getPiece() != nullptr && *(target_square->getPiece()->getOwner()) != this->getOwner())
      {
        return true;
      }
      // en pasant
      if (target_square->getPiece() == nullptr)
      {
        Square *square_next_to_pawn = board.getSquare(source_row, target_column);
        Piece *target_piece = square_next_to_pawn->getPiece();
        if (target_piece != nullptr && target_piece->getOwner() != this->getOwner() &&
          target_piece->getType() == PieceType::Pawn)
        {
          auto opponent_history = target_piece->getOwner()->getHistory();
          if (!opponent_history.empty() && !opponent_history.back().empty())
          {
            std::string last_move_opponent = opponent_history.back().back();
            std::string excpected_row_of_opponent = std::format("{}{}",
            static_cast<char>(std::tolower(square_next_to_pawn->getCoordinates().getFile())),
            square_next_to_pawn->getCoordinates().getRank());

            if (last_move_opponent.ends_with(excpected_row_of_opponent))
            {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}
