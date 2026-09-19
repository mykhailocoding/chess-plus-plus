//---------------------------------------------------------------------------------------------------------------------
/// Explosive pawn's special power. Checks that the target square is correct, captures the piece on the on the target 
/// square, identifies neighboring pieces that are not pawns, blows them up!
//---------------------------------------------------------------------------------------------------------------------
#include "ExplosivePawnPower.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "Piece.hpp"//enum

ExplosivePawnPower::ExplosivePawnPower() : ActivePower(MANA_COST_) {}

ExplosivePawnPower::ExplosivePawnPower(const ExplosivePawnPower& power) :
  ActivePower(power), pawn_square_(power.pawn_square_), target_square_(power.target_square_) {}

void ExplosivePawnPower::setContext(UserInputSpecial& user_input_special)
{
  pawn_square_ = user_input_special.square_;
  target_square_ = user_input_special.target_square_;
}

std::size_t ExplosivePawnPower::distinguishManaCost()
{
  return mana_cost_;
  //this power has constant mana cost
  //we do not have to even set it because it is done by ActivePower constructor
  //we only have to validate that player has enough mana
}

void ExplosivePawnPower::usePower(Game* game, UserInputSpecial& user_input_special)
{
  setContext(user_input_special);
  if(wrongTargetSquare(game))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  if(!validateMana(game->getCurrentPlayer()->getCurrentMana()))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
  }
  Coordinates center = target_square_;
  Square* pawn_square = game->getBoard().getSquare(pawn_square_);
  Square* target_square = game->getBoard().getSquare(target_square_);
  if(target_square->getPiece()->checkShield())
  {
    //if the piece has shield we remove it and change center of explosion to the pawn_square_
    //shield is removed inside checkShield(if there was a shield)
    center = pawn_square_;
  }
  else
  {
    //if the piece on the target square has item, we take it before capturing the piece
    if(target_square->getPiece()->hasItem())
    {
      pawn_square->getPiece()->addItem(target_square->getPiece()->releaseItem());
    }
    //we capture the piece(transfer it to prison, move pawn to the target square, set new coords for pawn)
    std::unique_ptr<Piece> captured_piece = target_square->releasePiece();
    game->getCurrentPlayer()->addPieceToPrison(std::move(captured_piece));
    target_square->setPiece(pawn_square->releasePiece());
    target_square->getPiece()->setCoordinates(target_square_);
  }

  std::vector<Coordinates> neighbors;
  char center_file = center.getFile();
  std::size_t center_rank = center.getRank();

  //we are iterating through all of the neighboring squares and also excluding the original square from the iteration
  //we take all coordinates to the vector
  for(int neighbor_file_offset = -1; neighbor_file_offset <= 1; ++neighbor_file_offset)
  {
    for(int neighbor_rank_offset = -1; neighbor_rank_offset <= 1; ++neighbor_rank_offset)
    {
      if(neighbor_file_offset == 0 && neighbor_rank_offset == 0) continue;
      char current_file = center_file + neighbor_file_offset;
      std::size_t current_rank = center_rank + neighbor_rank_offset;
      if(current_file >= 'A' && current_file <= 'H' && 
         current_rank >= 1 && current_rank <= 8)
      {
        Coordinates neighbor(current_file, current_rank);
        neighbors.push_back(neighbor);
      }
    }
  }
  //we check if there is a piece
  //we check if it is not a pawn
  //we check if it has shield
  //we capture it
  for(const auto& pos : neighbors)
  {
    if(game->getBoard().getSquare(pos)->hasPiece())
    {
      Piece* piece = game->getBoard().getSquare(pos)->getPiece();
      if(piece->checkShield())
      {
        //do nothig, shield is automatically removed in the checkShield()
      }
      else if(piece->getType() != PieceType::Pawn)
      {
        std::unique_ptr<Piece> captured_piece = game->getBoard().getSquare(pos)->releasePiece();
        game->getCurrentPlayer()->addPieceToPrison(std::move(captured_piece));
      }
    }
  }
  std::unique_ptr<Piece> captured_piece = game->getBoard().getSquare(center)->releasePiece();
  game->getCurrentPlayer()->addPieceToPrison(std::move(captured_piece));
  bool current_player_king_captured = game->currentPlayerKingCaptured();
  bool opponnent_king_captured = game->opponentKingCaptured();
  if(current_player_king_captured && opponnent_king_captured)
  {
    game->setGameState(GameState::BOTH_KINGS_CAPTURED_DRAW);
  }
  //basically we only have to check the case when two kings are captured
  //if only one king is captured it will be caught in the game loop after execution of the power
  game->reduceMana(mana_cost_);
}

bool ExplosivePawnPower::wrongTargetSquare(Game* game)
{
  if(!game->getBoard().getSquare(target_square_)->hasPiece())
  {
    return true;
  }
  if(game->getBoard().getSquare(target_square_)->getPiece()->getOwner()->getId() ==
     game->getCurrentPlayer()->getId() ||
     !game->getBoard().getSquare(target_square_)->getPiece()->canBeCaptured(PieceType::Pawn))
  {
    return true;
  }
  size_t file_difference = std::abs(target_square_.getFile() - pawn_square_.getFile());
  int rank_difference = static_cast<int>(target_square_.getRank()) - static_cast<int>(pawn_square_.getRank());
  if(file_difference != 1)
  {
    return true;
  }
  if(game->getCurrentPlayer()->getId() == WHITE_ID && rank_difference != 1)
  {
    return true;
  }
  else if(game->getCurrentPlayer()->getId() == BLACK_ID && rank_difference != -1)
  {
    return true;
  }
  return false;
}
