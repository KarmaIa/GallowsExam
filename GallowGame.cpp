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
using namespace std;

// Выбор случайного слова (С учётом того чтобы слова небыли одинаковыми подряд)
string GallowGame::getRandomWord(const vector<string> wordList)
{
    while (true)
    {
        int randomIndex = rand() % wordList.size();
        string secretWord = wordList[randomIndex];
        if (secretWord != previousWord)
        {
            previousWord = secretWord;
            return secretWord;
        }
    }
}

// Вывод на экран правил для игры "Виселица"
void GallowGame::showRules()
{
    cout << "Правила игры \"Виселица\":" << endl
        << "-------------------------------------" << endl
        << "1. Компьютер выбирает случайное слово из списка." << endl
        << "2. Вы должны угадать это слово, называя по одной букве." << endl
        << "3. У вас есть 6 попыток на неправильные догадки." << endl
        << "4. После каждой неправильной догадки на экране появляется часть \"виселицы\"." << endl
        << "5. Если вы угадали слово до того, как закончились попытки, вы побеждаете!" << endl
        << "6. Если вы не угадали слово, и \"виселица\" нарисована полностью, вы проигрываете." << endl
        << "7. Вводить можно только буквы русского алфавита." << endl
        << "8. Если вы уже называли букву, она не будет учитываться повторно." << endl
        << "-------------------------------------" << endl;
}

// Вывод на экран текущего состояния игры
void GallowGame::displayGameStatus() const
{
    getImageGallows(6 - attempts);
    cout << "Слово: " << guessedWord << endl;
    cout << "Попыток осталось: " << attempts << endl;
    cout << "Введёные буквы: ";
    for (int i = 0; i < enteredLetters.size(); i++)
    {
        cout << enteredLetters[i] << " ";
    }
    cout << endl;
}

// Получения буквы и её обработка
void GallowGame::letterProcessing()
{
    char guess;
    bool isCorrectLetter = false;
    while (!isCorrectLetter)
    {
        cout << "Угадай букву: ";
        cin >> guess;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        guess = tolower(guess);

        if (cin.gcount() != 1 || guess < 'а' || guess > 'я')
        {
            cout << "Ошибка! Введите одну букву русского алфавита" << endl;
            cin.clear();
            continue;
        }
        isCorrectLetter = true;
    }
    system("cls");

    if (find(enteredLetters.begin(), enteredLetters.end(), guess) != enteredLetters.end())
    {
        cout << "Вы уже вводили эту букву" << endl;
        return;
    }

    enteredLetters.push_back(guess);

    bool correctGuess = false;
    for (int i = 0; i < wordForGame.length(); i++)
    {
        if (wordForGame[i] == guess)
        {
            guessedWord[i] = guess;
            correctGuess = true;
        }
    }

    if (!correctGuess)
    {
        attempts--;
        cout << "Неверная догадка." << endl;
    }
}

// Вывод итогов игры
void GallowGame::gameOver()
{
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime);

    getImageGallows(6 - attempts);
    cout << "Игра окончена!" << endl;
    if (guessedWord == wordForGame)
    {
        cout << "Вы победили!" << endl;
    }
    else
    {
        cout << "Вы проиграли." << endl;
        cout << "Часть слова которое вы отгадали: " << guessedWord << endl;
    }
    cout << "Искомое слово: " << wordForGame << endl;
    cout << "Время игры: " << duration.count() << " секунд" << endl;
    cout << "Использовано попыток: " << 6 - attempts << endl;
    cout << "Ваш выбор букв во время игре: ";
    for (int i = 0; i < enteredLetters.size(); i++)
    {
        cout << enteredLetters[i] << " ";
    }
    cout << "\n\n";
}

// Функция для работы игры
void GallowGame::play(const string& word)
{
    wordForGame = word;
    guessedWord = string(word.length(), '_');
    attempts = 6;
    enteredLetters.clear();
    startTime = chrono::high_resolution_clock::now();

    while (guessedWord != wordForGame && attempts > 0)
    {
        displayGameStatus();
        letterProcessing();
    }
    gameOver();
}