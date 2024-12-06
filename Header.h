#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <set>
#include <algorithm>
#include <Windows.h>
#include <map>
#include <limits>
#include <cmath>
#include <random>
#include <ctime>
#include <iterator>
#include <filesystem>
#include <sstream>
#include "Header.h"
#include "utils.h"

using namespace std;

// ����� �������
string inputTextFromFile(); // ���� ������ �� ���?��
void saveTextToFile(const string& text); // ���������� ������ � ���?�

// ������� ����� �����
string Atbash(string text);
void AtbashEncrypt();
void AtbashDecrypt();

// ������� ��� ����� �������
string Vernam(const string& text, const string& key);
void VernamEncrypt();
void VernamDecrypt();

// ������� ��� ����� "���������� �������"
string MagicSquare(const string& text, const vector<vector<int>>& square, bool isEncrypt = true);
vector<vector<int>> generateMagicSquare(int size);
void MagicSquareEncrypt();
void MagicSquareDecrypt();