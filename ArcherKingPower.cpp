//---------------------------------------------------------------------------------------------------------------------
/// Archer king's special power. Validates path of the arrow, freezes the target piece.
//---------------------------------------------------------------------------------------------------------------------
#include "ArcherKingPower.hpp"
#include "Game.hpp"
#include "Square.hpp"

ArcherKingPower::ArcherKingPower() {}

void ArcherKingPower::usePower(Game* game, UserInputSpecial& user_input_special)
{
  setContext(user_input_special);
  setMana(distinguishManaCost());
  if(!validateFlightWay(game))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_ARCHER_TARGET));
  }
  auto* targeted_piece = game->getBoard().getSquare(target_square_)->getPiece();
  //it is important that nullptr check is first, otherwise we could have catched a seg fault
  if(targeted_piece == nullptr || targeted_piece->getOwner()->getId() == game->getCurrentPlayer()->getId())
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::OPPONENT_PIECE_NOT_FOUND));
  }
  if(!validateMana(game->getCurrentPlayer()->getCurrentMana()))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
  }
  game->getBoard().getSquare(target_square_)->getPiece()->setFrozen(FROZEN_FOR_);
  game->reduceMana(mana_cost_);
}

std::size_t ArcherKingPower::distinguishManaCost()
{
  std::size_t file_difference = std::abs(target_square_.getFile() - square_.getFile());
  std::size_t rank_difference = std::abs(static_cast<int>(target_square_.getRank()) - static_cast<int>(square_.getRank()));
  return std::max(file_difference, rank_difference);
}

void ArcherKingPower::setContext(UserInputSpecial& user_input_special)
{
  square_ = user_input_special.square_;
  target_square_ = user_input_special.target_square_;
}

bool ArcherKingPower::validateFlightWay(Game* game)
{
  if(target_square_.getFile() != square_.getFile())
  {
    return false;
  }
  if(game->getCurrentPlayer()->getId() == WHITE_ID)
  {
    if(target_square_.getRank() <= square_.getRank())
    {
      return false;
    }
  }
  else
  {
    if(target_square_.getRank() >= square_.getRank())
    {
      return false;
    }
  }
  return true;
}
