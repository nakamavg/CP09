#include "Rpn.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <string>

// Canonical form
Rpn::Rpn() {
	throw std::invalid_argument("Error");
}
Rpn::Rpn(char *str) {
	try {
        int result = evaluate(str);
        std::cout << result << std::endl;
    } catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
    }
}

Rpn::Rpn(const Rpn& other) {
	if (this != &other) {
		this->_executorStack = other._executorStack;
	}
	
}

Rpn& Rpn::operator=(const Rpn& other) {
    if (this != &other) {
		this->_executorStack = other._executorStack;
    }
    return *this;
}
int Rpn::evaluate(std::string exp) {
    std::stack<int> stack;    
    if (exp.find_first_not_of("0123456789+-/* ") != std::string::npos)
        throw std::invalid_argument("Invalid character in expression");
    if (exp.length() == 1) {
        return std::atoi(exp.c_str());
    }
    std::stringstream ss(exp);
    std::string c;
    while (ss >> c) {
        if (c == "+" || c == "-" || c == "*" || c == "/") {
            doOperation(stack, c);
        } else {
            stack.push(std::atoi(c.c_str()));
        }
    }
    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid RPN expression");
    }
    return stack.top();
}

void Rpn::doOperation(std::stack<int> &stack, std::string c) {
    if (stack.size() < 2) {
        throw std::invalid_argument("Invalid RPN expression");
    }
    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.pop();
    if (c == "+") {
        stack.push(b + a);
    } else if (c == "-") {
        stack.push(b - a);  // Cambio aquí
    } else if (c == "*") {
        stack.push(b * a);
    } else if (c == "/") {
        if (a == 0) {
            throw std::invalid_argument("Cannot divide by zero");
        }
        stack.push(b / a);
    }
}
Rpn::~Rpn() {
}

