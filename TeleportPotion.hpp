//---------------------------------------------------------------------------------------------------------------------
/// Teleport potion. Validates the target square, teleports(moves) the piece there.
//---------------------------------------------------------------------------------------------------------------------
#ifndef TELEPORT_POTION_HPP
#define TELEPORT_POTION_HPP
#include "Potion.hpp"

class TeleportPotion : public Potion
{
  protected:
    Coordinates square_;
    Coordinates target_square_;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 2;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor.
    TeleportPotion();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    TeleportPotion(const TeleportPotion& potion) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~TeleportPotion() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Main method of the class. Executes the effects of the potion.
    /// @param game pointer to the game object
    /// @param input struct where the user intput is stored
    void usePotion(Game* game, UserInputUse& input) override;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Validates the target square. Piece could be teleported to ranks strictly before the rank of the farthest
    /// friendly piece toward the opponent’s side. The square is also invalid if it is occupied.
    /// @param game pointer to the game object
    /// @return false if the square is correct, true otherwise
    bool wrongTargetSquare(Game* game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Identifies the furthest rank on which the current player has a piece(relatively to the opponent back
    /// rank).
    /// @param game pointer to the game object
    /// @return the number of the furthest rank
    std::size_t identifyMaxrank(Game* game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the potion requires.
    /// @return number of the required parameters
    std::size_t getNumberExpectedParameters() override
    {
      return NUMBER_EXPECTED_PARAMETERS_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Validates the parameters required to use the potion.
    /// @param parameters vector of the string where the parameters are
    /// @param user_input_use struct where the parameters will be stored after validation
    /// @return true if the parameters are correct, false otherwise
    bool validParameters(std::vector<std::string> parameters, UserInputUse& user_input_use) override;
};

#endif
