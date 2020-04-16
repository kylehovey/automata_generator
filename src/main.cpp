#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

int main() {
  const auto save_filename = "output.ppm";
  std::ofstream out(save_filename);
  const auto width = 64;
  const auto height = 64;

	out << "P2\n" << width  << " ";
	out << height << std::endl << 255 << std::endl << std::right;

	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
      out << std::setw(3) << (x + y);
      out << " ";
    }

		out << "\n";
	}

	out.close();

  std::cout << "File Written." << std::endl;

  return EXIT_SUCCESS;
}
