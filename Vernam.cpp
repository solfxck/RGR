#include "Header.h"
#include "utils.h"

using namespace std;
namespace fs = std::filesystem;

// ������� ��� ��������� ������� ������� (�������, �.�. ����������� �������� ��������� UTF-8)
int getCharIndex(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    int index = -1;
    
    // 0xC0-0xDF (������� ��������� ����� � win 1251)
    if (uc >= 0xC0 && uc <= 0xDF) {
        index = uc - 0xC0; // ������� 0-31
    }
    // 0xE0-0xFF (������� �������� �����)
    else if (uc >= 0xE0 && uc <= 0xFF) {
        index = (uc - 0xE0) + 32; // 32-63
    }

    else if (uc >= 'A' && uc <= 'Z') {
        index = (uc - 'A') + 64; // 64-89
    }

    else if (uc >= 'a' && uc <= 'z') {
        index = (uc - 'a') + 90; // 90-115
    }

    else if (uc >= '0' && uc <= '9') {
        index = (uc - '0') + 116; // 116-125
    }
    // ����������� ������� 126+
    else {
        const string specialChars = " .,!?@#$%^&*()-+=<>[]{}|/\"';:\\";
        size_t pos = specialChars.find(c);
        if (pos != string::npos) {
            index = 126 + pos;
        }
    }
    
    return index;
}

// ������� ��� ��������� ������� �� �������
char getCharFromIndex(int index) {
    if (index < 0) return '\0';
    
    if (index < 32) {
        return static_cast<char>(index + 0xC0);
    }

    else if (index < 64) {
        return static_cast<char>((index - 32) + 0xE0);
    }

    else if (index < 90) {
        return static_cast<char>((index - 64) + 'A');
    }

    else if (index < 116) {
        return static_cast<char>((index - 90) + 'a');
    }

    else if (index < 126) {
        return static_cast<char>((index - 116) + '0');
    }
    // ����������� �������
    else {
        const string specialChars = " .,!?@#$%^&*()-+=<>[]{}|/\"';:\\";
        int specialIndex = index - 126;
        if (specialIndex >= 0 && specialIndex < specialChars.length()) {
            return specialChars[specialIndex];
        }
    }
    
    return '\0';
}

// ������� ��� ��������� ���������� �����
string generateRandomKey(int length) {
    string key;
    key.reserve(length);
    
    srand(static_cast<unsigned int>(time(nullptr)));
    
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % 161; // ��������� ���������� �������
        key += getCharFromIndex(randomIndex);
    }
    
    return key;
}

// ������� ��� ���������� ������ � �������������� ������ �������
string Vernam(const string& text, const string& key) {    
    string result;
    result.reserve(text.length());
    
    for (size_t i = 0; i < text.length(); ++i) { // ������ �� ������� ������� ������
        unsigned char textChar = static_cast<unsigned char>(text[i]); // �������������� ������� � unsigned char
        unsigned char keyChar = static_cast<unsigned char>(key[i]);
        
        int textIndex = getCharIndex(text[i]); // ��������� ������� �������
        int keyIndex = getCharIndex(key[i]);
        
        // ���� ������ �� ������, ��������� ��� � ��������� ��� ���������
        if (textIndex == -1 || keyIndex == -1) { 
            result += text[i];
            continue;
        }
        
        // ���������� �������� XOR ��� ����������
        int resultIndex = (textIndex ^ keyIndex) % 256; // ����� �� 256, ����� �������� ������ � ��������� �� 0 �� 255 
        char resultChar = getCharFromIndex(resultIndex); // �������������� ������� � ������
        
        // ���� ��������� �� ������, ��������� �������� ������
        if (resultChar == '\0') { 
            result += text[i]; // ����������� �������� ������
        } else {
            result += resultChar; // ����� ���������� ������������� ������
        }
    }
    
    return result;
}

void VernamEncrypt() {
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

            string key;
            bool keyObtained = false; // ����, ����������� �� ��, ��� ���� ��� �������
            while (!keyObtained) {
                try {
                    // ����� ������� ��������� �����
                    string keyChoice;
                    cout << "\n�������� ������ ��������� �����:" << endl;
                    cout << "1. ������������� ��������� ����" << endl;
                    cout << "2. ��������� ���� �� �����" << endl;
                    cout << "��� �����: ";
                    getline(cin, keyChoice);

                    if (keyChoice != "1" && keyChoice != "2") {
                        throw invalid_argument("�������� ����� ������� ��������� �����.");
                    }

                    if (keyChoice == "1") {
                        key = generateRandomKey(text.length());
                        cout << "\n���� ������������." << endl;
                        
                        bool keySaveChosen = false;
                        while (!keySaveChosen) {
                            try {
                                // ���������� � ���������� �����
                                string saveKeyChoice; 
                                cout << "��������� ���� � ����?" << endl;
                                cout << "1. ��" << endl;
                                cout << "2. ���" << endl;
                                cout << "��� �����: ";
                                getline(cin, saveKeyChoice);

                                if (saveKeyChoice != "1" && saveKeyChoice != "2") {
                                    throw invalid_argument("�������� �����. ���������� �����.");
                                }

                                if (saveKeyChoice == "1") {
                                    saveKeyToFile(key);
                                }
                                keySaveChosen = true;
                            }
                            catch (const exception& e) {
                                cout << "������: " << e.what() << endl;
                                system("pause");
                                system("cls");
                                cout << "\n���� ������������." << endl;
                            }
                        }
                    } else {
                        key = loadKeyFromFile();
                    }

                    if (key.length() != text.length()) {
                        throw invalid_argument("����� ����� ������ ��������� � ������ ������!");
                    }
                    keyObtained = true;
                }
                catch (const exception& e) {
                    cout << "������: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "����� ��� ����������: " << text << endl;
                }
            }

            string result = Vernam(text, key);
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
void VernamDecrypt() {
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

            string key;
            bool keyObtained = false;
            while (!keyObtained) {
                try {
                    cout << "\n�������� ����� �� �����..." << endl;
                    key = loadKeyFromFile();

                    if (key.length() != text.length()) {
                        throw invalid_argument("����� ����� ������ ��������� � ������ ������!");
                    }
                    keyObtained = true;
                }
                catch (const exception& e) {
                    cout << "������: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "����� ��� �������������: " << text << endl;
                }
            }

            string result = Vernam(text, key);
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

                    if (inputChoice != "1" && inputChoice != "2" && inputChoice != "3") {
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