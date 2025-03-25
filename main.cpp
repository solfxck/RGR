#include "Header.h"
#include "utils.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        // авторизация
        string login, password;
        string correctLogin = "admin";
        string correctPassword = "123";

        cout << "Введите логин: ";
        getline(cin, login);
        cout << "Введите пароль: ";
        getline(cin, password);

        // проверка логина и пароля
        if (login != correctLogin || password != correctPassword || 
            login.find(' ') != string::npos || password.find(' ') != string::npos) {
            throw runtime_error("Неверный логин или пароль. Доступ запрещен.");
        }

        string choice; // для хранения выбора
        bool isExit = false; // для завершения работы

        while (!isExit) {
            try {
                system("cls");
                cout << "Выберите действие:" << endl;
                cout << "1. Шифр Атбаша" << endl;
                cout << "2. Шифр Вернама" << endl;
                cout << "3. Магический квадрат" << endl;
                cout << "4. Выход" << endl;
                cout << "Ваш выбор: ";
                
                getline(cin, choice);
                
                if (choice.length() != 1 || !isdigit(choice[0]) || choice[0] < '1' || choice[0] > '4' || 
                    choice.find(' ') != string::npos) {
                    throw invalid_argument("Неверный выбор. Попробуйте снова."); 
                }

                switch (choice[0]) {

                    case '1': {
                        bool backToMain = false;
                        while (!backToMain) {
                            try {
                                system("cls");
                                cout << "Шифр Атбаш:" << endl;
                                cout << "1. Шифрование" << endl;
                                cout << "2. Дешифрование" << endl;
                                cout << "3. Назад" << endl;
                                cout << "Ваш выбор: ";
                                
                                string subChoice; // для хранения выбора
                                getline(cin, subChoice); 
                                
                                if (subChoice == "1") AtbashEncrypt();
                                else if (subChoice == "2") AtbashDecrypt();
                                else if (subChoice == "3") backToMain = true;
                                else throw invalid_argument("Неверный выбор");
                            }
                            catch (const exception& e) {
                                cerr << "Ошибка: " << e.what() << endl;
                                system("pause");
                            }
                        }
                        break;
                    }

                    case '2': {
                        bool backToMain = false;
                        while (!backToMain) {
                            try {
                                system("cls");
                                cout << "Шифр Вернама:" << endl;
                                cout << "1. Шифрование" << endl;
                                cout << "2. Дешифрование" << endl;
                                cout << "3. Назад" << endl;
                                cout << "Ваш выбор: ";
                                
                                string subChoice;
                                getline(cin, subChoice);
                                
                                if (subChoice == "1") VernamEncrypt();
                                else if (subChoice == "2") VernamDecrypt();
                                else if (subChoice == "3") backToMain = true;
                                else throw invalid_argument("Неверный выбор");
                            }
                            catch (const exception& e) {
                                cerr << "Ошибка: " << e.what() << endl;
                                system("pause");
                            }
                        }
                        break;
                    }

                    case '3': {
                        bool backToMain = false;
                        while (!backToMain) {
                            try {
                                system("cls");
                                cout << "Шифр \"Магический квадрат\":" << endl;
                                cout << "1. Шифрование" << endl;
                                cout << "2. Дешифрование" << endl;
                                cout << "3. Назад" << endl;
                                cout << "Ваш выбор: ";
                                
                                string subChoice;
                                getline(cin, subChoice);
                                
                                if (subChoice == "1") MagicSquareEncrypt();
                                else if (subChoice == "2") MagicSquareDecrypt();
                                else if (subChoice == "3") backToMain = true;
                                else throw invalid_argument("Неверный выбор");
                            }
                            catch (const exception& e) {
                                cerr << "Ошибка: " << e.what() << endl;
                                system("pause");
                            }
                        }
                        break;
                    }
                    case '4':
                        isExit = true;
                        cout << "Завершение работы . . ." << endl;
                        break;
                }
            }

            catch (const exception& e) {
                cerr << "Ошибка: " << e.what() << endl;
                system("pause");
            }
        }
    }

    catch (const exception& e) {
        cerr << "Критическая ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}