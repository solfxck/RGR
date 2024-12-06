#include "Header.h"
#include "utils.h"

using namespace std;
namespace fs = std::filesystem;

// функция для получения индекса символа (костыли, т.к. некооректно работает кодировка UTF-8)
int getCharIndex(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    int index = -1;
    
    // проверка диапазона символов (0xC0-0xDF)
    if (uc >= 0xC0 && uc <= 0xDF) {
        index = uc - 0xC0;
    }
    // проверка диапазона символов (0xE0-0xFF)
    else if (uc >= 0xE0 && uc <= 0xFF) {
        index = (uc - 0xE0) + 32;
    }
    // проверка диапазона символов (A-Z)
    else if (uc >= 'A' && uc <= 'Z') {
        index = (uc - 'A') + 64;
    }
    // проверка диапазона символов (a-z)
    else if (uc >= 'a' && uc <= 'z') {
        index = (uc - 'a') + 90;
    }
    // проверка диапазона символов (0-9)
    else if (uc >= '0' && uc <= '9') {
        index = (uc - '0') + 116;
    }
    // специальные символы
    else {
        const string specialChars = " .,!?@#$%^&*()-+=<>[]{}|/\"';:\\";
        size_t pos = specialChars.find(c);
        if (pos != string::npos) {
            index = 126 + pos;
        }
    }
    
    return index;
}

// функция для получения символа по индексу
char getCharFromIndex(int index) {
    if (index < 0) return '\0';
    
    // проверка диапазона символов (0xC0)
    if (index < 32) {
        return static_cast<char>(index + 0xC0);
    }
    // проверка диапазона символов (0xE0)
    else if (index < 64) {
        return static_cast<char>((index - 32) + 0xE0);
    }
    // проверка диапазона символов (A-Z)
    else if (index < 90) {
        return static_cast<char>((index - 64) + 'A');
    }
    // проверка диапазона символов (a-z)
    else if (index < 116) {
        return static_cast<char>((index - 90) + 'a');
    }
    // проверка диапазона символов (0-9)
    else if (index < 126) {
        return static_cast<char>((index - 116) + '0');
    }
    // специальные символы
    else {
        const string specialChars = " .,!?@#$%^&*()-+=<>[]{}|/\"';:\\";
        int specialIndex = index - 126;
        if (specialIndex >= 0 && specialIndex < specialChars.length()) {
            return specialChars[specialIndex];
        }
    }
    
    return '\0';
}

// функция для генерации случайного ключа
string generateRandomKey(int length) {
    string key;
    key.reserve(length);
    
    srand(static_cast<unsigned int>(time(nullptr)));
    
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % 161; // генерация случайного индекса
        key += getCharFromIndex(randomIndex);
    }
    
    return key;
}

// функция для шифрования текста с использованием метода Вернама
string Vernam(const string& text, const string& key) {
    if (text.empty()) {
        throw runtime_error("Ошибка: текст не может быть пустым!");
    }
    
    if (key.empty()) {
        throw runtime_error("Ошибка: ключ не может быть пустым!");
    }
    
    if (key.length() < text.length()) {
        throw runtime_error("Ошибка: длина ключа должна быть не меньше длины текста!");
    }
    
    string result;
    result.reserve(text.length());
    
    for (size_t i = 0; i < text.length(); ++i) {
        unsigned char textChar = static_cast<unsigned char>(text[i]);
        unsigned char keyChar = static_cast<unsigned char>(key[i]);
        
        int textIndex = getCharIndex(text[i]);
        int keyIndex = getCharIndex(key[i]);
        
        // если символ не найден, добавляем его в результат без изменений
        if (textIndex == -1 || keyIndex == -1) {
            result += text[i];
            continue;
        }
        
        // применение операции XOR для шифрования
        int resultIndex = (textIndex ^ keyIndex) % 256;  
        char resultChar = getCharFromIndex(resultIndex);
        
        // если результат не найден, добавляем исходный символ
        if (resultChar == '\0') {
            result += text[i];
        } else {
            result += resultChar;
        }
    }
    
    return result;
}

