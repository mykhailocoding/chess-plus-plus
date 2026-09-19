//----------------------------------------------------------------------------------------------------------------------
/// This class represents the game that is being played and handles all related tasks.
//----------------------------------------------------------------------------------------------------------------------

#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Board.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"
#include "CommandParser.hpp"
#include "ConfigParser.hpp"

#include <array>
#include <functional>
#include <memory>
#include <iostream>
#include <format>
#include <string_view>

const std::size_t INITIAL_TURN_COUNT = 0;

class Piece;
class Player;
class ConfigParser;
enum class ErrorType;

enum class GameState
{
  PLAY,
  QUIT,
  NORMAL_WIN,
  RESIGNATION_WIN,
  DRAW_COMMAND_DRAW,
  MAX_TURN_COUNT_REACHED_DRAW,
  STALEMATE_RESIGNATION_DRAW,
  BOTH_KINGS_CAPTURED_DRAW
};

class Game
{
  protected:
    static const std::string DRAW_COMMAND_MESSAGE_;
    static const std::string MAX_TURN_COUNT_REACHED_MESSAGE_;
    static const std::string STALEMATE_RESIGNATION_MESSAGE_;
    static const std::string BOTH_KINGS_CAPTURED_MESSAGE_;

    ConfigParser& config_parser_;
    CommandParser command_parser_;
    std::size_t max_turn_count_;
    std::size_t mana_pool_;
    std::array<std::shared_ptr<Player>, 2> players_;
    Board& board_;
    std::size_t current_turn_;
    Player* current_player_;
    Player* winner_;
    Piece* current_piece_;
    bool additional_move_;
    bool passive_command_;
    GameState state_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a Game object and initializes its member variables.
    /// @param config_parser reference to the config parser object to have access to the data loaded from the configs
    Game(ConfigParser &config_parser);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    Game(const Game& game) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~Game() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the CommandParser object to get user input.
    /// @return Reference to the CommandParser object.
    CommandParser& getCommandParser();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the description mapping read from the config file.
    /// @return Reference to the description map.
    std::map<std::string, std::string>& getDescriptionMapping();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the error message mapping read from the config file.
    /// @return Reference to the error message map.
    std::map<ErrorType, std::string>& getErrorMessages();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the piece name mapping read from the config file.
    /// @return Reference to the piece name map.
    std::map<std::string, std::string>& getPieceIdNameMapping();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the piece info mapping read from the config file.
    /// @return Reference to the piece info map.
    std::map<std::string, std::string>& getPieceIdInfoMapping();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the piece special syntax mapping read from the config file.
    /// @return Reference to the piece special syntax map.
    std::map<std::string, std::string>& getPieceIdSyntaxMapping();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the current turn count.
    /// @return Current turn count.
    std::size_t getCurrentTurn();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the maximum turn count.
    /// @return Maximum turn count.
    std::size_t getMaxTurnCount();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the maximum mana of a player.
    /// @return Maximum mana amount of a player.
    std::size_t getManaPool();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the Board object.
    /// @return Reference to the Board.
    Board& getBoard();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the white player.
    /// @return Reference to the white Player object.
    Player& getWhitePlayer();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the black player.
    /// @return Reference to the black Player object.
    Player& getBlackPlayer();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the opponent player.
    /// @return Reference to the opponent Player object.
    Player& getOpponent();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the player that resigned.
    /// @return Reference to the resigning Player object.
    Player& getResigner();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the current player.
    /// @return Pointer to the current player.
    Player* getCurrentPlayer();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the current piece.
    /// @return Pointer to the current piece.
    Piece* getCurrentPiece();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the current game state.
    /// @return Game state.
    GameState getGameState();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a setter method for the current piece.
    /// @param piece pointer to the new current piece
    void setCurrentPiece(Piece* piece);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a setter method for the game state.
    /// @param state new game state
    void setGameState(GameState state);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function sets the winner.
    /// @param winner pointer to the player
    void setWinner(Player* winner);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a setter method for keeping track if the player has an additional turn or not.
    /// @param value true if the player has an additional turn and false if not
    void setAdditionalMove(bool value);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a setter method for keeping track if the player entered a passive command or not.
    /// @param value true if the player entered a passive command and false if not
    void setPassiveCommand(bool value);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the current player's additional turn.
    /// @return True if the player has an additional turn and false if not.
    bool AdditionalMove();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is responsible for handling the main game loop-
    void start();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function prints the welcome message to the terminal.
    void printWelcome();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function calls other functions to place all pieces on the board.
    void placePieces();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function counts how many pieces of same type are in a vector.
    /// @param piece reference to the piece that needs to be counted
    /// @param pieces vector of pieces
    /// @return Number of pieces of the same type in the vector.
    std::size_t countPieces(const Piece& piece, const std::vector<std::unique_ptr<Piece>>& pieces);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function handles the logic of changing the current player and updates the game state accordingly.
    void getNextPlayer();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function checks if a king has been captured.
    bool checkWin();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function calculates and prints the elo scores after the game has ended.
    /// @param output_stream reference to the output stream that the message should be printed to
    void calculateEloScores(std::ostream& output_stream);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function handles the logic of spawning an item with a spawn square.
    void spawnItems();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function prints the message necessary when a normal win occured.
    /// @param output_stream reference to the output stream that the message should be printed to
    void printNormalWin(std::ostream& output_stream);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function prints the message necessary when a resignation occured.
    /// @param output_stream reference to the output stream that the message should be printed to
    void printResignation(std::ostream& output_stream);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function prints the message necessary when a draw occured.
    /// @param output_stream reference to the output stream that the message should be printed to
    /// @param cause reason of the draw as a string
    void printDraw(std::ostream& output_stream, std::string cause);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function prints the history of game.
    /// @param output_stream reference to the output stream that the message should be printed to
    void printHistory(std::ostream& output_stream);
    
    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function reduces mana of the current player by the amount specified.
    /// @param mana_cost amount of mana the player lost
    void reduceMana(size_t mana_cost);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function checks if the king of the current player has been captured.
    /// @return True if the king has been captured and false if not
    bool currentPlayerKingCaptured();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function checks if the king of the current opponent player has been captured.
    /// @return True if the king has been captured and false if not.
    bool opponentKingCaptured();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function promotes a pawn to another piece if it reached the opponent's back rank.
    /// @param board reference to the Board object
    /// @param pawn_position coordinates of the square the pawn moved to
    /// @param promote_to character according to what piece the pawn promotes to
    void promote(Board& board, Coordinates pawn_position, char promote_to);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function updates the status of the player after checking if the player is in a check, checkmate or
    ///        a stalemate.
    /// @param player pointer to the player whose status needs to be checked
    /// @return Current status of the player after evaluating
    PlayerStatus checkPlayerStatus(Player* player);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function handles the logic of ending the game.
    void endGame();

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function saves the history into a file.
    void saveGame();
};

#endif
