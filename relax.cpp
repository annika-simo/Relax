#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

/*
 * format_compression_ratio
 *
 * This function will properly format _compression_ratio_ according
 * to the specifications set forth in the lab document.
 *
 * input: a double, _compression_ratio_, that is the compression ratio
 *        to format.
 * output: a std::string that contains _compression_ratio_ properly
 *         formatted according to the specifications set forth in
 *         the lab document.
 */
std::string format_compression_ratio(double compression_ratio) {
  std::stringstream formatted_ss{};
  formatted_ss << std::fixed << std::setprecision(2) << compression_ratio;
  return formatted_ss.str();
}

/*
 * extract_number
 *
 * This function reads the number from the file and determines if 
 * there's an error
 *
 * input: the filename and the number it reads (all passed by reference)
 * output: boolean value for if there's an error
 * 
 */

bool extract_number(std::ifstream &filename, int &number) {
	if (!(filename >> number)) {
		return false;
	} 
	else {
		return true;
	}
}

/*
 * extract_character
 *
 * This function reads the character from the file and determines if
 * there's an error. It also determines if there's a hyphen or not
 *
 * input: the filename and the character it reads (all passed by reference)
 * output: boolean value for if there's an error
 *
 */

bool extract_character(std::ifstream &filename, char &character) {
	if (!(filename >> character)) {
		return false;
	}
	if (character == '-') {
		if (!(filename >> character)) {
			return false;
		}
	}
	return true;
}


int main() {
	std::ifstream compressedFile;
	int number;
	char character;
	std::string compressed;
	std::string decompressed = "";
	int compressedLength = 0;
	double decompressedLength = 0;
	double compressionRatio = 0;

	compressedFile.open("input.rle");

	// check if open
	if (!compressedFile.is_open()) {
		std::cout << "Could not open the file containing the compressed data!" << std::endl;
		return 1;
	}

	// read compressed file and create decompressed file
	while (!std::iscntrl(compressedFile.peek()) && !compressedFile.eof()) {
		if ((!extract_number(compressedFile, number)) || (!extract_character(compressedFile, character))) {
			std::cout << "Compressed data format error!" << std::endl;
			return 1;
		}

		for (int i = 0; i < number; i++) {
			decompressed += character;
		}
	}

	std::cout << decompressed << std::endl;

	compressedFile.close();

	// reopen compressed file
	compressedFile.open("input.rle");

	if (!compressedFile.is_open()) {
		std::cout << "Could not open the file containing the compressed data!" << std::endl;
		return 1;
	}

	// calculate and print compression ratio 
	getline(compressedFile, compressed);
	compressedLength = compressed.length();
	decompressedLength = decompressed.length();
	compressionRatio = decompressedLength / compressedLength;
	std::cout << format_compression_ratio(compressionRatio) << std::endl;

	return 0;
		 

}
