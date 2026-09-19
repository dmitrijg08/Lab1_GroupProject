#include <iostream>
#include <memory>
#include <Windows.h>
#include "shared_types.h"

// Оголошення функції Студента А, яка повертає unique_ptr
std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data);

int main() {
    // Встановлюємо кодування UTF-8 для коректного відображення кирилиці в консолі Windows
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // Створення єдиного спільного об'єкта вхідних даних (shared_ptr), як вимагається у завданні
    auto data = std::make_shared<const InputData>(InputData{
        "це текст для тестування алгоритму рабіна-карпа, і ще один текст",
        "текст"
        });

    std::cout << "Текст: " << data->text << "\n";
    std::cout << "Шукаємо: '" << data->pattern << "'\n\n";

    // Виклик алгоритму Студента А. Передаємо спільний вказівник на дані.
    auto resultA = calculateA(data);

    // Використання structured bindings (C++17/20) для розпакування полів результату
    auto [positions, count, comparisons, time_ms] = *resultA;

    // Виведення результатів
    std::cout << "--- Метод Рабіна-Карпа (Студент А) ---\n";
    std::cout << "Кількість входжень: " << count << "\n";
    std::cout << "Кількість порівнянь: " << comparisons << "\n";
    std::cout << "Час виконання: " << time_ms << " ms\n";
    std::cout << "Позиції: ";

    // Ітеруємось по масиву позицій
    for (int pos : positions) {
        std::cout << pos << " ";
    }
    std::cout << "\n";

    return 0;
}