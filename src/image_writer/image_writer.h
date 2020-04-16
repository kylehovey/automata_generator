#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H

#include <iomanip>
#include <fstream>

namespace ImageWriter {
  class Descriptor {
    public:
      Descriptor(
        const std::string& file_path,
        const int& width,
        const int& height
      );

      void write();
      void close();
    private:
      std::ofstream out;
      const int width;
      const int height;
  };
}

#endif
