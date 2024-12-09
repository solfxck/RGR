#include "Header.h"
#include "utils.h"

using namespace std;

// генерация магического квадрата
vector<vector<int>> generateMagicSquare(int size) {
    vector<vector<int>> square(size, vector<int>(size, 0)); // создаем пустой квадрат
    int n = size;
    
    int i = n / 2; // начальные координаты
    int j = n - 1; // начальные координаты
    
    // заполняем квадрат числами от 1 до n*n
    for (int num = 1; num <= n * n;) { // num - номер числа
        if (i == -1 && j == n) { // если мы вышли за пределы квадрата
            j = n-2; // возвращаемся на предпоследнюю строку
            i = 0; // и переходим на первый столбец
        } else {
            if (j == n) j = 0; // если мы вышли за пределы столбца, возвращаемся на первый столбец
            if (i < 0) i = n-1; // если мы вышли за пределы строки, возвращаемся на последнюю строку
        }
        
        if (square[i][j] != 0) { // если клетка уже заполнена
            j -= 2; // возвращаемся на предпоследнюю строку
            i++; // и переходим на первый столбец
            continue; // продолжаем цикл
        } else { // если клетка пуста
            square[i][j] = num++; // заполняем клетку номером 
        }
        
        j++; // переходим на следующий столбец
        i--; // и на следующую строку
    }
    
    return square;
}

// реализация шифра "Магический квадрат"
string MagicSquare(const string& text, const vector<vector<int>>& square, bool isEncrypt) {    
    int n = square.size();
    int blockSize = n * n; 
    
    // создаем копию текста для обработки (чтобы не изменять исходный текст)
    string workText = text; 
    
    // находим количество поддерживаемых символов
    int supportedChars = 0; // количество поддерживаемых символов
    for (char c : workText) {
        if (isAllowedChar(c)) { 
            supportedChars++;
        }
    }
    
    // дополняем текст пробелами до размера, кратного размеру блока
    while (supportedChars % blockSize != 0) { // пока количество поддерживаемых символов не кратно размеру блока
        workText += ' '; // добавляем пробел
        supportedChars++;
    }
    
    string result;
    result.reserve(workText.length()); // предварительное выделение памяти (для оптимизации)
    
    // временный буфер для поддерживаемых символов (чтобы не изменять исходный текст)
    vector<char> supportedBuffer;
    vector<size_t> originalPositions; // позиции исходных символов
    
    // собираем поддерживаемые символы и их позиции
    for (size_t i = 0; i < workText.length(); i++) { // проходим по тексту
        if (isAllowedChar(workText[i])) { // если символ поддерживается
            supportedBuffer.push_back(workText[i]); // добавляем его в буфер
            originalPositions.push_back(i); // запоминаем его позицию
        }
    }
    
    // обрабатываем поддерживаемые символы блоками
    for (size_t blockStart = 0; blockStart < supportedBuffer.size(); blockStart += blockSize) { // проходим по блокам
        vector<char> block(blockSize);
        
        // шифрование: размещаем символы согласно магическому квадрату
        if (isEncrypt) {
            for (int i = 0; i < n; i++) { // проходим по строкам
                for (int j = 0; j < n; j++) { // проходим по столбцам
                    int pos = square[i][j] - 1; // вычисляем позицию
                    block[pos] = supportedBuffer[blockStart + i * n + j]; // помещаем символ в блок по формуле: 
                                            // стартовый блок + номер строки * размер квадрата + номер столбца
                                            // эта формула вычисляет позицию символа в блоке
                }
            }
        }
        // дешифрование: восстанавливаем исходный порядок символов
        else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int pos = square[i][j] - 1;
                    block[i * n + j] = supportedBuffer[blockStart + pos]; // помещаем символ в блок по формуле: 
                                            // номер строки * размер квадрата + номер столбца
                }
            }
        }
        
        // копируем обработанный блок обратно в буфер
        copy(block.begin(), block.end(), supportedBuffer.begin() + blockStart);
    }
    
    // формируем результат, вставляя обработанные символы на их исходные позиции
    result = workText;
    for (size_t i = 0; i < supportedBuffer.size(); i++) { // проходим по поддерживаемым символам
        result[originalPositions[i]] = supportedBuffer[i]; // вставляем символ на его исходную позицию
    }
    
    // убираем добавленные пробелы в конце
    while (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}

