#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>
#include <functional>

namespace GameBoard {
  struct Cell {
    Cell() : current(false), next(false) { };
    bool current;
    bool next;
  };

  using Board = std::vector< std::vector<Cell> >;
  using LocMutation = std::function<void(const int&, const int&, Cell&)>;
  using Mutation = std::function<void(Cell&)>;
  using Rule = std::function<int(const int&, const bool&)>;

  class GameBoard {
    public:
      GameBoard(const int&, const int&);

      void step_with_rule(const Rule&);
      void randomize(const int&);
      bool state_of(const int&, const int&) const;
      void print() const;
    private:
      int neighbors_of(const int&, const int&) const;
      void advance_time();
      void mutate(const LocMutation&);
      void mutate(const Mutation&);

      int width;
      int height;
      Board board;
  };
}

#endif
