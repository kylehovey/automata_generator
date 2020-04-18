#include <iostream>
#include <stdlib.h>

#include "game_board.h"

namespace GameBoard {
  GameBoard::GameBoard(
    const int& width,
    const int& height
  ) : board(Board(height, std::vector<Cell>(width))) { }

  void GameBoard::mutate(const LocMutation& mutation) {
    for (unsigned int y = 0; y < this->board.size(); ++y) {
      auto row = this->board[y];
      for (unsigned int x = 0; x < row.size(); ++x) {
        mutation(x, y, row[x]);
      }
    }
  }

  void GameBoard::mutate(const Mutation& mutation) {
    for (auto& row : this->board) {
      for (auto& cell : row) {
        mutation(cell);
      }
    }
  }

  void GameBoard::advance_time() {
    this->mutate([](Cell& cell) {
      cell.current = cell.next;
    });
  }

  void GameBoard::randomize(const int& seed = 0) {
    srand(seed);

    this->mutate([](Cell& cell) {
      cell.next = rand() % 2;
    });

    this->advance_time();
  }

  bool GameBoard::state_of(const int& x, const int& y) const {
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
