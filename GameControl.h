#pragma once
// Класс для управление игрой
class GameControl : private FileManager
{
private:
    GallowGame game;
public:
    // Вывод на экран игрового меню
    void displayGameMenu();

    // Вывод на экран меню разработчика
    void displayDeveloperMenu();

    // Вывод на экран главного меню в main
    void displayMainMenu();

    // Вывод всех слов
    void displayWords(const vector<string>& decipheredWords);

    // Меню игры
    void playGame(vector<string>& decipheredWords, const string& filename);

    // Меню разработчика
    void developerMode(vector<string>& decipheredWords, const string& filename);
};