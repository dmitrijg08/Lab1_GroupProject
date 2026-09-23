#include <iostream>
#include <memory>
#include <Windows.h>

#include "shared_types.h"

// Оголошення функції Студента А
std::unique_ptr<Result> calculateA(
    std::shared_ptr<const InputData> data);

// Оголошення функції Студента Б
std::unique_ptr<Result> calculateB(
    std::shared_ptr<const InputData> data);

int main()
{
    // Встановлюємо кодування UTF-8
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // Створення єдиного спільного об'єкта вхідних даних
    auto data = std::make_shared<const InputData>(InputData{
        "це текст для тестування алгоритму рабіна-карпа, і ще один текст",
        "текст"
        });

    std::cout << "Текст: " << data->text << "\n";
    std::cout << "Шукаємо: '" << data->pattern << "'\n\n";

    // ==========================================
    // АЛГОРИТМ СТУДЕНТА А — РАБІНА-КАРПА
    // ==========================================

    auto resultA = calculateA(data);

    auto [positions, count, comparisons, time_ms] = *resultA;

    std::cout << "--- Метод Рабіна-Карпа (Студент А) ---\n";
    std::cout << "Кількість входжень: " << count << "\n";
    std::cout << "Кількість порівнянь: " << comparisons << "\n";
    std::cout << "Час виконання: " << time_ms << " ms\n";

    std::cout << "Позиції: ";

    for (int pos : positions)
    {
        std::cout << pos << " ";
    }

    std::cout << "\n\n";

    // ==========================================
    // АЛГОРИТМ СТУДЕНТА Б — KMP
    // ==========================================

    auto resultB = calculateB(data);

    auto [positionsB, countB, comparisonsB, timeB] = *resultB;

    std::cout << "--- Алгоритм Кнута-Морріса-Пратта (Студент Б) ---\n";
    std::cout << "Кількість входжень: " << countB << "\n";
    std::cout << "Кількість порівнянь: " << comparisonsB << "\n";
    std::cout << "Час виконання: " << timeB << " ms\n";

    std::cout << "Позиції: ";

    for (int pos : positionsB)
    {
        std::cout << pos << " ";
    }

    std::cout << "\n";

    return 0;
}