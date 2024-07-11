#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <integer_sequence>" << std::endl;
        return 1;
    }

    try {
        PmergeMe pm(argv);
        pm.sortContainers();
        pm.display();
    } catch (std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}