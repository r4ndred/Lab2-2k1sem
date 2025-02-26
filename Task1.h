#ifndef TASK1_H
#define TASK1_H

#include <string>
#include <stack>

using namespace std;

// Функция для вычисления значения арифметического выражения
long long evaluateExpression(const string& expression);

// Вспомогательная функция для выполнения операций
void performOperation(stack<long long>& numbers, stack<char>& operations);

// Вспомогательная функция для определения приоритета операций
int precedence(char op);

#endif // TASK1_H