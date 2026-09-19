//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the King class and checks FrightenedKing-specific movement 
/// and capture rules and excecutes the move.
//----------------------------------------------------------------------------------------------------------------------


#ifndef FRIGHTENED_KING_HPP
#define FRIGHTENED_KING_HPP
#include "King.hpp"

class FrightenedKing : public King
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a FrightenedKing object and initializes its member variables 
    FrightenedKing();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a FrightenedKing
    /// @param piece FrightenedKing that should be copied
    FrightenedKing(const FrightenedKing& piece) : King(piece) {};

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the FrightenedKing class set to default
    ~FrightenedKing() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the attempet move is allowed onto to the target square
    /// @param board current state of the game board
    /// @param target_square square the FrightenedKing intends to move to
    /// @return returns true if the move is allowed according to FrightenedKing rules, otherwise false
    bool isMoveValid(Board& board, Square* target_square) override;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief excecutes the move for a FrightenedKing 
    /// @param game game being currently played on
    /// @param is_capture indicates wether the the intended move is a capture move or not
    /// @param target_square square the FrightenedKing intends to move to
    /// @param promote_to defines into what piece a pawn is promooted to when he reaches the back rank of the opponent
    void move(Game& game, bool is_capture, Square *target_square, std::optional<char> promote_to) override;
};

#endif
