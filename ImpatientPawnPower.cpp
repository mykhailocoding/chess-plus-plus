//---------------------------------------------------------------------------------------------------------------------
/// Impatient pawn's special power. Validates target piece, promotes the pawn to the target piece.
//---------------------------------------------------------------------------------------------------------------------
#include "ImpatientPawnPower.hpp"
#include "Game.hpp"
#include <iostream>

ImpatientPawnPower::ImpatientPawnPower(){}

std::size_t ImpatientPawnPower::distinguishManaCost()
{
  return rank_difference_ * target_piece_value_;
}

void ImpatientPawnPower::usePower(Game* game, UserInputSpecial& user_input_special)
{
  setContext(game, user_input_special);
  if(wrongTargetPiece())
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_PARAMETER_PIECE_TYPE));
  }
  setRankDifference();
  setTargetPieceValue();
  setMana(distinguishManaCost());
  if(!validateMana(game->getCurrentPlayer()->getCurrentMana()))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
  }
  game->reduceMana(mana_cost_);
  game->promote(game->getBoard(), square_, promote_to_);
}

void ImpatientPawnPower::setTargetPieceValue()
{
  if(promote_to_ == 'R') target_piece_value_ = 5;
  if(promote_to_ == 'N') target_piece_value_ = 3;
  if(promote_to_ == 'B') target_piece_value_ = 3;
  if(promote_to_ == 'Q') target_piece_value_ = 9;
}

bool ImpatientPawnPower::wrongTargetPiece()
{
  if(promote_to_ != 'R' &&
     promote_to_ != 'N' &&
     promote_to_ != 'B' &&
     promote_to_ != 'Q')
     {
      return true;
     }
  return false;
}

void ImpatientPawnPower::setRankDifference()
{
  if(piece_color_ == 'w')
  {
    opponents_back_rank_ = 8; 
    rank_difference_ = opponents_back_rank_ - rank_;
  }
  else if(piece_color_ == 'b')
  {
    opponents_back_rank_ = 1;
    rank_difference_ = rank_ - opponents_back_rank_;
  }
}

void ImpatientPawnPower::setContext(Game* game, UserInputSpecial& user_input_special)
{
  promote_to_ = user_input_special.piece_type_;
  if(game->getCurrentPlayer()->getId() == WHITE_ID)
  {
    piece_color_ = 'w';
  }
  else
  {
    piece_color_ = 'b';
  }
  rank_ = user_input_special.square_.getRank();
  square_ = user_input_special.square_;
}

void ImpatientPawnPower::checkParameters(std::vector<std::string> parameters, UserInputSpecial& user_input_special,
  std::map<ErrorType, std::string>& error_messages)
{
  if (parameters.at(0).length() != 1)
  {
    throw CustomException(error_messages.at(ErrorType::INVALID_PARAMETER_PIECE_TYPE));
  }
  else
  {
    user_input_special.piece_type_ = parameters.at(0).at(0);
  }
}
