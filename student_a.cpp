#include "shared_types.h"
#include <memory>
#include <chrono>

// Функція отримує спільний вказівник (shared_ptr) на константні вхідні дані
std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data) {
    // Створюємо унікальний вказівник (unique_ptr) для зберігання результату
    auto result = std::make_unique<Result>();

    // Початок відліку часу виконання
    auto start = std::chrono::high_resolution_clock::now();

    int d = 256; // Розмірність алфавіту (для UTF-8 використовуємо 256)
    int q = 101; // Просте число для обчислення хешу за модулем
    int m = data->pattern.length(); // Довжина шуканого підрядка
    int n = data->text.length();    // Довжина всього тексту

    // Перевірка на валідність вхідних даних: шаблон не порожній і не довший за текст
    if (m > 0 && m <= n) {
        int p = 0; // Значення хешу для шуканого шаблону
        int t = 0; // Значення хешу для поточного "вікна" тексту
        int h = 1; // Множник для найстаршої позиції у вікні

        // Обчислюємо множник h = (d^(m-1)) % q
        for (int i = 0; i < m - 1; i++)
            h = (h * d) % q;

        // Попереднє обчислення хешу для шаблону та першого "вікна" тексту.
        // Використовуємо (unsigned char) для уникнення від'ємних значень символів кирилиці в UTF-8.
        for (int i = 0; i < m; i++) {
            p = (d * p + (unsigned char)data->pattern[i]) % q;
            t = (d * t + (unsigned char)data->text[i]) % q;
        }

        // Проходимо по всьому тексту, зсуваючи вікно на один символ
        for (int i = 0; i <= n - m; i++) {
            // Якщо хеші збігаються, перевіряємо посимвольно (щоб виключити колізії хешування)
            if (p == t) {
                bool match = true;
                for (int j = 0; j < m; j++) {
                    result->comparisons++; // Збільшуємо лічильник операцій порівняння
                    if (data->text[i + j] != data->pattern[j]) {
                        match = false; // Знайдено розбіжність
                        break;
                    }
                }
                // Якщо всі символи збіглися, фіксуємо знайдене входження
                if (match) {
                    result->positions.push_back(i);
                    result->count++;
                }
            }

            // Якщо ми не досягли кінця тексту, обчислюємо хеш для наступного вікна
            if (i < n - m) {
                // Віднімаємо хеш символу, що виходить з вікна, і додаємо хеш нового символу.
                // Знову використовуємо (unsigned char) для безпечної роботи з кирилицею.
                t = (d * (t - (unsigned char)data->text[i] * h) + (unsigned char)data->text[i + m]) % q;

                // Якщо отриманий хеш став від'ємним, робимо його додатним
                if (t < 0) t = (t + q);
            }
        }
    }

    // Зупиняємо таймер та обчислюємо час у мілісекундах
    auto end = std::chrono::high_resolution_clock::now();
    result->time_ms = std::chrono::duration<double, std::milli>(end - start).count();

    // Повертаємо unique_ptr з результатом
    return result;
}