#include "Header.h"
#include "utils.h"

using namespace std;

// шифрования/дешифрования Атбаш
string Atbash(string text) { 
    if (text.empty()) {
        throw runtime_error("Ошибка: Пустой текст!");
    }

    // карту соответствий символов напрямую
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

    try {
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
                auto it = symbolMap.find(ch);
                if (it != symbolMap.end()) {
                    ch = it->second;
                }
            }
        }
    }
    catch (const exception& e) {
        throw runtime_error("Ошибка при шифровании: " + string(e.what()));
    }
    return text;
}

// функция шифрования
void AtbashEncrypt() {
    try {
        while (true) {
            system("cls");
            string inputChoice;
            cout << "Выберите способ ввода текста:" << endl;
            cout << "1. Ввод с консоли" << endl;
            cout << "2. Ввод из файла" << endl;
            cout << "3. Назад" << endl;
            cout << "Ваш выбор: ";
            cin >> inputChoice;

            if (inputChoice == "3") {
                return;
            }

            string text;
            try {
                if (inputChoice == "1") {
                    text = inputTextFromConsole();
                } else if (inputChoice == "2") {
                    text = inputTextFromFile();
                } else {
                    throw runtime_error("Неверный выбор.");
                }
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
                cout << "\nНажмите Enter для продолжения...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }

            if (text.empty()) continue;

            string result = Atbash(string(text));
            cout << "Зашифрованный текст: " << result << endl;

            while (true) {
                string saveChoice;
                cout << "\nСохранить результат в файл?" << endl;
                cout << "1. Да" << endl;
                cout << "2. Нет" << endl;
                cout << "3. Назад" << endl;
                cout << "Ваш выбор: ";
                cin >> saveChoice;

                if (saveChoice == "3") {
                    break; // возврат к выбору способа ввода
                }

                if (saveChoice == "1") {
                    try {
                        saveTextToFile(result);
                        cout << "\nНажмите Enter для продолжения...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                        return; // возврат в меню шифра
                    }
                    catch (const exception& e) {
                        cout << "Ошибка при сохранении: " << e.what() << endl;
                        cout << "\nНажмите Enter для продолжения...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                        continue; // повторить попытку сохранения
                    }
                }
                else if (saveChoice == "2") {
                    return; // возврат в меню шифра
                }
                else {
                    cout << "Неверный выбор." << endl;
                    cout << "\nНажмите Enter для продолжения...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                }
            }
        }
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        cout << "\nНажмите Enter для продолжения...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}

// функция дешифрования
void AtbashDecrypt() {
    try {
        while (true) {
            system("cls");
            string inputChoice;
            cout << "Выберите способ ввода текста:" << endl;
            cout << "1. Ввод с консоли" << endl;
            cout << "2. Ввод из файла" << endl;
            cout << "3. Назад" << endl;
            cout << "Ваш выбор: ";
            cin >> inputChoice;

            if (inputChoice == "3") {
                return;
            }

            string text;
            try {
                if (inputChoice == "1") {
                    text = inputTextFromConsole();
                } else if (inputChoice == "2") {
                    text = inputTextFromFile();
                } else {
                    throw runtime_error("Неверный выбор.");
                }
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
                cout << "\nНажмите Enter для продолжения...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }

            if (text.empty()) continue;

            string result = Atbash(string(text));
            cout << "Дешифрованный текст: " << result << endl;

            while (true) {
                string saveChoice;
                cout << "\nСохранить результат в файл?" << endl;
                cout << "1. Да" << endl;
                cout << "2. Нет" << endl;
                cout << "3. Назад" << endl;
                cout << "Ваш выбор: ";
                cin >> saveChoice;

                if (saveChoice == "3") {
                    break; // возврат к выбору способа ввода
                }

                if (saveChoice == "1") {
                    try {
                        saveTextToFile(result);
                        cout << "\nНажмите Enter для продолжения...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                        return; // возврат в меню шифра
                    }
                    catch (const exception& e) {
                        cout << "Ошибка при сохранении: " << e.what() << endl;
                        cout << "\nНажмите Enter для продолжения...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                        continue; // повторить попытку сохранения
                    }
                }
                else if (saveChoice == "2") {
                    return; // возврат в меню шифра
                }
                else {
                    cout << "Неверный выбор." << endl;
                    cout << "\nНажмите Enter для продолжения...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                }
            }
        }
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        cout << "\nНажмите Enter для продолжения...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}