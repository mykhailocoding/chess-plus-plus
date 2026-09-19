//----------------------------------------------------------------------------------------------------------------------
/// This class represents the game that is being played and handles all related tasks.
//----------------------------------------------------------------------------------------------------------------------

#include "Game.hpp"
#include "Pawn.hpp"
#include "GoldenPawn.hpp"
#include "ImpatientPawn.hpp"
#include "StubbornPawn.hpp"
#include "NervousPawn.hpp"
#include "ExplosivePawn.hpp"
#include "Rook.hpp"
#include "InvincibleRook.hpp"
#include "PainterRook.hpp"
#include "Knight.hpp"
#include "JumpyKnight.hpp"
#include "IceKnight.hpp"
#include "Bishop.hpp"
#include "ColorBlindBishop.hpp"
#include "PreacherBishop.hpp"
#include "Queen.hpp"
#include "FlipperQueen.hpp"
#include "JumpyQueen.hpp"
#include "HungryQueen.hpp"
#include "King.hpp"
#include "FrightenedKing.hpp"
#include "ArcherKing.hpp"
#include "FreezePotion.hpp"
#include "TeleportPotion.hpp"
#include "EvenOddPotion.hpp"
#include "SkywalkerPotion.hpp"
#include "Shield.hpp"
#include "InvisibilityCloak.hpp"
#include "QueenRepellant.hpp"
#include "ManaSquare.hpp"
#include "SpawnSquare.hpp"
#include "BoostSquare.hpp"
#include "ManaSquare.hpp"
#include "SpawnSquare.hpp"
#include "BoostSquare.hpp"

#include <cmath>

Game::Game(ConfigParser& config_parser) :
  config_parser_(config_parser),
  command_parser_(*this),
  max_turn_count_(config_parser_.getMaxTurnCount()),
  mana_pool_(config_parser_.getManaPool()),
  board_(config_parser.getBoard()),
  current_turn_(INITIAL_TURN_COUNT),
  current_player_(nullptr),
  winner_(nullptr),
  current_piece_(nullptr),
  additional_move_(false),
  state_(GameState::PLAY)
{
  players_.at(WHITE) = std::make_shared<Player>(WHITE_ID, config_parser.getInitialMana(),
    config_parser.getWhiteEloScore(), config_parser.getManaPool());
  players_.at(BLACK) = std::make_shared<Player>(BLACK_ID, config_parser.getInitialMana(),
    config_parser.getBlackEloScore(), config_parser.getManaPool());
}

const std::string Game::DRAW_COMMAND_MESSAGE_ = "you both agreed to a draw";

const std::string Game::MAX_TURN_COUNT_REACHED_MESSAGE_ = "too many turns were played";

const std::string Game::STALEMATE_RESIGNATION_MESSAGE_ = "of stalemate";

const std::string Game::BOTH_KINGS_CAPTURED_MESSAGE_ = "you both lost your king";

std::size_t Game::getCurrentTurn()
{
  return current_turn_;
}

std::size_t Game::getMaxTurnCount()
{
  return max_turn_count_;
}

std::size_t Game::getManaPool()
{
  return mana_pool_;
}

Board &Game::getBoard()
{
  return board_;
}

Player &Game::getWhitePlayer()
{
  return *(players_.at(PlayerId::WHITE).get());
}

Player &Game::getBlackPlayer()
{
  return *(players_.at(PlayerId::BLACK).get());
}

std::map<std::string, std::string> &Game::getDescriptionMapping()
{
  return config_parser_.getDescriptionMapping();
}

std::map<ErrorType, std::string> &Game::getErrorMessages()
{
  return config_parser_.getErrorMessages();
}

std::map<std::string, std::string> &Game::getPieceIdNameMapping()
{
  return config_parser_.getPieceIdNameMapping();
}

std::map<std::string, std::string> &Game::getPieceIdInfoMapping()
{
  return config_parser_.getPieceIdInfoMapping();
}

std::map<std::string, std::string> &Game::getPieceIdSyntaxMapping()
{
  return config_parser_.getPieceIdSyntaxMapping();
}

CommandParser& Game::getCommandParser()
{
  return command_parser_;
}

GameState Game::getGameState()
{
  return state_;
}

