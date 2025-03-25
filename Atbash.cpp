#include "Header.h"
#include "utils.h"

using namespace std;

// шифрования/дешифрования Атбаш
string Atbash(string text) { 
    // таблица соответствий
    map<char, char> symbolMap = {
        {'0', '='}, {'=', '0'},
        {'1', '?'}, {'?', '1'},
        {'2', '/'}, {'/', '2'},
        {'3', '>'}, {'>', '3'},
        {'4', '<'}, {'<', '4'},
        {'5', '.'}, {'.', '5'},
        {'6', ','}, {',', '6'},
        {'7', '\''}, {'\'', '7'},
        {'8', '"'}, {'"', '8'},
        {'9', ';'}, {';', '9'},
        {'!', ':'}, {':', '!'},
        {'@', ']'}, {']', '@'},
        {'#', '['}, {'[', '#'},
        {'$', '}'}, {'}', '$'},
        {'%', '{'}, {'{', '%'},
        {'^', '|'}, {'|', '^'},
        {'&', '\\'}, {'\\', '&'},
        {'*', '~'}, {'~', '*'},
        {'(', '+'}, {'+', '('},
        {')', '_'}, {'_', ')'},
        {'-', '-'}
    };

    for (char& ch : text) {
        // русский алфавит
        if (ch >= 'А' && ch <= 'Я') {
            ch = 'я' - (ch - 'А');
        }
        else if (ch >= 'а' && ch <= 'я') {
            ch = 'Я' - (ch - 'а');
        }
        // английский алфавит
        else if (ch >= 'A' && ch <= 'Z') {
            ch = 'z' - (ch - 'A');
        }
        else if (ch >= 'a' && ch <= 'z') {
            ch = 'Z' - (ch - 'a');
        }
        // цифры и специальные символы
        else {
            auto it = symbolMap.find(ch); // поиск символа в таблице (возвращает итератор)
            if (it != symbolMap.end()) { // если символ наи?ден (проверям, что итератор указывает не напозицию после последнего элемента)
                ch = it->second; // замена (обращение ко второму элементу)
            }
        }
    }

    return text;
}

void AtbashEncrypt() {
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

            if (inputChoice != "1" && inputChoice != "2" && inputChoice != "3") {
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

            string result = Atbash(text);
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

                    if (saveChoice != "1" && saveChoice != "2" && saveChoice != "3") {
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
void AtbashDecrypt() {
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

            if (inputChoice != "1" && inputChoice != "2" && inputChoice != "3") {
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

            string result = Atbash(text);
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

                    if (saveChoice != "1" && saveChoice != "2" && saveChoice != "3") {
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