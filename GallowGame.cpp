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

// ����� ���������� ����� (� ������ ���� ����� ����� ������ ����������� ������)
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

// ����� �� ����� ������ ��� ���� "��������"
void GallowGame::showRules()
{
    cout << "������� ���� \"��������\":" << endl
        << "-------------------------------------" << endl
        << "1. ��������� �������� ��������� ����� �� ������." << endl
        << "2. �� ������ ������� ��� �����, ������� �� ����� �����." << endl
        << "3. � ��� ���� 6 ������� �� ������������ �������." << endl
        << "4. ����� ������ ������������ ������� �� ������ ���������� ����� \"��������\"." << endl
        << "5. ���� �� ������� ����� �� ����, ��� ����������� �������, �� ����������!" << endl
        << "6. ���� �� �� ������� �����, � \"��������\" ���������� ���������, �� ������������." << endl
        << "7. ������� ����� ������ ����� �������� ��������." << endl
        << "8. ���� �� ��� �������� �����, ��� �� ����� ����������� ��������." << endl
        << "-------------------------------------" << endl;
}

// ����� �� ����� �������� ��������� ����
void GallowGame::displayGameStatus() const
{
    getImageGallows(6 - attempts);
    cout << "�����: " << guessedWord << endl;
    cout << "������� ��������: " << attempts << endl;
    cout << "������� �����: ";
    for (int i = 0; i < enteredLetters.size(); i++)
    {
        cout << enteredLetters[i] << " ";
    }
    cout << endl;
}

// ��������� ����� � � ���������
void GallowGame::letterProcessing()
{
    char guess;
    bool isCorrectLetter = false;
    while (!isCorrectLetter)
    {
        cout << "������ �����: ";
        cin >> guess;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        guess = tolower(guess);

        if (cin.gcount() != 1 || guess < '�' || guess > '�')
        {
            cout << "������! ������� ���� ����� �������� ��������" << endl;
            cin.clear();
            continue;
        }
        isCorrectLetter = true;
    }
    system("cls");

    if (find(enteredLetters.begin(), enteredLetters.end(), guess) != enteredLetters.end())
    {
        cout << "�� ��� ������� ��� �����" << endl;
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
        cout << "�������� �������." << endl;
    }
}

// ����� ������ ����
void GallowGame::gameOver()
{
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime);

    getImageGallows(6 - attempts);
    cout << "���� ��������!" << endl;
    if (guessedWord == wordForGame)
    {
        cout << "�� ��������!" << endl;
    }
    else
    {
        cout << "�� ���������." << endl;
        cout << "����� ����� ������� �� ��������: " << guessedWord << endl;
    }
    cout << "������� �����: " << wordForGame << endl;
    cout << "����� ����: " << duration.count() << " ������" << endl;
    cout << "������������ �������: " << 6 - attempts << endl;
    cout << "��� ����� ���� �� ����� ����: ";
    for (int i = 0; i < enteredLetters.size(); i++)
    {
        cout << enteredLetters[i] << " ";
    }
    cout << "\n\n";
}

// ������� ��� ������ ����
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