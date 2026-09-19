//---------------------------------------------------------------------------------------------------------------------
/// This class represents a player. Contains essential members such as: id, mana, prison, history and others. Also has
/// getters/setters and some methods.
//---------------------------------------------------------------------------------------------------------------------
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <memory>
#include <vector>
#include <string>

class Piece;

const std::string WHITE_ID = "White";
const std::string BLACK_ID = "Black";

enum PlayerId
{
  WHITE,
  BLACK,
  PLAYER_COUNT
};

enum class PlayerStatus
{
  NONE,
  CHECK,
  CHECK_MATE,
  STALE_MATE
};

class Player
{
  private:
    std::string id_;
    std::size_t current_mana_;
    std::size_t elo_score_;
    std::size_t mana_pool_;
    std::vector<std::unique_ptr<Piece>> prison_;
    std::vector<std::vector<std::string>> history_;
    PlayerStatus status_;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor. Initialises essential members.
    /// @param id id(color) of the player
    /// @param mana start amount of the mana
    /// @param elo_score current elo score
    /// @param mana_pool maximal amount of mana allowed
    Player(std::string id, std::size_t mana, std::size_t elo_score, std::size_t mana_pool);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor which implements a deep copy.
    /// @param player object to copy from
    Player(const Player& player);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default destructor.
    ~Player() = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Equality operator.
    /// @param rhs_player player to compare with
    /// @return true if the id is the same, false otherwise
    bool operator==(Player* rhs_player);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Inequality operator.
    /// @param rhs_player player to compare with
    /// @return true if the id differs, false otherwise
    bool operator!=(Player* rhs_player);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets current elo score of the player.
    /// @return elo score number
    std::size_t getEloScore() const { return elo_score_; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Sets new elo score.
    /// @param new_score new elo score number
    void setEloScore(std::size_t new_score) { elo_score_ = new_score; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets id of the player.
    /// @return id string
    const std::string& getId() const { return id_; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets current amount of mana available.
    /// @return number of mana
    std::size_t getCurrentMana() const {return current_mana_;}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Adds specified amount of mana to the current mana of the player.
    /// @param mana_to_add specified amount of mana
    void addMana(std::size_t mana_to_add);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Substracts specified amount of mana from the current mana of the player.
    /// @param mana_cost specified amount of mana
    void reduceMana(size_t mana_cost);
    
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets the prison containing captured pieces.
    /// @return reference to the vector of unique piece pointers
    const std::vector<std::unique_ptr<Piece>>& getPrison() const
    {
      return prison_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Moves piece to the prison.
    /// @param piece unique pointer of the piece
    void addPieceToPrison(std::unique_ptr<Piece> piece);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets the history.
    /// @return reference to the history
    std::vector<std::vector<std::string>>& getHistory() { return history_; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Sets new status of the player.
    /// @param status new status
    void setStatus(PlayerStatus status) { status_ = status; };

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the player is checkmated(status).
    /// @return true if that is the case, false otherwise
    bool isCheckMated();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the player is stalemated(status).
    /// @return true if that is the case, false otherwise
    bool isStaleMated();
};

#endif
