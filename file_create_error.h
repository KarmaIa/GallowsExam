#pragma once
#include <iostream>
#include <string>
#include <exception>
using namespace std;

// �������� ����� ��� �������� ������ exception
class file_create_error : public exception
{
    string filename;
public:
    file_create_error(const string& filename) : filename(filename) {}
    const char* what() const override
    {
        return (new string("������ ��� �������� ����� " + filename))->c_str();
    }
};