void Game::setGameState(GameState state)
{
  state_ = state;
}

void Game::setWinner(Player* winner)
{
  winner_ = winner;
}

bool Game::AdditionalMove()
{
  return additional_move_;
}

Player *Game::getCurrentPlayer()
{
  return current_player_;
}

Piece *Game::getCurrentPiece()
{
  return current_piece_;
}

void Game::setCurrentPiece(Piece* piece)
{
  current_piece_ = piece;
}

void Game::setAdditionalMove(bool value)
{
  additional_move_ = value;
}

void Game::setPassiveCommand(bool value)
{
  passive_command_ = value;
}

void Game::start()
{
  printWelcome();
  placePieces();
  if (state_ != GameState::PLAY)
  {

    return;
  }

  while (state_ == GameState::PLAY)
  {
    if (!additional_move_)
    {
      getNextPlayer();
    }
    if (state_ != GameState::PLAY) // if max round count reached
    {
      return;
    }

    current_player_->setStatus(checkPlayerStatus(current_player_));
    board_.printBoard(*this, *players_.at(PlayerId::WHITE).get(), *players_.at(PlayerId::BLACK).get());
    while (1)
    {
      try
      {
        passive_command_ = false;
        std::string user_input = command_parser_.getUserInput(current_player_);
        command_parser_.execute(user_input);
      }
      catch (const CustomException &exception)
      {
        std::cout << exception.what() << std::endl;
        continue;
      }

      if(!passive_command_)
      {
        break;
      }
    }
    if (state_ == GameState::PLAY && checkWin())
    {
      state_ = GameState::NORMAL_WIN;
    }
  }
}

void Game::spawnItems()
{
 for(const auto& rank : board_.getBoard())
 {
  for(auto* square : rank)
  {
    if(square->getType() == SquareType::SPAWN_SQUARE)
    {
      auto* spaw_square = dynamic_cast<SpawnSquare*>(square);
      spaw_square->spawnItem(*this);
    }
  }
 } 
}

void Game::printWelcome()
{
  std::cout << getDescriptionMapping().at("BORDER_D") << std::endl;
  std::cout << getDescriptionMapping().at("WELCOME") << std::endl;
  std::cout << getDescriptionMapping().at("BORDER_D") << std::endl;
}

void Game::placePieces()
{
  for (Square *square : board_.getBoard().at(1)) // get rank 2 and iterate through the squares placed there
  {
    std::unique_ptr<Piece> &piece = config_parser_.getWhiteFrontRank().at(0);
    piece->setCoordinates(square->getCoordinates());
    piece->setOwner(players_.at(PlayerId::WHITE).get());
    square->setPiece(std::move(piece));
    config_parser_.getWhiteFrontRank().erase(config_parser_.getWhiteFrontRank().begin());
  }

  for (Square *square : board_.getBoard().at(6)) // get rank 7 and iterate through the squares placed there
  {
    std::unique_ptr<Piece> &piece = config_parser_.getBlackFrontRank().at(0);
    piece->setCoordinates(square->getCoordinates());
    piece->setOwner(players_.at(PlayerId::BLACK).get());
    square->setPiece(std::move(piece));
    config_parser_.getBlackFrontRank().erase(config_parser_.getBlackFrontRank().begin());
  }

  int turn_count = 0;
  int current_player;
  std::vector<std::vector<std::unique_ptr<Piece>>> back_ranks;
  back_ranks.push_back(std::move(config_parser_.getWhiteBackRank()));
  back_ranks.push_back(std::move(config_parser_.getBlackBackRank()));

  // stop the loop if all the pieces specified in the config are placed
  while ((state_ == GameState::PLAY) &&
    (!back_ranks.at(PlayerId::WHITE).empty() && !back_ranks.at(PlayerId::BLACK).empty()))
  {
    current_player = turn_count % PLAYER_COUNT;
    if (back_ranks.at(current_player).size() != 0)
    {
      command_parser_.placePiece(players_.at(current_player).get(), back_ranks.at(current_player), *this);
      if (state_ != GameState::PLAY)
      {
        return;
      }
    }

    turn_count++;

    current_player = turn_count % PLAYER_COUNT;
    if (back_ranks.at(current_player).size() != 0)
    {
      command_parser_.placePiece(players_.at(current_player).get(), back_ranks.at(current_player), *this);
    }
  }
}

