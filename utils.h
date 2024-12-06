#pragma once
#include "Header.h"

using namespace std;

// ������� ����� ������ � �������
string inputTextFromConsole();

// ������� ����� ������ �� �����
string inputTextFromFile();

// ������� ���������� ������ � ����
void saveTextToFile(const string& text);

// ������� ���������� ����� � ����
void saveKeyToFile(const string& key, const string& filename = "");

// ������� �������� ����� �� �����
string loadKeyFromFile(const string& filename = "");

// ������� ��� ������ � ���������� ���������
bool validateMagicSquare(const vector<vector<int>>& square); // �������� ������������
void saveMagicSquare(const vector<vector<int>>& square, const string& filename);
vector<vector<int>> loadMagicSquare(const string& filename);
void displayMagicSquare(const vector<vector<int>>& square);

bool isAllowedChar(char c); // �������� �� ���������� �������