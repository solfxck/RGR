#include "Header.h"
#include "utils.h"

using namespace std;

// генерация магического квадрата методом Сиамский метод
vector<vector<int>> generateMagicSquare(int size) {
    if (size % 2 == 0) {
        throw runtime_error("Размер магического квадрата должен быть нечетным числом!");
    }
    
    if (size < 3 || size > 9) {
        throw runtime_error("Размер магического квадрата должен быть нечетным числом от 3 до 9!");
    }

    vector<vector<int>> square(size, vector<int>(size, 0));
    int n = size;
    
    int i = n/2;
    int j = n-1;
    
    // заполняем квадрат числами от 1 до n*n
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

// реализация шифра "Магический квадрат"
string MagicSquare(const string& text, const vector<vector<int>>& square, bool isEncrypt) {
    if (text.empty()) {
        throw runtime_error("Ошибка: Пустой текст!");
    }
    
    if (!validateMagicSquare(square)) {
        throw runtime_error("Ошибка: Некорректный магический квадрат!");
    }
    
    int n = square.size();
    int blockSize = n * n;
    
    // создаем копию текста для обработки
    string workText = text;
    
    // находим количество поддерживаемых символов
    int supportedChars = 0;
    for (char c : workText) {
        if (isAllowedChar(c)) {
            supportedChars++;
        }
    }
    
    // дополняем текст пробелами до размера, кратного размеру блока
    while (supportedChars % blockSize != 0) {
        workText += ' ';
        supportedChars++;
    }
    
    string result;
    result.reserve(workText.length());
    
    // временный буфер для поддерживаемых символов
    vector<char> supportedBuffer;
    vector<size_t> originalPositions;
    
    // собираем поддерживаемые символы и их позиции
    for (size_t i = 0; i < workText.length(); i++) {
        if (isAllowedChar(workText[i])) {
            supportedBuffer.push_back(workText[i]);
            originalPositions.push_back(i);
        }
    }
    
    // обрабатываем поддерживаемые символы блоками
    for (size_t blockStart = 0; blockStart < supportedBuffer.size(); blockStart += blockSize) {
        vector<char> block(blockSize);
        
        // шифрование: размещаем символы согласно магическому квадрату
        if (isEncrypt) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int pos = square[i][j] - 1;
                    block[pos] = supportedBuffer[blockStart + i * n + j];
                }
            }
        }
        // дешифрование: восстанавливаем исходный порядок символов
        else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int pos = square[i][j] - 1;
                    block[i * n + j] = supportedBuffer[blockStart + pos];
                }
            }
        }
        
        // копируем обработанный блок обратно в буфер
        copy(block.begin(), block.end(), supportedBuffer.begin() + blockStart);
    }
    
    // формируем результат, вставляя обработанные символы на их исходные позиции
    result = workText;
    for (size_t i = 0; i < supportedBuffer.size(); i++) {
        result[originalPositions[i]] = supportedBuffer[i];
    }
    
    // убираем добавленные пробелы в конце
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
            cout << "Выберите способ ввода текста:" << endl;
            cout << "1. Ввод с консоли" << endl;
            cout << "2. Ввод из файла" << endl;
            cout << "3. Назад" << endl;
            cout << "Ваш выбор: ";
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
                    throw runtime_error("Неверный выбор.");
                }
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
                cout << "\nНажмите Enter для продолжения...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }

            if (text.empty()) continue;

            while (true) {
                // выбор размера магического квадрата
                string sizeChoice;
                cout << "\nВыберите размер магического квадрата (3-9, нечетное):" << endl;
                cout << "1. 3x3" << endl;
                cout << "2. 5x5" << endl;
                cout << "3. 7x7" << endl;
                cout << "4. 9x9" << endl;
                cout << "5. Назад" << endl;
                cout << "Ваш выбор: ";
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
                    else throw runtime_error("Неверный выбор размера квадрата.");

                    vector<vector<int>> square = generateMagicSquare(size);
                    displayMagicSquare(square);

                    // предложение сохранить магический квадрат
                    string saveSquareChoice;
                    cout << "Сохранить магический квадрат в файл?" << endl;
                    cout << "1. Да" << endl;
                    cout << "2. Нет" << endl;
                    cout << "Ваш выбор: ";
                    cin >> saveSquareChoice;

                    if (saveSquareChoice == "1") {
                        string filename;
                        cout << "Введите имя файла для сохранения магического квадрата: ";
                        cin >> filename;
                        saveMagicSquare(square, filename);
                        cout << "Магический квадрат сохранен в файл: " << filename << endl;
                    }

                    string encrypted = MagicSquare(text, square, true);
                    cout << "\nТекст успешно зашифрован" << endl;
                    cout << "Зашифрованный текст: " << encrypted << endl;

                    while (true) {
                        // сохранение результата
                        string saveChoice;
                        cout << "\nСохранить результат в файл?" << endl;
                        cout << "1. Да" << endl;
                        cout << "2. Нет" << endl;
                        cout << "3. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> saveChoice;

                        if (saveChoice == "3") {
                            break;
                        }

                        if (saveChoice == "1") {
                            try {
                                saveTextToFile(encrypted);
                                cout << "\nНажмите Enter для продолжения...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                return;
                            }
                            catch (const exception& e) {
                                cout << "Ошибка при сохранении: " << e.what() << endl;
                                cout << "\nНажмите Enter для продолжения...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                continue;
                            }
                        }
                        else if (saveChoice == "2") {
                            return;
                        }
                        else {
                            cout << "Неверный выбор." << endl;
                            cout << "\nНажмите Enter для продолжения...";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.get();
                        }
                    }
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                    cout << "\nНажмите Enter для продолжения...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    continue;
                }
            }
        }
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        cout << "\nНажмите Enter для продолжения...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}

