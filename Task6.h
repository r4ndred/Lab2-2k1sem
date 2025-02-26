#ifndef HASHTABLE_H
#define HASHTABLE_H

using namespace std;

#include <iostream>
#include <string>

const int TABLE_SIZE = 10;  // Размер таблицы для хранения хеш-значений, хотя он не будет использоваться в этом задании

// Структура для представления узла в хеш-таблице
struct NodeH {
    string key;   // Ключ узла (не будем использовать для данного задания)
    string value; // Значение узла (не будем использовать для данного задания)
    NodeH* next;  // Указатель на следующий узел (не будем использовать для данного задания)

    // Конструктор для инициализации узла
    NodeH(const string &k, const string &v) : key(k), value(v), next(nullptr) {}
};

// Класс для реализации хеш-таблицы, но в данном случае не используем все функции
class HashTable {
public:
    HashTable() {}  // Конструктор, но не используется для данного задания
    ~HashTable() {} // Деструктор, но не используется для данного задания
    
    // Функция для проверки изоморфности строк
    bool areIsomorphic(const string &a, const string &b);
};

#endif