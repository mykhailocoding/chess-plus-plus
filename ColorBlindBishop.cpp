//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Bishop class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power.
//----------------------------------------------------------------------------------------------------------------------


#include "ColorBlindBishop.hpp"

ColorBlindBishop::ColorBlindBishop() : Bishop("BCLR", SpecialPowerType::Active, "♝bc")
  {
    this->power_ = std::make_unique<ColorBlindBishopPower>(this);//adding power
  }
  
