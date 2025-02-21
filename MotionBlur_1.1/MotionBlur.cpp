/*
=====  INFORMACJE  ======
TEMAT PROJEKTU : Motion Blur - liniowe rozmycie obrazu.
KRÓTKI OPIS : Funkcja nakładająca na obraz ARGB filtr Motion Blur - rozmycia pozorującego ruch liniowy.
Algorytm pracuje na mape bajtów uprzednio przygotowaną przez część GUI.
DATA WYKONANIA : Semestr Zimowy 2024 / 2025
AUTOR: Krzysztof Kluczka
*/

/*
=====  MOTIONBLUR.CPP  ======
MotionBlur.cpp odpowiada za aktywacaje DLL oraz mierznie czasu.
*/


#include "MotionBlur.h"
#include "pch.h"


using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;

// Deklaracje funkcji eksportowanych z asmDLL i cppDLL (zgodnie z ich specyfikacją)
typedef int (*AsmFunction)(int, int);
typedef int (*CppFunction)(int, int);
typedef void (*LinearBlurFunction)(unsigned char*, int, int, int, int, int, int);
std::vector<unsigned char> image;
std::vector<unsigned char> tempImage;
unsigned int width;
unsigned int height;
std::chrono::duration<double, std::milli> asmTimeMs;
std::chrono::duration<double, std::milli> cppTimeMs;

double getAsmTimeMs(){
    return asmTimeMs.count();
}

double getCppTimeMs() {
    return cppTimeMs.count();
}

int LinearBlur(unsigned char* imageData, int width, int height, int channels, int blurLevel, int angle, bool use_ASM) {

    double radians = angle * 3.14 / 180.0;
    int dx = std::round(std::cos(radians));
    int dy = std::round(std::sin(radians));


    if (use_ASM) {
        // Ładowanie biblioteki asmDLL
        HMODULE asmDllHandle = LoadLibrary(L"asmDLL.dll");
        if (!asmDllHandle) {
            std::cerr << "Nie można załadować asmDLL.dll!\n";
            FreeLibrary(asmDllHandle);
            return 1;
        }

        // Ładowanie funkcji z asmDLL
        LinearBlurFunction asmLinear_blur = (LinearBlurFunction)GetProcAddress(asmDllHandle, "apply_linear_blur_asm");
        if (!asmLinear_blur) {
            std::cerr << "Nie można znaleźć funkcji apply_linear_blur_asm w asmDLL.dll!\n";
            FreeLibrary(asmDllHandle);
            return 1;
        }
        // Oznaczenie czasu startu Asm DLL
        auto startAsm = std::chrono::high_resolution_clock::now();
        // Wywołanie Asm DLL
        asmLinear_blur(imageData, width, height, channels, blurLevel, dx, dy);
        // Oznaczenie czasu końca Asm DLL
        auto endAsm = std::chrono::high_resolution_clock::now();
        // Obliczenie czasu Asm DLL
        asmTimeMs = endAsm - startAsm;

        FreeLibrary(asmDllHandle);

    }
    else {
        // Ładowanie biblioteki cppDLL
        HMODULE cppDllHandle = LoadLibrary(L"cppDLL.dll");
        if (!cppDllHandle) {
            std::cerr << "Nie można załadować cppDLL.dll!\n";
            FreeLibrary(cppDllHandle);
            return 1;
        }
        // Ładowanie funkcji z cppDLL
        LinearBlurFunction cppLinear_blur = (LinearBlurFunction)GetProcAddress(cppDllHandle, "apply_linear_blur_cpp");
        if (!cppLinear_blur) {
            std::cerr << "Nie można znaleźć funkcji apply_linear_blur_cpp w cppDLL.dll!\n";
            FreeLibrary(cppDllHandle);
            return 1;
        }

        // Oznaczenie czasu startu Cpp DLL
        auto startCpp = std::chrono::high_resolution_clock::now();
        // Wywołanie Cpp DLL
        cppLinear_blur(imageData, width, height, channels, blurLevel, dx, dy);
        // Oznaczenie czasu końca Cpp DLL
        auto endCpp = std::chrono::high_resolution_clock::now();
        // Obliczenie czasu Cpp DLL
        cppTimeMs = endCpp - startCpp;
        FreeLibrary(cppDllHandle);
    }
    return 0;
}




    
