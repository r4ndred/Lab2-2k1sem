#include <iostream>
#include <string>

using namespace std;

// Класс для самописного массива
template <typename T>
class Array {
private:
    T* data;         // Указатель на массив
    int size;        // Текущий размер массива
    int capacity;    // Вместимость массива

    void resize();   // Метод для изменения размера массива

public:
    Array();         // Конструктор
    ~Array();        // Деструктор

    void push(const T& element);  // Добавление элемента в массив
    int length() const;           // Получение длины массива
    T get(int index) const;       // Получение элемента по индексу
    void printSubarrays() const;  // Вывод всех подмассивов
};

// Конструктор класса Array
template <typename T>
Array<T>::Array() : size(0), capacity(10) {
    data = new T[capacity];  // Выделяем память для массива с начальной вместимостью
}

// Деструктор класса Array
template <typename T>
Array<T>::~Array() {
    delete[] data;  // Освобождаем память, выделенную для массива
}

// Метод для изменения размера массива
template <typename T>
void Array<T>::resize() {
    capacity *= 2;  // Удваиваем текущую вместимость
    T* newData = new T[capacity];  // Создаем новый массив с увеличенной вместимостью
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];  // Копируем старые данные в новый массив
    }
    delete[] data;  // Освобождаем старый массив
    data = newData;  // Перенаправляем указатель на новый массив
}

// Метод добавления элемента в массив
template <typename T>
void Array<T>::push(const T& element) {
    if (size == capacity) {  // Проверяем, нужно ли увеличивать размер массива
        resize();
    }
    data[size++] = element;  // Добавляем элемент и увеличиваем размер
}

// Метод получения длины массива
template <typename T>
int Array<T>::length() const {
    return size;
}

// Метод получения элемента по индексу
template <typename T>
T Array<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");  // Проверяем, находится ли индекс в допустимых пределах
    }
    return data[index];  // Возвращаем элемент по индексу
}

// Метод для вывода всех подмассивов
template <typename T>
void Array<T>::printSubarrays() const {
    int n = size;
    // Перебор всех возможных подмассивов
    for (int i = 0; i < (1 << n); ++i) {  // (1 << n) = 2^n
        cout << "{";
        bool first = true;
        
        // Перебор битов числа i для определения подмножества
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {  // Если j-й бит числа i равен 1, то включаем элемент data[j] в подмножество
                if (!first) {
                    cout << ", ";
                }
                cout << data[j];
                first = false;
            }
        }
        cout << "}" << endl;
    }
}

int main() {
    Array<string> arr;  // Создаем массив для строк
    string element;

    // Ввод элементов массива поочередно
    cout << "Введите элементы массива по одному: " << endl;
    
    // Ввод первого элемента (x)
    cout << "Введите первый элемент: ";
    cin >> element;
    arr.push(element);  // Добавляем элемент в массив

    // Ввод второго элемента (y)
    cout << "Введите второй элемент: ";
    cin >> element;
    arr.push(element);  // Добавляем элемент в массив

    // Ввод третьего элемента (z)
    cout << "Введите третий элемент: ";
    cin >> element;
    arr.push(element);  // Добавляем элемент в массив

    // Печать всех подмассивов
    arr.printSubarrays();

    return 0;
}
