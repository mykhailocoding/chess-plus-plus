//---------------------------------------------------------------------------------------------------------------------
/// Implements spawn square. Contains a vector of unique pointers of items, spawns the item according to the logic
/// by copying the item from the vector.
//---------------------------------------------------------------------------------------------------------------------
#ifndef SPAWN_SQUARE_HPP
#define SPAWN_SQUARE_HPP
#include "Square.hpp"
#include "Coordinates.hpp"
#include "Game.hpp"
#include<vector>

class Item;
class Game;

class SpawnSquare: public Square
{
  private:
    std::vector<std::unique_ptr<Item>> items_;
    std::size_t next_item_index_;
    std::unique_ptr<Item> current_item_on_square_;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor.
    /// @param coordinates coordinates of the square
    SpawnSquare(Coordinates coordinates);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor. Implements a deep copy of the items vector and current item.
    /// @param square square to copy
    SpawnSquare(const SpawnSquare& square);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~SpawnSquare() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks conditions for spawning, creates a new item object copying it from the vector, moves it either
    /// to the piece on the square or to the current_item_on_square_.
    /// @param game pointer to the game object
    void spawnItem(Game &game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if there is an item on the square.
    /// @return true if that is the case, false otherwise
    bool hasItem();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Transfers ownership of the current item to the caller.
    /// @return a unique pointer to the released item
    std::unique_ptr<Item> releaseItem();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Implements the logic of the item symbol. Considers king status and the current item on the square.
    /// @param game pointer to the game object
    /// @return code for the item symbol as a string
    std::string getItemSymbol(Game &game) const override;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copies the items from the reference vector to the member vector.
    /// @param items reference vector
    void setItems(std::vector<std::unique_ptr<Item>>& items);
};

#endif
