//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Pawn class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#include "NervousPawn.hpp"

NervousPawn::NervousPawn() : Pawn("PNRV", SpecialPowerType::Active, "♟p-")
  {
    this->power_ = std::make_unique<NervousPawnPower>();//adding power
  }
