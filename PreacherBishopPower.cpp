//---------------------------------------------------------------------------------------------------------------------
/// Preacher bishop's special power. Validates that the bishop can capture opponent's piece on the target square,
/// changes the owner of the targeted piece to the current player.
//---------------------------------------------------------------------------------------------------------------------
#include "PreacherBishopPower.hpp"
#include "Game.hpp"
#include "Square.hpp"

PreacherBishopPower::PreacherBishopPower() {}

void PreacherBishopPower::usePower(Game* game, UserInputSpecial& user_input_special)
{
  setContext(user_input_special);
  //it is okay that invalid move is before the unwavering faith
  //because if the square is empty it can not be the other preacher bishop
  if(!game->getBoard().getSquare(target_square_)->hasPiece())
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  targeted_piece_value_ = game->getBoard().getSquare(target_square_)->getPiece()->getValue();
  setMana(distinguishManaCost());
  //if another preacher bishop is standing on the target square
  if(game->getBoard().getSquare(target_square_)->getPiece()->getId() == "BPRC")
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::UNWAVERING_FAITH));
  }
  //we check that bishop can capture the piece on the target square
  if(!game->getBoard().getSquare(square_)->getPiece()->isMoveValid(game->getBoard(), game->getBoard().getSquare(target_square_)))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }

  if(!validateMana(game->getCurrentPlayer()->getCurrentMana()))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
  }
  game->getBoard().getSquare(target_square_)->getPiece()->setOwner(game->getCurrentPlayer());
  game->reduceMana(mana_cost_);
}

void PreacherBishopPower::setContext(UserInputSpecial& user_input_special)
{
  square_ = user_input_special.square_;
  target_square_ = user_input_special.target_square_;
}

std::size_t PreacherBishopPower::distinguishManaCost()
{
  return 3 * targeted_piece_value_;
}
