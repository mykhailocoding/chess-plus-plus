//----------------------------------------------------------------------------------------------------------------------
/// A subclass from piece and implements the checks if a bishop movement is allowed and creates bishop objects.
//----------------------------------------------------------------------------------------------------------------------
#include "Bishop.hpp"
#include "Board.hpp"
#include "Square.hpp"
#include "Conditions.hpp"

Bishop::Bishop() : Piece(PieceType::Bishop, "B", 3, SpecialPowerType::None, "♝b") {}

Bishop::Bishop(char movement_color) : Piece(PieceType::Bishop, "B", 3, SpecialPowerType::None, "♝b")
{
  if(movement_color == 'w')
  {
    movement_color_ = MovementColor::WHITE;
  }
  if(movement_color == 'b')
  {
    movement_color_ = MovementColor::BLACK;
  }
}

Bishop::Bishop(std::string id, SpecialPowerType special_power_type, std::string short_name)
  : Piece(PieceType::Bishop, id, 3, special_power_type, short_name) {}

bool Bishop::isMoveValid(Board& board, Square* target_square)
{
  if(target_square->getPiece() != nullptr && (*(target_square->getPiece()->getOwner()) == this->getOwner()
    || !target_square->getPiece()->canBeCaptured(PieceType::Bishop)))
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
  //move is not a straight line
  if(!(row_difference == 0 || column_difference == 0 || row_difference == column_difference))
  {
    return false;
  }

  int row_difference_raw = target_row - source_row;
  int column_difference_raw = target_column - source_column;
  int distance = std::max(row_difference, column_difference);

  int row_step = row_difference_raw / distance;
  int column_step = column_difference_raw / distance;

  int current_row = source_row + row_step;
  int current_column = source_column + column_step;
  

  for (int i = 1; i < distance; i++)
  {
    Square* step_square = board.getSquare(current_row, current_column);

    if (step_square->getPiece() != nullptr)
    {
      return false; 
    }

    if (!step_square->isSpecialSquare())
    {
      MovementColor step_color;
      if(step_square->getType() == SquareType::BASIC_WHITE)
      {
        step_color = MovementColor::WHITE;
      }
      else
      {
        step_color = MovementColor::BLACK;
      }

      if (step_color != this->movement_color_)
      {
        return false; 
      }
    }

    current_row += row_step;
    current_column += column_step;
  }

  // checking color of the target square
  if (!target_square->isSpecialSquare())
  {
    MovementColor target_color;
    if(target_square->getType() == SquareType::BASIC_WHITE)
    {
      target_color = MovementColor::WHITE;
    }
    else
    {
      target_color = MovementColor::BLACK;
    }

    if (target_color != movement_color_)
    {
      return false;
    }
  }
  return true;
}
