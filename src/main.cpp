#include <iostream>
#include <vector>

#include "image_writer/image_writer.cpp"
#include "game_board/game_board.cpp"

int main() {
  /**
   * Settings
   */
  const std::string save_file = "tmp/output.pbm";
  const int width = 120;
  const int height = 64;

  /**
   * Game board initialization
   */
  GameBoard::GameBoard board(width, height);
  board.randomize();

  /**
   * Image data creation
   */
  ImageWriter::PixelMap mapper = [&](const int& x, const int& y) {
    return board.stateOf(x, y);
  };

  /**
   * Write the file to output
   */
  ImageWriter::Descriptor descriptor(save_file, width, height);
  descriptor.write(mapper);
  descriptor.close();

  /**
   * Let the humans know this is done
   */
  std::cout << "File Written." << std::endl;

  return EXIT_SUCCESS;
}
