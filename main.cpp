#define STRICT
#define UNICODE
#include <windows.h>
#include <psapi.h>
#include <wingdi.h>
#include <mmsystem.h>
#include <iostream>

#include "utils.h"
#include "texts.h"

///////////////////////////////////////////////////////////////////////////
// create window
const wchar_t g_szClassName[] = L"myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
    {

        print_chrome_texts(hwnd);
    }

    break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    // ############################# hook foreground change
    HWINEVENTHOOK hWinEventHook = SetWinEventHook(
        EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND,
        NULL, WinEventProc, 0, 0,
        WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
    // ########################## create window
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hbrBackground = CreateSolidBrush(RGB(37, 37, 38));

    read_json();

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = createAppWindow(g_szClassName, hInstance, 100);

    // Step 2: Creating the Window

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    SetWindowLong(hwnd, GWL_STYLE, 0);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while (GetMessage(&Msg, NULL, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    if (hWinEventHook)
        UnhookWinEvent(hWinEventHook);

    return Msg.wParam;
}
