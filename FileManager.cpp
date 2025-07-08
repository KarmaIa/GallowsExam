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
using namespace std;

// �������� ���� �� ����� ������������� ��
vector<string> FileManager::loadEncryptedWords(const string& filename)
{
    vector<string> encryptedWords;
    ifstream file(filename);

    if (!file.is_open())
    {
        throw file_open_error(filename);
    }
    string encryptedWord;
    while (getline(file, encryptedWord))
    {
        encryptedWords.push_back(decrypt(encryptedWord));
    }
    file.close();
    return encryptedWords;
}

// �������� ����� �� ������� �� ���������
void FileManager::createDefaultEncryptedFileWithWordlist(const string& filename)
{
    vector<string> words = {
        "������", "��������", "�����", "�����", "��������", "������", "�����", "��������",
    "�������", "������", "�������", "���������", "��������", "�������", "�����",
    "������", "�����", "���", "����", "�������", "��������", "�����", "�����",
    "����", "����", "������", "������", "��������", "�������", "��������", "������",
    "�����", "������", "���������", "�����", "�����", "���������", "�������",
    "�����", "����", "����", "�����", "����", "����", "�������", "������", "������",
    "������", "�������", "����"
    };

    ofstream file(filename);

    if (!file.is_open())
    {
        throw file_create_error(filename);
    }
    for (int i = 0; i < words.size(); i++)
    {
        file << encrypt(words[i]) << endl;
    }
    file.close();
}

// ���������� ������ ����� � ����
void FileManager::addNewWordInFile(const string& filename, vector<string>& decipheredWords)
{
    fstream file(filename, ios::app);

    if (!file.is_open())
    {
        throw file_open_error(filename);
    }

    string wordEmp;
    bool isCorrectWord = true;
    cout << "������� ����� ����� ��� ����: ";
    cin.ignore();
    getline(cin, wordEmp);
    system("cls");
    transform(wordEmp.begin(), wordEmp.end(), wordEmp.begin(), tolower);

    for (int i = 0; i < wordEmp.size(); i++)
    {
        if (wordEmp[i] < '�' || wordEmp[i] > '�')
        {
            cout << "������! ����� ����� ���� ������ �� ������� �����" << endl;
            isCorrectWord = false;
            break;
        }
    }
    for (int i = 0; i < decipheredWords.size(); i++)
    {
        if (decipheredWords[i] == wordEmp)
        {
            cout << "������! ����� ����� ��� ���� � ������" << endl;
            isCorrectWord = false;
            break;
        }
    }
    if (isCorrectWord)
    {
        file << encrypt(wordEmp) << endl;
        decipheredWords.push_back(wordEmp);
        cout << "����� " << wordEmp << " ���� ������� ���������!" << endl;
    }
    file.close();
}

// �������� ����� �� �����
void FileManager::removeWordInFile(const string& filename, vector<string>& decipheredWords)
{
    bool isFind = false;
    string wordForRemove;
    cout << "������� ����� ��� ��������: ";
    cin.ignore();
    getline(cin, wordForRemove);
    system("cls");
    transform(wordForRemove.begin(), wordForRemove.end(), wordForRemove.begin(), tolower);

    for (int i = 0; i < decipheredWords.size(); i++)
    {
        if (decipheredWords[i] == wordForRemove)
        {
            isFind = true;
            decipheredWords.erase(decipheredWords.begin() + i);

            ofstream file(filename);
            if (!file.is_open())
            {
                throw file_create_error(filename);
            }
            for (int i = 0; i < decipheredWords.size(); i++)
            {
                file << encrypt(decipheredWords[i]) << endl;
            }
            file.close();

            cout << "����� " << wordForRemove << " ���� ������� �������\n" << endl;
            break;
        }
    }

    if (!isFind)
    {
        cout << "����� " << wordForRemove << " ���� � ������\n" << endl;
    }
}