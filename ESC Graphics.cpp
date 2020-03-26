// ESC Graphics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Image.h"
#include <iostream>

int main()
{
	Image img(200, 200, "out", COLOR_BROWN);

	img.Save();
}
