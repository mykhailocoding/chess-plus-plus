//---------------------------------------------------------------------------------------------------------------------
/// Color blind bishop's special power. Checks that the target square is adjacent, moves the bishop and if target
/// square has piece captures it, identifies and sets new movement color.
//---------------------------------------------------------------------------------------------------------------------
#include "ColorBlindBishopPower.hpp"
#include "ColorBlindBishop.hpp"
#include "Game.hpp"
#include "Square.hpp"//for enum
#include "SpawnSquare.hpp"

ColorBlindBishopPower::ColorBlindBishopPower(ColorBlindBishop* owner) : ActivePower(MANA_COST_), owner_(owner) {}

ColorBlindBishopPower::ColorBlindBishopPower(const ColorBlindBishopPower& power) : ActivePower(power),
  square_(power.square_), target_square_(power.target_square_)
  {
    // not a deep copy anymore but since we need to check for the active powers with copying the board, it doesn't matter
    owner_ = nullptr;
  }

void ColorBlindBishopPower::usePower(Game* game, UserInputSpecial& user_input_special)
{
  setContext(user_input_special);
  if(!isAdjacent())
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  bool capture = false;
  bool move = false;
  Square* square = game->getBoard().getSquare(square_);
  Square* target_square = game->getBoard().getSquare(target_square_);
  auto* targeted_piece = target_square->getPiece();

  if(targeted_piece != nullptr)
  {
    if(targeted_piece->getOwner()->getId() != game->getCurrentPlayer()->getId())
    {
      capture = true;
    }
    else
    {
      throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
      //contains friendly piece
    }
  }
  else
  {
    move = true;
  }
  if(!validateMana(game->getCurrentPlayer()->getCurrentMana()))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
  }
  if(capture)
  {
    if(!target_square->getPiece()->canBeCaptured(PieceType::Bishop))
    {
      throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
    }
    //if the piece on the target square has shield we break it but do not move
    if(target_square->getPiece()->checkShield())
    {
      owner_->setMovementColor(owner_->getMovementColor());//if the bishop has not moved the color stays the same
      game->reduceMana(mana_cost_);
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
  else if(move)
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
  owner_->setMovementColor(identifyMovementColor(game));
  game->reduceMana(mana_cost_);
}

void ColorBlindBishopPower::setContext(UserInputSpecial& user_input_special)
{
  square_ = user_input_special.square_;
  target_square_ = user_input_special.target_square_;
}

bool ColorBlindBishopPower::isAdjacent()
{
  int file_difference = std::abs(target_square_.getFile() - square_.getFile());
  int rank_difference = std::abs(static_cast<int>(target_square_.getRank()) - static_cast<int>(square_.getRank()));
  return (file_difference <= 1 && rank_difference <= 1) && !(file_difference == 0 && rank_difference == 0);
}

std::size_t ColorBlindBishopPower::distinguishManaCost()
{
  return mana_cost_;
}

MovementColor ColorBlindBishopPower::identifyMovementColor(Game* game)
{
  if(game->getBoard().getSquare(target_square_)->getType() == SquareType::BASIC_BLACK)
  {
    return MovementColor::BLACK;
  }
  if(game->getBoard().getSquare(target_square_)->getType() == SquareType::BASIC_WHITE)
  {
    return MovementColor::WHITE;
  }
  return owner_->getMovementColor();
}
