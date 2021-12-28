#include "texts.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace rapidjson;

void TextStyle::print(wchar_t *text, int len, RECT rect)
{
    SelectObject(hdc, hFont);
    SetTextColor(hdc, textColor);
    SetBkColor(hdc, bgcolor);
    DrawText(hdc, text, len, &rect, DT_WORDBREAK);
}

TagStyle::TagStyle(HDC m_hdc)
{
    hdc = m_hdc;
    hFont = CreateFont(14, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                       CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
    textColor = RGB(50, 130, 214);
    bgcolor = RGB(37, 37, 38);
}

DescriptionStyle::DescriptionStyle(HDC m_hdc)
{
    hdc = m_hdc;
    hFont = CreateFont(12, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                       CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
    textColor = RGB(240, 240, 240);
    bgcolor = RGB(30, 30, 30);
}

TitleStyle::TitleStyle(HDC m_hdc)
{
    hdc = m_hdc;
    hFont = CreateFont(14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                       CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
    textColor = RGB(67, 138, 73);
    bgcolor = RGB(37, 37, 38);
}

// class Printer
// {
// public:
//     std::string model;
//     int year;
//     Printer(std::string x, std::string y, int z)
//     {
//         model = y;
//         year = z;
//     }

//     void printname()
//     {
//         std::cout << "Geekname is: " << year;
//     }
// };

int read_json()
{
    // 1. Parse a JSON string into DOM.
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    Document d;
    d.Parse(json);

    // 2. Modify it by DOM.
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
    return 0;
}

void print_chrome_texts(HWND hwnd)
{

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rect;
    SetRect(&rect, 10, 10, 100, 100);

    TitleStyle title_style = TitleStyle(hdc);
    title_style.print(L"Ctrl+ Shift + C", 4, rect);

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