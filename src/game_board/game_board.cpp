#include <iostream>
#include <stdlib.h>

#include "game_board.h"

namespace GameBoard {
  GameBoard::GameBoard(
    const int& width,
    const int& height
  ) : width(width), height(height), board(Board(width, std::vector<Cell>(height))) { }

  void GameBoard::mutate(const LocMutation& mutation) {
    for (int x = 0; x < width; ++x) {
      auto col = this->board[x];
      for (int y = 0; y < height; ++y) {
        mutation(x, y, col[y]);
      }
    }
  }

  int GameBoard::neighbors_of(const int& x, const int& y) const {
    int neighbor_count = 0;

    // Pad x and y so that residue is non-negative
    const int x_start = x + width - 1;
    const int x_end = x_start + 2;
    const int y_start = y + height - 1;
    const int y_end = y_start + 2;

    for (int _u = x_start; _u <= x_end; ++_u) {
      for (int _v = y_start; _v <= y_end; ++_v) {
        const int u = _u % width;
        const int v = _v % height;

        if (u != v && this->state_of(u, v)) {
          neighbor_count++;
        }
      }
    }

    return neighbor_count;
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
    return this->board[x][y].current;
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
