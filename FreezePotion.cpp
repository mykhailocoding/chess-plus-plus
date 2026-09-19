//---------------------------------------------------------------------------------------------------------------------
/// Freeze potion. Validates the target square, freezes the targeted piece for 1 turn(excluding the current one).
//---------------------------------------------------------------------------------------------------------------------
#include "FreezePotion.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "UseCommand.hpp"

FreezePotion::FreezePotion() : Potion(ItemId::FREEZE, "Freeze", "*") {}

void FreezePotion::usePotion(Game* game, UserInputUse& input)
{
  square_ = input.square_;
  target_square_ = input.target_square_;
  if(wrongTargetSquare(game))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_PARAMETER_USE));
  }
  game->getBoard().getSquare(target_square_)->getPiece()->setFrozen(2);
}

bool FreezePotion::wrongTargetSquare(Game* game)
{
  if(!game->getBoard().getSquare(target_square_)->hasPiece())
  {
    return true;
  }
  return false;
}

bool FreezePotion::validParameters(std::vector<std::string> parameters, UserInputUse& user_input_use)
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
