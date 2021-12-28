#include "utils.h"

void print_chrome_texts(HWND hwnd);
void print_tag(HDC hdc);
void print_description(HDC hdc);
void print_title(HDC hdc);
int read_json();

#ifndef TextStyle_H
#define TextStyle_H

class TextStyle
{
public:
    HFONT hFont;
    COLORREF textColor;
    COLORREF bgcolor;
    HDC hdc;

    void print(wchar_t *text, int len, RECT rect);
};

#endif

#ifndef TagStyle_H
#define TagStyle_H

class TagStyle : public TextStyle
{
public:
    TagStyle(HDC _hdc);
};
#endif

#ifndef DescriptionStyle_H
#define DescriptionStyle_H

class DescriptionStyle : public TextStyle
{
public:
    DescriptionStyle(HDC _hdc);
};
#endif


#ifndef TitleStyle_H
#define TitleStyle_H

class TitleStyle : public TextStyle
{
public:
    TitleStyle(HDC _hdc);
};
#endif
