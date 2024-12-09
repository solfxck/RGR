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
void saveKeyToFile(const string& key);

// ������� �������� ����� �� �����
string loadKeyFromFile();

// ������� ��� ������ � ���������� ���������
bool validateMagicSquare(const vector<vector<int>>& square); // �������� ������������
void saveMagicSquare(const vector<vector<int>>& square);
vector<vector<int>> loadMagicSquare();
void displayMagicSquare(const vector<vector<int>>& square);

bool isAllowedChar(char c); // �������� �� ���������� �������