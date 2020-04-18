#include <iostream>
#include <stdlib.h>

#include "game_board.h"

namespace GameBoard {
  GameBoard::GameBoard(
    const int& width,
    const int& height
  ) : width(width), height(height), board(Board(width, std::vector<Cell>(height))) { }

  void GameBoard::step_with_rule(const Rule& rule) {
    this->mutate([&](const int& x, const int& y, Cell& cell) {
      cell.next = rule(this->neighbors_of(x, y), cell.current);
    });

    this->advance_time();
  }

  void GameBoard::mutate(const LocMutation& mutation) {
    for (int x = 0; x < this->width; ++x) {
      auto& col = this->board[x];
      for (int y = 0; y < this->height; ++y) {
        mutation(x, y, col[y]);
      }
    }
  }

  int GameBoard::neighbors_of(const int& x, const int& y) const {
    int neighbor_count = 0;

    // Pad x and y so that residue is non-negative
    const int x_start = x + this->width - 1;
    const int x_end = x_start + 2;
    const int y_start = y + this->height - 1;
    const int y_end = y_start + 2;

    for (int _u = x_start; _u <= x_end; ++_u) {
      for (int _v = y_start; _v <= y_end; ++_v) {
        // Embed grid on a torus
        const int u = _u % this->width;
        const int v = _v % this->height;

        if (!(u == x && v == y) && this->state_of(u, v)) {
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
    for (const auto& col : this->board) {
      for (const auto& cell : col) {
        std::cout << cell.current << ",";
      }

      std::cout << std::endl;
    }
  }
}
