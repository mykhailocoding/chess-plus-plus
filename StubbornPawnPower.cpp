//---------------------------------------------------------------------------------------------------------------------
/// Stubborn pawn's special power. Validates the target square, captures the piece direct infront of the stubborn pawn.
//---------------------------------------------------------------------------------------------------------------------
#include "StubbornPawnPower.hpp"
#include "Game.hpp"
#include "Square.hpp"
StubbornPawnPower::StubbornPawnPower() : ActivePower(MANA_COST_) {}

void StubbornPawnPower::setContext(Game* game, UserInputSpecial& user_input_special)
{
  square_ = user_input_special.square_;
  if(game->getCurrentPlayer()->getId() == WHITE_ID)
  {
    piece_color_ = 'w';
    target_square_.setRank(square_.getRank() + 1);
  }
  else
  {
    piece_color_ = 'b';
    target_square_.setRank(square_.getRank() - 1);
  }
  target_square_.setFile(square_.getFile());
}

std::size_t StubbornPawnPower::distinguishManaCost()
{
  return mana_cost_;
  //this power has constant mana cost
  //we do not have to even set it because it is done by ActivePower constructor
  //we only have to validate that player has enough mana
}

void StubbornPawnPower::usePower(Game* game, UserInputSpecial& user_input_special)
{
  setContext(game, user_input_special);
  Square* square = game->getBoard().getSquare(square_);
  Square* target_square = game->getBoard().getSquare(target_square_);
  if(wrongTargetSquare(game, target_square))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  if(!validateMana(game->getCurrentPlayer()->getCurrentMana()))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
  }
  
  //we promote manually so we just do not promote it here

  //if the piece on the target square has shield we break it but do not move
  if(target_square->getPiece()->checkShield())
  {
    square->getPiece()->setFirstMove(false);
    game->reduceMana(mana_cost_);
    return;
  }
  //if the piece on the target square has item, we take it before capturing the piece
  if(target_square->getPiece()->hasItem())
  {
    square->getPiece()->addItem(target_square->getPiece()->releaseItem());
  }
  //capturing the piece, moving it to the prison and setting new coords
  std::unique_ptr<Piece> captured_piece = target_square->releasePiece();
  game->getCurrentPlayer()->addPieceToPrison(std::move(captured_piece));
  target_square->setPiece(square->releasePiece());
  target_square->getPiece()->setCoordinates(target_square_);
  target_square->getPiece()->setFirstMove(false);
  game->reduceMana(mana_cost_);
}

bool StubbornPawnPower::wrongTargetSquare(Game* game, Square* target_square)
{
  if(target_square_.getRank() == 9 || target_square_.getRank() == 0 ||
    target_square->hasPiece() == false ||
    target_square->getPiece()->getOwner()->getId() == game->getCurrentPlayer()->getId() ||
    !target_square->getPiece()->canBeCaptured(PieceType::Pawn))
  {
    return true;
  }
  return false;
}
