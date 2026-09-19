//---------------------------------------------------------------------------------------------------------------------
/// The Conditiosn class is written to help other classes check if a move or special command is allowed to be excecuted
/// though it does not check if the moves for a piece are correc it collects the possible pieces a move could be 
//  excecuted with. Other checks are also done (is a sqaure under attack,
//  is the path the piece wants to move along free). All methods are static, meaning they can be called directly 
///  without instantiating an object.
//---------------------------------------------------------------------------------------------------------------------

#ifndef CONDITIONS_HPP
#define CONDITIONS_HPP

#include <vector>
#include "Square.hpp"
#include "Game.hpp"
#include "Piece.hpp"
#include "Player.hpp"

class Conditions
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief  Constructor is deleted explicitly.
    Conditions() = delete;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy  Constructor is deleted explicitly.
    Conditions(const Conditions&) = delete;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief  Deconstructor is deleted explicitly.
    ~Conditions() = delete;
    
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Finds pieces of the specified type that are able to execute the move, iterating through the board and
    /// pushes them to the vector.
    /// @param game reference to the current gaame being played
    /// @param current_player pointer to the current player
    /// @param type specified type of the piece
    /// @return vector of the possible pieces
    static std::vector<Piece*> findPossiblePieces(Game& game, Player* current_player, PieceType type);
    
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief checks if a move ends with the king of the current player in check 
    /// @param game reference to the current gaame being played 
    /// @param target_square the square the player wants to move to
    /// @param source_square the sqaure the player wants to move from 
    /// @return returns true if the move results in a check of the king otherwise false
    static bool checkMoveResultInCheck(Game&  game, Square* target_square, Square* source_square);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief checcks if the King is currently in ckeck
    /// @param board the  board currently being played with 
    /// @param player the player whose King should bee checked
    /// @return returns true if the king is in check otherwise false
    static bool isKingInCheck(Board& board,Player* player );

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief checks if a square is under attack(a piece coould move to its coordinates)
    /// @param board the board currently being played with
    /// @param target_square the square that should be checked
    /// @return return true if the square is under attack otherwise false
    static bool checkIsSquareUnderAttack(Board& board, Square* target_square);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief checks if the path a piece wants to movve along is free  (not pieces are between source- & target-square)
    /// @param board the board currently being played with
    /// @param source_square the sqaure the player wants to move from 
    /// @param target_square the square the player wants to move to
    /// @return return true if the path is empty otherwise false
    static bool isPathClear(Board& board, Square* source_square, Square* target_square);
     
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if a specific player has at least one valid move available on the board.
    /// @param game the game currently being played with
    /// @param player the player whose moves should be checked
    /// @return returns true if the player can make at least one legal move, otherwise false
    static bool hasLegalMove(Game& game, Player& player);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the piece on the given source square has at least one valid destination on the board.
    /// It verifies both the piece's movement rules and ensures the move doesn't leave the king in check.
    /// @param game the game currently being played with 
    /// @param source_square the sqaure the player wants to move from
    /// @return returns true if the piece has at least one legal move, otherwise false
    static bool checkForLegalMoves(Game& game, Square* source_square);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief special method made for castling as isSquareUnderAttack method had no acces to the current player
    /// if a square is empty 
    /// @param board the board currently being played with
    /// @param target_square the square the player wants to move to
    /// @param current_player the player that wants to move a piece 
    /// @return return true if the empty square is under attack otherwise falsse 
    static bool isEmptySquareUnderAttack(Board &board, Square *target_square, Player* current_player);
};

#endif //CONDITIONS_HPP
