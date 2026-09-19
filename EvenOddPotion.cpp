//---------------------------------------------------------------------------------------------------------------------
/// Even/odd potion. Validates the target square, forces the opponents piece on the target square to move on either
/// even or odd turns for the remainder of the game.
//---------------------------------------------------------------------------------------------------------------------
#include "EvenOddPotion.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "UseCommand.hpp"

EvenOddPotion::EvenOddPotion() : Potion(ItemId::EVENODD, "Even/Odd", "½") {}

void EvenOddPotion::usePotion(Game* game, UserInputUse& input)
{
  square_ = input.square_;
  target_square_ = input.target_square_;
  parity_ = input.parity_;
  if(wrongTargetSquare(game))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_PARAMETER_USE));
  }
  game->getBoard().getSquare(target_square_)->getPiece()->setParity(parity_);
}

bool EvenOddPotion::wrongTargetSquare(Game* game)
{
  if(!game->getBoard().getSquare(target_square_)->hasPiece())
  {
    return true;
  }
  if(game->getBoard().getSquare(target_square_)->getPiece()->getOwner()->getId() ==
     game->getCurrentPlayer()->getId())
  {
    return true;
  }
  if(parity_ != Parity::EVEN && parity_ != Parity::ODD)
  {
    return true;
  }
  return false;
}

bool EvenOddPotion::validParameters(std::vector<std::string> parameters, UserInputUse& user_input_use)
{
  if (parameters.at(0).length() != 2)
  {
    return false;
  }
  else if ((parameters.at(0).at(0) >= 'A') && (parameters.at(0).at(0) <= 'H')
    && (parameters.at(0).at(1) >= '1') && (parameters.at(0).at(1) <= '8'))
  {
    user_input_use.target_square_ = Coordinates(parameters.at(0));
  }
  else
  {
    return false;
  }

  if (parameters.at(1) == "EVEN")
  {
    user_input_use.parity_ = Parity::EVEN;
  }
  else if (parameters.at(1) == "ODD")
  {
    user_input_use.parity_ = Parity::ODD;
  }
  else
  {
    return false;
  }

  return true;
}
