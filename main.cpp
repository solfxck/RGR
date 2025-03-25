#include "Header.h"
#include "utils.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        // �����������
        string login, password;
        string correctLogin = "admin";
        string correctPassword = "123";

        cout << "������� �����: ";
        getline(cin, login);
        cout << "������� ������: ";
        getline(cin, password);

        // �������� ������ � ������
        if (login != correctLogin || password != correctPassword || 
            login.find(' ') != string::npos || password.find(' ') != string::npos) {
            throw runtime_error("�������� ����� ��� ������. ������ ��������.");
        }

        string choice; // ��� �������� ������
        bool isExit = false; // ��� ���������� ������

        while (!isExit) {
            try {
                system("cls");
                cout << "�������� ��������:" << endl;
                cout << "1. ���� ������" << endl;
                cout << "2. ���� �������" << endl;
                cout << "3. ���������� �������" << endl;
                cout << "4. �����" << endl;
                cout << "��� �����: ";
                
                getline(cin, choice);
                
                if (choice.length() != 1 || !isdigit(choice[0]) || choice[0] < '1' || choice[0] > '4' || 
                    choice.find(' ') != string::npos) {
                    throw invalid_argument("�������� �����. ���������� �����."); 
                }

                switch (choice[0]) {

                    case '1': {
                        bool backToMain = false;
                        while (!backToMain) {
                            try {
                                system("cls");
                                cout << "���� �����:" << endl;
                                cout << "1. ����������" << endl;
                                cout << "2. ������������" << endl;
                                cout << "3. �����" << endl;
                                cout << "��� �����: ";
                                
                                string subChoice; // ��� �������� ������
                                getline(cin, subChoice); 
                                
                                if (subChoice == "1") AtbashEncrypt();
                                else if (subChoice == "2") AtbashDecrypt();
                                else if (subChoice == "3") backToMain = true;
                                else throw invalid_argument("�������� �����");
                            }
                            catch (const exception& e) {
                                cerr << "������: " << e.what() << endl;
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
                                cout << "���� �������:" << endl;
                                cout << "1. ����������" << endl;
                                cout << "2. ������������" << endl;
                                cout << "3. �����" << endl;
                                cout << "��� �����: ";
                                
                                string subChoice;
                                getline(cin, subChoice);
                                
                                if (subChoice == "1") VernamEncrypt();
                                else if (subChoice == "2") VernamDecrypt();
                                else if (subChoice == "3") backToMain = true;
                                else throw invalid_argument("�������� �����");
                            }
                            catch (const exception& e) {
                                cerr << "������: " << e.what() << endl;
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
                                cout << "���� \"���������� �������\":" << endl;
                                cout << "1. ����������" << endl;
                                cout << "2. ������������" << endl;
                                cout << "3. �����" << endl;
                                cout << "��� �����: ";
                                
                                string subChoice;
                                getline(cin, subChoice);
                                
                                if (subChoice == "1") MagicSquareEncrypt();
                                else if (subChoice == "2") MagicSquareDecrypt();
                                else if (subChoice == "3") backToMain = true;
                                else throw invalid_argument("�������� �����");
                            }
                            catch (const exception& e) {
                                cerr << "������: " << e.what() << endl;
                                system("pause");
                            }
                        }
                        break;
                    }
                    case '4':
                        isExit = true;
                        cout << "���������� ������ . . ." << endl;
                        break;
                }
            }

            catch (const exception& e) {
                cerr << "������: " << e.what() << endl;
                system("pause");
            }
        }
    }

    catch (const exception& e) {
        cerr << "����������� ������: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}