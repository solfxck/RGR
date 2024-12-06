#include "Header.h"
#include "utils.h"

using namespace std;

// ��������� ����������� �������� ������� �������� �����
vector<vector<int>> generateMagicSquare(int size) {
    if (size % 2 == 0) {
        throw runtime_error("������ ����������� �������� ������ ���� �������� ������!");
    }
    
    if (size < 3 || size > 9) {
        throw runtime_error("������ ����������� �������� ������ ���� �������� ������ �� 3 �� 9!");
    }

    vector<vector<int>> square(size, vector<int>(size, 0));
    int n = size;
    
    int i = n/2;
    int j = n-1;
    
    // ��������� ������� ������� �� 1 �� n*n
    for (int num = 1; num <= n * n;) {
        if (i == -1 && j == n) {
            j = n-2;
            i = 0;
        } else {
            if (j == n) j = 0;
            if (i < 0) i = n-1;
        }
        
        if (square[i][j] != 0) {
            j -= 2;
            i++;
            continue;
        } else {
            square[i][j] = num++;
        }
        
        j++;
        i--;
    }
    
    return square;
}

// ���������� ����� "���������� �������"
string MagicSquare(const string& text, const vector<vector<int>>& square, bool isEncrypt) {
    if (text.empty()) {
        throw runtime_error("������: ������ �����!");
    }
    
    if (!validateMagicSquare(square)) {
        throw runtime_error("������: ������������ ���������� �������!");
    }
    
    int n = square.size();
    int blockSize = n * n;
    
    // ������� ����� ������ ��� ���������
    string workText = text;
    
    // ������� ���������� �������������� ��������
    int supportedChars = 0;
    for (char c : workText) {
        if (isAllowedChar(c)) {
            supportedChars++;
        }
    }
    
    // ��������� ����� ��������� �� �������, �������� ������� �����
    while (supportedChars % blockSize != 0) {
        workText += ' ';
        supportedChars++;
    }
    
    string result;
    result.reserve(workText.length());
    
    // ��������� ����� ��� �������������� ��������
    vector<char> supportedBuffer;
    vector<size_t> originalPositions;
    
    // �������� �������������� ������� � �� �������
    for (size_t i = 0; i < workText.length(); i++) {
        if (isAllowedChar(workText[i])) {
            supportedBuffer.push_back(workText[i]);
            originalPositions.push_back(i);
        }
    }
    
    // ������������ �������������� ������� �������
    for (size_t blockStart = 0; blockStart < supportedBuffer.size(); blockStart += blockSize) {
        vector<char> block(blockSize);
        
        // ����������: ��������� ������� �������� ����������� ��������
        if (isEncrypt) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int pos = square[i][j] - 1;
                    block[pos] = supportedBuffer[blockStart + i * n + j];
                }
            }
        }
        // ������������: ��������������� �������� ������� ��������
        else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int pos = square[i][j] - 1;
                    block[i * n + j] = supportedBuffer[blockStart + pos];
                }
            }
        }
        
        // �������� ������������ ���� ������� � �����
        copy(block.begin(), block.end(), supportedBuffer.begin() + blockStart);
    }
    
    // ��������� ���������, �������� ������������ ������� �� �� �������� �������
    result = workText;
    for (size_t i = 0; i < supportedBuffer.size(); i++) {
        result[originalPositions[i]] = supportedBuffer[i];
    }
    
    // ������� ����������� ������� � �����
    while (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}

