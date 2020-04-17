#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>

namespace GameBoard {
  struct Cell {
    bool current;
    bool next;
  };

  using Board = std::vector<std::vector<Cell> >;

  class GameBoard {
    public:
      GameBoard(const int&, const int&);

      bool stateOf(const int&, const int&) const;
      void print() const;
    private:
      Board board;
  };
}

#endif
