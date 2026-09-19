//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Pawn class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#ifndef NERVOUS_PAWN_HPP
#define NERVOUS_PAWN_HPP
#include "Pawn.hpp"
#include "NervousPawnPower.hpp"

class NervousPawn : public Pawn
{ 
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a NervousPawn object and initializes its member variables
    NervousPawn();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a IceKnight
    /// @param piece NervousPawn that should be copied
    NervousPawn(const NervousPawn& piece) : Pawn(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the NervousPawn class set to defaul
    ~NervousPawn() override = default;
};

#endif
