//----------------------------------------------------------------------------------------------------------------------
/// The Conditiosn class is written to help other classes check if a move or special command is allowed to be excecuted
/// though it does not check if the moves for a piece are correc it collects the possible pieces a move could be 
//  excecuted with. Other checks are also done (is a sqaure under attack,
//  is the path the piece wants to move along free). All methods are static, meaning they can be called directly 
///  without instantiating an object.
//----------------------------------------------------------------------------------------------------------------------


#include "Conditions.hpp"
#include "Board.hpp"
#include <algorithm> // std::max
#include <cmath>     // std::abs

std::vector<Piece *> Conditions::findPossiblePieces(Game &game, Player *current_player, PieceType type)
{
  std::vector<Piece *> possible_pieces;

  Board &board = game.getBoard();
  for (int row = 0; row < 8; row++)
  {
    for (int column = 0; column < 8; column++)
    {
      Square *current_square = board.getSquare(row, column);
      Piece *current_piece = current_square->getPiece();
      //piece is not a nullpointer, from the player, is the type intented to move, is not frozen, and is alowed to move
      if ((current_piece != nullptr) && (*(current_piece->getOwner()) == current_player)
       && (current_piece->getType() == type) && (current_piece->getFrozenCounter() == 0)
       && current_piece->canMove(&game))
      {
        possible_pieces.push_back(current_square->getPiece());
      }
    }
  }
  return possible_pieces;
}

bool Conditions::checkMoveResultInCheck(Game &game, Square *target_square, Square *source_square)
{
  Board copied_board(game.getBoard());

  Coordinates target_coordinates = target_square->getCoordinates();
  Coordinates source_coordinates = source_square->getCoordinates();

  Square *copied_source_square = copied_board.getSquare(source_coordinates.getRank() - 1, source_coordinates.getFile() - 'A');
  Square *copied_target_square = copied_board.getSquare(target_coordinates.getRank() - 1, target_coordinates.getFile() - 'A');

  if (copied_target_square->hasPiece())
  {
    // owner of the "captured" piece has to be deleted since owner is a raw pointer and the piece gets overwritten
    // manual memory management to avoid memory leaks
    delete copied_target_square->getPiece()->getOwner();
    copied_target_square->getPiece()->setOwner(nullptr);
  }

  copied_target_square->setPiece(copied_source_square->releasePiece());

  copied_target_square->getPiece()->setCoordinates(copied_target_square->getCoordinates());

  if (isKingInCheck(copied_board, copied_target_square->getPiece()->getOwner()) == true)
  {
    for (auto& row : copied_board.getBoard())
    {
      for (auto& square : row)
      {
        if (square->hasPiece())
        {
          delete square->getPiece()->getOwner();
          square->getPiece()->setOwner(nullptr);
        }
      }
    }
    return true;
  }
  else
  {
    for (auto& row : copied_board.getBoard())
    {
      for (auto& square : row)
      {
        if (square->hasPiece())
        {
          delete square->getPiece()->getOwner();
          square->getPiece()->setOwner(nullptr);
        }
      }
    }
    return false;
  }
}

bool Conditions::isKingInCheck(Board& board, Player *player)
{
  Square *king_is_here = nullptr;

  for (int row = 0; row < 8; row++)
  {
    for (int column = 0; column < 8; column++)
    {
      Square *current_square = board.getSquare(row, column);
      Piece *current_piece = current_square->getPiece();
      if (current_piece != nullptr)
      {
        if (*(current_piece->getOwner()) == player && current_piece->getType() == PieceType::King)
        {
          king_is_here = current_square;
          return checkIsSquareUnderAttack(board, king_is_here);
        }
      }
    }
  }
  return false;
}

bool Conditions::checkIsSquareUnderAttack(Board& board, Square *target_square)
{
  for (int row = 0; row < 8; row++)
  {
    for (int column = 0; column < 8; column++)
    {
      Square *current_square = board.getSquare(row, column);
      Piece *opponent_piece = current_square->getPiece();
      if (opponent_piece != nullptr &&
        (target_square->getPiece() == nullptr || *(opponent_piece->getOwner()) != target_square->getPiece()->getOwner()))
      {
        // passsiv powers and frozen pieces have to be taken into account
        if (opponent_piece->isMoveValid(board, target_square) == true && opponent_piece->getFrozenCounter() == 0)
        {
          return true;
        }
      }
    }
  }
  return false;
}


bool Conditions::isEmptySquareUnderAttack(Board &board, Square *target_square, Player* current_player)
{
  for (int row = 0; row < 8; row++)
  {
    for(int column = 0; column < 8; column++)
    {
      Piece* attacking_piece = board.getSquare(row, column)->getPiece();
      if(attacking_piece != nullptr && attacking_piece->getOwner() != current_player)
      {
        if(attacking_piece->isMoveValid(board, target_square) == true && attacking_piece->getFrozenCounter() == 0)
        {
          return true;
        }
      }
    }
  }
  return false;
}

 bool Conditions::isPathClear(Board &board, Square *source_square, Square *target_square)
{
  int source_row = static_cast<int>(source_square->getCoordinates().getRank()) - 1;
  int source_column = static_cast<int>(source_square->getCoordinates().getFile()) - 'A';

  int target_row = static_cast<int>(target_square->getCoordinates().getRank()) - 1;
  int target_column = static_cast<int>(target_square->getCoordinates().getFile()) - 'A';

  int row_difference = target_row - source_row;
  int column_difference = target_column - source_column;

  int distance = std::max(std::abs(row_difference), std::abs(column_difference));

  int row_step = row_difference / distance;
  int column_step = column_difference / distance;

  if (distance <= 1)
  {
    return true;
  }

  int current_row = source_row + row_step;
  int current_column = source_column + column_step;

  // starts with 1 to avoid checking the target square occupancy
  for (int i = 1; i < distance; i++)
  {
    if (board.getSquare(current_row, current_column)->getPiece() != nullptr)
    {
      return false;
    }
    current_row += row_step;
    current_column += column_step;
  }
  return true;
}

bool Conditions::hasLegalMove(Game& game, Player& player)
{
  for (auto row : game.getBoard().getBoard())
  {
    for (auto square : row)
    {
      if (square->hasPiece() && !square->getPiece()->isFrozen() && player == square->getPiece()->getOwner())
      {
        // check all possible moves of the piece(isMoveValid and checkMoveResultInCheck))
        // iterate through board
        if (checkForLegalMoves(game, square))
        {
          return true;
        }
      }
    }
  }

  return false;
}

bool Conditions::checkForLegalMoves(Game& game, Square* source_square)
{
  for (auto row : game.getBoard().getBoard())
  {
    for (auto target_square : row)
    {
      if (source_square->getPiece()->isMoveValid(game.getBoard(), target_square) &&
        !checkMoveResultInCheck(game, target_square, source_square))
      {
        return true;
      }
    }
  }

  return false;
}
