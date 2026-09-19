//---------------------------------------------------------------------------------------------------------------------
/// Freeze potion. Validates the target square, freezes the targeted piece for 1 turn(excluding the current one).
//---------------------------------------------------------------------------------------------------------------------
#ifndef FREEZE_POTION_HPP
#define FREEZE_POTION_HPP
#include "Potion.hpp"

class FreezePotion : public Potion
{
  protected:
    Coordinates square_;
    Coordinates target_square_;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 2;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor.
    FreezePotion();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    FreezePotion(const FreezePotion& potion) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~FreezePotion() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Main method of the class. Executes the effects of the potion.
    /// @param game pointer to the game object
    /// @param input struct where the user intput is stored
    void usePotion(Game* game, UserInputUse& input) override;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if there is a piece on the target square.
    /// @param game pointer to the game object
    /// @return false if the square is correct, true otherwise
    bool wrongTargetSquare(Game* game);

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
