#include <iostream>
#include <vector>
#include <time.h>

#include "image_writer/image_writer.cpp"
#include "game_board/game_board.cpp"

int main() {
  /**
   * Settings
   */
  const std::string save_file = "tmp/output.pbm";
  const int width = 500;
  const int height = 500;
  const GameBoard::Rule anneal = [](const int& neighbors, const bool& alive) {
    const bool sixseveneight = neighbors >= 6 && neighbors <= 8;
    if (neighbors == 4 || sixseveneight) return true;
    if (alive && (neighbors == 3 || neighbors == 5 || sixseveneight)) return true;
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
  for (int i = 0; i < 255; ++i) {
    std::cout << "Running iteration " << i << std::endl;
    const std::string file_name = "tmp/pbm/" + std::to_string(i) + ".pbm";
    ImageWriter::Descriptor descriptor(file_name, width, height);
    descriptor.write(mapper);
    descriptor.close();
    board.step_with_rule(GoL);
  }

  return EXIT_SUCCESS;
}
