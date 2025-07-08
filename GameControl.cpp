#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <exception>
#include "file_open_error.h"
#include "file_create_error.h"
#include "CaesarCipher.h"
#include "FileManager.h"
#include "GallowGame.h"
#include "GameControl.h"
using namespace std;

// Вывод на экран игрового меню
void GameControl::displayGameMenu()
{
    cout << "1 - Начать новую игру" << endl;
    cout << "2 - Правила игры" << endl;
    cout << "0 - Назад" << endl;
    cout << "Выбор: ";
}

// Вывод на экран меню разработчика
void GameControl::displayDeveloperMenu()
{
    cout << "Меню разработчика" << endl;
    cout << "1 - Добавить новое слово" << endl;
    cout << "2 - Удалить слово" << endl;
    cout << "3 - Показать все слова" << endl;
    cout << "4 - Пересоздать список слов по умолчанию" << endl;
    cout << "0 - Назад" << endl;
    cout << "Выбор: ";
}

// Вывод на экран главного меню в main
void GameControl::displayMainMenu()
{
    cout << "Главное Меню" << endl;
    cout << "1 - Начать игру \"Виселица\"" << endl;
    cout << "2 - Режим разработчика" << endl;
    cout << "0 - Выход" << endl;
    cout << "Выбор: ";
}

// Вывод всех слов
void GameControl::displayWords(const vector<string>& decipheredWords)
{
    cout << "Список слов:" << endl;
    for (string word : decipheredWords)
    {
        cout << word << endl;
    }
    cout << endl;
}

// Меню игры
void GameControl::playGame(vector<string>& decipheredWords, const string& filename)
{
    int choice;
    cout << "Добро пожаловать в игру \"Виселица\"" << endl;
    do
    {
        displayGameMenu();
        cin >> choice;
        while (cin.fail())
        {
            system("cls");
            cout << "Некоректный ввод. Введите заново" << endl;
            displayGameMenu();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }
        system("cls");
        switch (choice)
        {
        case 1:
        {
            game.play(game.getRandomWord(decipheredWords));
            break;
        }
        case 2:
        {
            game.showRules();
            break;
        }
        case 0:
        {
            break;
        }
        default:
        {
            cout << "Некоректный ввод. Введите заново" << endl;
            break;
        }
        }
    } while (choice != 0);
}

// Меню разработчика
void GameControl::developerMode(vector<string>& decipheredWords, const string& filename)
{
    int choice;
    do
    {
        displayDeveloperMenu();
        cin >> choice;
        while (cin.fail())
        {
            system("cls");
            cout << "Некоректный ввод. Введите заново" << endl;
            displayDeveloperMenu();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }
        system("cls");
        switch (choice)
        {
        case 1:
        {
            addNewWordInFile("encrypted_words.txt", decipheredWords);
            break;
        }
        case 2:
        {
            displayWords(decipheredWords);
            removeWordInFile("encrypted_words.txt", decipheredWords);
            break;
        }
        case 3:
        {
            displayWords(decipheredWords);
            break;
        }
        case 4:
        {
            try
            {
                createDefaultEncryptedFileWithWordlist("encrypted_words.txt");
                decipheredWords.clear();
                decipheredWords = loadEncryptedWords("encrypted_words.txt");
                cout << "Файл со списком слов по умолчанию был успешно пересоздан\n" << endl;
            }
            catch (file_create_error e)
            {
                cout << e.what() << endl;
            }
            break;
        }
        case 0:
        {
            break;
        }
        default:
        {
            cout << "Некоректный ввод. Введите заново" << endl;
            break;
        }
        }
    } while (choice != 0);
}