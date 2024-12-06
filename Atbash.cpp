#include "Header.h"
#include "utils.h"

using namespace std;

// ����������/������������ �����
string Atbash(string text) { 
    if (text.empty()) {
        throw runtime_error("������: ������ �����!");
    }

    // ����� ������������ �������� ��������
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
                auto it = symbolMap.find(ch);
                if (it != symbolMap.end()) {
                    ch = it->second;
                }
            }
        }
    }
    catch (const exception& e) {
        throw runtime_error("������ ��� ����������: " + string(e.what()));
    }
    return text;
}

// ������� ����������
void AtbashEncrypt() {
    try {
        while (true) {
            system("cls");
            string inputChoice;
            cout << "�������� ������ ����� ������:" << endl;
            cout << "1. ���� � �������" << endl;
            cout << "2. ���� �� �����" << endl;
            cout << "3. �����" << endl;
            cout << "��� �����: ";
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
                    throw runtime_error("�������� �����.");
                }
            }
            catch (const exception& e) {
                cout << "������: " << e.what() << endl;
                cout << "\n������� Enter ��� �����������...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }

            if (text.empty()) continue;

            string result = Atbash(string(text));
            cout << "������������� �����: " << result << endl;

            while (true) {
                string saveChoice;
                cout << "\n��������� ��������� � ����?" << endl;
                cout << "1. ��" << endl;
                cout << "2. ���" << endl;
                cout << "3. �����" << endl;
                cout << "��� �����: ";
                cin >> saveChoice;

                if (saveChoice == "3") {
                    break; // ������� � ������ ������� �����
                }

                if (saveChoice == "1") {
                    try {
                        saveTextToFile(result);
                        cout << "\n������� Enter ��� �����������...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                        return; // ������� � ���� �����
                    }
                    catch (const exception& e) {
                        cout << "������ ��� ����������: " << e.what() << endl;
                        cout << "\n������� Enter ��� �����������...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                        continue; // ��������� ������� ����������
                    }
                }
                else if (saveChoice == "2") {
                    return; // ������� � ���� �����
                }
                else {
                    cout << "�������� �����." << endl;
                    cout << "\n������� Enter ��� �����������...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                }
            }
        }
    }
    catch (const exception& e) {
        cout << "������: " << e.what() << endl;
        cout << "\n������� Enter ��� �����������...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}

// ������� ������������
void AtbashDecrypt() {
    try {
        while (true) {
            system("cls");
            string inputChoice;
            cout << "�������� ������ ����� ������:" << endl;
            cout << "1. ���� � �������" << endl;
            cout << "2. ���� �� �����" << endl;
            cout << "3. �����" << endl;
            cout << "��� �����: ";
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
                    throw runtime_error("�������� �����.");
                }
            }
            catch (const exception& e) {
                cout << "������: " << e.what() << endl;
                cout << "\n������� Enter ��� �����������...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }

            if (text.empty()) continue;

            string result = Atbash(string(text));
            cout << "������������� �����: " << result << endl;

            while (true) {
                string saveChoice;
                cout << "\n��������� ��������� � ����?" << endl;
                cout << "1. ��" << endl;
                cout << "2. ���" << endl;
                cout << "3. �����" << endl;
                cout << "��� �����: ";
                cin >> saveChoice;

                if (saveChoice == "3") {
                    break; // ������� � ������ ������� �����
                }

                if (saveChoice == "1") {
                    try {
                        saveTextToFile(result);
                        cout << "\n������� Enter ��� �����������...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                        return; // ������� � ���� �����
                    }
                    catch (const exception& e) {
                        cout << "������ ��� ����������: " << e.what() << endl;
                        cout << "\n������� Enter ��� �����������...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                        continue; // ��������� ������� ����������
                    }
                }
                else if (saveChoice == "2") {
                    return; // ������� � ���� �����
                }
                else {
                    cout << "�������� �����." << endl;
                    cout << "\n������� Enter ��� �����������...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                }
            }
        }
    }
    catch (const exception& e) {
        cout << "������: " << e.what() << endl;
        cout << "\n������� Enter ��� �����������...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}