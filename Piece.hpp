//----------------------------------------------------------------------------------------------------------------------
/// creates the base class for all pieces ( basic pieces special pieces and passive pieces) and excecutes the basic  
/// movements of the pieces and promotes pawns if they reach the backrank of the oppononent as well as stop the game 
/// if a goldenPawn reaches the back rank
//----------------------------------------------------------------------------------------------------------------------


#ifndef PIECE_HPP
#define PIECE_HPP

#include "Coordinates.hpp"
#include "Player.hpp"
#include "Item.hpp"

#include <string>
#include <memory>
#include <cctype>
#include <iostream>
#include <optional>

//forward declarations
class ActivePower;
class Board;
class Square;
class Game;
class Item;

enum class PieceType
{
  Pawn,
  Rook,
  Knight,
  Bishop,
  Queen,
  King
};

enum class SpecialPowerType
{
  None,
  Passive,
  Active
};

class Piece
{
  protected:
    PieceType piece_type_;
    std::string id_;
    Player* owner_ = nullptr;
    std::unique_ptr<ActivePower> power_;
    std::string short_name_;
    std::size_t value_;//how much does a piece cost(power points e.g. queen - 9 points)
    Coordinates coordinates_ ;
    std::size_t frozen_counter_;
    std::size_t invincible_counter_;
    std::unique_ptr<Item> item_;
    SpecialPowerType special_power_type_;
    Parity parity_;
    bool first_move_;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructs a new Piece object with specific attributes 
    /// @param piece_type defines what kind of piece ic created 
    /// @param id string identifier for the piece 
    /// @param value piece cost
    /// @param special_power_type classification of the piece's special power 
    /// @param short_name visual representation of the piece on the board 
    Piece(PieceType piece_type, std::string id, std::size_t value, SpecialPowerType special_power_type, std::string short_name);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a Piece
    /// @param piece Piece that should be copied
    Piece(const Piece& piece);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor overwritten in subclasses 
    virtual ~Piece();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief operator overload for == 
    /// @param rhs 
    bool operator==(const Piece& rhs) const;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief getter for the member id
    /// @return returns member id_
    std::string getId() const { return id_; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief getter for protected member power_
    /// @return raw pointer of an object of the type ActivePower 
    ActivePower* getPower()
    {
      return power_.get();
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief setter for protected member new_coords_
    void setCoordinates(const Coordinates& new_coords);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual setter for the protected member owner_
    virtual void setOwner(Player* owner); // should call setShortName() to set the correct name

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief getter for the protected member item_
    /// @return raw pointer of an object of the type Item
    Item* getItem() { return item_.get(); }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief adds  an item to the piece 
    /// @param item item that is added to the piece 
    void addItem(std::unique_ptr<Item> item);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief gives information if a piece currently has an item 
    /// @return return true if the piece has an item otherwise false
    bool hasItem() const;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief removes an item from a piece
    void removeItem();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief the pieces releases the item it currently holds
    /// @return the pointer of the item that was released
    std::unique_ptr<Item> releaseItem();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief sets the protected member accordingly 
    /// @param parity the value the variable should be set to 
    void setParity(Parity parity);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief used for printing gives information if a piece ha an invisibility Cloak or not
    /// @return true if the piece holds a cloak otherwise false
    bool hasInvisibilityCloak() const;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief used for validating queen capture
    /// @return retruns true if the queen has a repellant othwerwise false 
    bool hasQueenRepellant() const;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief gives information if a piece has a shield or not 
    /// @return returns true if the piece has a shield otherwise false 
    bool hasShield() const;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief gives information if the piece has a shield and deletes the item (used for every capture)
    /// @return return true if the piece has a shield otherwise false
    bool checkShield();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief setter for the protected memebr first_move_
    /// @param value the value the variable should be set to 
    void setFirstMove(bool value) { first_move_ = value; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief getter for the foreground color of the piece 
    /// @return return the string for white or black pieces to show on the board
    virtual std::string getFGColor() const;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief getter for the protected memebr owner_ of the piece
    /// @return return a pointer of the owner 
    Player* getOwner () {return owner_;}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief getter for the visual representation of the piece
    /// @return returns the string for the visual representation of the piece
    std::string getShortName() {return short_name_;}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief pure virtual method overwritten in subclasses return if a attempted move is valid according to
    /// its piece_specific movement and capture rules     
    /// @param board current state of the game board
    /// @param target_square square the piece intends to move to
    /// @return returns true if the move is allowed according to piece_specific rules, otherwise false
    virtual bool isMoveValid(Board& board, Square* target_square)= 0;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks that it is a first move of the piece.
    /// @return true if that is the case, false otherwise
    bool isFirstMove() const { return first_move_; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief excecutes the move for all pieces (generic) for some pieces with special ocurrences 
    /// the method is overwritten
    /// @param game game being currently played on
    /// @param is_capture indicates wether the the intended move is a capture move or not
    /// @param target_square square the piece intends to move to
    /// @param promote_to used if a move with a pawn ends at the back rank of the opponent to promote the pawn
    virtual void move(Game &game,  bool is_capture, Square* target_square,  std::optional<char> promote_to);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief getter for the privte member frozen_counter_
    /// @return return an integer of the current frozent_counter_ status of the piece
    int getFrozenCounter() const {return static_cast<int> (frozen_counter_);}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief setter for the member invinible counter 
    /// @param turn the value the variable should be set to
    void setInvincible(std::size_t turns) { invincible_counter_ = turns; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief setter for the member frozen_counter_
    /// @param turns the value the member should be set to
    void setFrozen(std::size_t turns) { frozen_counter_ = turns; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief updates the counters at the end of the turn in the game for forzen_counter_ and invincible_counter_
    void updateCounters();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief gives information about if a piece could be captured or not 
    /// @param type type of the piece that should be checked if it can be captured 
    /// @return returns true if the piece could be captured otherwise false 
    virtual bool canBeCaptured(PieceType type);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief gives information if a piece can move or not 
    /// @param game game being currently played on
    ///@return returns true if the piece can move otherwise false 
    virtual bool canMove(Game* game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief getter for the member value_
    /// @return value of the piece as size_t
    std::size_t getValue() const 
    {
      return value_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief getter for the member piece_type_
    /// @return return the type of the piece
    PieceType getType()
    {
      return piece_type_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief reduces the frozen_counter_ of a piece
    void reduceFrozenCounter();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief gives information if a piece has special powers 
    /// @return return true if the pieces has special powers otherwise false
    bool hasSpecialPower();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief gives information if the piece is currently frozen or not
    /// @return returs ture if the piece is frozen otherwise false
    bool isFrozen();    

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief getter for the member coordinates_
    /// @return return the coordinates of the game 
    Coordinates getCoordinates() {return coordinates_;}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief gives information if a piece currently has a potion or not
    /// @return returns true if the piece has a potion otherwise false 
    bool hasPotion();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief gives information if the piece is currently invincible or not 
    /// @return returns true if a piece is invincible otherwise false 
    bool isInvincible();
};

#endif
