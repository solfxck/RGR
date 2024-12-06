#include "Header.h"
#include "utils.h"

namespace fs = std::filesystem;
using namespace std;

// функция ввода текста с консоли
string inputTextFromConsole() {
    string text;
    cout << "Введите текст: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    cin >> filename;

    if (filename.empty()) {
        throw runtime_error("Имя файла не может быть пустым!");
    }

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка открытия файла: " + filename);
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

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
    cin >> filename;

    if (filename.empty()) {
        throw runtime_error("Имя файла не может быть пустым!");
    }

    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка создания файла: " + filename);
    }

    file << text;
    file.close();
    cout << "Текст сохранен в файл: " << filename << endl;
}

// сохранение ключа в файл
void saveKeyToFile(const string& key, const string& filename) {
    string saveFilename = filename;
    
    if (filename.empty()) {
        cout << "Введите имя файла для сохранения ключа: ";
        cin >> saveFilename;
    }

    if (saveFilename.empty()) {
        throw runtime_error("Имя файла не может быть пустым!");
    }

    // добавляем расширение .key, если его нет
    if (fs::path(saveFilename).extension().empty()) {
        saveFilename += ".key";
    }

    ofstream keyFile(saveFilename, ios::binary);
    if (!keyFile.is_open()) {
        throw runtime_error("Ошибка создания файла ключа: " + saveFilename);
    }

    keyFile.write(key.c_str(), key.length());
    keyFile.close();

    cout << "Ключ сохранен в файл: " << saveFilename << endl;
}

// загрузка ключа из файла
string loadKeyFromFile(const string& filename) {
    string loadFilename = filename;
    
    if (filename.empty()) {
        cout << "Введите имя файла ключа: ";
        cin >> loadFilename;
    }

    ifstream keyFile(loadFilename, ios::binary);
    if (!keyFile.is_open()) {
        throw runtime_error("Ошибка открытия файла ключа: " + loadFilename);
    }

    // читаем файл в строку
    stringstream buffer;
    buffer << keyFile.rdbuf();
    string key = buffer.str();
    keyFile.close();

    if (key.empty()) {
        throw runtime_error("Файл ключа пуст!");
    }

    return key;
}

// проверка корректности магического квадрата
bool validateMagicSquare(const vector<vector<int>>& square) {
    if (square.empty() || square[0].empty() || square.size() != square[0].size()) {
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
void saveMagicSquare(const vector<vector<int>>& square, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка создания файла: " + filename);
    }
    
    file << square.size() << endl;  // сохраняем размер квадрата
    for (const auto& row : square) {
        for (int num : row) {
            file << num << " ";
        }
        file << endl;
    }
    file.close();
}

// загрузка магического квадрата из файла
vector<vector<int>> loadMagicSquare(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка открытия файла: " + filename);
    }
    
    int size;
    file >> size;  // читаем размер квадрата
    
    vector<vector<int>> square(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file >> square[i][j];
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
    for (const auto& row : square) {
        for (int num : row) {
            cout << num << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// алфавит для русских букв и спецсимволов
const string RUSSIAN_ALPHABET = 
    "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
    "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
    "!@#$%^&*()_+-={}[]|\\:;<>,.?/~`'\""
    " \n";

bool isAllowedChar(char c) {
    return RUSSIAN_ALPHABET.find(c) != string::npos ||  // Русские буквы и спецсимволы
           (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9');
}