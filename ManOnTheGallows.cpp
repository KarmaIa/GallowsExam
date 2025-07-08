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
#include "ManOnTheGallows.h"
using namespace std;

// Получения изображения человека на виселицы по индексу
void ManOnTheGallows::getImageGallows(int index) const
{
    cout << imageGallows[index] << endl;
}