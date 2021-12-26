#define STRICT
#define UNICODE
#include <windows.h>
#include <psapi.h>
#include <wingdi.h>
#include <mmsystem.h>
#include <iostream>

std::wstring getText(HWND hwnd);
std::wstring getAppName(HWND hwnd);

void CALLBACK WinEventProc(
    HWINEVENTHOOK hWinEventHook,
    DWORD event,
    HWND hwnd,
    LONG idObject,
    LONG idChild,
    DWORD dwEventThread,
    DWORD dwmsEventTime);

void resize();
