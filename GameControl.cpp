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

// ����� �� ����� �������� ����
void GameControl::displayGameMenu()
{
    cout << "1 - ������ ����� ����" << endl;
    cout << "2 - ������� ����" << endl;
    cout << "0 - �����" << endl;
    cout << "�����: ";
}

// ����� �� ����� ���� ������������
void GameControl::displayDeveloperMenu()
{
    cout << "���� ������������" << endl;
    cout << "1 - �������� ����� �����" << endl;
    cout << "2 - ������� �����" << endl;
    cout << "3 - �������� ��� �����" << endl;
    cout << "4 - ����������� ������ ���� �� ���������" << endl;
    cout << "0 - �����" << endl;
    cout << "�����: ";
}

// ����� �� ����� �������� ���� � main
void GameControl::displayMainMenu()
{
    cout << "������� ����" << endl;
    cout << "1 - ������ ���� \"��������\"" << endl;
    cout << "2 - ����� ������������" << endl;
    cout << "0 - �����" << endl;
    cout << "�����: ";
}

// ����� ���� ����
void GameControl::displayWords(const vector<string>& decipheredWords)
{
    cout << "������ ����:" << endl;
    for (string word : decipheredWords)
    {
        cout << word << endl;
    }
    cout << endl;
}

// ���� ����
void GameControl::playGame(vector<string>& decipheredWords, const string& filename)
{
    int choice;
    cout << "����� ���������� � ���� \"��������\"" << endl;
    do
    {
        displayGameMenu();
        cin >> choice;
        while (cin.fail())
        {
            system("cls");
            cout << "����������� ����. ������� ������" << endl;
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
            cout << "����������� ����. ������� ������" << endl;
            break;
        }
        }
    } while (choice != 0);
}

// ���� ������������
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
            cout << "����������� ����. ������� ������" << endl;
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
                cout << "���� �� ������� ���� �� ��������� ��� ������� ����������\n" << endl;
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
            cout << "����������� ����. ������� ������" << endl;
            break;
        }
        }
    } while (choice != 0);
}