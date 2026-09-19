//---------------------------------------------------------------------------------------------------------------------
/// Implements boost square. Gives additional turn to the current player.
//---------------------------------------------------------------------------------------------------------------------
#include "BoostSquare.hpp"
#include "Coordinates.hpp"
#include "Game.hpp"

BoostSquare::BoostSquare (Coordinates coordinates): Square(SquareType::BOOST_SQUARE, coordinates) {}

void BoostSquare::additionalTurn(Game &game)
{
  if(piece_ != nullptr)
  {
    game.setAdditionalMove(true);
  }
}
