//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Pawn class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#include "ExplosivePawn.hpp"

ExplosivePawn::ExplosivePawn() : Pawn("PEXP", SpecialPowerType::Active, "♟p!")
  {
    this->power_ = std::make_unique<ExplosivePawnPower>();//adding power
  }
  