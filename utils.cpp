#define STRICT
#define UNICODE
#include "utils.h"

std::wstring getText(HWND hwnd)
{
    int len = 0 + GetWindowTextLength(hwnd);

    //initialize a string large enough to read data
    std::wstring str(len, L'\0');
    GetWindowText(hwnd, &str[0], len);
    return str;
}

std::wstring getAppName(HWND hwnd)
{
    int len = 79;
    std::wstring str(len, L'\0');

    DWORD dwProcId = 0;
    GetWindowThreadProcessId(hwnd, &dwProcId);
    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);
    GetModuleFileNameExW((HMODULE)hProc, NULL, &str[0], len);

    CloseHandle(hProc);

    return str;
}

void CALLBACK WinEventProc(
    HWINEVENTHOOK hWinEventHook,
    DWORD event,
    HWND hwnd,
    LONG idObject,
    LONG idChild,
    DWORD dwEventThread,
    DWORD dwmsEventTime)
{
    if (hwnd &&
        idObject == OBJID_WINDOW &&
        idChild == CHILDID_SELF &&
        event == EVENT_SYSTEM_FOREGROUND)
    {
        context_url = getAppName(hwnd);
        InvalidateRect(this_hwnd, NULL, TRUE);
    }
}

RECT resize(int left)
{
    RECT workarea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workarea, 0);
    workarea.left = left;
    SystemParametersInfo(SPI_SETWORKAREA, 0, &workarea, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);

    return workarea;
}

HWND createAppWindow(const wchar_t *g_szClassName, HINSTANCE hInstance, int width)
{
    RECT workarea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workarea, 0);
    workarea.left = width;
    SystemParametersInfo(SPI_SETWORKAREA, 0, &workarea, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);

    HWND hwnd = CreateWindowEx(
        WS_EX_PALETTEWINDOW,
        g_szClassName,
        L"The title of my window",
        WS_OVERLAPPEDWINDOW,
        0,
        workarea.top,
        width,
        workarea.bottom - workarea.top,
        NULL, NULL, hInstance, NULL);

    return hwnd;
}