std::size_t Game::countPieces(const Piece &piece, const std::vector<std::unique_ptr<Piece>> &pieces)
{
  std::size_t number_of_pieces = 0;

  for (const std::unique_ptr<Piece> &current_piece : pieces)
  {
    if (*(current_piece.get()) == piece)
    {
      number_of_pieces++;
    }
  }

  return number_of_pieces;
}

Player &Game::getOpponent()
{
  if (current_player_->getId() == getWhitePlayer().getId())
  {
    return getBlackPlayer();
  }
  else
  {
    return getWhitePlayer();
  }
}

void Game::getNextPlayer()
{
  if (current_player_ == players_.at(PlayerId::WHITE).get())
  {
    current_player_ = players_.at(PlayerId::BLACK).get();
  }
  else
  {
    current_player_ = players_.at(PlayerId::WHITE).get();
    current_turn_++;
    spawnItems(); // calling spawn_square spawnItem function 
    if (current_turn_ == max_turn_count_)
    {
      state_ = GameState::QUIT;
      return;
    }
    for (auto &row : board_.getBoard())
    {
      for (auto &square : row)
      {
        if (square->hasPiece())
        {
          square->getPiece()->updateCounters();
        }
      }
    }
  }

  current_player_->addMana(1);
  for (auto& row : board_.getBoard()) // mana square adds 1 mana if player has a piece on it
  {
    for (auto& square : row)
    {
      if ((square->getType() == SquareType::MANA_SQUARE)
        && (square->getPiece() != nullptr)
        && (*(square->getPiece()->getOwner()) == current_player_)
        && (square->getPiece() != current_piece_))
        {
          current_player_->addMana(1);
        }
    }
  }
  current_piece_ = nullptr;
  additional_move_ = false;
}

bool Game::checkWin()
{
  if (currentPlayerKingCaptured())
  {
    winner_ = &getOpponent();
    return true;
  }
  else if (opponentKingCaptured())
  {
    winner_ = getCurrentPlayer();
    return true;
  }
  return false;
}

//does not check anything, only gives the resigner
//do not call if there is no winner_
Player& Game::getResigner()
{
  if(winner_->getId() == getWhitePlayer().getId())
  {
    return getBlackPlayer();
  }
  else
  {
    return getWhitePlayer();
  }
}

//calculate + print
void Game::calculateEloScores(std::ostream& output_stream)
{
  std::size_t white_score_current = getWhitePlayer().getEloScore();
  std::size_t black_score_current = getBlackPlayer().getEloScore();

  float qw = std::pow(10.0f, white_score_current / 400.0f);
  float qb = std::pow(10.0f, black_score_current / 400.0f);

  float white_score_expected = qw / (qw + qb);
  float black_score_expected = 1 - white_score_expected;

  float white_score_actual;
  float black_score_actual;

  if(winner_ == nullptr)
  {
    // no winner - draw
    white_score_actual = 0.5;
    black_score_actual = 0.5;
  }
  else if(winner_->getId() == getWhitePlayer().getId())
  {
    white_score_actual = 1;
    black_score_actual = 0;
  }
  else
  {
    white_score_actual = 0;
    black_score_actual = 1;
  }

  std::size_t white_score_new = std::floor(white_score_current + 32 * (white_score_actual - white_score_expected));
  std::size_t black_score_new = std::floor(black_score_current + 32 * (black_score_actual - black_score_expected));

  output_stream << "\nThe new Elo scores are:\n - White: " << white_score_new << std::endl;
  output_stream << " - Black: " << black_score_new << "\n"
                << std::endl;
}

void Game::printNormalWin(std::ostream& output_stream)
{
  output_stream << "This was a great match! Well done to you both!" << std::endl;
  output_stream << "Good job to " << winner_->getId() << " for winning in " << current_turn_ << " turns." << std::endl;
}

void Game::printResignation(std::ostream& output_stream)
{
  output_stream << "Oh I see one of you couldn't take the pressure..." << std::endl;
  output_stream << "Well done to " << winner_->getId() << " for making " << getResigner().getId()
                << " resign in " << current_turn_ << " turns." << std::endl;
}

