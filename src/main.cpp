#include <iostream>
#include <vector>

#include "image_writer/image_writer.cpp"

int main() {
  const std::string save_file = "tmp/output.ppm";
  const int width = 64;
  const int height = 64;

  ImageWriter::Descriptor descriptor(save_file, width, height);

  descriptor.write();
  descriptor.close();

  std::cout << "File Written." << std::endl;

  return EXIT_SUCCESS;
}