void VernamEncrypt() {
    try {
        while (true) {
            system("cls");
            string inputChoice;
            cout << "Р’С‹Р±РµСЂРёС‚Рµ СЃРїРѕСЃРѕР± РІРІРѕРґР° С‚РµРєСЃС‚Р°:" << endl;
            cout << "1. Р’РІРѕРґ СЃ РєРѕРЅСЃРѕР»Рё" << endl;
            cout << "2. Р’РІРѕРґ РёР· С„Р°Р№Р»Р°" << endl;
            cout << "3. РќР°Р·Р°Рґ" << endl;
            cout << "Р’Р°С€ РІС‹Р±РѕСЂ: ";
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
                    throw runtime_error("РќРµРІРµСЂРЅС‹Р№ РІС‹Р±РѕСЂ.");
                }
            }
            catch (const exception& e) {
                cout << "РћС€РёР±РєР°: " << e.what() << endl;
                cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }

            if (text.empty()) continue;
            
            cout << "Р”Р»РёРЅР° РІС…РѕРґРЅРѕРіРѕ С‚РµРєСЃС‚Р°: " << text.length() << " Р±Р°Р№С‚" << endl;

            while (true) {
                string keyChoice;
                cout << "\nР’С‹Р±РµСЂРёС‚Рµ СЃРїРѕСЃРѕР± РїРѕР»СѓС‡РµРЅРёСЏ РєР»СЋС‡Р°:" << endl;
                cout << "1. Р’РІРµСЃС‚Рё РєР»СЋС‡ РІСЂСѓС‡РЅСѓСЋ" << endl;
                cout << "2. РЎРіРµРЅРµСЂРёСЂРѕРІР°С‚СЊ СЃР»СѓС‡Р°Р№РЅС‹Р№ РєР»СЋС‡" << endl;
                cout << "3. Р—Р°РіСЂСѓР·РёС‚СЊ РєР»СЋС‡ РёР· С„Р°Р№Р»Р°" << endl;
                cout << "4. РќР°Р·Р°Рґ" << endl;
                cout << "Р’Р°С€ РІС‹Р±РѕСЂ: ";
                cin >> keyChoice;

                if (keyChoice == "4") {
                    break;
                }

                string key;
                try {
                    if (keyChoice == "1") {
                        cout << "Р’РІРµРґРёС‚Рµ РєР»СЋС‡ (РґР»РёРЅР° РєР»СЋС‡Р° РґРѕР»Р¶РЅР° Р±С‹С‚СЊ РЅРµ РјРµРЅСЊС€Рµ РґР»РёРЅС‹ С‚РµРєСЃС‚Р°: " << text.length() << "): ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, key);
                    }
                    else if (keyChoice == "2") {
                        key = generateRandomKey(text.length());
                        cout << "РЎРіРµРЅРµСЂРёСЂРѕРІР°РЅ РєР»СЋС‡ РґР»РёРЅРѕР№ " << key.length() << " Р±Р°Р№С‚" << endl;
                        
                        string saveKeyChoice;
                        cout << "РҐРѕС‚РёС‚Рµ СЃРѕС…СЂР°РЅРёС‚СЊ РєР»СЋС‡ РІ С„Р°Р№Р»?" << endl;
                        cout << "1. Р”Р°" << endl;
                        cout << "2. РќРµС‚" << endl;
                        cout << "3. РќР°Р·Р°Рґ" << endl;
                        cout << "Р’Р°С€ РІС‹Р±РѕСЂ: ";
                        cin >> saveKeyChoice;
                        
                        if (saveKeyChoice == "3") {
                            continue;
                        }
                        
                        if (saveKeyChoice == "1") {
                            saveKeyToFile(key, "");
                        }
                    }
                    else if (keyChoice == "3") {
                        key = loadKeyFromFile();
                        cout << "Р—Р°РіСЂСѓР¶РµРЅ РєР»СЋС‡ РґР»РёРЅРѕР№ " << key.length() << " Р±Р°Р№С‚" << endl;
                    }
                    else {
                        throw runtime_error("РќРµРІРµСЂРЅС‹Р№ РІС‹Р±РѕСЂ.");
                    }

                    string encrypted = Vernam(text, key);
                    cout << "РўРµРєСЃС‚ СѓСЃРїРµС€РЅРѕ Р·Р°С€РёС„СЂРѕРІР°РЅ (РґР»РёРЅР°: " << encrypted.length() << " Р±Р°Р№С‚)" << endl;
                    cout << "Р—Р°С€РёС„СЂРѕРІР°РЅРЅС‹Р№ С‚РµРєСЃС‚: " << encrypted << endl;

                    while (true) {
                        string saveChoice;
                        cout << "\nРЎРѕС…СЂР°РЅРёС‚СЊ СЂРµР·СѓР»СЊС‚Р°С‚ РІ С„Р°Р№Р»?" << endl;
                        cout << "1. Р”Р°" << endl;
                        cout << "2. РќРµС‚" << endl;
                        cout << "3. РќР°Р·Р°Рґ" << endl;
                        cout << "Р’Р°С€ РІС‹Р±РѕСЂ: ";
                        cin >> saveChoice;

                        if (saveChoice == "3") {
                            break;
                        }

                        if (saveChoice == "1") {
                            try {
                                saveTextToFile(encrypted);
                                cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                return;
                            }
                            catch (const exception& e) {
                                cout << "РћС€РёР±РєР° РїСЂРё СЃРѕС…СЂР°РЅРµРЅРёРё: " << e.what() << endl;
                                cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                continue;
                            }
                        }
                        else if (saveChoice == "2") {
                            return;
                        }
                        else {
                            cout << "РќРµРІРµСЂРЅС‹Р№ РІС‹Р±РѕСЂ." << endl;
                            cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.get();
                        }
                    }
                }
                catch (const exception& e) {
                    cout << "РћС€РёР±РєР°: " << e.what() << endl;
                    cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    continue;
                }
            }
        }
    }
    catch (const exception& e) {
        cout << "РћС€РёР±РєР°: " << e.what() << endl;
        cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}

