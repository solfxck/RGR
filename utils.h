#pragma once
#include "Header.h"

using namespace std;

// функция ввода текста с консоли
string inputTextFromConsole();

// функция ввода текста из файла
string inputTextFromFile();

// функция сохранения текста в файл
void saveTextToFile(const string& text);

// функция сохранения ключа в файл
void saveKeyToFile(const string& key, const string& filename = "");

// функция загрузки ключа из файла
string loadKeyFromFile(const string& filename = "");

// функции для работы с магическим квадратом
bool validateMagicSquare(const vector<vector<int>>& square); // проверка корректности
void saveMagicSquare(const vector<vector<int>>& square, const string& filename);
vector<vector<int>> loadMagicSquare(const string& filename);
void displayMagicSquare(const vector<vector<int>>& square);

bool isAllowedChar(char c); // проверка на допустимые символы