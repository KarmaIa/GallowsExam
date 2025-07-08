#pragma once
// Класс для хранения слов и их шифрования
class FileManager : private CaesarCipher
{
public:
    // Загрузка слов из файла расшифровывая их
    vector<string> loadEncryptedWords(const string& filename);

    // Создания файла со словами по умолчанию
    void createDefaultEncryptedFileWithWordlist(const string& filename);

    // Добавления нового слова в файл
    void addNewWordInFile(const string& filename, vector<string>& decipheredWords);

    // Удаление слова из файла
    void removeWordInFile(const string& filename, vector<string>& decipheredWords);
};