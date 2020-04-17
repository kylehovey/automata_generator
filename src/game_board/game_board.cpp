#include <iostream>
#include <stdlib.h>

#include "game_board.h"

namespace GameBoard {
  GameBoard::GameBoard(
    const int& width,
    const int& height
  ) : board(Board(height, std::vector<Cell>(width))) { }

  void GameBoard::advance_time() {
    for (auto& row : this->board) {
      for (auto& cell : row) {
        cell.current = cell.next;
      }
    }
  }

  void GameBoard::randomize(const int& seed = 0) {
    srand(seed);

    for (auto& row : this->board) {
      for (auto& cell : row) {
        cell.next = rand() % 2;
      }
    }

    this->advance_time();
  }

  bool GameBoard::stateOf(const int& x, const int& y) const {
    return this->board[y][x].current;
  }

  void GameBoard::print() const {
    for (const auto& row : this->board) {
      for (const auto& cell : row) {
        std::cout << cell.current;
      }

      std::cout << std::endl;
    }
  }
}
