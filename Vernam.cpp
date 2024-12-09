#include "Header.h"
#include "utils.h"

using namespace std;
namespace fs = std::filesystem;

// функция для получения индекса символа (костыли, т.к. некооректно работает кодировка UTF-8)
int getCharIndex(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    int index = -1;
    
    // проверка диапазона символов (0xC0-0xDF)
    if (uc >= 0xC0 && uc <= 0xDF) {
        index = uc - 0xC0;
    }
    // проверка диапазона символов (0xE0-0xFF)
    else if (uc >= 0xE0 && uc <= 0xFF) {
        index = (uc - 0xE0) + 32;
    }
    // проверка диапазона символов (A-Z)
    else if (uc >= 'A' && uc <= 'Z') {
        index = (uc - 'A') + 64;
    }
    // проверка диапазона символов (a-z)
    else if (uc >= 'a' && uc <= 'z') {
        index = (uc - 'a') + 90;
    }
    // проверка диапазона символов (0-9)
    else if (uc >= '0' && uc <= '9') {
        index = (uc - '0') + 116;
    }
    // специальные символы
    else {
        const string specialChars = " .,!?@#$%^&*()-+=<>[]{}|/\"';:\\";
        size_t pos = specialChars.find(c);
        if (pos != string::npos) {
            index = 126 + pos;
        }
    }
    
    return index;
}

// функция для получения символа по индексу
char getCharFromIndex(int index) {
    if (index < 0) return '\0';
    
    // проверка диапазона символов (0xC0)
    if (index < 32) {
        return static_cast<char>(index + 0xC0);
    }
    // проверка диапазона символов (0xE0)
    else if (index < 64) {
        return static_cast<char>((index - 32) + 0xE0);
    }
    // проверка диапазона символов (A-Z)
    else if (index < 90) {
        return static_cast<char>((index - 64) + 'A');
    }
    // проверка диапазона символов (a-z)
    else if (index < 116) {
        return static_cast<char>((index - 90) + 'a');
    }
    // проверка диапазона символов (0-9)
    else if (index < 126) {
        return static_cast<char>((index - 116) + '0');
    }
    // специальные символы
    else {
        const string specialChars = " .,!?@#$%^&*()-+=<>[]{}|/\"';:\\";
        int specialIndex = index - 126;
        if (specialIndex >= 0 && specialIndex < specialChars.length()) {
            return specialChars[specialIndex];
        }
    }
    
    return '\0';
}

// функция для генерации случайного ключа
string generateRandomKey(int length) {
    string key;
    key.reserve(length);
    
    srand(static_cast<unsigned int>(time(nullptr)));
    
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % 161; // генерация случайного индекса
        key += getCharFromIndex(randomIndex);
    }
    
    return key;
}

// функция для шифрования текста с использованием метода Вернама
string Vernam(const string& text, const string& key) {    
    string result; // строка для хранения зашифрованного текста
    result.reserve(text.length()); // предварительное выделение памяти
    
    for (size_t i = 0; i < text.length(); ++i) { // проход по каждому символу текста
        unsigned char textChar = static_cast<unsigned char>(text[i]); // преобразование символа в unsigned char
        unsigned char keyChar = static_cast<unsigned char>(key[i]);
        
        int textIndex = getCharIndex(text[i]); // получение индекса символа
        int keyIndex = getCharIndex(key[i]);
        
        // если символ не найден, добавляем его в результат без изменений
        if (textIndex == -1 || keyIndex == -1) { 
            result += text[i];
            continue;
        }
        
        // применение операции XOR для шифрования
        int resultIndex = (textIndex ^ keyIndex) % 256; // делим на 256, чтобы получить индекс в диапазоне от 0 до 255 
        char resultChar = getCharFromIndex(resultIndex); // преобразование индекса в символ
        
        // если результат не найден, добавляем исходный символ
        if (resultChar == '\0') {
            result += text[i];
        } else {
            result += resultChar;
        }
    }
    
    return result;
}

