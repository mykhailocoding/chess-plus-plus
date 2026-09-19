//---------------------------------------------------------------------------------------------------------------------
/// Teleport potion. Validates the target square, teleports(moves) the piece there.
//---------------------------------------------------------------------------------------------------------------------
#include "TeleportPotion.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "UseCommand.hpp"

TeleportPotion::TeleportPotion() : Potion(ItemId::TP, "Teleport", "→") {}

void TeleportPotion::usePotion(Game* game, UserInputUse& input)
{
  square_ = input.square_;
  target_square_ = input.target_square_;
  if(wrongTargetSquare(game))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_PARAMETER_USE));
  }
  game->getBoard().getSquare(target_square_)->setPiece(game->getBoard().getSquare(square_)->releasePiece());
  game->getBoard().getSquare(target_square_)->getPiece()->setCoordinates(target_square_);
}

bool TeleportPotion::wrongTargetSquare(Game* game)
{
  if(game->getBoard().getSquare(target_square_)->hasPiece())
  {
    return true;
  }
  std::size_t max_rank = identifyMaxrank(game);
  if(target_square_.getRank() >= max_rank &&
     game->getCurrentPlayer()->getId() == game->getWhitePlayer().getId())
  {
    return true;
  }
  else if(target_square_.getRank() <= max_rank &&
     game->getCurrentPlayer()->getId() == game->getBlackPlayer().getId())
  {
    return true;
  }
  return false;
}

std::size_t TeleportPotion::identifyMaxrank(Game* game)
{
  bool bigger;
  std::size_t max_rank;
  if(game->getCurrentPlayer()->getId() == game->getWhitePlayer().getId())
  {
    bigger = true;
    max_rank = 0;
  }
  else
  {
    bigger = false;
    max_rank = 8;
  }
  for(int row = 0; row < 8; row++)
  {
    for(int column = 0; column < 8; column++)
    {
      auto piece = game->getBoard().getSquare(row, column)->getPiece();
      if(piece == nullptr) continue;
      if(piece->getOwner()->getId() == game->getCurrentPlayer()->getId() &&
      piece->getCoordinates().getRank() > max_rank && bigger)
      {
        max_rank = piece->getCoordinates().getRank();
      }
      else if(piece->getOwner()->getId() == game->getCurrentPlayer()->getId() &&
      piece->getCoordinates().getRank() < max_rank && !bigger)
      {
        max_rank = piece->getCoordinates().getRank();
      }
    }
  }
  return max_rank;
}

bool TeleportPotion::validParameters(std::vector<std::string> parameters, UserInputUse& user_input_use)
{
  if (parameters.at(0).length() != 2)
  {
    return false;
  }
  else if ((parameters.at(0).at(0) >= 'A') && (parameters.at(0).at(0) <= 'H')
    && (parameters.at(0).at(1) >= '1') && (parameters.at(0).at(1) <= '8'))
  {
    user_input_use.target_square_ = Coordinates(parameters.at(0));
    return true;
  }
  else
  {
    return false;
  }
}
