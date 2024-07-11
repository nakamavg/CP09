#pragma once
#include <vector>
#include <deque>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int> _deq;
    double _vecTime;
    double _deqTime;

    void mergeInsertVector(int begin, int end);
    void mergeInsertDeque(int begin, int end);
    void insertSortVector(int begin, int end);
    void insertSortDeque(int begin, int end);
    void mergeVector(int begin, int mid, int end);
    void mergeDeque(int begin, int mid, int end);

public:
    PmergeMe();
    PmergeMe(char **args);
    PmergeMe(const PmergeMe& src);
    PmergeMe& operator=(const PmergeMe& src);
    ~PmergeMe();

    void sortContainers();
    void display();
    void setVecTime(double time);
    void setDeqTime(double time);
    double getVecTime();
    double getDeqTime();
};