void MagicSquareEncrypt() {
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

            while (true) {
                // ����� ������� ����������� ��������
                string sizeChoice;
                cout << "\n�������� ������ ����������� �������� (3-9, ��������):" << endl;
                cout << "1. 3x3" << endl;
                cout << "2. 5x5" << endl;
                cout << "3. 7x7" << endl;
                cout << "4. 9x9" << endl;
                cout << "5. �����" << endl;
                cout << "��� �����: ";
                cin >> sizeChoice;

                if (sizeChoice == "5") {
                    break;
                }

                int size;
                try {
                    if (sizeChoice == "1") size = 3;
                    else if (sizeChoice == "2") size = 5;
                    else if (sizeChoice == "3") size = 7;
                    else if (sizeChoice == "4") size = 9;
                    else throw runtime_error("�������� ����� ������� ��������.");

                    vector<vector<int>> square = generateMagicSquare(size);
                    displayMagicSquare(square);

                    // ����������� ��������� ���������� �������
                    string saveSquareChoice;
                    cout << "��������� ���������� ������� � ����?" << endl;
                    cout << "1. ��" << endl;
                    cout << "2. ���" << endl;
                    cout << "��� �����: ";
                    cin >> saveSquareChoice;

                    if (saveSquareChoice == "1") {
                        string filename;
                        cout << "������� ��� ����� ��� ���������� ����������� ��������: ";
                        cin >> filename;
                        saveMagicSquare(square, filename);
                        cout << "���������� ������� �������� � ����: " << filename << endl;
                    }

                    string encrypted = MagicSquare(text, square, true);
                    cout << "\n����� ������� ����������" << endl;
                    cout << "������������� �����: " << encrypted << endl;

                    while (true) {
                        // ���������� ����������
                        string saveChoice;
                        cout << "\n��������� ��������� � ����?" << endl;
                        cout << "1. ��" << endl;
                        cout << "2. ���" << endl;
                        cout << "3. �����" << endl;
                        cout << "��� �����: ";
                        cin >> saveChoice;

                        if (saveChoice == "3") {
                            break;
                        }

                        if (saveChoice == "1") {
                            try {
                                saveTextToFile(encrypted);
                                cout << "\n������� Enter ��� �����������...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                return;
                            }
                            catch (const exception& e) {
                                cout << "������ ��� ����������: " << e.what() << endl;
                                cout << "\n������� Enter ��� �����������...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                continue;
                            }
                        }
                        else if (saveChoice == "2") {
                            return;
                        }
                        else {
                            cout << "�������� �����." << endl;
                            cout << "\n������� Enter ��� �����������...";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.get();
                        }
                    }
                }
                catch (const exception& e) {
                    cout << "������: " << e.what() << endl;
                    cout << "\n������� Enter ��� �����������...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    continue;
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

void MagicSquareDecrypt() {
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

            while (true) {
                // ����� ������� ��������� ����������� ��������
                string squareChoice;
                cout << "\n�������� ������ ��������� ����������� ��������:" << endl;
                cout << "1. ��������� �� �����" << endl;
                cout << "2. ������� �����" << endl;
                cout << "3. �����" << endl;
                cout << "��� �����: ";
                cin >> squareChoice;

                if (squareChoice == "3") {
                    break;
                }

                vector<vector<int>> square;
                try {
                    if (squareChoice == "1") {
                        string filename;
                        cout << "������� ��� ����� � ���������� ���������: ";
                        cin >> filename;
                        square = loadMagicSquare(filename);
                        displayMagicSquare(square);
                    }
                    else if (squareChoice == "2") {
                        string sizeChoice;
                        cout << "\n�������� ������ ����������� �������� (3-9, ��������):" << endl;
                        cout << "1. 3x3" << endl;
                        cout << "2. 5x5" << endl;
                        cout << "3. 7x7" << endl;
                        cout << "4. 9x9" << endl;
                        cout << "5. �����" << endl;
                        cout << "��� �����: ";
                        cin >> sizeChoice;

                        if (sizeChoice == "5") {
                            continue;
                        }

                        int size;
                        if (sizeChoice == "1") size = 3;
                        else if (sizeChoice == "2") size = 5;
                        else if (sizeChoice == "3") size = 7;
                        else if (sizeChoice == "4") size = 9;
                        else throw runtime_error("�������� ����� ������� ��������.");

                        square = generateMagicSquare(size);
                        displayMagicSquare(square);

                        // ����������� ��������� ���������� �������
                        string saveSquareChoice;
                        cout << "��������� ���������� ������� � ����?" << endl;
                        cout << "1. ��" << endl;
                        cout << "2. ���" << endl;
                        cout << "��� �����: ";
                        cin >> saveSquareChoice;

                        if (saveSquareChoice == "1") {
                            string filename;
                            cout << "������� ��� ����� ��� ���������� ����������� ��������: ";
                            cin >> filename;
                            saveMagicSquare(square, filename);
                            cout << "���������� ������� �������� � ����: " << filename << endl;
                        }
                    }
                    else {
                        throw runtime_error("�������� �����.");
                    }

                    string decrypted = MagicSquare(text, square, false);
                    cout << "\n����� ������� ����������" << endl;
                    cout << "������������� �����: " << decrypted << endl;

                    while (true) {
                        // ���������� ����������
                        string saveChoice;
                        cout << "\n��������� ��������� � ����?" << endl;
                        cout << "1. ��" << endl;
                        cout << "2. ���" << endl;
                        cout << "3. �����" << endl;
                        cout << "��� �����: ";
                        cin >> saveChoice;

                        if (saveChoice == "3") {
                            break;
                        }

                        if (saveChoice == "1") {
                            try {
                                saveTextToFile(decrypted);
                                cout << "\n������� Enter ��� �����������...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                return;
                            }
                            catch (const exception& e) {
                                cout << "������ ��� ����������: " << e.what() << endl;
                                cout << "\n������� Enter ��� �����������...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                continue;
                            }
                        }
                        else if (saveChoice == "2") {
                            return;
                        }
                        else {
                            cout << "�������� �����." << endl;
                            cout << "\n������� Enter ��� �����������...";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.get();
                        }
                    }
                }
                catch (const exception& e) {
                    cout << "������: " << e.what() << endl;
                    cout << "\n������� Enter ��� �����������...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    continue;
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