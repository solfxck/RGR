#include "Header.h"
#include "utils.h"

namespace fs = std::filesystem;
using namespace std;

// функция ввода текста с консоли
string inputTextFromConsole() {
    string text;
    cout << "Введите текст: ";
    getline(cin, text);
    
    if (text.empty()) {
        throw runtime_error("Текст не может быть пустым!");
    }
    return text;
}

// функция ввода текста из файла
string inputTextFromFile() {
    string filename;
    cout << "Введите имя файла: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("Некорректное имя файла!");
    }

    ifstream file(filename); // открываем файл
    if (!file.is_open()) {
        throw runtime_error("Ошибка открытия файла: " + filename);
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>()); // читаем файл в строку
    file.close(); // закрываем файл

    if (text.empty()) {
        throw runtime_error("Файл пуст!");
    }
    return text;
}

// функция сохранения текста в файл
void saveTextToFile(const string& text) {
    if (text.empty()) {
        throw runtime_error("Нечего сохранять - текст пуст!");
    }

    string filename;
    cout << "Введите имя файла для сохранения: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("Некорректное имя файла!");
    }

    ofstream file(filename); // открываем файл
    if (!file.is_open()) {
        throw runtime_error("Ошибка создания файла: " + filename);
    }

    file << text; // записываем текст в файл
    file.close(); // закрываем файл
    cout << "Текст сохранен в файл: " << filename << endl;
}

// сохранение ключа в файл
void saveKeyToFile(const string& key) {
    string filename;
    
    cout << "Введите имя файла для сохранения ключа: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("Некорректное имя файла!");
    }

    // добавляем расширение .key, если его нет
    if (fs::path(filename).extension().empty()) {
        filename += ".key";
    }

    ofstream keyFile(filename, ios::binary); // открываем файл
    if (!keyFile.is_open()) { // если не удалось открыть файл
        throw runtime_error("Ошибка создания файла ключа: " + filename);
    }

    keyFile.write(key.c_str(), key.length()); // записываем ключ в файл 
                                              // c_str() возвращает указатель на начало строки 
                                              // length() возвращает длину строки 
    keyFile.close();

    cout << "Ключ сохранен в файл: " << filename << endl;
}

// загрузка ключа из файла
string loadKeyFromFile() {
    string filename;
    
    cout << "Введите имя файла ключа: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("Некорректное имя файла!");
    }

    ifstream keyFile(filename, ios::binary); // открываем файл (ios::binary - чтение в бинарном формате, для сохранения спецсимволов)
    if (!keyFile.is_open()) {
        throw runtime_error("Ошибка открытия файла ключа: " + filename);
    }

    // читаем файл в строку
    stringstream buffer; 
    buffer << keyFile.rdbuf(); // перемещаем содержимое файла в поток
    string key = buffer.str(); // преобразуем поток в строку
    keyFile.close();

    if (key.empty()) {
        throw runtime_error("Файл ключа пуст!");
    }

    return key;
}

// проверка корректности магического квадрата
bool validateMagicSquare(const vector<vector<int>>& square) {
    if (square.empty() || square[0].empty() || square.size() != square[0].size()) { // проверка на пустой квадрат
        return false;
    }

    int n = square.size();
    int magicSum = n * (n * n + 1) / 2;  // магическая константа

    // проверка строк
    for (const auto& row : square) {
        int sum = 0;
        for (int num : row) {
            sum += num;
        }
        if (sum != magicSum) return false;
    }

    // проверка столбцов
    for (int j = 0; j < n; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += square[i][j];
        }
        if (sum != magicSum) return false;
    }

    // проверка главной диагонали
    int diagSum1 = 0;
    for (int i = 0; i < n; i++) {
        diagSum1 += square[i][i];
    }
    if (diagSum1 != magicSum) return false;

    // проверка побочной диагонали
    int diagSum2 = 0;
    for (int i = 0; i < n; i++) {
        diagSum2 += square[i][n - 1 - i];
    }
    if (diagSum2 != magicSum) return false;

    return true;
}

// сохранение магического квадрата в файл
void saveMagicSquare(const vector<vector<int>>& square) {
    string filename;
    cout << "Введите имя файла для сохранения магического квадрата: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("Некорректное имя файла!");
    }

    // добавляем расширение .msq, если его нет
    if (fs::path(filename).extension().empty()) {
        filename += ".msq";
    }

    ofstream file(filename); // открываем файл
    if (!file.is_open()) {
        throw runtime_error("Ошибка создания файла: " + filename);
    }
    
    file << square.size() << endl;  // сохраняем размер квадрата
    for (const auto& row : square) { // сохраняем элементы квадрата
        for (int num : row) { // проходимся по всем элементам строки
            file << num << " ";
        }
        file << endl;
    }
    file.close();
    cout << "Магический квадрат сохранен в файл: " << filename << endl;
}

// загрузка магического квадрата из файла
vector<vector<int>> loadMagicSquare() {
    string filename;
    cout << "Введите имя файла магического квадрата: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("Некорректное имя файла!");
    }

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка открытия файла: " + filename);
    }
    
    int size;
    file >> size;  // читаем размер квадрата
    
    if (size % 2 == 0 || size < 3 || size > 9) {
        file.close();
        throw runtime_error("Некорректный размер магического квадрата в файле!");
    }
    
    vector<vector<int>> square(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (!(file >> square[i][j])) {
                file.close();
                throw runtime_error("Ошибка чтения данных из файла!");
            }
        }
    }
    file.close();
    
    if (!validateMagicSquare(square)) {
        throw runtime_error("Загруженный магический квадрат некорректен!");
    }
    
    return square;
}

// вывод магического квадрата на экран
void displayMagicSquare(const vector<vector<int>>& square) {
    cout << "\nМагический квадрат " << square.size() << "x" << square.size() << ":" << endl;
    for (const auto& row : square) { // проходимся по всем элементам квадрата
        for (int num : row) {
            cout << num << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// алфавит для русских букв и спецсимволов (для проверки корректности текста)
const string RUSSIAN_ALPHABET = 
    "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
    "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
    "!@#$%^&*()_+-={}[]|\\:;<>,.?/~`'\""
    " \n";

// проверка корректности текста
bool isAllowedChar(char c) {
    return RUSSIAN_ALPHABET.find(c) != string::npos ||  // русские буквы и спецсимволы
           (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9');
}