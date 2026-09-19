//---------------------------------------------------------------------------------------------------------------------
/// Impatient pawn's special power. Validates target piece, promotes the pawn to the target piece.
//---------------------------------------------------------------------------------------------------------------------
#ifndef IMPATIENT_PAWN_POWER
#define IMPATIENT_PAWN_POWER
#include "ActivePower.hpp"

class Game;
struct UserInputSpecial;

class ImpatientPawnPower : public ActivePower
{
  protected:
    std::size_t rank_difference_;
    std::size_t target_piece_value_;
    std::size_t opponents_back_rank_;
    char promote_to_;//type of piece to promote to
    char piece_color_;//to identify opponent back rank
    std::size_t rank_;//current rank of the pawn
    Coordinates square_;
    static constexpr std::size_t NUMBER_EXPECTED_PARAMETERS_ = 2;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor.
    ImpatientPawnPower();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    ImpatientPawnPower(const ImpatientPawnPower& power) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    ~ImpatientPawnPower() = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Main method of the class. Executes the special power.
    /// @param game pointer to the game object
    /// @param user_input_special struct with the necessary information from user
    void usePower(Game* game, UserInputSpecial& user_input_special) override;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Identifies amount of mana needed for the power.
    /// @return amount of required mana
    std::size_t distinguishManaCost() override;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Identifies and sets a target piece value.
    void setTargetPieceValue();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks that the target piece type is appropriate.
    /// @return true if it is the case, false otherwise
    bool wrongTargetPiece();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Identifies opponent's back rank, calculates rank difference, initialises according member.
    void setRankDifference();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets the information from the struct and sets it to the internal variables of the class.
    /// @param game pointer to the game object
    /// @param user_input_special struct the information is taken from
    void setContext(Game* game, UserInputSpecial& user_input_special);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns number of parameters that the special power requires.
    /// @return number of the required parameters
    std::size_t getNumberExpectedParameters() override
    {
      return NUMBER_EXPECTED_PARAMETERS_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Validates the parameters required for the power.
    /// @param parameters vector with parameters as strings
    /// @param user_input_special struct where the parameters will be saved after validation
    /// @param error_messages map of the error messages
    void checkParameters(std::vector<std::string> parameters, UserInputSpecial& user_input_special,
      std::map<ErrorType, std::string>& error_messages) override;
};

#endif
