#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>

#include "image_writer/image_writer.cpp"
#include "game_board/game_board.cpp"

int main(const int argc, const char *argv[]) {
  (void) argc;

  /**
   * Settings
   */
  const std::string save_file = "tmp/output.pbm";
  const int width = 100;
  const int height = 100;
  const GameBoard::Rule anneal = [](const int& neighbors, const bool& alive) {
    const bool sixseveneight = neighbors == 6 || neighbors == 7 || neighbors == 8;
    if (alive) {
      if (neighbors == 3 || neighbors == 5 || sixseveneight) {
        return true;
      } else {
        return false;
      }
    } else {
      if (neighbors == 4 || sixseveneight) {
        return true;
      } else {
        return false;
      }
    }


    return false;
  };
  const GameBoard::Rule GoL = [](const int& neighbors, const bool& alive) {
    if (neighbors == 3) return true;
    if (alive && (neighbors == 2 || neighbors == 3)) return true;
    return false;
  };
  const GameBoard::Rule seeds = [](const int& neighbors, const bool& alive) {
    (void) alive;
    if (neighbors == 2) return true;
    return false;
  };
  const GameBoard::Rule dayAndNight = [](const int& neighbors, const bool& alive) {
    const bool sixseveneight = neighbors >= 6 && neighbors <= 8;
    if (neighbors == 3 || sixseveneight) return true;
    if (alive && (neighbors == 3 || neighbors == 4 || sixseveneight)) return true;
    return false;
  };
  const GameBoard::Rule thirtyFourLife = [](const int& neighbors, const bool& alive) {
    const bool thirtyFour = neighbors == 3 || neighbors == 4;
    if (thirtyFour) return true;
    if (alive && thirtyFour) return true;
    return false;
  };
  const GameBoard::Rule longLife = [](const int& neighbors, const bool& alive) {
    if (neighbors == 5) return true;
    if (alive && (neighbors == 3 || neighbors == 4 || neighbors == 5)) return true;
    return false;
  };
  const GameBoard::Rule replicator = [](const int& neighbors, const bool& alive) {
    const bool oneThreeFiveSeven = neighbors == 1 || neighbors == 3 || neighbors == 5 || neighbors == 7;
    if (oneThreeFiveSeven) return true;
    if (alive && oneThreeFiveSeven) return true;
    return false;
  };

  /**
   * Game board initialization
   */
  GameBoard::GameBoard board(width, height);
  board.randomize(time(NULL));

  /**
   * Image data creation
   */
  ImageWriter::PixelMap mapper = [&](const int& x, const int& y) {
    return board.state_of(y, x);
  };

  /**
   * Write the file to output
   */
  const unsigned int ruleNo = atoi(argv[1]);
  const GameBoard::Rule custom = GameBoard::GameBoard::rule_for(ruleNo);

  for (int i = 0; i < 255; ++i) {
    std::cout << "Running iteration " << i << std::endl;
    const std::string file_name = "tmp/" + static_cast<std::string>(argv[2]) + "/pbm/" + std::to_string(i) + ".pbm";
    ImageWriter::Descriptor descriptor(file_name, width, height);
    descriptor.write(mapper);
    descriptor.close();
    board.step_with_rule(custom);
  }

  return EXIT_SUCCESS;
}
