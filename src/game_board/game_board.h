#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>

namespace GameBoard {
  struct Cell {
    Cell() : current(true), next(false) { };
    bool current;
    bool next;
  };

  using Board = std::vector< std::vector<Cell> >;

  class GameBoard {
    public:
      GameBoard(const int&, const int&);

      void randomize(const int&);
      bool stateOf(const int&, const int&) const;
      void print() const;
    private:
      void advance_time();
      Board board;
  };
}

#endif
