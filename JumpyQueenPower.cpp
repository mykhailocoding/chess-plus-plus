//---------------------------------------------------------------------------------------------------------------------
/// Jumpy queen's special power. Validates target square, identifies if the command is move or capture, executes the
/// command.
//---------------------------------------------------------------------------------------------------------------------
#include "JumpyQueenPower.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "SpawnSquare.hpp"

JumpyQueenPower::JumpyQueenPower() : ActivePower(MANA_COST_) {}

void JumpyQueenPower::usePower(Game* game, UserInputSpecial& user_input_special)
{
  setContext(user_input_special);
  if(!validKnightJump())
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  bool capture = false;
  bool move = false;
  if(!validateCaptureAndMove(game, capture, move))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  if(!validateMana(game->getCurrentPlayer()->getCurrentMana()))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
  }
  Square* square = game->getBoard().getSquare(square_);
  Square* target_square = game->getBoard().getSquare(target_square_);
  if(capture)
  {
    QueenKnightCapture(game, square, target_square);
  }
  else if(move)
  {
    QueenKnightMove(square, target_square);
  }
  game->reduceMana(mana_cost_);
}

std::size_t JumpyQueenPower::distinguishManaCost()
{
  return mana_cost_;
}

void JumpyQueenPower::setContext(UserInputSpecial& user_input_special)
{
  square_ = user_input_special.square_;
  target_square_ = user_input_special.target_square_;
}

bool JumpyQueenPower::validateCaptureAndMove(Game* game, bool& capture, bool& move)
{
  auto* targeted_piece = game->getBoard().getSquare(target_square_)->getPiece();
  if(targeted_piece != nullptr)
  {
    if(!targeted_piece->canBeCaptured(PieceType::Queen)) return false;
    if(targeted_piece->getOwner()->getId() != game->getCurrentPlayer()->getId())
    {
      capture = true;
    }
    else
    {
      return false;
      //contains friendly piece
    }
  }
  else
  {
    move = true;
  }
  return true;
}

bool JumpyQueenPower::validKnightJump()
{
  std::size_t file_difference = std::abs(target_square_.getFile() - square_.getFile());
  std::size_t rank_difference = std::abs(static_cast<int>(target_square_.getRank()) - static_cast<int>(square_.getRank()));
  return (file_difference == 1 && rank_difference == 2) || (file_difference == 2 && rank_difference ==1);
}

void JumpyQueenPower::QueenKnightCapture(Game* game, Square* square, Square* target_square)
{
  //if the piece on the target square has shield we break it but do not move
  if(target_square->getPiece()->checkShield())
  {
    return;
  }
  //if the piece on the target square has item, we take it before capturing the piece
  if(target_square->getPiece()->hasItem())
  {
    square->getPiece()->addItem(target_square->getPiece()->releaseItem());
  }
  std::unique_ptr<Piece> captured_piece = target_square->releasePiece();
  game->getCurrentPlayer()->addPieceToPrison(std::move(captured_piece));
  target_square->setPiece(square->releasePiece());
  target_square->getPiece()->setCoordinates(target_square_);
}

void JumpyQueenPower::QueenKnightMove(Square* square, Square* target_square)
{
  //we check if there is an item on the target square, and if so take it
  if(target_square->getType() == SquareType::SPAWN_SQUARE &&
      dynamic_cast<SpawnSquare*>(target_square)->hasItem())
  {
    square->getPiece()->addItem(dynamic_cast<SpawnSquare*>(target_square)->releaseItem());
  }
  target_square->setPiece(square->releasePiece());
  target_square->getPiece()->setCoordinates(target_square_);
}
