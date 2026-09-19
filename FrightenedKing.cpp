//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the King class and checks FrightenedKing-specific movement 
/// and capture rules and excecutes the move.
//----------------------------------------------------------------------------------------------------------------------


#include "FrightenedKing.hpp"
#include "Conditions.hpp"

FrightenedKing::FrightenedKing() : King("KFRT", SpecialPowerType::Passive, "♚kf") {}

bool FrightenedKing::isMoveValid(Board& board, Square* target_square)
{
  if (!King::isMoveValid(board, target_square))
  {
    return false;
  }
  if(target_square->getPiece() != nullptr)
  {
    if(Conditions::isKingInCheck(board, this->getOwner()))
    {
      return false;
    }
  }
  return true;
}

void FrightenedKing::move(Game& game, bool is_capture, Square *target_square, std::optional<char> promote_to)
{
  if(Conditions::isKingInCheck(game.getBoard(), this->getOwner()))
  {
    game.setAdditionalMove(true);
  }  
  King::move(game, is_capture, target_square, promote_to);
}
