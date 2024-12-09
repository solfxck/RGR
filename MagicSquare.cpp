#include "Header.h"
#include "utils.h"

using namespace std;

// ��������� ����������� ��������
vector<vector<int>> generateMagicSquare(int size) {
    vector<vector<int>> square(size, vector<int>(size, 0)); // ������� ������ �������
    int n = size;
    
    int i = n / 2; // ��������� ����������
    int j = n - 1; // ��������� ����������
    
    // ��������� ������� ������� �� 1 �� n*n
    for (int num = 1; num <= n * n;) { // num - ����� �����
        if (i == -1 && j == n) { // ���� �� ����� �� ������� ��������
            j = n-2; // ������������ �� ������������� ������
            i = 0; // � ��������� �� ������ �������
        } else {
            if (j == n) j = 0; // ���� �� ����� �� ������� �������, ������������ �� ������ �������
            if (i < 0) i = n-1; // ���� �� ����� �� ������� ������, ������������ �� ��������� ������
        }
        
        if (square[i][j] != 0) { // ���� ������ ��� ���������
            j -= 2; // ������������ �� ������������� ������
            i++; // � ��������� �� ������ �������
            continue; // ���������� ����
        } else { // ���� ������ �����
            square[i][j] = num++; // ��������� ������ ������� 
        }
        
        j++; // ��������� �� ��������� �������
        i--; // � �� ��������� ������
    }
    
    return square;
}

// ���������� ����� "���������� �������"
string MagicSquare(const string& text, const vector<vector<int>>& square, bool isEncrypt) {    
    int n = square.size();
    int blockSize = n * n; 
    
    // ������� ����� ������ ��� ��������� (����� �� �������� �������� �����)
    string workText = text; 
    
    // ������� ���������� �������������� ��������
    int supportedChars = 0; // ���������� �������������� ��������
    for (char c : workText) {
        if (isAllowedChar(c)) { 
            supportedChars++;
        }
    }
    
    // ��������� ����� ��������� �� �������, �������� ������� �����
    while (supportedChars % blockSize != 0) { // ���� ���������� �������������� �������� �� ������ ������� �����
        workText += ' '; // ��������� ������
        supportedChars++;
    }
    
    string result;
    result.reserve(workText.length()); // ��������������� ��������� ������ (��� �����������)
    
    // ��������� ����� ��� �������������� �������� (����� �� �������� �������� �����)
    vector<char> supportedBuffer;
    vector<size_t> originalPositions; // ������� �������� ��������
    
    // �������� �������������� ������� � �� �������
    for (size_t i = 0; i < workText.length(); i++) { // �������� �� ������
        if (isAllowedChar(workText[i])) { // ���� ������ ��������������
            supportedBuffer.push_back(workText[i]); // ��������� ��� � �����
            originalPositions.push_back(i); // ���������� ��� �������
        }
    }
    
    // ������������ �������������� ������� �������
    for (size_t blockStart = 0; blockStart < supportedBuffer.size(); blockStart += blockSize) { // �������� �� ������
        vector<char> block(blockSize);
        
        // ����������: ��������� ������� �������� ����������� ��������
        if (isEncrypt) {
            for (int i = 0; i < n; i++) { // �������� �� �������
                for (int j = 0; j < n; j++) { // �������� �� ��������
                    int pos = square[i][j] - 1; // ��������� �������
                    block[pos] = supportedBuffer[blockStart + i * n + j]; // �������� ������ � ���� �� �������: 
                                            // ��������� ���� + ����� ������ * ������ �������� + ����� �������
                                            // ��� ������� ��������� ������� ������� � �����
                }
            }
        }
        // ������������: ��������������� �������� ������� ��������
        else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int pos = square[i][j] - 1;
                    block[i * n + j] = supportedBuffer[blockStart + pos]; // �������� ������ � ���� �� �������: 
                                            // ����� ������ * ������ �������� + ����� �������
                }
            }
        }
        
        // �������� ������������ ���� ������� � �����
        copy(block.begin(), block.end(), supportedBuffer.begin() + blockStart);
    }
    
    // ��������� ���������, �������� ������������ ������� �� �� �������� �������
    result = workText;
    for (size_t i = 0; i < supportedBuffer.size(); i++) { // �������� �� �������������� ��������
        result[originalPositions[i]] = supportedBuffer[i]; // ��������� ������ �� ��� �������� �������
    }
    
    // ������� ����������� ������� � �����
    while (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}

