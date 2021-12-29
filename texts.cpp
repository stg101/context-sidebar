#include "texts.h"

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

void load_json()
{
    FILE *fp = fopen("contexts.json", "rb"); // non-Windows use "r"
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    doc.ParseStream(is);
    fclose(fp);
}

void print_chrome_texts(HWND hwnd)
{

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rect;
    SetRect(&rect, 10, 10, 100, 100);

    TitleStyle title_style = TitleStyle(hdc);
    title_style.print(L"Ctrl+ Shift + C", 4, rect);

    for (rapidjson::Value::ConstValueIterator itr = doc["contexts"].Begin(); itr != doc["contexts"].End(); ++itr)
    { // Ok
        if (itr->HasMember("title"))
        {                                                  // Ok
            auto somestring = (*itr)["title"].GetString(); // bingo
            std::cout << somestring << std::endl;
        }
    }

    EndPaint(hwnd, &ps);
}
