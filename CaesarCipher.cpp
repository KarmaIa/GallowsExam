#include <iostream>
#include <string>
#include <vector>
#include "file_open_error.h"
#include "file_create_error.h"
#include "CaesarCipher.h"
using namespace std;

// �������� ������
string CaesarCipher::encrypt(const string& word)
{
    string encryptedWord = "";
    for (int i = 0; i < word.size(); i++)
    {
        encryptedWord += (char)((word[i] + caesar));
    }
    return encryptedWord;
}
// ���������� ������
string CaesarCipher::decrypt(const string& word)
{
    string encryptedWord = "";
    for (int i = 0; i < word.size(); i++)
    {
        encryptedWord += (char)((word[i] - caesar));
    }
    return encryptedWord;
}