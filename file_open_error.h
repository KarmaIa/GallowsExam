#pragma once
#include <iostream>
#include <string>
#include <exception>
using namespace std;

// �������� ����� ��� �������� ������ exception
class file_open_error : public exception
{
    string filename;
public:
    file_open_error(const string& filename) : filename(filename) {}
    const char* what() const override
    {
        return (new string("������ ��� �������� ����� " + filename))->c_str();
    }
};