void Game::printDraw(std::ostream& output_stream, std::string cause)
{
  output_stream << "This game ended in a draw because " << cause << "." << std::endl;
  output_stream << "Thank you for playing " << current_turn_ << " turns." << std::endl;
}

void Game::reduceMana(size_t mana_cost)
{
  current_player_->reduceMana(mana_cost);
}

bool Game::currentPlayerKingCaptured()
{
  for (auto row : board_.getBoard())
  {
    for (auto square : row)
    {
      if (square->hasPiece() && *current_player_ == square->getPiece()->getOwner() &&
        square->getPiece()->getType() == PieceType::King)
      {
        return false;
      }
    }
  }

  return true;
}

bool Game::opponentKingCaptured()
{
  for (auto row : board_.getBoard())
  {
    for (auto square : row)
    {
      if (square->hasPiece() && getOpponent() == square->getPiece()->getOwner() &&
        square->getPiece()->getType() == PieceType::King)
      {
        return false;
      }
    }
  }

  return true;
}

void Game::promote(Board &board, Coordinates pawn_position, char promote_to)
{
  Player *current_player = board.getSquare(pawn_position)->getPiece()->getOwner();
  if (promote_to == 'R')
  {
    board.getSquare(pawn_position)->setPiece(std::make_unique<Rook>());
  }
  if (promote_to == 'N')
  {
    board.getSquare(pawn_position)->setPiece(std::make_unique<Knight>());
  }
  if (promote_to == 'B')
  {
    // we have to set movement color for the bishop
    char movement_color = 0;
    if (board.getSquare(pawn_position)->getType() == SquareType::BASIC_WHITE)
    {
      movement_color = 'w';
    }
    if (board.getSquare(pawn_position)->getType() == SquareType::BASIC_BLACK)
    {
      movement_color = 'b';
    }
    if (board.getSquare(pawn_position)->getType() != SquareType::BASIC_WHITE &&
        board.getSquare(pawn_position)->getType() != SquareType::BASIC_BLACK)
    {
      if (current_player->getId() == WHITE_ID)
      {
        movement_color = 'w';
      }
      if (current_player->getId() == BLACK_ID)
      {
        movement_color = 'b';
      }
    }
    board.getSquare(pawn_position)->setPiece(std::make_unique<Bishop>(movement_color));
  }
  if (promote_to == 'Q')
  {
    board.getSquare(pawn_position)->setPiece(std::make_unique<Queen>());
  }
  // set coords and owner for the new piece
  board.getSquare(pawn_position)->getPiece()->setCoordinates(pawn_position);
  board.getSquare(pawn_position)->getPiece()->setOwner(current_player);
}

PlayerStatus Game::checkPlayerStatus(Player* player)
{
  if (Conditions::isKingInCheck(board_, player))
  {
    if (Conditions::hasLegalMove(*this, *player))
    {
      return PlayerStatus::CHECK;
    }
    else
    {
      return PlayerStatus::CHECK_MATE;
    }
  }
  else
  {
    if (Conditions::hasLegalMove(*this, *player))
    {
      return PlayerStatus::NONE;
    }
    else
    {
      return PlayerStatus::STALE_MATE;
    }
  }
}

void Game::endGame()
{
  if (state_ == GameState::QUIT)
  {
    return;
  }
  switch (state_)
  {
    case GameState::NORMAL_WIN:
      printNormalWin(std::cout);
      break;
    case GameState::RESIGNATION_WIN:
      printResignation(std::cout);
      break;
    case GameState::DRAW_COMMAND_DRAW:
      printDraw(std::cout, DRAW_COMMAND_MESSAGE_);
      break;
    case GameState::MAX_TURN_COUNT_REACHED_DRAW:
      printDraw(std::cout, MAX_TURN_COUNT_REACHED_MESSAGE_);
      break;
    case GameState::STALEMATE_RESIGNATION_DRAW:
      printDraw(std::cout, STALEMATE_RESIGNATION_MESSAGE_);
      break;
    case GameState::BOTH_KINGS_CAPTURED_DRAW:
      printDraw(std::cout, BOTH_KINGS_CAPTURED_MESSAGE_);
      break;
    default:
      break;
  }
  calculateEloScores(std::cout);
  saveGame();
}

