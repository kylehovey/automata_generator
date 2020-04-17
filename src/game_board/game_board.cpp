#include <iostream>

#include "game_board.h"

namespace GameBoard {
  GameBoard::GameBoard(
    const int& width,
    const int& height
  ) : board(Board(height, std::vector<Cell>(width))) { }

  bool GameBoard::stateOf(const int& x, const int& y) const {
    return this->board[y][x].current;
  }

  void GameBoard::print() const {
    for (const auto row : this->board) {
      for (const Cell cell : row) {
        std::cout << cell.current;
      }

      std::cout << std::endl;
    }
  }
}
