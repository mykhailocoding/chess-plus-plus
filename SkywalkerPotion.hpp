//---------------------------------------------------------------------------------------------------------------------
/// Skywalker potion. Pushes the piece directly in front of the activating piece (relative to the player’s forward
/// direction) one square backward. If multiple pieces are aligned behind it, they are pushed as well. The command
/// fails if there is no piece to push or if the last piece is already on the final rank.
//---------------------------------------------------------------------------------------------------------------------
#ifndef SKYWALKER_POTION_HPP
#define SKYWALKER_POTION_HPP
#include "Potion.hpp"

class SkywalkerPotion : public Potion
{
  protected:
    std::size_t back_rank_;
    Coordinates square;
    std::size_t amount_pieces_to_push_;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 1;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor.
    SkywalkerPotion();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    SkywalkerPotion(const SkywalkerPotion& potion) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~SkywalkerPotion() override = default;
    
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Main method of the class. Executes the effects of the potion.
    /// @param game pointer to the game object
    /// @param input struct where the user intput is stored
    void usePotion(Game* game, UserInputUse& input) override;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Identifies the back rank of the current player.
    /// @param game pointer to the game object
    void setBackRank(Game* game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks that there is a piece directly infront of the activating piece and that if there are several
    /// pieces one after another the last one is not on the back rank.
    /// @param game pointer to the game object
    /// @return false if it is possible to push piece(s), true otherwise
    bool canNotPush(Game* game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Moves the pieces one square backward.
    /// @param game pointer to the game object
    void push(Game* game);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the potion requires.
    /// @return number of the required parameters
    std::size_t getNumberExpectedParameters() override
    {
      return NUMBER_EXPECTED_PARAMETERS_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Validates the parameters required to use the potion. All parameters are valid since the numbers is
    /// checked already and technically this function is never called. But we have to implement it since it is virtual.
    /// Therefore [[maybe_unused]].
    /// @param parameters vector of the string where the parameters are
    /// @param user_input_use struct where the parameters will be stored after validation
    /// @return true if the parameters are correct, false otherwise
    bool validParameters([[maybe_unused]] std::vector<std::string> parameters,
      [[maybe_unused]] UserInputUse& user_input_use) override { return true; }
};

#endif
