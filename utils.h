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
void saveKeyToFile(const string& key);

// функция загрузки ключа из файла
string loadKeyFromFile();

// функции для работы с магическим квадратом
bool validateMagicSquare(const vector<vector<int>>& square); // проверка корректности
void saveMagicSquare(const vector<vector<int>>& square);
vector<vector<int>> loadMagicSquare();
void displayMagicSquare(const vector<vector<int>>& square);

bool isAllowedChar(char c); // проверка на допустимые символы