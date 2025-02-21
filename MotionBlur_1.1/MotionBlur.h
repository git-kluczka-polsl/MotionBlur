#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include "GUI.h"
#include <chrono>


double getAsmTimeMs();
double getCppTimeMs();
int LinearBlur(unsigned char* imageData, int width, int height, int channels, int blurLevel, int angle, bool use_ASM);





