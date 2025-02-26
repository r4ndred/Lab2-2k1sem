#include "Task1.h"
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <stack>

using namespace std;

// Функция для определения приоритета операций
int precedence(char op) {
    if (op == '+' || op == '-') return 1; // Приоритет сложения и вычитания
    if (op == '*' || op == '/') return 2; // Приоритет умножения и деления
    return 0; // Для всех остальных символов (например, скобок)
}

// Вспомогательная функция для выполнения операций
void performOperation(stack<long long>& numbers, stack<char>& operations) {
    long long b = numbers.top(); numbers.pop(); // Берем верхний элемент из стека чисел
    long long a = numbers.top(); numbers.pop(); // Берем следующий элемент из стека чисел
    char op = operations.top(); operations.pop(); // Берем операцию из стека операций

    long long result = 0;

    // Выполняем операцию
    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': 
            if (b == 0) throw runtime_error("Деление на ноль");
            result = a / b; 
            break;
        default: throw runtime_error("Неизвестная операция");
    }

    numbers.push(result); // Кладем результат обратно в стек чисел
}

// Функция для проверки допустимости символов в выражении
bool isValidExpression(const string& expression) {
    for (char c : expression) {
        // Допустимые символы: цифры, операторы +, -, *, /, скобки и пробелы
        if (!isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')' && !isspace(c)) {
            return false; // Недопустимый символ
        }
    }
    return true; // Все символы допустимы
}

// Основная функция для вычисления значения выражения
long long evaluateExpression(const string& expression) {
    stack<long long> numbers; // Стек для хранения чисел
    stack<char> operations; // Стек для хранения операций

    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];

        // Пропускаем пробелы
        if (isspace(c)) continue;

        // Если символ - цифра, считываем все число и кладем в стек чисел
        if (isdigit(c)) {
            long long num = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--; // Возвращаемся на один символ назад, так как цикл for тоже увеличивает i

            // Проверка, что число не превышает 2 * 10^9 по модулю
            if (abs(num) > 2'000'000'000) {
                throw runtime_error("Число превышает допустимое значение 2 * 10^9");
            }

            numbers.push(num);
        }
        // Если символ - открывающая скобка, кладем ее в стек операций
        else if (c == '(') {
            operations.push(c);
        }
        // Если символ - закрывающая скобка, выполняем все операции до открывающей скобки
        else if (c == ')') {
            while (!operations.empty() && operations.top() != '(') {
                performOperation(numbers, operations);
            }
            operations.pop(); // Удаляем открывающую скобку из стека операций
        }
        // Если символ - операция, выполняем операции с более высоким приоритетом
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operations.empty() && precedence(operations.top()) >= precedence(c)) {
                performOperation(numbers, operations);
            }
            operations.push(c); // Кладем текущую операцию в стек операций
        }
    }

    // Выполняем оставшиеся операции
    while (!operations.empty()) {
        performOperation(numbers, operations);
    }

    // Результат находится на вершине стека чисел
    return numbers.top();
}

// Функция для отображения меню
void showMenu() {
    cout << "Меню:" << endl;
    cout << "1. Решить пример" << endl;
    cout << "2. Выход" << endl;
    cout << "Выберите опцию: ";
}

int main() {
    int choice;
    do {
        showMenu(); // Показываем меню
        cin >> choice; // Считываем выбор пользователя
        cin.ignore(); // Очищаем буфер ввода

        switch (choice) {
            case 1: {
                string expression;
                cout << "Введите арифметическое выражение: ";
                getline(cin, expression); // Считываем выражение

                // Проверка на допустимые символы
                if (!isValidExpression(expression)) {
                    cout << "Ошибка: Выражение содержит недопустимые символы." << endl;
                    break;
                }

                try {
                    long long result = evaluateExpression(expression); // Вычисляем результат
                    cout << "Результат: " << result << endl;
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            }
            case 2:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
        }
    } while (choice != 2); // Повторяем, пока пользователь не выберет выход

    return 0;
}