//----------------------------------------------------------------------------------------------------------------------
/// This class is responsible for validating and executing the effects of the MoveCommand.
//----------------------------------------------------------------------------------------------------------------------

#ifndef MOVECOMMAND_HPP
#define MOVECOMMAND_HPP

#include "Command.hpp"
#include "Coordinates.hpp"
#include "Piece.hpp"

#include <optional>
#include <format>

class MoveCommand : public Command
{
  private:
    static constexpr std::string_view USER_INPUT_CANCEL_ = "CANCEL";
    static constexpr std::string_view AMBIGUOUS_HISTORY_FORMAT_ = "{}{}:";

    Coordinates target_square_;
    PieceType piece_type_;
    std::optional<char> promote_pawn_to_; // cannot be 'P' or 'K'
    std::optional<char> pawn_file_;
    bool is_capture_;
    std::vector<Piece*> possible_pieces_;
    bool is_ambiguous_;
    std::string move_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a MoveCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    MoveCommand(Game& game);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    MoveCommand(const QuitCommand&) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~MoveCommand() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the MoveCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function calls the correct function to read, validate and store the parameters specified by
    ///        the user for the move.
    /// @param move move as a string entered by the user
    void parseParameters(std::string move);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function parses and validates coordinate from user input and initializes the correct variable.
    /// @param coordinate possible coordinate entered by the user
    /// @param square reference to the variable where the square should be stored
    void parseCoordinates(std::string coordinate, Coordinates& square) override;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function parses and validates the syntax for a normal move for any piece other than a pawn
    /// @param move move as a string entered by the user
    void parseMove(std::string move);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function parses and validates the syntax for a capture.
    /// @param move move as a string entered by the user
    void parseCapture(std::string move);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function parses and validates the syntax for a pawn capture.
    /// @param move move as a string entered by the user
    void parsePawnPromotion(std::string move);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function parses and validates the syntax for a pawn capture and promotion.
    /// @param move move as a string entered by the user
    void parsePawnCapturePromotion(std::string move);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is called when a move is ambiguous and needs more validation to execute the move.
    void handleAmbiguousMove();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to update the current player's history.
    void updateHistory() override;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function determines all pieces of the current player that could theoretically perform the move.
    void determinePossiblePieces();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function executes the effect of the move command and updates the game state accordingly.
    /// @param piece pointer to the piece that is being moved
    void executeMove(Piece* piece);
};

#endif
