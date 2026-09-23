#include <memory>
#include <vector>
#include <string>
#include <chrono>

#include "shared_types.h"

// Побудова префіксної функції
std::vector<int> prefixFunction(const std::string& pattern)
{
    std::vector<int> pi(pattern.size(), 0);
    for (int i = 1; i < static_cast<int>(pattern.size()); ++i)
    {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j])
        {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

// Алгоритм Кнута-Морріса-Пратта
std::unique_ptr<Result> calculateB(
    std::shared_ptr<const InputData> data)
{
    auto result = std::make_unique<Result>();
    auto start = std::chrono::high_resolution_clock::now();
    const std::string& text = data->text;
    const std::string& pattern = data->pattern;
    // Якщо підрядок порожній
    if (pattern.empty())
    {
        auto end = std::chrono::high_resolution_clock::now();

        result->time_ms =
            std::chrono::duration<double, std::milli>(
                end - start
            ).count();

        return result;
    }

    // Побудова префіксної функції
    std::vector<int> pi = prefixFunction(pattern);
    int j = 0;

    // Пошук усіх входжень підрядка
    for (int i = 0; i < static_cast<int>(text.size()); ++i)
    {
        while (j > 0 && text[i] != pattern[j])
        {
            ++result->comparisons;
            j = pi[j - 1];
        }

        ++result->comparisons;

        if (text[i] == pattern[j])
        {
            ++j;
        }

        // Знайдено повне входження
        if (j == static_cast<int>(pattern.size()))
        {
            int position =
                i - static_cast<int>(pattern.size()) + 1;

            result->positions.push_back(position);
            ++result->count;

            // Продовжуємо пошук.
            j = pi[j - 1];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    result->time_ms =
        std::chrono::duration<double, std::milli>(
            end - start
        ).count();
    return result;
}