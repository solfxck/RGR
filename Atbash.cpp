#include "Header.h"
#include "utils.h"

using namespace std;

// ����������/������������ �����
string Atbash(string text) { 
    // ������� ������������
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
        // ������� �������
        if (ch >= '�' && ch <= '�') {
            ch = '�' - (ch - '�');
        }
        else if (ch >= '�' && ch <= '�') {
            ch = '�' - (ch - '�');
        }
        // ���������� �������
        else if (ch >= 'A' && ch <= 'Z') {
            ch = 'z' - (ch - 'A');
        }
        else if (ch >= 'a' && ch <= 'z') {
            ch = 'Z' - (ch - 'a');
        }
        // ����� � ����������� �������
        else {
            auto it = symbolMap.find(ch); // ����� ������� � ������� (���������� ��������)
            if (it != symbolMap.end()) { // ���� ������ ���?��� (��������, ��� �������� ��������� �� ��������� ����� ���������� ��������)
                ch = it->second; // ������ (��������� �� ������� ��������)
            }
        }
    }

    return text;
}

void AtbashEncrypt() {
    while (true) {
        system("cls");

        string inputChoice;
        cout << "�������� ������ ����� ������:" << endl;
        cout << "1. ���� � �������" << endl;
        cout << "2. ���� �� �����" << endl;
        cout << "3. �����" << endl;
        cout << "��� �����: ";
        
        try {
            getline(cin, inputChoice);

            if (inputChoice == "3") {
                return;
            }

            if (inputChoice != "1" && inputChoice != "2" && inputChoice != "3") {
                throw invalid_argument("�������� �����. ���������� �����.");
            }

            string text;
            if (inputChoice == "1") {
                text = inputTextFromConsole();
            } else if (inputChoice == "2") {
                text = inputTextFromFile();
            }

            if (text.empty()) {
                throw invalid_argument("����� �� ����� ���� ������.");
            }

            string result = Atbash(text);
            cout << "\n������������� �����: " << result << endl;

            bool saveMenuActive = true;
            while (saveMenuActive) {
                try {
                    string saveChoice;
                    cout << "\n��������� ��������� � ����?" << endl;
                    cout << "1. ��" << endl;
                    cout << "2. ���" << endl;
                    cout << "3. �����" << endl;
                    cout << "��� �����: ";
                    getline(cin, saveChoice);

                    if (saveChoice != "1" && saveChoice != "2" && saveChoice != "3") {
                        throw invalid_argument("�������� �����. ���������� �����.");
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
                    cout << "������: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "\n������������� �����: " << result << endl;
                }
            }
        }
        catch (const exception& e) {
            cout << "������: " << e.what() << endl;
            system("pause");
        }
    }
}

// ������� ������������
void AtbashDecrypt() {
    while (true) {
        system("cls");

        string inputChoice;
        cout << "�������� ������ ����� ������:" << endl;
        cout << "1. ���� � �������" << endl;
        cout << "2. ���� �� �����" << endl;
        cout << "3. �����" << endl;
        cout << "��� �����: ";
        
        try {
            getline(cin, inputChoice);

            if (inputChoice == "3") {
                return;
            }

            if (inputChoice != "1" && inputChoice != "2" && inputChoice != "3") {
                throw invalid_argument("�������� �����. ���������� �����.");
            }

            string text;
            if (inputChoice == "1") {
                text = inputTextFromConsole();
            } else if (inputChoice == "2") {
                text = inputTextFromFile();
            }

            if (text.empty()) {
                throw invalid_argument("����� �� ����� ���� ������.");
            }

            string result = Atbash(text);
            cout << "\n�������������� �����: " << result << endl;

            bool saveMenuActive = true;
            while (saveMenuActive) {
                try {
                    string saveChoice;
                    cout << "\n��������� ��������� � ����?" << endl;
                    cout << "1. ��" << endl;
                    cout << "2. ���" << endl;
                    cout << "3. �����" << endl;
                    cout << "��� �����: ";
                    getline(cin, saveChoice);

                    if (saveChoice != "1" && saveChoice != "2" && saveChoice != "3") {
                        throw invalid_argument("�������� �����. ���������� �����.");
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
                    cout << "������: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "\n�������������� �����: " << result << endl;
                }
            }
        }
        catch (const exception& e) {
            cout << "������: " << e.what() << endl;
            system("pause");
        }
    }
}