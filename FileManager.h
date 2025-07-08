#pragma once
// ����� ��� �������� ���� � �� ����������
class FileManager : private CaesarCipher
{
public:
    // �������� ���� �� ����� ������������� ��
    vector<string> loadEncryptedWords(const string& filename);

    // �������� ����� �� ������� �� ���������
    void createDefaultEncryptedFileWithWordlist(const string& filename);

    // ���������� ������ ����� � ����
    void addNewWordInFile(const string& filename, vector<string>& decipheredWords);

    // �������� ����� �� �����
    void removeWordInFile(const string& filename, vector<string>& decipheredWords);
};