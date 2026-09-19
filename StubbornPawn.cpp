//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Pawn class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#include "StubbornPawn.hpp"

StubbornPawn::StubbornPawn() : Pawn("PSTB", SpecialPowerType::Active, "♟p+")
  {
    this->power_ = std::make_unique<StubbornPawnPower>();//adding power
  }
