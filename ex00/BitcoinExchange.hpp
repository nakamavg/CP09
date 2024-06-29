#pragma once
#include <string>
#include <map>

class BitcoinExchange {
public:
    BitcoinExchange(const std::string& csvFilePath);
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void processInputFile(const std::string& inputFilePath);

private:
    void loadCSVData(const std::string& csvFilePath);
    void processLine(const std::string& line);
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& value) const;
    double getExchangeRate(const std::string& date) const;

    std::map<std::string, double> historicalPrices;
};

