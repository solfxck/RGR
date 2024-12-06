#include "Header.h"
#include "utils.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // �������� ������
    string login, password;
    string correctLogin = "admin";
    string correctPassword = "123";

    cout << "������� �����: ";
    cin >> login;
    cout << "������� ������: ";
    cin >> password;

    if (login != correctLogin || password != correctPassword) {
        cout << "�������� ����� ��� ������. ������ ��������." << endl;
        return 0;
    }

    string choice; // ���������� ��� ������
    bool isExit = false; // ���������� ��� ������

    while (!isExit) {
        system("cls");

        // ������� ����
        cout << "�������� ��������:" << endl;
        cout << "1. ���� ������" << endl;
        cout << "2. ���� �������" << endl;
        cout << "3. ���������� �������" << endl;
        cout << "4. �����" << endl;
        cout << "��� �����: ";
        
        cin >> choice;

        // ��������� ������ ������������
        switch (choice[0]) {
            case '1': {
                bool backToMain = false;
                while (!backToMain) {
                    system("cls");
                    cout << "���� �����:" << endl;
                    cout << "1. ����������" << endl;
                    cout << "2. ������������" << endl;
                    cout << "3. �����" << endl;
                    cout << "��� �����: ";
                    
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
                        cout << "�������� �����." << endl;
                    }
                }
                break;
            }
            case '2': {
                bool backToMain = false;
                while (!backToMain) {
                    system("cls");
                    cout << "���� �������:" << endl;
                    cout << "1. ����������" << endl;
                    cout << "2. ������������" << endl;
                    cout << "3. �����" << endl;
                    cout << "��� �����: ";
                    
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
                        cout << "�������� �����." << endl;
                    }
                }
                break;
            }
            case '3': {
                bool backToMain = false;
                while (!backToMain) {
                    system("cls");
                    cout << "���� \"���������� �������\":" << endl;
                    cout << "1. ����������" << endl;
                    cout << "2. ������������" << endl;
                    cout << "3. �����" << endl;
                    cout << "��� �����: ";
                    
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
                        cout << "�������� �����." << endl;
                    }
                }
                break;
            }
            case '4':
                isExit = true;
                cout << "���������� ������ . . ." << endl;
                break;
            default:
                cout << "�������� �����. ���������� �����." << endl;
        }
    }
    return 0;
}