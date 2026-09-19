//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the base Piece class and implements checks for king-specific movement 
/// and capture rules
//----------------------------------------------------------------------------------------------------------------------


#ifndef KING_HPP
#define KING_HPP
#include "Piece.hpp"

class Square;
class Board;

class King : public Piece
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a King object and initializes its member variables 
    King();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructs a new King object with specific attributes 
    /// @param id string identifier for the piece 
    /// @param special_power_type classification of the piece's special power 
    /// @param short_name visual representation of the piece on the board
    King(std::string id, SpecialPowerType special_power_type, std::string short_name);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a King
    /// @param piece King that should be copied
    King(const King& piece) : Piece(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is explicitly declared as a default destructor and made virtual so the subclasses can also
    ///        correctly delete themselves.
    virtual ~King() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the attempet move is allowed onto to the target square
    /// @param board current state of the game board
    /// @param target_square square the King intends to move to
    /// @return returns true if the move is allowed according to King rules, otherwise false
    bool isMoveValid(Board& board, Square* target_square)override;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief has to be overwritten here because of special rules and occurrences if a castling is done 
    /// (rook is moved as well)
    /// @param game game being currently played on
    /// @param is_capture indicates wether the the intended move is a capture move or not
    /// @param target_square square the King intends to move to
    /// @param promote_to ignored for the King, but has to be handed over so no compiler warning or errors occur
    void move(Game &game, bool is_capture, Square *target_square, std::optional<char> promote_to) override;

    /// @brief checks if the conditions for an attempted castling move are met
    /// @param board current state of the game board
    /// @param source_row current row index of the King
    /// @param source_column current column index of the King
    /// @param target_column destination column index of the King
    /// @return returns true if the attempted castling move is legal otherwise false
    bool checkCastlingConditions(Board &board, int source_row, int source_column, int target_column);
};

#endif
