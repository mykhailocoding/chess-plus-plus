//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Bishop class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#ifndef PREACHER_BISHOP_HPP
#define PREACHER_BISHOP_HPP
#include "Bishop.hpp"
#include "PreacherBishopPower.hpp"

class PreacherBishop : public Bishop
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a PreacherBishop object and initializes its member variables 
    PreacherBishop();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a PreacherBishop
    /// @param piece PreacherBishop that should be copied
    PreacherBishop (const PreacherBishop& piece) : Bishop(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the PreacherBishop class set to default
    ~PreacherBishop() override = default;
};

#endif
