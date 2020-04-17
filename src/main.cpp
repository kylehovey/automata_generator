#include <iostream>
#include <vector>

#include "image_writer/image_writer.cpp"

int main() {
  const std::string save_file = "tmp/output.pbm";
  const int width = 120;
  const int height = 64;
  ImageWriter::PixelMap mapper = [](const int& x, const int& y) {
    return (x + y) % 2;
  };

  ImageWriter::Descriptor descriptor(save_file, width, height);

  descriptor.write(mapper);
  descriptor.close();

  std::cout << "File Written." << std::endl;

  return EXIT_SUCCESS;
}
