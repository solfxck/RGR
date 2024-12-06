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

// общие функции
string inputTextFromFile(); // ввод текста из фаи?ла
void saveTextToFile(const string& text); // сохранение текста в фаи?л

// функции шифра Атбаш
string Atbash(string text);
void AtbashEncrypt();
void AtbashDecrypt();

// функции для шифра Вернама
string Vernam(const string& text, const string& key);
void VernamEncrypt();
void VernamDecrypt();

// функции для шифра "Магический квадрат"
string MagicSquare(const string& text, const vector<vector<int>>& square, bool isEncrypt = true);
vector<vector<int>> generateMagicSquare(int size);
void MagicSquareEncrypt();
void MagicSquareDecrypt();