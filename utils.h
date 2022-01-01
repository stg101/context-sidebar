#define STRICT
#define UNICODE
#include <windows.h>
#include <psapi.h>
#include <wingdi.h>
#include <mmsystem.h>
#include <iostream>

std::wstring getText(HWND hwnd);
std::wstring getAppName(HWND hwnd);

extern std::wstring context_url;
extern HWND this_hwnd;

void CALLBACK WinEventProc(
    HWINEVENTHOOK hWinEventHook,
    DWORD event,
    HWND hwnd,
    LONG idObject,
    LONG idChild,
    DWORD dwEventThread,
    DWORD dwmsEventTime);

RECT resize(int left);

HWND createAppWindow(const wchar_t *g_szClassName, HINSTANCE hInstance, int width);
void closeAppWindow(HWND hwnd);