void MagicSquareEncrypt() {
    while (true) {
        system("cls");

        string inputChoice;
        cout << "Выберите способ ввода текста:" << endl;
        cout << "1. Ввод с консоли" << endl;
        cout << "2. Ввод из файла" << endl;
        cout << "3. Назад" << endl;
        cout << "Ваш выбор: ";
        
        try {
            getline(cin, inputChoice);

            if (inputChoice == "3") {
                return;
            }

            if (inputChoice.length() != 1 || !isdigit(inputChoice[0]) || 
                inputChoice[0] < '1' || inputChoice[0] > '3' || 
                inputChoice.find(' ') != string::npos) {
                throw invalid_argument("Неверный выбор. Попробуйте снова.");
            }

            string text;
            if (inputChoice == "1") {
                text = inputTextFromConsole();
            } else if (inputChoice == "2") {
                text = inputTextFromFile();
            }

            if (text.empty()) {
                throw invalid_argument("Текст не может быть пустым.");
            }

            vector<vector<int>> square;
            bool squareObtained = false;
            while (!squareObtained) {
                try {
                    string sizeChoice;
                    cout << "\nВыберите размер магического квадрата:" << endl;
                    cout << "1. 3x3" << endl;
                    cout << "2. 5x5" << endl;
                    cout << "3. 7x7" << endl;
                    cout << "4. 9x9" << endl;
                    cout << "Ваш выбор: ";
                    getline(cin, sizeChoice);

                    if (sizeChoice.length() != 1 || !isdigit(sizeChoice[0]) || 
                        sizeChoice[0] < '1' || sizeChoice[0] > '4' || 
                        sizeChoice.find(' ') != string::npos) {
                        throw invalid_argument("Неверный выбор размера квадрата.");
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
                            cout << "\nСохранить магический квадрат в файл?" << endl;
                            cout << "1. Да" << endl;
                            cout << "2. Нет" << endl;
                            cout << "Ваш выбор: ";
                            getline(cin, saveSquareChoice);

                            if (saveSquareChoice.length() != 1 || !isdigit(saveSquareChoice[0]) || 
                                saveSquareChoice[0] < '1' || saveSquareChoice[0] > '2' || 
                                saveSquareChoice.find(' ') != string::npos) {
                                throw invalid_argument("Неверный выбор. Попробуйте снова.");
                            }

                            if (saveSquareChoice == "1") {
                                saveMagicSquare(square);
                            }
                            saveSquareChosen = true;
                        }
                        catch (const exception& e) {
                            cout << "Ошибка: " << e.what() << endl;
                            system("pause");
                            system("cls");
                            displayMagicSquare(square);
                        }
                    }
                    squareObtained = true;
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "Текст для шифрования: " << text << endl;
                }
            }

            string result = MagicSquare(text, square, true);
            cout << "\nЗашифрованный текст: " << result << endl;

            bool saveMenuActive = true;
            while (saveMenuActive) {
                try {
                    string saveChoice;
                    cout << "\nСохранить результат в файл?" << endl;
                    cout << "1. Да" << endl;
                    cout << "2. Нет" << endl;
                    cout << "3. Назад" << endl;
                    cout << "Ваш выбор: ";
                    getline(cin, saveChoice);

                    if (saveChoice.length() != 1 || !isdigit(saveChoice[0]) || 
                        saveChoice[0] < '1' || saveChoice[0] > '3' || 
                        saveChoice.find(' ') != string::npos) {
                        throw invalid_argument("Неверный выбор. Попробуйте снова.");
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
                    cout << "Ошибка: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "\nЗашифрованный текст: " << result << endl;
                }
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            system("pause");
        }
    }
}

void MagicSquareDecrypt() {
    while (true) {
        system("cls");

        string inputChoice;
        cout << "Выберите способ ввода текста:" << endl;
        cout << "1. Ввод с консоли" << endl;
        cout << "2. Ввод из файла" << endl;
        cout << "3. Назад" << endl;
        cout << "Ваш выбор: ";
        
        try {
            getline(cin, inputChoice);

            if (inputChoice == "3") {
                return;
            }

            if (inputChoice.length() != 1 || !isdigit(inputChoice[0]) || 
                inputChoice[0] < '1' || inputChoice[0] > '3' || 
                inputChoice.find(' ') != string::npos) {
                throw invalid_argument("Неверный выбор. Попробуйте снова.");
            }

            string text;
            if (inputChoice == "1") {
                text = inputTextFromConsole();
            } else if (inputChoice == "2") {
                text = inputTextFromFile();
            }

            if (text.empty()) {
                throw invalid_argument("Текст не может быть пустым.");
            }

            vector<vector<int>> square;
            bool squareObtained = false;
            while (!squareObtained) {
                try {
                    cout << "\nЗагрузка магического квадрата из файла..." << endl;
                    square = loadMagicSquare();

                    if (!validateMagicSquare(square)) {
                        throw invalid_argument("Некорректный магический квадрат!");
                    }
                    squareObtained = true;
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "Текст для расшифрования: " << text << endl;
                }
            }

            string result = MagicSquare(text, square, false);
            cout << "\nРасшифрованный текст: " << result << endl;

            bool saveMenuActive = true;
            while (saveMenuActive) {
                try {
                    string saveChoice;
                    cout << "\nСохранить результат в файл?" << endl;
                    cout << "1. Да" << endl;
                    cout << "2. Нет" << endl;
                    cout << "3. Назад" << endl;
                    cout << "Ваш выбор: ";
                    getline(cin, saveChoice);

                    if (saveChoice.length() != 1 || !isdigit(saveChoice[0]) || 
                        saveChoice[0] < '1' || saveChoice[0] > '3' || 
                        saveChoice.find(' ') != string::npos) {
                        throw invalid_argument("Неверный выбор. Попробуйте снова.");
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
                    cout << "Ошибка: " << e.what() << endl;
                    system("pause");
                    system("cls");
                    cout << "\nРасшифрованный текст: " << result << endl;
                }
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            system("pause");
        }
    }
}