void Game::saveGame()
{
  std::cout << "Enter the output file name" << std::endl;

  std::string user_input;
  while (1)
  {
    try
    {
      std::cout << " > ";
      if (!getline(std::cin, user_input))
      {
        return;
      }
      Utils::trim(user_input);
      // quit is case insensitive but the file path is case sensitive
      std::string checking_for_quit = user_input;
      Utils::toUpperCase(checking_for_quit);
      // if its an invalid quit(invalid parameter count) then its handled in the main command game loop
      // with any other input the parameters shouldnt be validated for quit
      if (user_input.empty() || checking_for_quit == "QUIT")
      {
        return;
      }

      std::ofstream output_file(user_input);
      if (!output_file.is_open())
      {
        throw CustomException(getErrorMessages().at(ErrorType::INVALID_PATH));
      }
      switch (state_)
      {
        case GameState::NORMAL_WIN:
          printNormalWin(output_file);
          break;
        case GameState::RESIGNATION_WIN:
          printResignation(output_file);
          break;
        case GameState::DRAW_COMMAND_DRAW:
          printDraw(output_file, DRAW_COMMAND_MESSAGE_);
          break;
        case GameState::MAX_TURN_COUNT_REACHED_DRAW:
          printDraw(output_file, MAX_TURN_COUNT_REACHED_MESSAGE_);
          break;
        case GameState::STALEMATE_RESIGNATION_DRAW:
          printDraw(output_file, STALEMATE_RESIGNATION_MESSAGE_);
          break;
        case GameState::BOTH_KINGS_CAPTURED_DRAW:
          printDraw(output_file, BOTH_KINGS_CAPTURED_MESSAGE_);
          break;
        default:
          break;
      }
      calculateEloScores(output_file);
      printHistory(output_file);
      break;
    }
    catch(const CustomException& exception)
    {
      std::cout << exception.what() << std::endl;
      continue;
    }
  }
}

void Game::printHistory(std::ostream& output_stream)
{
  std::size_t rounds_played;
  std::size_t max_move_count_in_round;
  std::string current_move_white;
  std::string current_move_black;
  std::vector<std::vector<std::string>> white_history = players_.at(PlayerId::WHITE)->getHistory();
  std::vector<std::vector<std::string>> black_history = players_.at(PlayerId::BLACK)->getHistory();

  if (white_history.size() >= black_history.size())
  {
    rounds_played = white_history.size();
  }
  else
  {
    rounds_played = black_history.size();
  }

  output_stream << getDescriptionMapping().at("BORDER_HISTORY") << "\n"
    << std::endl;
  output_stream << getDescriptionMapping().at("HISTORY_HEADER") << std::endl;

  for (std::size_t round_number = 1; round_number <= rounds_played; round_number++)
  {
    std::size_t white_history_size = 0;
    if (round_number <= white_history.size()) 
    {
      white_history_size = white_history.at(round_number - 1).size();
    }

    std::size_t black_history_size = 0;
    if(round_number <= black_history.size())
    {
      black_history_size = black_history.at(round_number -1).size();
    }
    
    if (white_history_size >= black_history_size)
    {
      max_move_count_in_round = white_history_size;
    }
    else
    {
      max_move_count_in_round = black_history_size;
    }

    // game ended with white move
    if (black_history_size == 0)
    {
      current_move_black = "";
    }
    else
    {
      current_move_black = black_history.at(round_number - 1).at(0);
    }
    current_move_white = white_history.at(round_number - 1).at(0);

    output_stream << std::format("{:<3}| {:<8} | {:<8} |", round_number,
      current_move_white, current_move_black) << std::endl;
    // more than 1 move made in a turn
    if (max_move_count_in_round > 1)
    {
      for (std::size_t move_count = 2; move_count <= max_move_count_in_round; move_count++)
      {
        current_move_white = (move_count <= white_history_size) ?
          white_history.at(round_number - 1).at(move_count - 1) : "";
        current_move_black = (move_count <= black_history_size) ?
          black_history.at(round_number - 1).at(move_count - 1) : "";
        std::cout << std::format("   | {:<8} | {:<8} |", current_move_white, current_move_black) << std::endl;
      }
    }
  }

  output_stream << "\n" << getDescriptionMapping().at("BORDER_D")<< std::endl;
}
