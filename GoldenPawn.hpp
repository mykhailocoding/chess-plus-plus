//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Pawn class and checks GoldenPawn-specific movement 
/// and capture rules and excecutes the move.
//----------------------------------------------------------------------------------------------------------------------


#ifndef GOLDEN_PAWN_HPP
#define GOLDEN_PAWN_HPP
#include "Pawn.hpp"

class Game;
class Square;

class GoldenPawn : public Pawn
{
  protected:
    bool on_the_last_row_;//when golden pawn reaches opponent's back rank, player wins the game
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a GoldenPawn object and initializes its member variables 
    GoldenPawn();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a GoldenPawn
    /// @param piece GoldenPawn that should be copied
    GoldenPawn(const GoldenPawn& piece) : Pawn(piece), on_the_last_row_(piece.on_the_last_row_) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the GoldenPawn class set to default
    ~GoldenPawn() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief excecutes the move for a GoldenPawn 
    /// @param game game being currently played on
    /// @param is_capture indicates wether the the intended move is a capture move or not
    /// @param target_square square the GoldenPawn intends to move to
    /// @param promote_to defines into what piece a pawn is promooted to when he reaches the back rank of the opponent
    void move(Game& game, bool is_capture, Square *target_square , std::optional<char> promote_to) override;
};

#endif
