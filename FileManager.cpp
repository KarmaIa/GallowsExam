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

// Загрузка слов из файла расшифровывая их
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

// Создания файла со словами по умолчанию
void FileManager::createDefaultEncryptedFileWithWordlist(const string& filename)
{
    vector<string> words = {
        "яблоко", "апельсин", "банан", "манго", "клубника", "ананас", "арбуз", "виноград",
    "помидор", "огурец", "морковь", "картофель", "брокколи", "капуста", "перец",
    "собака", "кошка", "лев", "тигр", "медведь", "обезьяна", "зебра", "жираф",
    "слон", "лиса", "россия", "япония", "германия", "франция", "бразилия", "канада",
    "китай", "италия", "австралия", "индия", "книга", "компьютер", "телефон",
    "ручка", "часы", "окно", "дверь", "стол", "стул", "зеркало", "солнце", "звезда",
    "радуга", "счастье", "снег"
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

// Добавления нового слова в файл
void FileManager::addNewWordInFile(const string& filename, vector<string>& decipheredWords)
{
    fstream file(filename, ios::app);

    if (!file.is_open())
    {
        throw file_open_error(filename);
    }

    string wordEmp;
    bool isCorrectWord = true;
    cout << "Введите новое слово для игры: ";
    cin.ignore();
    getline(cin, wordEmp);
    system("cls");
    transform(wordEmp.begin(), wordEmp.end(), wordEmp.begin(), tolower);

    for (int i = 0; i < wordEmp.size(); i++)
    {
        if (wordEmp[i] < 'а' || wordEmp[i] > 'я')
        {
            cout << "Ошибка! Слово может быть только на русском языке" << endl;
            isCorrectWord = false;
            break;
        }
    }
    for (int i = 0; i < decipheredWords.size(); i++)
    {
        if (decipheredWords[i] == wordEmp)
        {
            cout << "Ошибка! Такое слово уже есть в списке" << endl;
            isCorrectWord = false;
            break;
        }
    }
    if (isCorrectWord)
    {
        file << encrypt(wordEmp) << endl;
        decipheredWords.push_back(wordEmp);
        cout << "Слово " << wordEmp << " было успешно добавлено!" << endl;
    }
    file.close();
}

// Удаление слова из файла
void FileManager::removeWordInFile(const string& filename, vector<string>& decipheredWords)
{
    bool isFind = false;
    string wordForRemove;
    cout << "Введите слово для удаление: ";
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

            cout << "Слово " << wordForRemove << " было успешно удалено\n" << endl;
            break;
        }
    }

    if (!isFind)
    {
        cout << "Слова " << wordForRemove << " нету в списке\n" << endl;
    }
}