void MagicSquareEncrypt() {
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

            if (inputChoice.length() != 1 || !isdigit(inputChoice[0]) || 
                inputChoice[0] < '1' || inputChoice[0] > '3' || 
                inputChoice.find(' ') != string::npos) {
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

            vector<vector<int>> square;
            bool squareObtained = false;
            while (!squareObtained) {
                try {
                    string sizeChoice;
                    cout << "\n�������� ������ ����������� ��������:" << endl;
                    cout << "1. 3x3" << endl;
                    cout << "2. 5x5" << endl;
                    cout << "3. 7x7" << endl;
                    cout << "4. 9x9" << endl;
                    cout << "��� �����: ";
                    getline(cin, sizeChoice);

                    if (sizeChoice.length() != 1 || !isdigit(sizeChoice[0]) || 
                        sizeChoice[0] < '1' || sizeChoice[0] > '4' || 
                        sizeChoice.find(' ') != string::npos) {
                        throw invalid_argument("�������� ����� ������� ��������.");
                    }

                    int size;
                    if (sizeChoice == "1") size = 3;
                    else if (sizeChoice == "2") size = 5;
                    else if (sizeChoice == "3") size = 7;
                    else size = 9;

                    square = generateMagicSquare(size);
                    displayMagicSquare(square);
                    
                    bool saveSquareChosen = false;
                    while (!saveSquareChosen) {
                        try {
                            string saveSquareChoice;
                            cout << "\n��������� ���������� ������� � ����?" << endl;
                            cout << "1. ��" << endl;
                            cout << "2. ���" << endl;
                            cout << "��� �����: ";
                            getline(cin, saveSquareChoice);

                            if (saveSquareChoice.length() != 1 || !isdigit(saveSquareChoice[0]) || 
                                saveSquareChoice[0] < '1' || saveSquareChoice[0] > '2' || 
                                saveSquareChoice.find(' ') != string::npos) {
                                throw invalid_argument("�������� �����. ���������� �����.");
                            }

                            if (saveSquareChoice == "1") {
                                saveMagicSquare(square);
                            }
                            saveSquareChosen = true;
                        }
                        catch (const exception& e) {
                            cout << "������: " << e.what() << endl;
                            system("pause");
                            system("cls");
                            displayMagicSquare(square);
                        }
                    }
                    squareObtained = true;
                }
                catch (const exception& e) {
                    cout << "������: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "����� ��� ����������: " << text << endl;
                }
            }

            string result = MagicSquare(text, square, true);
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

                    if (saveChoice.length() != 1 || !isdigit(saveChoice[0]) || 
                        saveChoice[0] < '1' || saveChoice[0] > '3' || 
                        saveChoice.find(' ') != string::npos) {
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

void MagicSquareDecrypt() {
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

            if (inputChoice.length() != 1 || !isdigit(inputChoice[0]) || 
                inputChoice[0] < '1' || inputChoice[0] > '3' || 
                inputChoice.find(' ') != string::npos) {
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

            vector<vector<int>> square;
            bool squareObtained = false;
            while (!squareObtained) {
                try {
                    cout << "\n�������� ����������� �������� �� �����..." << endl;
                    square = loadMagicSquare();

                    if (!validateMagicSquare(square)) {
                        throw invalid_argument("������������ ���������� �������!");
                    }
                    squareObtained = true;
                }
                catch (const exception& e) {
                    cout << "������: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "����� ��� �������������: " << text << endl;
                }
            }

            string result = MagicSquare(text, square, false);
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

                    if (saveChoice.length() != 1 || !isdigit(saveChoice[0]) || 
                        saveChoice[0] < '1' || saveChoice[0] > '3' || 
                        saveChoice.find(' ') != string::npos) {
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