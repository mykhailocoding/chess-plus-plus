//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Pawn class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#include "ImpatientPawn.hpp"

ImpatientPawn::ImpatientPawn() : Pawn("PIPT", SpecialPowerType::Active, "♟pi")
  {
    this->power_ = std::make_unique<ImpatientPawnPower>();//adding power
  }
