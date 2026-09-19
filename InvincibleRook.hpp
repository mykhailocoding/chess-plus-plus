//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Rook class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#ifndef INVINCIBLE_ROOK_HPP
#define INVINCIBLE_ROOK_HPP
#include "Rook.hpp"
#include "InvincibleRookPower.hpp"

class InvincibleRook : public Rook
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a InvincibleRook object and initializes its member variables 
    InvincibleRook();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a InvincibleRook
    /// @param piece InvincibleRook that should be copied
    InvincibleRook(const InvincibleRook& piece) : Rook(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the InvincibleRook class set to default
    ~InvincibleRook() override = default;
};

#endif
