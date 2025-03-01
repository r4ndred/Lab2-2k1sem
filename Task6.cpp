#include "Task6.h"

// Функция для проверки, являются ли строки изоморфными
bool HashTable::areIsomorphic(const string &a, const string &b) {
    // Если строки разной длины, то они не могут быть изоморфными
    if (a.length() != b.length()) {
        return false;  // Возвращаем false, если длины не совпадают
    }

    // Массивы для отслеживания соответствий символов
    int mapA[256] = {0};  // Массив для символов из строки a
    int mapB[256] = {0};  // Массив для символов из строки b

    // Проходим по символам строк
    for (int i = 0; i < a.length(); ++i) {
        // Если для текущего символа строки a еще не было соответствующего символа в b
        if (mapA[a[i]] == 0 && mapB[b[i]] == 0) {
            mapA[a[i]] = b[i];  // Сопоставляем символ из a с символом из b
            mapB[b[i]] = a[i];  // Сопоставляем символ из b с символом из a
        } 
        // Если символы не совпадают, значит строки не изоморфны
        else if (mapA[a[i]] != b[i] || mapB[b[i]] != a[i]) {
            return false;  // Возвращаем false, если символы не соответствуют друг другу
        }
    }
    
    return true;  // Возвращаем true, если все символы совпадают
}

int main() {
    HashTable ht;  // Создаем объект хеш-таблицы (на самом деле для этого задания хеш-таблица не используется)
    
    string a, b;
    
    // Запрашиваем ввод строк
    cout << "Введите первую строку: "; 
    cin >> a;  // Ввод первой строки
    
    cout << "Введите вторую строку: "; 
    cin >> b;  // Ввод второй строки
    
    // Проверка на изоморфность
    if (ht.areIsomorphic(a, b)) {
        cout << "Строки изоморфны!" << endl;  // Выводим, что строки изоморфны
    } else {
        cout << "Строки не изоморфны!" << endl;  // Выводим, что строки не изоморфны
    }

    return 0;
}