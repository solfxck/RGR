#include "Header.h"
#include "utils.h"

namespace fs = std::filesystem;
using namespace std;

// ������� ����� ������ � �������
string inputTextFromConsole() {
    string text;
    cout << "������� �����: ";
    getline(cin, text);
    
    if (text.empty()) {
        throw runtime_error("����� �� ����� ���� ������!");
    }
    return text;
}

// ������� ����� ������ �� �����
string inputTextFromFile() {
    string filename;
    cout << "������� ��� �����: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("������������ ��� �����!");
    }

    ifstream file(filename); // ��������� ����
    if (!file.is_open()) {
        throw runtime_error("������ �������� �����: " + filename);
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>()); // ������ ���� � ������
    file.close(); // ��������� ����

    if (text.empty()) {
        throw runtime_error("���� ����!");
    }
    return text;
}

// ������� ���������� ������ � ����
void saveTextToFile(const string& text) {
    if (text.empty()) {
        throw runtime_error("������ ��������� - ����� ����!");
    }

    string filename;
    cout << "������� ��� ����� ��� ����������: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("������������ ��� �����!");
    }

    ofstream file(filename); // ��������� ����
    if (!file.is_open()) {
        throw runtime_error("������ �������� �����: " + filename);
    }

    file << text; // ���������� ����� � ����
    file.close(); // ��������� ����
    cout << "����� �������� � ����: " << filename << endl;
}

// ���������� ����� � ����
void saveKeyToFile(const string& key) {
    string filename;
    
    cout << "������� ��� ����� ��� ���������� �����: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("������������ ��� �����!");
    }

    // ��������� ���������� .key, ���� ��� ���
    if (fs::path(filename).extension().empty()) {
        filename += ".key";
    }

    ofstream keyFile(filename, ios::binary); // ��������� ����
    if (!keyFile.is_open()) { // ���� �� ������� ������� ����
        throw runtime_error("������ �������� ����� �����: " + filename);
    }

    keyFile.write(key.c_str(), key.length()); // ���������� ���� � ���� 
                                              // c_str() ���������� ��������� �� ������ ������ 
                                              // length() ���������� ����� ������ 
    keyFile.close();

    cout << "���� �������� � ����: " << filename << endl;
}

// �������� ����� �� �����
string loadKeyFromFile() {
    string filename;
    
    cout << "������� ��� ����� �����: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("������������ ��� �����!");
    }

    ifstream keyFile(filename, ios::binary); // ��������� ���� (ios::binary - ������ � �������� �������, ��� ���������� ������������)
    if (!keyFile.is_open()) {
        throw runtime_error("������ �������� ����� �����: " + filename);
    }

    // ������ ���� � ������
    stringstream buffer; 
    buffer << keyFile.rdbuf(); // ���������� ���������� ����� � �����
    string key = buffer.str(); // ����������� ����� � ������
    keyFile.close();

    if (key.empty()) {
        throw runtime_error("���� ����� ����!");
    }

    return key;
}

// �������� ������������ ����������� ��������
bool validateMagicSquare(const vector<vector<int>>& square) {
    if (square.empty() || square[0].empty() || square.size() != square[0].size()) { // �������� �� ������ �������
        return false;
    }

    int n = square.size();
    int magicSum = n * (n * n + 1) / 2;  // ���������� ���������

    // �������� �����
    for (const auto& row : square) {
        int sum = 0;
        for (int num : row) {
            sum += num;
        }
        if (sum != magicSum) return false;
    }

    // �������� ��������
    for (int j = 0; j < n; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += square[i][j];
        }
        if (sum != magicSum) return false;
    }

    // �������� ������� ���������
    int diagSum1 = 0;
    for (int i = 0; i < n; i++) {
        diagSum1 += square[i][i];
    }
    if (diagSum1 != magicSum) return false;

    // �������� �������� ���������
    int diagSum2 = 0;
    for (int i = 0; i < n; i++) {
        diagSum2 += square[i][n - 1 - i];
    }
    if (diagSum2 != magicSum) return false;

    return true;
}

// ���������� ����������� �������� � ����
void saveMagicSquare(const vector<vector<int>>& square) {
    string filename;
    cout << "������� ��� ����� ��� ���������� ����������� ��������: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("������������ ��� �����!");
    }

    // ��������� ���������� .msq, ���� ��� ���
    if (fs::path(filename).extension().empty()) {
        filename += ".msq";
    }

    ofstream file(filename); // ��������� ����
    if (!file.is_open()) {
        throw runtime_error("������ �������� �����: " + filename);
    }
    
    file << square.size() << endl;  // ��������� ������ ��������
    for (const auto& row : square) { // ��������� �������� ��������
        for (int num : row) { // ���������� �� ���� ��������� ������
            file << num << " ";
        }
        file << endl;
    }
    file.close();
    cout << "���������� ������� �������� � ����: " << filename << endl;
}

// �������� ����������� �������� �� �����
vector<vector<int>> loadMagicSquare() {
    string filename;
    cout << "������� ��� ����� ����������� ��������: ";
    getline(cin, filename);

    if (filename.empty() || filename.find(' ') != string::npos) {
        throw runtime_error("������������ ��� �����!");
    }

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("������ �������� �����: " + filename);
    }
    
    int size;
    file >> size;  // ������ ������ ��������
    
    if (size % 2 == 0 || size < 3 || size > 9) {
        file.close();
        throw runtime_error("������������ ������ ����������� �������� � �����!");
    }
    
    vector<vector<int>> square(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (!(file >> square[i][j])) {
                file.close();
                throw runtime_error("������ ������ ������ �� �����!");
            }
        }
    }
    file.close();
    
    if (!validateMagicSquare(square)) {
        throw runtime_error("����������� ���������� ������� �����������!");
    }
    
    return square;
}

// ����� ����������� �������� �� �����
void displayMagicSquare(const vector<vector<int>>& square) {
    cout << "\n���������� ������� " << square.size() << "x" << square.size() << ":" << endl;
    for (const auto& row : square) { // ���������� �� ���� ��������� ��������
        for (int num : row) {
            cout << num << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// ������� ��� ������� ���� � ������������ (��� �������� ������������ ������)
const string RUSSIAN_ALPHABET = 
    "�����Ũ��������������������������"
    "��������������������������������"
    "!@#$%^&*()_+-={}[]|\\:;<>,.?/~`'\""
    " \n";

// �������� ������������ ������
bool isAllowedChar(char c) {
    return RUSSIAN_ALPHABET.find(c) != string::npos ||  // ������� ����� � �����������
           (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9');
}