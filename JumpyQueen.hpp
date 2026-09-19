//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Queen class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#ifndef JUMPY_QUEEN_HPP
#define JUMPY_QUEEN_HPP
#include "Queen.hpp"
#include "JumpyQueenPower.hpp"

class JumpyQueen : public Queen
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a JumpyQueen object and initializes its member variables 
    JumpyQueen();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a JumpyQueen
    /// @param piece JumpyQueen that should be copied
    JumpyQueen(const JumpyQueen& piece) : Queen(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the JumpyQueen class set to default
    ~JumpyQueen() override = default;
};

#endif
