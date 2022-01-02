#include "texts.h"

using namespace rapidjson;

RECT TextStyle::print(const wchar_t *text, RECT rect)
{
    SelectObject(hdc, hFont);
    SetTextColor(hdc, textColor);
    SetBkColor(hdc, bgcolor);
    DrawText(hdc, text, wcslen(text), &rect, DT_WORDBREAK | DT_CALCRECT);
    DrawText(hdc, text, wcslen(text), &rect, DT_WORDBREAK);

    return rect;
}

TagStyle::TagStyle(HDC m_hdc)
{
    hdc = m_hdc;
    hFont = CreateFont(13, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                       CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
    textColor = RGB(50, 130, 214);
    bgcolor = RGB(37, 37, 38);
    padding = 4;
}

DescriptionStyle::DescriptionStyle(HDC m_hdc)
{
    hdc = m_hdc;
    hFont = CreateFont(12, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                       CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
    textColor = RGB(240, 240, 240);
    bgcolor = RGB(30, 30, 30);
    padding = 8;
}

TitleStyle::TitleStyle(HDC m_hdc)
{
    hdc = m_hdc;
    hFont = CreateFont(14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                       CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
    textColor = RGB(67, 138, 73);
    bgcolor = RGB(37, 37, 38);
    padding = 8;
}

ContextStyle::ContextStyle(HDC m_hdc)
{
    hdc = m_hdc;
    hFont = CreateFont(17, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                       CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
    textColor = RGB(240, 240, 240);
    bgcolor = RGB(37, 37, 38);
    padding = 10;
}

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

void draw_texts(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    auto context_url_str = wstring2string(context_url);

    int cursor = 15;

    TitleStyle title_style = TitleStyle(hdc);
    DescriptionStyle description_style = DescriptionStyle(hdc);
    TagStyle tag_style = TagStyle(hdc);
    ContextStyle context_style = ContextStyle(hdc);
    RECT rect;

    rapidjson::Value::ConstValueIterator itr;

    for (itr = doc["contexts"].Begin(); itr != doc["contexts"].End(); ++itr)
    {
        if (itr->HasMember("title"))
        {
            auto current_match_url = (*itr)["match_url"].GetString();

            if (context_url_str.find(current_match_url) != std::string::npos)
            {
                auto title_str = (*itr)["title"].GetString();
                const wchar_t *title = wstring2wchar_t(utf8toUtf16(title_str));

                std::wcout << title << " : " << wcslen(title) << std::endl;

                SetRect(&rect, 10, cursor, 100, cursor + context_style.padding);
                RECT calc_rect_title = context_style.print(title, rect);

                cursor = calc_rect_title.bottom + context_style.padding;

                for (rapidjson::Value::ConstValueIterator itrContent = (*itr)["content"].Begin(); itrContent != (*itr)["content"].End(); ++itrContent)
                {
                    auto content_title_str = (*itrContent)["title"].GetString();
                    const wchar_t *content_title = wstring2wchar_t(utf8toUtf16(content_title_str));

                    SetRect(&rect, 10, cursor, 100, cursor + title_style.padding);
                    RECT calc_rect_sub = title_style.print(content_title, rect);

                    cursor = calc_rect_sub.bottom + title_style.padding;

                    for (rapidjson::Value::ConstValueIterator itrCommand = (*itrContent)["commands"].Begin(); itrCommand != (*itrContent)["commands"].End(); ++itrCommand)
                    {
                        auto key_str = (*itrCommand)["key"].GetString();
                        const wchar_t *key = wstring2wchar_t(utf8toUtf16(key_str));

                        SetRect(&rect, 10, cursor, 100, cursor + tag_style.padding);
                        RECT calc_rect_tag = tag_style.print(key, rect);

                        cursor = calc_rect_tag.bottom + tag_style.padding;

                        auto desc_str = (*itrCommand)["description"].GetString();
                        const wchar_t *desc = wstring2wchar_t(utf8toUtf16(desc_str));

                        SetRect(&rect, 10, cursor, 100, cursor + description_style.padding);
                        RECT calc_rect_desc = description_style.print(desc, rect);

                        cursor = calc_rect_desc.bottom + description_style.padding;
                    }
                }

                break;
            }
        }
    }

    if (itr == doc["contexts"].End())
    {
        const wchar_t *default_text = L"I'm Context Sidebar. \n\nI can help you find commands easier. :). \n\nJust open an application supported on the contexts. json file. \n\n     __\n .--()°'.'\n'|, . ,'\n !_-(_\\ \n";
        SetRect(&rect, 10, 30, 100, 60);
        tag_style.print(default_text, rect);
    }

    // clear window
    // get current AppName
    // get commands from loaded json
    // render commands

    EndPaint(hwnd, &ps);
}
