//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Bishop class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power.
//----------------------------------------------------------------------------------------------------------------------


#ifndef COLOR_BLIND_BISHOP_HPP
#define COLOR_BLIND_BISHOP_HPP
#include "Bishop.hpp"
#include "ColorBlindBishopPower.hpp"

class ColorBlindBishop : public Bishop
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a ColorBlindBishop object and initializes its member variables 
    ColorBlindBishop();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a ColorBlindBishop
    /// @param piece ColorBlindBishop that should be copied
    ColorBlindBishop(const ColorBlindBishop& piece) : Bishop(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the ColorBlindBishop class set to default
    ~ColorBlindBishop() override = default;
};

#endif
