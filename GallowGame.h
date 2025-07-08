#pragma once
// ����� ��� ����
class GallowGame : private ManOnTheGallows
{
private:
    string wordForGame; // ��������� ����� ��� ����
    string guessedWord; // ������ ��� ������ �� ����� ���������� ����� � ���� "_____", 
                        // � ����� �����-�� ����� ���� ������� ��� ������������� ������ '_'. ������ ���� ������ '�': "_�_�_"
    int attempts; // �������
    vector<char> enteredLetters; // ������ ��� �������� ������ ���� �� ����� ����
    string previousWord; // ������ �������� ���������� ��������� �����
    chrono::time_point<chrono::high_resolution_clock> startTime; // ���������� �������� �����
public:
    GallowGame() : wordForGame(""), guessedWord(""), attempts(0) {}

    // ����� ���������� ����� (� ������ ���� ����� ����� ������ ����������� ������)
    string getRandomWord(const vector<string> wordList);

    // ����� �� ����� ������ ��� ���� "��������"
    void showRules();

    // ����� �� ����� �������� ��������� ����
    void displayGameStatus() const;

    // ��������� ����� � � ���������
    void letterProcessing();

    // ����� ������ ����
    void gameOver();

    // ������� ��� ������ ����
    void play(const string& word);
};