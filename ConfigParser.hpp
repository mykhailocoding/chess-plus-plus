//----------------------------------------------------------------------------------------------------------------------
/// This class is responsible for parsing the provided config files.
//----------------------------------------------------------------------------------------------------------------------

#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include "Exceptions.hpp"
#include "Board.hpp"
#include "Piece.hpp"

#include <fstream>
#include <array>
#include <map>
#include <memory>
#include <functional>
#include <iostream>

enum class ErrorType
{
  UNKNOWN_COMMAND,
  INVALID_PARAMETER_COUNT,
  SPECIAL_USE_UNAVAILABLE,
  INVALID_PARAMETER_PLAYER,
  INVALID_PARAMETER_SQUARE,
  INVALID_PARAMETER_PIECE,
  PLAYER_PIECE_NOT_FOUND,
  NO_SPECIAL_POWER,
  INVALID_PARAMETER_COUNT_SPECIAL,
  PIECE_FROZEN,
  INVALID_PARAMETER_SPECIAL_SQUARE,
  INVALID_PARAMETER_PIECE_TYPE,
  INVALID_PARAMETER_TURN_COUNT,
  UNWAVERING_FAITH,
  INVALID_ARCHER_TARGET,
  OPPONENT_PIECE_NOT_FOUND,
  INVALID_PARAMETER_MOVE,
  INVALID_MOVE,
  INSUFFICIENT_MANA,
  NO_POTION_FOUND,
  INVALID_PARAMETER_COUNT_USE,
  INVALID_PARAMETER_USE,
  INVALID_PASS,
  INVALID_PARAMETER_YES_NO,
  INVALID_PATH
};

class ConfigParser
{
  private:
    static const std::string MAGIC_NUMBER_GAME_CONFIG_;
    static const std::string MAGIC_NUMBER_MESSAGE_CONFIG_;

    std::map<ErrorType, std::string> error_messages_;
    std::map<std::string, std::string> piece_id_name_mapping_;
    std::map<std::string, std::string> piece_id_info_mapping_;
    std::map<std::string, std::string> piece_id_syntax_mapping_;
    std::map<std::string, std::string> description_id_message_mapping_;

    std::size_t max_turn_count_;
    std::size_t initial_mana_;
    std::size_t mana_pool_;
    std::size_t white_elo_score_;
    std::size_t black_elo_score_;
    Board board_;
    std::array<std::vector<std::unique_ptr<Piece>>, 2> white_pieces_;
    std::array<std::vector<std::unique_ptr<Piece>>, 2> black_pieces_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor is declared explicitly as a default constructor.
    ConfigParser() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    ConfigParser(const ConfigParser&) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~ConfigParser() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the error messages read from the config file.
    /// @return Reference to the map that stores the error messages sorted by id.
    std::map<ErrorType, std::string>& getErrorMessages() { return error_messages_; }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the description messages read from the config file.
    /// @return Reference to the map that stores the description messages sorted by id.
    std::map<std::string, std::string>& getDescriptionMapping() { return description_id_message_mapping_; }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the full names of the pieces read from the config file.
    /// @return Reference to the map that stores the names sorted by piece id.
    std::map<std::string, std::string>& getPieceIdNameMapping() { return piece_id_name_mapping_; }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the info string of the pieces read from the config file.
    /// @return Reference to the map that stores the info strings sorted by piece id.
    std::map<std::string, std::string>& getPieceIdInfoMapping() { return piece_id_info_mapping_; }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the required special command syntax of the pieces read from the
    ///        config file.
    /// @return Reference to the map that stores the syntaxes sorted by piece id.
    std::map<std::string, std::string>& getPieceIdSyntaxMapping() { return piece_id_syntax_mapping_; }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the maximum turn count read from the config file.
    /// @return Maximum number of turns that can be played.
    std::size_t getMaxTurnCount() { return max_turn_count_; }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the maximum mana read from the config file.
    /// @return Maximum amount of mana the players can have.
    std::size_t getManaPool() { return mana_pool_; }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the initial mana read from the config file.
    /// @return Amount of mana the players have at the start of the game.
    std::size_t getInitialMana() { return initial_mana_; }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the elo score the white player read from the config file.
    /// @return Elo score of the white player.
    std::size_t getWhiteEloScore() { return white_elo_score_; }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the elo score the black player read from the config file.
    /// @return Elo score of the black player.
    std::size_t getBlackEloScore() { return black_elo_score_; }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the vector of pieces that should be placed on rank 2 read
    ///        from the config file.
    /// @return Reference to the vector of pieces that should be placed on rank 2
    std::vector<std::unique_ptr<Piece>>& getWhiteFrontRank() { return white_pieces_.at(0); }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the vector of pieces that should be placed on rank 1 read
    ///        from the config file.
    /// @return Reference to the vector of pieces that should be placed on rank 1
    std::vector<std::unique_ptr<Piece>>& getWhiteBackRank() { return white_pieces_.at(1); }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the vector of pieces that should be placed on rank 7 read
    ///        from the config file.
    /// @return Reference to the vector of pieces that should be placed on rank 7
    std::vector<std::unique_ptr<Piece>>& getBlackFrontRank() { return black_pieces_.at(0); }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the vector of pieces that should be placed on rank 8 read
    ///        from the config file.
    /// @return Reference to the vector of pieces that should be placed on rank 8
    std::vector<std::unique_ptr<Piece>>& getBlackBackRank() { return black_pieces_.at(1); }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a getter method for the board the game is going to be played on.
    /// @return Reference to the initialized Board object.
    Board& getBoard() { return board_; }

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function opens the config files and checks the magic numbers. It also calls the functions to parse
    ///        the config if both of them are valid.
    /// @param game_config_file_path path to the game config file read in from the command line arguments
    /// @param message_config_file_path path to the message config file read in from the command line arguments
    void loadConfigFiles(std::string& game_config_file_path, std::string& message_config_file_path);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function parses the game config file and initializes the member variables of the class accordingly.
    /// @param game_config reference to the game config file that was already opened for reading
    void loadGameConfig(std::fstream& game_config);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function parses the message config file and sorts the messages into the member variables.
    /// @param message_config reference to the message config file that was already opened for reading
    void loadMessageConfig(std::fstream& message_config);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function calls the piece constructors to create the pieces and stores the piece in a vector.
    /// @param game_config reference to the game config file that was already opened for reading
    /// @param pieces reference to the member variable that is being initialized
    void parsePieces(std::fstream& game_config, std::array<std::vector<std::unique_ptr<Piece>>, 2>& pieces);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function handles the logic of placing the specified special squares on the board correctly.
    /// @param game_config reference to the game config file that was already opened for reading
    void parseSquares(std::fstream& game_config);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function converts the string error id into an enum class id and stores the message in a map.
    /// @param error_message_mapping reference to the map that stores the messages by id
    void registerErrorMessages(std::map<std::string, std::string>& error_message_mapping);
};

#endif
