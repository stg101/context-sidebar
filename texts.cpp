#include "texts.h"

void print_chrome_texts(HWND hwnd)
{

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // int y_pos = 0;
    // const int array_size = 3;
    // wchar_t *text_array[array_size] = {
    //     L"Hello World!",
    //     L"This is a hello world application made in the Win32 API",
    //     L"This example was made by some random dude, aka -LeetGamer-"};

    // std::wcout << "len : " << wcslen(text_array[1]) << std::endl;
    // std::wcout << "pointer : " << text_array[3] << std::endl;

    // for (int i = 0; i < array_size; i++, y_pos += 20)
    // {
    //     TextOut(hdc, 5, y_pos, text_array[i], wcslen(text_array[i]));
    // }

    // TextOut(hdc, 5, 5, str, wcslen(str));

    print_tag(hdc);
    print_description(hdc);
    print_title(hdc);

    EndPaint(hwnd, &ps);
}

void print_tag(HDC hdc)
{
    // max : 13  chars one line

    HFONT hFont = CreateFont(14, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                             CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

    SelectObject(hdc, hFont);

    const COLORREF textColor = RGB(50, 130, 214);
    const COLORREF bgcolor = RGB(37, 37, 38);

    SetTextColor(hdc, textColor);
    SetBkColor(hdc, bgcolor);

    RECT rect;
    SetRect(&rect, 10, 10, 90, 38);
    DrawText(hdc, L"Ctrl+ Shift + C", 15, &rect, DT_WORDBREAK);
}

void print_description(HDC hdc)
{
    HFONT hFont = CreateFont(12, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                             CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

    SelectObject(hdc, hFont);

    const COLORREF textColor = RGB(240, 240, 240);
    const COLORREF bgcolor = RGB(30, 30, 30);

    SetTextColor(hdc, textColor);
    SetBkColor(hdc, bgcolor);

    RECT rect;
    SetRect(&rect, 10, 40, 90, 74);
    DrawText(hdc, L"xxx xxx xxxxx xxxx", 20, &rect, DT_WORDBREAK);
}

void print_title(HDC hdc)
{
    HFONT hFont = CreateFont(14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                             CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

    SelectObject(hdc, hFont);

    const COLORREF textColor = RGB(67, 138, 73);
    const COLORREF bgcolor = RGB(37, 37, 38);

    SetTextColor(hdc, textColor);
    SetBkColor(hdc, bgcolor);

    RECT rect;
    SetRect(&rect, 10, 80, 90, 108);
    DrawText(hdc, L"Chrome", 6, &rect, DT_WORDBREAK);
}