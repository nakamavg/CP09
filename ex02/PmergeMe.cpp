#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
    : _vecTime(0.0), _deqTime(0.0) {
    throw std::invalid_argument("Error");
}

PmergeMe::PmergeMe(char **args)
    : _vecTime(0.0), _deqTime(0.0) {
    for (unsigned int i = 1; args[i] != NULL; i++) {
        std::string line = static_cast<std::string>(args[i]);
        if (line.find_first_not_of("0123456789+") != std::string::npos)
            throw std::invalid_argument("Error");
        else {
            _vec.push_back(std::atoi(line.c_str()));
            _deq.push_back(std::atoi(line.c_str()));
        }
    }
}

PmergeMe::PmergeMe(const PmergeMe& src)
    : _vec(src._vec), _deq(src._deq), _vecTime(src._vecTime), _deqTime(src._deqTime) {
}

PmergeMe& PmergeMe::operator=(const PmergeMe& src) {
    if (this != &src) {
        _vec = src._vec;
        _deq = src._deq;
        _vecTime = src._vecTime;
        _deqTime = src._deqTime;
    }
    return (*this);
}

PmergeMe::~PmergeMe() {
    _vec.clear();
    _deq.clear();
}

void PmergeMe::sortContainers() {
    std::clock_t v_startTime = std::clock();
    mergeInsertVector(0, _vec.size() - 1);
    std::clock_t v_endTime = std::clock();
    setVecTime(1000000.0 * ((v_endTime - v_startTime) / static_cast<double>(CLOCKS_PER_SEC)));

    std::clock_t d_startTime = std::clock();
    mergeInsertDeque(0, _deq.size() - 1);
    std::clock_t d_endTime = std::clock();
    setDeqTime(1000000.0 * ((d_endTime - d_startTime) / static_cast<double>(CLOCKS_PER_SEC)));
}

void PmergeMe::mergeInsertVector(int begin, int end) {
    if (end - begin > 5) {
        int mid = (begin + end) / 2;
        mergeInsertVector(begin, mid);
        mergeInsertVector(mid + 1, end);
        mergeVector(begin, mid, end);
    } else
        insertSortVector(begin, end);
}

void PmergeMe::mergeInsertDeque(int begin, int end) {
    if (end - begin > 5) {
        int mid = (begin + end) / 2;
        mergeInsertDeque(begin, mid);
        mergeInsertDeque(mid + 1, end);
        mergeDeque(begin, mid, end);
    } else
        insertSortDeque(begin, end);
}

void PmergeMe::insertSortVector(int begin, int end) {
    for (int i = begin; i < end; i++) {
        int tempVal = _vec[i + 1];
        int j = i + 1;
        while (j > begin && _vec[j - 1] > tempVal) {
            _vec[j] = _vec[j - 1];
            j--;
        }
        _vec[j] = tempVal;
    }
}

void PmergeMe::insertSortDeque(int begin, int end) {
    for (int i = begin; i < end; i++) {
        int tempVal = _deq[i + 1];
        int j = i + 1;
        while (j > begin && _deq[j - 1] > tempVal) {
            _deq[j] = _deq[j - 1];
            j--;
        }
        _deq[j] = tempVal;
    }
}

void PmergeMe::mergeVector(int begin, int mid, int end) {
    int i = begin;
    int k = begin;
    int j = mid + 1;
    std::vector<int> temp(_vec.size());
    while (i <= mid && j <= end) {
        if (_vec[i] < _vec[j]) {
            temp[k] = _vec[i];
            i++;
        } else {
            temp[k] = _vec[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        temp[k] = _vec[i];
        i++;
        k++;
    }
    while (j <= end) {
        temp[k] = _vec[j];
        j++;
        k++;
    }
    for (i = begin; i <= end; i++)
        _vec[i] = temp[i];
}

void PmergeMe::mergeDeque(int begin, int mid, int end) {
    int i = begin;
    int k = begin;
    int j = mid + 1;
    std::deque<int> temp(_deq.size());
    while (i <= mid && j <= end) {
        if (_deq[i] < _deq[j]) {
            temp[k] = _deq[i];
            i++;
        } else {
            temp[k] = _deq[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        temp[k] = _deq[i];
        i++;
        k++;
    }
    while (j <= end) {
        temp[k] = _deq[j];
        j++;
        k++;
    }
    for (i = begin; i <= end; i++)
        _deq[i] = temp[i];
}

void PmergeMe::display() {
    std::cout << "Before: ";
    for (std::vector<int>::iterator it = _vec.begin(); it != _vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "After: ";
    for (std::vector<int>::iterator it = _vec.begin(); it != _vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector: " << _vecTime << " us" << std::endl;

    std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque: " << _deqTime << " us" << std::endl;
}

void PmergeMe::setVecTime(double time) {
    _vecTime = time;
}

void PmergeMe::setDeqTime(double time) {
    _deqTime = time;
}

double PmergeMe::getVecTime() {
    return _vecTime;
}

double PmergeMe::getDeqTime() {
    return _deqTime;
}