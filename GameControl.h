#pragma once
// ����� ��� ���������� �����
class GameControl : private FileManager
{
private:
    GallowGame game;
public:
    // ����� �� ����� �������� ����
    void displayGameMenu();

    // ����� �� ����� ���� ������������
    void displayDeveloperMenu();

    // ����� �� ����� �������� ���� � main
    void displayMainMenu();

    // ����� ���� ����
    void displayWords(const vector<string>& decipheredWords);

    // ���� ����
    void playGame(vector<string>& decipheredWords, const string& filename);

    // ���� ������������
    void developerMode(vector<string>& decipheredWords, const string& filename);
};