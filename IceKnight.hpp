//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Knight class and excecutes IceKnight-specific movement 
/// and capture rules.
//----------------------------------------------------------------------------------------------------------------------


#ifndef ICE_KNIGHT_HPP
#define ICE_KNIGHT_HPP
#include "Knight.hpp"

class Square;

class IceKnight : public Knight
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a IceKnight object and initializes its member variables 
    IceKnight();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a IceKnight
    /// @param piece IceKnight that should be copied
    IceKnight(const IceKnight& piece) : Knight(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the IceKnight class set to default
    ~IceKnight() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief has to be overwritten here because of special occurences when an IceKnight is moved
    /// @param game game being currently played on
    /// @param is_capture indicates wether the the intended move is a capture move or not
    /// @param target_square square the IceKnight intends to move to
    /// @param promote_to ignored for the IceKnight, but has to be handed over because of the original method
    void move(Game& game, bool is_capture, Square *target_square , [[maybe_unused]] std::optional<char> promote_to) override;
};

#endif
