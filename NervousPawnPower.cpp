//---------------------------------------------------------------------------------------------------------------------
/// Nervous pawn's special power. Validates the target square, moves the pawn there(one rank behind the source square).
//---------------------------------------------------------------------------------------------------------------------
#include "NervousPawnPower.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "SpawnSquare.hpp"

NervousPawnPower::NervousPawnPower() : ActivePower(MANA_COST_) {}

void NervousPawnPower::setContext(Game* game, UserInputSpecial& user_input_special)
{
  square_ = user_input_special.square_;
  if(game->getCurrentPlayer()->getId() == WHITE_ID)
  {
    target_square_.setRank(square_.getRank() - 1);
  }
  else
  {
    target_square_.setRank(square_.getRank() + 1);
  }
  target_square_.setFile(square_.getFile());
}

std::size_t NervousPawnPower::distinguishManaCost()
{
  return mana_cost_;
  //this power has constant mana cost
  //we do not have to even set it because it is done by ActivePower constructor
  //we only have to validate that player has enough mana
}

void NervousPawnPower::usePower(Game* game, UserInputSpecial& user_input_special)
{
  setContext(game, user_input_special);
  if(wrongTargetSquare(game))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  if(!validateMana(game->getCurrentPlayer()->getCurrentMana()))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
  }
  Square* square = game->getBoard().getSquare(square_);
  Square* target_square = game->getBoard().getSquare(target_square_);
  //we check if there is an item on the target square, and if so take it
  if(target_square->getType() == SquareType::SPAWN_SQUARE &&
      dynamic_cast<SpawnSquare*>(target_square)->hasItem())
  {
    square->getPiece()->addItem(dynamic_cast<SpawnSquare*>(target_square)->releaseItem());
  }
  target_square->setPiece(square->releasePiece());
  target_square->getPiece()->setCoordinates(target_square_);
  target_square->getPiece()->setFirstMove(false);
  game->reduceMana(mana_cost_);
}

bool NervousPawnPower::wrongTargetSquare(Game* game)
{
  if(target_square_.getRank() == 0 || target_square_.getRank() == 9)
  {
    return true;
  }
  if(game->getBoard().getSquare(target_square_)->hasPiece() == true)
  {
    return true;
  }
  return false;
}
