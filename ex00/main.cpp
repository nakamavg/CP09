
#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    try {
        std::string csvFilePath = "data.csv";
        std::string inputFilePath = argv[1];

        BitcoinExchange bitcoinExchange(csvFilePath);
        bitcoinExchange.processInputFile(inputFilePath);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
