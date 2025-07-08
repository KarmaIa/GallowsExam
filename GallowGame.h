#pragma once
// Класс для игры
class GallowGame
{
private:
    string wordForGame; // Секретное слово для игры
    string guessedWord; // Строка для вывода на экран секретного слово в виде "_____", 
                        // а когда какая-то буква была угадана она подставляется вместо '_'. Пример если ввести 'а': "_а_а_"
    int attempts; // Попытки
    vector<char> enteredLetters; // Вектор для хранения выбора букв во время игре
    string previousWord; // Строка хранящее предыдущее секретное слово
    chrono::time_point<chrono::high_resolution_clock> startTime; // Переменная хранящее время
    vector<string> imageGallows { // Изображение виселицы
        {"________________\n | /          |\n |/\n |\n |\n |\n |\n |\n |\n_|______\n"},
        {"________________\n | /          |\n |/           O\n |\n |\n |\n |\n |\n |\n_|______\n"},
        {"________________\n | /          |\n |/           O\n |            |\n |            |\n |\n |\n |\n |\n_|______\n"},
        {"________________\n | /          |\n |/           O\n |           /|\n |            |\n |\n |\n |\n |\n_|______\n"},
        {"________________\n | /          |\n |/           O\n |           /|\\\n |            |\n |\n |\n |\n |\n_|______\n"},
        {"________________\n | /          |\n |/           O\n |           /|\\\n |            |\n |           /\n |\n |\n |\n_|______\n"},
        {"________________\n | /          |\n |/           O\n |           /|\\\n |            |\n |           / \\\n |\n |\n |\n_|______\n"}
    };
public:
    GallowGame() : wordForGame(""), guessedWord(""), attempts(0) {}

    // Выбор случайного слова (С учётом того чтобы слова небыли одинаковыми подряд)
    string getRandomWord(const vector<string> wordList);

    // Вывод на экран правил для игры "Виселица"
    void showRules();

    // Вывод на экран текущего состояния игры
    void displayGameStatus() const;

    // Получения буквы и её обработка
    void letterProcessing();

    // Вывод итогов игры
    void gameOver();

    // Функция для работы игры
    void play(const string& word);
};