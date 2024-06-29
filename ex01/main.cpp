#include "Rpn.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	if (argc  < 1) {
		std::cerr << "Usage: ./rpn \"expression\"" << std::endl;
		return 0;
	}
   try {
    Rpn calc(argv[1]);
	   } catch (std::exception &e) {
	   std::cerr << e.what() << std::endl;

    return 0;
}
}