//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Queen class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power.
//----------------------------------------------------------------------------------------------------------------------


#ifndef FLIPPER_QUEEN_HPP
#define FLIPPER_QUEEN_HPP
#include "Queen.hpp"
#include "FlipperQueenPower.hpp"

class FlipperQueen : public Queen
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a FlipperQueen object and initializes its member variables 
    FlipperQueen();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a FlipperQueen
    /// @param piece FlipperQueen that should be copied
    FlipperQueen(const FlipperQueen& piece) : Queen(piece) {};

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the FlipperQueen class set to default
    ~FlipperQueen() override = default;
};

#endif
