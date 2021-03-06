#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H

#include <iomanip>
#include <fstream>
#include <functional>

namespace ImageWriter {
  using PixelMap = std::function<int(const int&, const int&)>;

  class Descriptor {
    public:
      Descriptor(
        const std::string& file_path,
        const int& width,
        const int& height
      );

      void write(const PixelMap&);
      void close();
    private:
      std::ofstream out;
      const int width;
      const int height;
  };
}

#endif
