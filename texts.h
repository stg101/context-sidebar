#include "utils.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include <iostream>

void print_chrome_texts(HWND hwnd);
void load_json();

extern rapidjson::Document doc;

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
