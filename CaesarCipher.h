#pragma once
// ����� ��� ����������/������������ ������� ������
class CaesarCipher
{
private:
    int caesar = 13;
public:
    // �������� ������
    string encrypt(const string& word);

    // ���������� ������
    string decrypt(const string& word);
};