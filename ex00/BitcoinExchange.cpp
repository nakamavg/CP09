#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

BitcoinExchange::BitcoinExchange(const std::string& csvFilePath) {
    loadCSVData(csvFilePath);
}

void BitcoinExchange::loadCSVData(const std::string& csvFilePath) {
    std::ifstream file(csvFilePath.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, price;
        if (std::getline(ss, date, ',') && std::getline(ss, price)) {
            historicalPrices[date] = std::atof(price.c_str());
        }
    }
}

void BitcoinExchange::processInputFile(const std::string& inputFilePath) {
    std::ifstream file(inputFilePath.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        processLine(line);
    }
}

void BitcoinExchange::processLine(const std::string& line) {
    std::stringstream ss(line);
    std::string date, value;
    if (std::getline(ss, date, '|') && std::getline(ss, value)) {
        date = date.substr(0, date.find_last_not_of(" ") + 1);
        value = value.substr(value.find_first_not_of(" "));

        if (!isValidDate(date)) {
            std::cerr << "Error: bad input date => " << date << std::endl;
            return;
        }
        if (!isValidValue(value)) {
            std::cerr << "Error: not a valid number." << std::endl;
            return;
        }

        double val = std::atof(value.c_str());
        if (val < 0) {
            std::cerr << "Error: negative value." << std::endl;
            return;
        }
        if (val > INT_MAX) {
            std::cerr << "Error: value too large." << std::endl;
            return;
        }

        double rate = getExchangeRate(date);
        std::cout << date << " => " << value << " = " << std::fixed << std::setprecision(2) << (val * rate) << std::endl;
    } else {
        std::cerr << "Error: bad input format." << std::endl;
    }
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);
    if (!isdigit(yearStr[0]) || !isdigit(yearStr[1]) || !isdigit(yearStr[2]) || !isdigit(yearStr[3]) ||
        !isdigit(monthStr[0]) || !isdigit(monthStr[1]) ||
        !isdigit(dayStr[0]) || !isdigit(dayStr[1])) {
        return false;
    }
    int year = std::atoi(yearStr.c_str());
    int month = std::atoi(monthStr.c_str());
    int day = std::atoi(dayStr.c_str());
    
    if (month < 1 || month > 12 || day < 1 || year < 2000) {
        return false;
    }
    
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int maxDay = daysInMonth[month - 1];
    
    if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
        maxDay = 29; // leap year
    }
    
    if (day > maxDay) {
        return false;
    }
    
    return true;
}

bool BitcoinExchange::isValidValue(const std::string& value) const {
    for (size_t i = 0; i < value.size(); ++i) {
        if (!isdigit(value[i]) && value[i] != '.') {
            return false;
        }
    }
    return true;
}

double BitcoinExchange::getExchangeRate(const std::string& date) const {
    std::map<std::string, double>::const_iterator it = historicalPrices.lower_bound(date);
    if (it == historicalPrices.end() || it->first != date) {
        if (it == historicalPrices.begin()) {
            return 0.0;
        }
        --it;
    }
    return it->second;
}

// canonical
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    historicalPrices = other.historicalPrices;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        historicalPrices = other.historicalPrices;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}
// end canonical
