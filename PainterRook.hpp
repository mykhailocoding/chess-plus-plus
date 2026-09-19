//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Rook class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#ifndef PAINTER_ROOK_HPP
#define PAINTER_ROOK_HPP
#include "Rook.hpp"
#include "PainterRookPower.hpp"

class PainterRook : public Rook
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a PainterRook object and initializes its member variables 
    PainterRook();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a PainterRook
    /// @param piece PainterRook that should be copied
    PainterRook(const PainterRook& piece) : Rook(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the PainterRook class set to default
    ~PainterRook() override = default;
};

#endif
