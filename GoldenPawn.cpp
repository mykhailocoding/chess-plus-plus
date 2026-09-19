//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Pawn class and checks GoldenPawn-specific movement 
/// and capture rules and excecutes the move.
//----------------------------------------------------------------------------------------------------------------------


#include "GoldenPawn.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "Square.hpp"

GoldenPawn::GoldenPawn() : Pawn("PGLD", SpecialPowerType::Passive, "♟pg"), on_the_last_row_(false) {}

void GoldenPawn::move(Game &game, bool is_capture, Square *target_square, std::optional<char> promote_to)
{
  Player *opponent_player = &game.getOpponent();
  int target_row = target_square->getCoordinates().getRank();

  int back_rank_opponent ;
  if (opponent_player->getId() == WHITE_ID)
  {
    back_rank_opponent = 1;
  }
  else  
  {
    back_rank_opponent = 8;
  }

  if (((target_row != back_rank_opponent) && (promote_to.has_value()))||
      ((target_row == back_rank_opponent) && (!promote_to.has_value())))
  {
    throw CustomException(game.getErrorMessages().at(ErrorType::INVALID_MOVE));
  }

  Piece::move(game, is_capture, target_square, promote_to);

  if ((target_row == back_rank_opponent) && (promote_to.has_value()))
  {
    game.setGameState(GameState::NORMAL_WIN);
    game.setWinner(game.getCurrentPlayer());
  }
}
