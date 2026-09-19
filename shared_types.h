#pragma once
#include <string>
#include <vector>

struct InputData {
    std::string text;
    std::string pattern;
};

struct Result {
    std::vector<int> positions;
    int count;
    int comparisons; // Для порівняння ефективності
    double time_ms;  // Час виконання
};