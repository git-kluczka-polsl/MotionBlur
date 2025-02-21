
; =====  INFORMACJE  ======
; TEMAT PROJEKTU: Motion Blur - liniowe rozmycie obrazu.
; KR�TKI OPIS: Funkcja nak�adaj�ca na obraz ARGB filtr Motion Blur - rozmycia pozoruj�cego ruch liniowy.
; Algorytm pracuje na mape bajt�w uprzednio przygotowan� przez cz�� GUI.
; DATA WYKONANIA: Semestr Zimowy 2024/2025
; AUTOR: Krzysztof Kluczka
;
; ===== PARAMETRY FUNKCJI ======
; image_data -  wska�nik na dane obrazu.
; width -       szeroko�� obrazu,
; height -      wysoko�� obrazu,
; channels -    ilo�� kana��w na pixel (4 dla ARGB),
; blur_level -  poziom rozmycia wyra�any w pikselach,
; dx -          sk�adnik x kierunku rozmycia,
; dy -          sk�adowa y kierunku rozmycia.

PUBLIC apply_linear_blur_asm

.CODE

apply_linear_blur_asm PROC
    ; Prolog - zapisanie rejestr�w nietrwa�ych
    push    rbp
    push    rbx
    push    rdi        
    push    rsi        
    push    r12
    push    r13
    push    r14
    push    r15
    mov     rbp, rsp

    ; Przeniesienie parametr�w do rejestr�w
    mov     rsi, rcx           ; image_data
    mov     edi, edx           ; width (32-bit)
    mov     ebx, r8d           ; height (32-bit)
    mov     r12d, r9d          ; channels (32-bit)
    mov     r13d, DWORD PTR[rbp+104] ; blur_level (32-bit, rozszerzenie znaku)
    mov     r14d, DWORD PTR[rbp+112] ; dx (32-bit, rozszerzenie znaku)
    mov     r15d, DWORD PTR[rbp+120] ; dy (32-bit, rozszerzenie znaku)

    ; Obliczanie kernelSize (2*blur_level +1) i zachowanie w ecx
    mov     ecx, r13d
    lea     ecx, [ecx*2 + 1]   ; edx = kernelSize

    ; --- P�tle przetwarzania obrazu ---
    xor     r9, r9              ; y = 0 (64-bit, ale zakres 32-bit)

pixel_y_loop:
    cmp     r9d, ebx            ; Por�wnanie y z height (32-bit)
    jge     end_pixel_y_loop

    xor     r10, r10            ; x = 0

pixel_x_loop:
    cmp     r10d, edi           ; Por�wnanie x z width (32-bit)
    jge     end_pixel_x_loop

    xor     r11, r11            ; c = 0

channel_loop:
    cmp     r11d, 4          ; Por�wnanie c z channels (32-bit)
    jge     end_channel_loop

    ; --- Obliczanie indeksu bie��cego piksela ---
    ; index = (y * width + x) * channels + c
    mov     eax, r9d            ; eax = y
    imul    eax, edi            ; y * width
    add     eax, r10d           ; y * width + x
    imul    eax, 4              ; (y * width + x) * channels
    add     eax, r11d           ; + c ? eax = index (32-bit)
    mov     r8d, eax            ; index w r8d

    ; --- Inicjalizacja sumy ---
    xor     edx, edx            ; sum = 0

    ; --- P�tla po j�dru rozmycia ---
    mov     eax, r13d           ; blur_level
    neg     eax                 ; i zaczyna od -blur_level
    mov     r12d, eax           ; i w r12d (32-bit) 


    sub rsp, 8; rezerwacja miejsca dla temp_x i temp_y
loop_i:
    cmp     r12d, r13d          ; Por�wnanie i z blur_level (32-bit)
    jg      end_loop_i

    ; --- Obliczanie temp_x = x + i*dx ---
    mov     eax, r12d           ; i
    imul    eax, r14d           ; i * dx
    add     eax, r10d           ; x + i*dx ? temp_x (32-bit)
    mov     [rsp], eax          ; temp_x na stosie

    ; --- Obliczanie temp_y = y + i*dy ---
    mov     eax, r12d           ; i
    imul    eax, r15d           ; i * dy
    add     eax, r9d            ; y + i*dy ? temp_y (32-bit)
    mov     [rsp + 4], eax      ; temp_y na stosie

    ; --- Granice temp_x i temp_y ---
    mov eax, 0
    cmp     [rsp], eax
    jl      out_of_bounds
    cmp     [rsp], edi          ; edi = width (32-bit)
    jge     out_of_bounds

    cmp     [rsp + 4], eax
    jl      out_of_bounds
    cmp     [rsp + 4], ebx       ; ebx = height (32-bit)
    jge     out_of_bounds

    ; --- Obliczanie indeksu s�siada ---
    ; neighbor_index = (temp_y * width + temp_x) * channels + c
    mov     eax, [rsp + 4]       ; temp_y
    imul    eax, edi             ; temp_y * width
    add     eax, [rsp]           ; + temp_x
    imul    eax, 4               ; * channels
    add     eax, r11d            ; + c ? eax = neighbor_index

    cmp     eax, 0
    jl      out_of_bounds
    sub     rsp, 8               ; miejsce na stosie dla zachowania edi
    mov     dword ptr [rsp], edi
    imul    edi, ebx
    lea     edi, [edi*4]
    cmp     eax, edi             ; edi = width * height * channels (32-bit)   
    jge     restore_stack        ; je�eli eax > edi, pomi� sumowanie

    movzx   eax, BYTE PTR [rsi + rax] ; 8-bitowa warto�� do EAX
    add     edx, eax                  ; rozszerzona warto�� do EDX
  
restore_stack:
    mov     edi, dword ptr [rsp] ; edi (width) ze stosu
    add     rsp, 8               ; i wyr�wnanie

out_of_bounds:

    inc     r12d                 ; i++
    jmp     loop_i

end_loop_i:
    add rsp, 8 ;przywr�cenie RSP po temp_x/y

    ; --- Oblicz �redni� i zapisz wynik ---    
    mov     eax, edx             ; przenie� sum� do eax
    xor     edx, edx             ; wyzeruj edx, poniewa� suma jest nieujemna
    div     ecx                  ; wykonaj dzielenie: (edx:eax) / kernelSize
    mov     BYTE PTR [rsi + r8], al             ; zapisz wynik (�redni�)

    ; --- Nast�pny kana� ---
    inc     r11
    jmp     channel_loop

end_channel_loop:
    inc     r10
    jmp     pixel_x_loop

end_pixel_x_loop:
    inc     r9
    jmp     pixel_y_loop

end_pixel_y_loop:
    ; Epilog - przywr�cenie rejestr�w
    mov     rsp, rbp
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     rsi
    pop     rdi
    pop     rbx
    pop     rbp
    ret

apply_linear_blur_asm ENDP

END