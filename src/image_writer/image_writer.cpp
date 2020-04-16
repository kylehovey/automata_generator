#include "image_writer.h"

namespace ImageWriter {
  Descriptor::Descriptor(
    const std::string& file_path,
    const int& width,
    const int& height
  ) : width(width), height(height) {
    this->out = std::ofstream(file_path);
    this->out << "P1\n" << width  << " ";
    this->out << height << std::endl;
    this->out << 1 << std::endl << std::right;
  }

  /**
   * TODO: Take a 2D array here
   */
  void Descriptor::write() {
    for(int y=0; y<height; y++) {
      for(int x=0; x<width; x++) {
        this->out << std::setw(3) << ((x + y) % 2);
        this->out << " ";
      }

      this->out << "\n";
    }
  }

  void Descriptor::close() {
    this->out.close();
  }
}
