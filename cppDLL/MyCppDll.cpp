// dllmain.cpp : Definiuje punkt wejścia dla aplikacji DLL.
#include "pch.h"
#include <windows.h>
#include <vector>
#include <cmath>
#include <iostream>



    extern "C" __declspec(dllexport) int test_dll_cpp(int a, int b) {
        return a + b; // Prosta operacja dodawania
    }
    
// Eksportowanie funkcji z DLL
    extern "C" __declspec(dllexport) void apply_linear_blur_cpp(unsigned char* image_data, int width, int height, int channels,int blur_level, int dx, int dy) {
        
        // Określamy stały rozmiar jądra rozmycia
        int kernelSize = 2 * blur_level + 1;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int c = 0; c < channels; ++c) {
                    int index = (y * width + x) * channels + c;
                    int sum = 0;
                    
                    // Dla każdego piksela sumujemy wartości z okna o rozmiarze kernelSize.
                    // Dla pozycji poza obrazem dodajemy 0.
                    for (int i = -blur_level; i <= blur_level; ++i) {
                        int offset_x = x + i * dx;
                        int offset_y = y + i * dy;
                        // Jeśli sąsiad znajduje się wewnątrz obrazu, dodajemy jego wartość;
                        // w przeciwnym razie dodajemy 0.
                        if (offset_x >= 0 && offset_x < width && offset_y >= 0 && offset_y < height) {
                            int neighbor_index = (offset_y * width + offset_x) * channels + c;
                            sum += image_data[neighbor_index];
                        }
                        else {
                            sum += 0; // Brakujący piksel – wartość domyślna 0
                        }
                    }

                    // Obliczamy średnią (uwzględniając cały kernel, nawet jeśli nie wszystkie pozycje są dostępne)
                    image_data[index] = static_cast<unsigned char>(sum / kernelSize);
                }
            }
        }
    }

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