void VernamDecrypt() {
    try {
        while (true) {
            system("cls");
            string inputChoice;
            cout << "Р’С‹Р±РµСЂРёС‚Рµ СЃРїРѕСЃРѕР± РІРІРѕРґР° С‚РµРєСЃС‚Р°:" << endl;
            cout << "1. Р’РІРѕРґ СЃ РєРѕРЅСЃРѕР»Рё" << endl;
            cout << "2. Р’РІРѕРґ РёР· С„Р°Р№Р»Р°" << endl;
            cout << "3. РќР°Р·Р°Рґ" << endl;
            cout << "Р’Р°С€ РІС‹Р±РѕСЂ: ";
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
                    throw runtime_error("РќРµРІРµСЂРЅС‹Р№ РІС‹Р±РѕСЂ.");
                }
            }
            catch (const exception& e) {
                cout << "РћС€РёР±РєР°: " << e.what() << endl;
                cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }

            if (text.empty()) continue;
            
            cout << "Р”Р»РёРЅР° РІС…РѕРґРЅРѕРіРѕ С‚РµРєСЃС‚Р°: " << text.length() << " Р±Р°Р№С‚" << endl;

            while (true) {
                string keyChoice;
                cout << "\nР’С‹Р±РµСЂРёС‚Рµ СЃРїРѕСЃРѕР± РїРѕР»СѓС‡РµРЅРёСЏ РєР»СЋС‡Р°:" << endl;
                cout << "1. Р’РІРµСЃС‚Рё РєР»СЋС‡ РІСЂСѓС‡РЅСѓСЋ" << endl;
                cout << "2. Р—Р°РіСЂСѓР·РёС‚СЊ РєР»СЋС‡ РёР· С„Р°Р№Р»Р°" << endl;
                cout << "3. РќР°Р·Р°Рґ" << endl;
                cout << "Р’Р°С€ РІС‹Р±РѕСЂ: ";
                cin >> keyChoice;

                if (keyChoice == "3") {
                    break;
                }

                string key;
                try {
                    if (keyChoice == "1") {
                        cout << "Р’РІРµРґРёС‚Рµ РєР»СЋС‡ (РґР»РёРЅР° РєР»СЋС‡Р° РґРѕР»Р¶РЅР° Р±С‹С‚СЊ РЅРµ РјРµРЅСЊС€Рµ РґР»РёРЅС‹ С‚РµРєСЃС‚Р°: " << text.length() << "): ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, key);
                    }
                    else if (keyChoice == "2") {
                        key = loadKeyFromFile();
                        cout << "Р—Р°РіСЂСѓР¶РµРЅ РєР»СЋС‡ РґР»РёРЅРѕР№ " << key.length() << " Р±Р°Р№С‚" << endl;
                    }
                    else {
                        throw runtime_error("РќРµРІРµСЂРЅС‹Р№ РІС‹Р±РѕСЂ.");
                    }

                    string decrypted = Vernam(text, key);
                    cout << "РўРµРєСЃС‚ СѓСЃРїРµС€РЅРѕ РґРµС€РёС„СЂРѕРІР°РЅ (РґР»РёРЅР°: " << decrypted.length() << " Р±Р°Р№С‚)" << endl;
                    cout << "Р”РµС€РёС„СЂРѕРІР°РЅРЅС‹Р№ С‚РµРєСЃС‚: " << decrypted << endl;

                    while (true) {
                        string saveChoice;
                        cout << "\nРЎРѕС…СЂР°РЅРёС‚СЊ СЂРµР·СѓР»СЊС‚Р°С‚ РІ С„Р°Р№Р»?" << endl;
                        cout << "1. Р”Р°" << endl;
                        cout << "2. РќРµС‚" << endl;
                        cout << "3. РќР°Р·Р°Рґ" << endl;
                        cout << "Р’Р°С€ РІС‹Р±РѕСЂ: ";
                        cin >> saveChoice;

                        if (saveChoice == "3") {
                            break;
                        }

                        if (saveChoice == "1") {
                            try {
                                saveTextToFile(decrypted);
                                cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                return;
                            }
                            catch (const exception& e) {
                                cout << "РћС€РёР±РєР° РїСЂРё СЃРѕС…СЂР°РЅРµРЅРёРё: " << e.what() << endl;
                                cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                                continue;
                            }
                        }
                        else if (saveChoice == "2") {
                            return;
                        }
                        else {
                            cout << "РќРµРІРµСЂРЅС‹Р№ РІС‹Р±РѕСЂ." << endl;
                            cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.get();
                        }
                    }
                }
                catch (const exception& e) {
                    cout << "РћС€РёР±РєР°: " << e.what() << endl;
                    cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    continue;
                }
            }
        }
    }
    catch (const exception& e) {
        cout << "РћС€РёР±РєР°: " << e.what() << endl;
        cout << "\nРќР°Р¶РјРёС‚Рµ Enter РґР»СЏ РїСЂРѕРґРѕР»Р¶РµРЅРёСЏ...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}