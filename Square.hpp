//---------------------------------------------------------------------------------------------------------------------
/// Base class for the squares. Contains constructor, deep copy constructor, default virtual destructor, methods for
/// printing, copy method, and methods for handling of the pieces.
//---------------------------------------------------------------------------------------------------------------------
#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <memory>
#include "Piece.hpp"
#include "Game.hpp"
#include "Coordinates.hpp"
#include <iostream>
#include <string>
#include <format>

class Coordinates;
class Piece;

enum class SquareType
{
  BASIC_WHITE,
  BASIC_BLACK,
  MANA_SQUARE,
  BOOST_SQUARE,
  SPAWN_SQUARE,
};

class Square
{
  protected:
    SquareType type_;
    std::unique_ptr<Piece> piece_ ;
    Coordinates coordinates_;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor.
    /// @param type type of the square
    /// @param coordinates coordinates of the square
    Square(SquareType type, Coordinates coordinates);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Implements deep copy.
    /// @param square square to copy
    Square (const Square& square);
    
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    virtual ~Square() = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Base method for printing the square, takes pieces and items into account.
    /// @param game pointer to the game object
    virtual void print(Game &game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets background color of the square depending on the type.
    /// @return code for the backgroung color as a string
    virtual std::string getBackgroundColor() const;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Implements the logic of the item symbol. Considers king status as well.
    /// @param game pointer to the game object
    /// @return code for the item symbol as a string
    virtual std::string getItemSymbol(Game &game) const;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns a raw pointer of the piece on the square.
    /// @return raw pointer to the piece
    Piece* getPiece();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Sets(moves) the piece on the square.
    /// @param piece piece to set
    virtual void setPiece(std::unique_ptr<Piece> piece);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Allows to move the piece(unique pointer).
    /// @return unique pointer to the released piece
    std::unique_ptr<Piece> releasePiece();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets coordinates of the square.
    /// @return coordinates object
    Coordinates getCoordinates();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if there is a piece on the square.
    /// @return true if that is the case, false otherwise
    bool hasPiece();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the square is special.
    /// @return true if thats the case, false otherwise
    bool isSpecialSquare();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets the type of the square.
    /// @return type of the square
    SquareType getType();
};

#endif
