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
#include "ManOnTheGallows.h"
#include "GallowGame.h"
#include "GameControl.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    system("chcp 1251");
    system("cls");
    srand(time(0));

    GameControl gameControl;
    FileManager fileManager;

    // Загрузка зашифрованных слов из файла расшифровывая их (если файла со словами нет, то создаётся новый файл со словами по умолчанию)
    vector<string> decipheredWords;
    try
    {
        decipheredWords = fileManager.loadEncryptedWords("encrypted_words.txt");
    }
    catch (file_open_error e)
    {
        cout << e.what() << endl;
        cout << "Создание файла со списком слов игры по умолчанию" << endl;
        try
        {
            fileManager.createDefaultEncryptedFileWithWordlist("encrypted_words.txt");
            decipheredWords.clear();
            decipheredWords = fileManager.loadEncryptedWords("encrypted_words.txt");
            cout << "Файл со списком слов по умолчанию был успешно создан\n" << endl;
        }
        catch (file_create_error e)
        {
            cout << e.what() << endl;
            return -1;
        }
    }

    // Выбор режима игры
    int choice;
    do
    {
        gameControl.displayMainMenu();
        cin >> choice;
        while (cin.fail())
        {
            system("cls");
            cout << "Некоректный ввод. Введите заново" << endl;
            gameControl.displayMainMenu();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }
        system("cls");
        switch (choice)
        {
        case 1:
        {
            gameControl.playGame(decipheredWords, "encrypted_words.txt");
            break;
        }
        case 2:
        {
            gameControl.developerMode(decipheredWords, "encrypted_words.txt");
            break;
        }
        case 0:
        {
            cout << "Выход из игры..." << endl;
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