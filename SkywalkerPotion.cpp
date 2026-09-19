//---------------------------------------------------------------------------------------------------------------------
/// Skywalker potion. Pushes the piece directly in front of the activating piece (relative to the player’s forward
/// direction) one square backward. If multiple pieces are aligned behind it, they are pushed as well. The command
/// fails if there is no piece to push or if the last piece is already on the final rank.
//---------------------------------------------------------------------------------------------------------------------
#include "SkywalkerPotion.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "UseCommand.hpp"

SkywalkerPotion::SkywalkerPotion() : Potion(ItemId::LUKE, "Skywalker", "↑") {}

void SkywalkerPotion::usePotion(Game* game, UserInputUse& input)
{
  square = input.square_;
  setBackRank(game);
  if(canNotPush(game))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_PARAMETER_USE));
  }
  push(game);
}

void SkywalkerPotion::push(Game* game)
{
  if(back_rank_ == 8)
  {
    for(int counter = amount_pieces_to_push_; counter > 0; counter--)
    {
      Coordinates pushed_to(square.getFile(), counter + square.getRank() + 1);
      Coordinates pushed_from(square.getFile(), counter + square.getRank());
      game->getBoard().getSquare(pushed_to)->setPiece(game->getBoard().getSquare(pushed_from)->releasePiece());
      game->getBoard().getSquare(pushed_to)->getPiece()->setCoordinates(pushed_to);
    }
  }
  else if(back_rank_ == 1)
  {
    for(int counter = amount_pieces_to_push_; counter > 0; counter--)
    {
      Coordinates pushed_to(square.getFile(), square.getRank() - counter - 1);
      Coordinates pushed_from(square.getFile(), square.getRank() - counter);
      game->getBoard().getSquare(pushed_to)->setPiece(game->getBoard().getSquare(pushed_from)->releasePiece());
      game->getBoard().getSquare(pushed_to)->getPiece()->setCoordinates(pushed_to);
    }
  }

}

void SkywalkerPotion::setBackRank(Game* game)
{
  if(game->getCurrentPlayer()->getId() == game->getWhitePlayer().getId())
  {
    back_rank_ =  8;
  }
  else
  {
    back_rank_ =  1;
  }
}

bool SkywalkerPotion::canNotPush(Game* game)
{
  
  amount_pieces_to_push_ = 0;
  if(back_rank_ == 8)
  {
    if(square.getRank() == 8) return true;
    if(!game->getBoard().getSquare(square.getRank(), square.getFile() - 'A')->hasPiece())
    {
      return true;
    }
    amount_pieces_to_push_++;
    for(int rank = square.getRank() + 2; rank <= 8; rank++)
    {
      if(!game->getBoard().getSquare(rank - 1, square.getFile() - 'A')->hasPiece())
      {
        return false;
      }
      amount_pieces_to_push_++;
    }
  }
  else if(back_rank_ == 1)
  {
    if(square.getRank() == 1) return true;
    if(!game->getBoard().getSquare(square.getRank() - 2, square.getFile() - 'A')->hasPiece())
    {
      return true;
    }
    amount_pieces_to_push_++;
    for(int rank = square.getRank() - 2; rank >= 1; rank--)
    {
      if(!game->getBoard().getSquare(rank - 1, square.getFile() - 'A')->hasPiece())
      {
        return false;
      }
      amount_pieces_to_push_++;
    }
  }
  return true;
}
