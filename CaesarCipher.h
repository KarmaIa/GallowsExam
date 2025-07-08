#pragma once
// Класс для шифрования/дешифрования методом Цезаря
class CaesarCipher
{
private:
    int caesar = 13;
public:
    // Шифровка строки
    string encrypt(const string& word);

    // Дешифровка строки
    string decrypt(const string& word);
};