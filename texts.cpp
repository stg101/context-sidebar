#include "texts.h"

using namespace rapidjson;

void TextStyle::print(const wchar_t *text, RECT rect)
{
    SelectObject(hdc, hFont);
    SetTextColor(hdc, textColor);
    SetBkColor(hdc, bgcolor);
    DrawText(hdc, text, wcslen(text), &rect, DT_WORDBREAK);
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

wstring utf8toUtf16(const string &str)
{
    if (str.empty())
        return wstring();

    size_t charsNeeded = ::MultiByteToWideChar(CP_UTF8, 0,
                                               str.data(), (int)str.size(), NULL, 0);
    if (charsNeeded == 0)
        throw runtime_error("Failed converting UTF-8 string to UTF-16");

    vector<wchar_t> buffer(charsNeeded);
    int charsConverted = ::MultiByteToWideChar(CP_UTF8, 0,
                                               str.data(), (int)str.size(), &buffer[0], buffer.size());
    if (charsConverted == 0)
        throw runtime_error("Failed converting UTF-8 string to UTF-16");

    return wstring(&buffer[0], charsConverted);
}

std::string wstring2string(std::wstring wide)
{
    std::string str(wide.begin(), wide.end());
    return str;
}

const wchar_t *wstring2wchar_t(std::wstring wide)
{
    const wchar_t *wcs = wide.c_str();
    return wcs;
}

void print_chrome_texts(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    auto context_url_str = wstring2string(context_url);

    const wchar_t *title = L"Context Sidebar";

    for (rapidjson::Value::ConstValueIterator itr = doc["contexts"].Begin(); itr != doc["contexts"].End(); ++itr)
    {
        if (itr->HasMember("title"))
        {
            auto current_match_url = (*itr)["match_url"].GetString();

            if (context_url_str.find(current_match_url) != std::string::npos)
            {
                auto title_str = (*itr)["title"].GetString();
                title = wstring2wchar_t(utf8toUtf16(title_str));
                break;
            }
        }
    }

    std::wcout << title << " : " << wcslen(title) << std::endl;
    RECT rect;
    SetRect(&rect, 9, 10, 100, 100);

    TitleStyle title_style = TitleStyle(hdc);
    title_style.print(title, rect);

    // clear window
    // get current AppName
    // get commands from loaded json
    // render commands

    EndPaint(hwnd, &ps);
}
