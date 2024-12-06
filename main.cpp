#include "Header.h"
#include "utils.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // проверка пароля
    string login, password;
    string correctLogin = "admin";
    string correctPassword = "123";

    cout << "Введите логин: ";
    cin >> login;
    cout << "Введите пароль: ";
    cin >> password;

    if (login != correctLogin || password != correctPassword) {
        cout << "Неверный логин или пароль. Доступ запрещен." << endl;
        return 0;
    }

    string choice; // переменная для выбора
    bool isExit = false; // переменная для выхода

    while (!isExit) {
        system("cls");

        // главное меню
        cout << "Выберите действие:" << endl;
        cout << "1. Шифр Атбаша" << endl;
        cout << "2. Шифр Вернама" << endl;
        cout << "3. Магический квадрат" << endl;
        cout << "4. Выход" << endl;
        cout << "Ваш выбор: ";
        
        cin >> choice;

        // обработка выбора пользователя
        switch (choice[0]) {
            case '1': {
                bool backToMain = false;
                while (!backToMain) {
                    system("cls");
                    cout << "Шифр Атбаш:" << endl;
                    cout << "1. Шифрование" << endl;
                    cout << "2. Дешифрование" << endl;
                    cout << "3. Назад" << endl;
                    cout << "Ваш выбор: ";
                    
                    string choice;
                    cin >> choice;
                    
                    if (choice == "1") {
                        AtbashEncrypt();
                    }
                    else if (choice == "2") {
                        AtbashDecrypt();
                    }
                    else if (choice == "3") {
                        backToMain = true;
                    }
                    else {
                        cout << "Неверный выбор." << endl;
                    }
                }
                break;
            }
            case '2': {
                bool backToMain = false;
                while (!backToMain) {
                    system("cls");
                    cout << "Шифр Вернама:" << endl;
                    cout << "1. Шифрование" << endl;
                    cout << "2. Дешифрование" << endl;
                    cout << "3. Назад" << endl;
                    cout << "Ваш выбор: ";
                    
                    string choice;
                    cin >> choice;
                    
                    if (choice == "1") {
                        VernamEncrypt();
                    }
                    else if (choice == "2") {
                        VernamDecrypt();
                    }
                    else if (choice == "3") {
                        backToMain = true;
                    }
                    else {
                        cout << "Неверный выбор." << endl;
                    }
                }
                break;
            }
            case '3': {
                bool backToMain = false;
                while (!backToMain) {
                    system("cls");
                    cout << "Шифр \"Магический квадрат\":" << endl;
                    cout << "1. Шифрование" << endl;
                    cout << "2. Дешифрование" << endl;
                    cout << "3. Назад" << endl;
                    cout << "Ваш выбор: ";
                    
                    string choice;
                    cin >> choice;
                    
                    if (choice == "1") {
                        MagicSquareEncrypt();
                    }
                    else if (choice == "2") {
                        MagicSquareDecrypt();
                    }
                    else if (choice == "3") {
                        backToMain = true;
                    }
                    else {
                        cout << "Неверный выбор." << endl;
                    }
                }
                break;
            }
            case '4':
                isExit = true;
                cout << "Завершение работы . . ." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
    return 0;
}