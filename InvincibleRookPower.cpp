//---------------------------------------------------------------------------------------------------------------------
/// Invincible rook's special power. Makes the rook invincible for a specified number of turns not including the
/// current one.
//---------------------------------------------------------------------------------------------------------------------
#include "InvincibleRookPower.hpp"
#include "Game.hpp"
#include "Square.hpp"
InvincibleRookPower::InvincibleRookPower() {}

void InvincibleRookPower::usePower(Game* game, UserInputSpecial& user_input_special)
{
  setContext(user_input_special);
  if(wrongTurnCount())
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_PARAMETER_TURN_COUNT));
  }
  setMana(distinguishManaCost());
  if(!validateMana(game->getCurrentPlayer()->getCurrentMana()))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
  }
  game->getBoard().getSquare(square_)->getPiece()->setInvincible(turn_count_);
  game->reduceMana(mana_cost_);
}

std::size_t InvincibleRookPower::distinguishManaCost()
{
  return (turn_count_ - 1);
}

void InvincibleRookPower::setContext(UserInputSpecial& user_input_special)
{
  turn_count_ = user_input_special.turn_count_ + 1;
  square_ = user_input_special.square_;
}

bool InvincibleRookPower::wrongTurnCount()
{
  if(turn_count_ < 1)
  {
    return true;
  }
  return false;
}

void InvincibleRookPower::checkParameters(std::vector<std::string> parameters, UserInputSpecial& user_input_special,
  std::map<ErrorType, std::string>& error_messages)
{
  if ((parameters.at(0).at(0) == '-') || (!Utils::stringToSizeT(parameters.at(0), user_input_special.turn_count_)))
  {
    throw CustomException(error_messages.at(ErrorType::INVALID_PARAMETER_TURN_COUNT));
  }
}