void MagicSquareDecrypt() {
    try {
        while (true) {
            system("cls");
            string inputChoice;
            cout << "Выберите способ ввода текста:" << endl;
            cout << "1. Ввод с консоли" << endl;
            cout << "2. Ввод из файла" << endl;
            cout << "3. Назад" << endl;
            cout << "Ваш выбор: ";
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
                    throw runtime_error("Неверный выбор.");
                }
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
                cout << "\nНажмите Enter для продолжения...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }

            if (text.empty()) continue;

            while (true) {
                // выбор способа получения магического квадрата
                string squareChoice;
                cout << "\nВыберите способ получения магического квадрата:" << endl;
                cout << "1. Загрузить из файла" << endl;
                cout << "2. Создать новый" << endl;
                cout << "3. Назад" << endl;
                cout << "Ваш выбор: ";
                cin >> squareChoice;

                if (squareChoice == "3") {
                    break;
                }

                vector<vector<int>> square;
                try {
                    if (squareChoice == "1") {
                        string filename;
                        cout << "Введите имя файла с магическим квадратом: ";
                        cin >> filename;
                        square = loadMagicSquare(filename);
                        displayMagicSquare(square);
                    }
                    else if (squareChoice == "2") {
                        string sizeChoice;
                        cout << "\nВыберите размер магического квадрата (3-9, нечетное):" << endl;
                        cout << "1. 3x3" << endl;
                        cout << "2. 5x5" << endl;
                        cout << "3. 7x7" << endl;
                        cout << "4. 9x9" << endl;
                        cout << "5. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> sizeChoice;

                        if (sizeChoice == "5") {
                            continue;
                        }

                        int size;
                        if (sizeChoice == "1") size = 3;
                        else if (sizeChoice == "2") size = 5;
                        else if (sizeChoice == "3") size = 7;
                        else if (sizeChoice == "4") size = 9;
                        else throw runtime_error("Неверный выбор размера квадрата.");

                        square = generateMagicSquare(size);
                        displayMagicSquare(square);

                        // Предложение сохранить магический квадрат
                        string saveSquareChoice;
                        cout << "Сохранить магический квадрат в файл?" << endl;
                        cout << "1. Да" << endl;
                        cout << "2. Нет" << endl;
                        cout << "Ваш выбор: ";
                        cin >> saveSquareChoice;

                        if (saveSquareChoice == "1") {
                            string filename;
                            cout << "Введите имя файла для сохранения магического квадрата: ";
                            cin >> filename;
                            saveMagicSquare(square, filename);
                            cout << "Магический квадрат сохранен в файл: " << filename << endl;
                        }
                    }
                    else {
                        throw runtime_error("Неверный выбор.");
                    }

                    string decrypted = MagicSquare(text, square, false);
                    cout << "\nТекст успешно дешифрован" << endl;
                    cout << "Дешифрованный текст: " << decrypted << endl;

                    while (true) {
                        // сохранение результата
                        string saveChoice;
                        cout << "\nСохранить результат в файл?" << endl;
                        cout << "1. Да" << endl;
                        cout << "2. Нет" << endl;
                        cout << "3. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> saveChoice;

                        if (saveChoice == "3") {
                            break;
                        }

                        if (saveChoice == "1") {
                            try {
                                saveTextToFile(decrypted);
                                cout << "\nНажмите Enter для продолжения...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                return;
                            }
                            catch (const exception& e) {
                                cout << "Ошибка при сохранении: " << e.what() << endl;
                                cout << "\nНажмите Enter для продолжения...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                continue;
                            }
                        }
                        else if (saveChoice == "2") {
                            return;
                        }
                        else {
                            cout << "Неверный выбор." << endl;
                            cout << "\nНажмите Enter для продолжения...";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.get();
                        }
                    }
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                    cout << "\nНажмите Enter для продолжения...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    continue;
                }
            }
        }
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        cout << "\nНажмите Enter для продолжения...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}