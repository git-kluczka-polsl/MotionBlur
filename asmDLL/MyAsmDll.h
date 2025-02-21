#ifndef ASMDLL_H
#define ASMDLL_H

#ifdef ASMDLL_EXPORTS
#define ASMDLL_API __declspec(dllexport)
#else
#define ASMDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

    // Deklaracja funkcji eksportowanej z asemblera
    ASMDLL_API void apply_linear_blur_asm(
        unsigned char* imageData,
        int width,
        int height,
        int channels,
        int blurLevel,
        int dx,
        int dy
    );

#ifdef __cplusplus
}
#endif

#endif // ASMDLL_H