void VernamEncrypt() {
    while (true) {
        system("cls");

        string inputChoice; // переменная для выбора способа ввода текста
        cout << "Выберите способ ввода текста:" << endl;
        cout << "1. Ввод с консоли" << endl;
        cout << "2. Ввод из файла" << endl;
        cout << "3. Назад" << endl;
        cout << "Ваш выбор: ";
        
        try {
            getline(cin, inputChoice);

            if (inputChoice == "3") {
                return;
            }

            if (inputChoice.length() != 1 || !isdigit(inputChoice[0]) || 
                inputChoice[0] < '1' || inputChoice[0] > '3' || 
                inputChoice.find(' ') != string::npos) {
                throw invalid_argument("Неверный выбор. Попробуйте снова.");
            }

            string text;
            if (inputChoice == "1") {
                text = inputTextFromConsole();
            } else if (inputChoice == "2") {
                text = inputTextFromFile();
            }

            if (text.empty()) {
                throw invalid_argument("Текст не может быть пустым.");
            }

            string key;
            bool keyObtained = false; // флаг, указывающий на то, что ключ был получен
            while (!keyObtained) {
                try {
                    // Выбор способа получения ключа
                    string keyChoice;
                    cout << "\nВыберите способ получения ключа:" << endl;
                    cout << "1. Сгенерировать случайный ключ" << endl;
                    cout << "2. Загрузить ключ из файла" << endl;
                    cout << "Ваш выбор: ";
                    getline(cin, keyChoice);

                    if (keyChoice.length() != 1 || !isdigit(keyChoice[0]) || 
                        keyChoice[0] < '1' || keyChoice[0] > '2' || 
                        keyChoice.find(' ') != string::npos) {
                        throw invalid_argument("Неверный выбор способа получения ключа.");
                    }

                    if (keyChoice == "1") {
                        key = generateRandomKey(text.length());
                        cout << "\nКлюч сгенерирован." << endl;
                        
                        bool keySaveChosen = false;
                        while (!keySaveChosen) {
                            try {
                                // Спрашиваем о сохранении ключа
                                string saveKeyChoice; 
                                cout << "Сохранить ключ в файл?" << endl;
                                cout << "1. Да" << endl;
                                cout << "2. Нет" << endl;
                                cout << "Ваш выбор: ";
                                getline(cin, saveKeyChoice);

                                if (saveKeyChoice.length() != 1 || !isdigit(saveKeyChoice[0]) || 
                                    saveKeyChoice[0] < '1' || saveKeyChoice[0] > '2' || 
                                    saveKeyChoice.find(' ') != string::npos) {
                                    throw invalid_argument("Неверный выбор. Попробуйте снова.");
                                }

                                if (saveKeyChoice == "1") {
                                    saveKeyToFile(key);
                                }
                                keySaveChosen = true;
                            }
                            catch (const exception& e) {
                                cout << "Ошибка: " << e.what() << endl;
                                system("pause");
                                system("cls");
                                cout << "\nКлюч сгенерирован." << endl;
                            }
                        }
                    } else {
                        key = loadKeyFromFile();
                    }

                    if (key.length() != text.length()) {
                        throw invalid_argument("Длина ключа должна совпадать с длиной текста!");
                    }
                    keyObtained = true;
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "Текст для шифрования: " << text << endl;
                }
            }

            string result = Vernam(text, key);
            cout << "\nЗашифрованный текст: " << result << endl;

            bool saveMenuActive = true;
            while (saveMenuActive) {
                try {
                    string saveChoice;
                    cout << "\nСохранить результат в файл?" << endl;
                    cout << "1. Да" << endl;
                    cout << "2. Нет" << endl;
                    cout << "3. Назад" << endl;
                    cout << "Ваш выбор: ";
                    getline(cin, saveChoice);

                    if (saveChoice.length() != 1 || !isdigit(saveChoice[0]) || 
                        saveChoice[0] < '1' || saveChoice[0] > '3' || 
                        saveChoice.find(' ') != string::npos) {
                        throw invalid_argument("Неверный выбор. Попробуйте снова.");
                    }

                    if (saveChoice == "1") {
                        saveTextToFile(result);
                        system("pause");
                        return;
                    }
                    else if (saveChoice == "2") {
                        return;
                    }
                    else if (saveChoice == "3") {
                        saveMenuActive = false;
                    }
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "\nЗашифрованный текст: " << result << endl;
                }
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            system("pause");
        }
    }
}

// функция дешифрования
void VernamDecrypt() {
    while (true) {
        system("cls");

        string inputChoice;
        cout << "Выберите способ ввода текста:" << endl;
        cout << "1. Ввод с консоли" << endl;
        cout << "2. Ввод из файла" << endl;
        cout << "3. Назад" << endl;
        cout << "Ваш выбор: ";
        
        try {
            getline(cin, inputChoice);

            if (inputChoice == "3") {
                return;
            }

            if (inputChoice.length() != 1 || !isdigit(inputChoice[0]) || 
                inputChoice[0] < '1' || inputChoice[0] > '3' || 
                inputChoice.find(' ') != string::npos) {
                throw invalid_argument("Неверный выбор. Попробуйте снова.");
            }

            string text;
            if (inputChoice == "1") {
                text = inputTextFromConsole();
            } else if (inputChoice == "2") {
                text = inputTextFromFile();
            }

            if (text.empty()) {
                throw invalid_argument("Текст не может быть пустым.");
            }

            string key;
            bool keyObtained = false;
            while (!keyObtained) {
                try {
                    cout << "\nЗагрузка ключа из файла..." << endl;
                    key = loadKeyFromFile();

                    if (key.length() != text.length()) {
                        throw invalid_argument("Длина ключа должна совпадать с длиной текста!");
                    }
                    keyObtained = true;
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "Текст для расшифрования: " << text << endl;
                }
            }

            string result = Vernam(text, key);
            cout << "\nРасшифрованный текст: " << result << endl;

            bool saveMenuActive = true;
            while (saveMenuActive) {
                try {
                    string saveChoice;
                    cout << "\nСохранить результат в файл?" << endl;
                    cout << "1. Да" << endl;
                    cout << "2. Нет" << endl;
                    cout << "3. Назад" << endl;
                    cout << "Ваш выбор: ";
                    getline(cin, saveChoice);

                    if (saveChoice.length() != 1 || !isdigit(saveChoice[0]) || 
                        saveChoice[0] < '1' || saveChoice[0] > '3' || 
                        saveChoice.find(' ') != string::npos) {
                        throw invalid_argument("Неверный выбор. Попробуйте снова.");
                    }

                    if (saveChoice == "1") {
                        saveTextToFile(result);
                        system("pause");
                        return;
                    }
                    else if (saveChoice == "2") {
                        return;
                    }
                    else if (saveChoice == "3") {
                        saveMenuActive = false;
                    }
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "\nРасшифрованный текст: " << result << endl;
                }
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            system("pause");
        }
    }
}