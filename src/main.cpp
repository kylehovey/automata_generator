#include <iostream>
#include <vector>
#include <stdlib.h>

#include "image_writer/image_writer.cpp"
#include "game_board/game_board.cpp"

int main() {
  const std::string save_file = "tmp/output.pbm";
  const int width = 120;
  const int height = 64;
  const GameBoard::GameBoard board(width, height);

  ImageWriter::PixelMap mapper = [&](const int& x, const int& y) {
    return board.stateOf(x, y);
  };

  ImageWriter::Descriptor descriptor(save_file, width, height);

  descriptor.write(mapper);
  descriptor.close();

  std::cout << "File Written." << std::endl;

  return EXIT_SUCCESS;
}
