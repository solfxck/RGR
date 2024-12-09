Данная расчетно-графическая работа посвящена разработке программного обеспечения для шифрования и дешифрования текста с использованием трех различных криптографических методов: шифра Атбаш, шифра Вернама и метода магического квадрата. 

Программа реализована на языке С++ в Visual Studio Code. В программе существуют следующие модули:

•	main.cpp – главный модуль программы. содержит функцию main(), реализует аутентификацию пользователя, управляет главным меню программы, обрабатывает выбор пользователя.

•	Header.h – заголовочный файл. Содержит объявления всех функций, подключает необходимые библиотеки, определяет общие константы и типы данных.
•	utils.cpp и utils.h – модуль вспомогательных функций
  
  o	string inputTextFromConsole() - ввод текста с консоли.
  
  o	string inputTextFromFile() - чтение текста из файла.
  
  o	void saveTextToFile(const string& text) - сохранение текста в файл.
  
  o	void saveKeyToFile(const string& key) - сохранение ключа в файл.
  
  o	string loadKeyFromFile() - загрузка ключа из файла.
  
  o	bool isAllowedChar(char c) - проверка допустимости символа.
  
  o	bool validateMagicSquare(const vector<vector<int>>& square) - проверка корректности магического квадрата.
  
  o	void displayMagicSquare(const vector<vector<int>>& square) - вывод магического квадрата.
  
  o	void saveMagicSquare(const vector<vector<int>>& square) - сохранение магического квадрата в файл.
  
  o	vector<vector<int>> loadMagicSquare() - загрузка магического квадрата из файла.

•	Atbash.cpp – модуль шифра Атбаш.
  
  o	string Atbash(string text) – функция шифрование/дешифрование текста.
  
  o	void AtbashEncrypt() - функция реализующая меню шифрования.
  
  o	void AtbashDecrypt() - функция реализующая меню дешифрования.

•	Vernam.cpp – модуль шифра Вернама.
  
  o	int getCharIndex(char c) – функция для получения индекса.
  
  o	char getCharFromIndex(int index) – функция для получения символа по индексу.

o	string generateRandomKey(int length) - генерация случайного ключа.
  
  o	string Vernam(const string& text, const string& key) – функция шифрование/дешифрование текста.
  
  o	void VernamEncrypt() – функция реализующая меню шифрования.
  
  o	void VernamDecrypt() – функция реализующая меню дешифрования.

•	MagicSquare.cpp – модуль шифра Магический квадрат.
  
  o	vector<vector<int>> generateMagicSquare(int size) - генерация магического квадрата.
  
  o	string MagicSquare(const string& text, const vector<vector<int>>& square, bool isEncrypt) - основной алгоритм шифрования/дешифрования.
  
  o	void MagicSquareEncrypt() - функция реализующая меню шифрования.
  
  o	void MagicSquareDecrypt() - функция реализующая меню дешифрования.
