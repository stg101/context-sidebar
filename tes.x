#define STRICT
#define UNICODE
#include <windows.h>
#include <psapi.h>
#include <wingdi.h>
// #include <WinGDI.h>

#include <mmsystem.h>
#include <iostream>


//////////////////////////////////////////////////////////////////
// print path when foreground app changes

// std::wstring getText(HWND hwnd)
// {
//     int len = 1 + GetWindowTextLength(hwnd);

//     //initialize a string large enough to read data
//     std::wstring str(len, L'\0');
//     GetWindowText(hwnd, &str[0], len);
//     return str;
// }

// std::wstring getAppName(HWND hwnd)
// {
//     int len = 80;
//     std::wstring str(len, L'\0');

//     DWORD dwProcId = 0;
//     GetWindowThreadProcessId(hwnd, &dwProcId);
//     HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);
//     GetModuleFileNameExW((HMODULE)hProc, NULL, &str[0], len);

//     CloseHandle(hProc);

//     return str;
// }

// void CALLBACK WinEventProc(
//     HWINEVENTHOOK hWinEventHook,
//     DWORD event,
//     HWND hwnd,
//     LONG idObject,
//     LONG idChild,
//     DWORD dwEventThread,
//     DWORD dwmsEventTime)
// {
//     if (hwnd &&
//         idObject == OBJID_WINDOW &&
//         idChild == CHILDID_SELF &&
//         event == EVENT_SYSTEM_FOREGROUND)
//     {

//         std::wcout << hwnd << " || " << getText(hwnd) << " || " << getAppName(hwnd) << std::endl;
//     }
// }

// int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hinstPrev,
//                    LPSTR lpCmdLine, int nShowCmd)
// {
//     HWINEVENTHOOK hWinEventHook = SetWinEventHook(
//         EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND,
//         NULL, WinEventProc, 0, 0,
//         WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
//     MSG msg;
//     while (GetMessage(&msg, NULL, 0, 0))
//     {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//     }
//     if (hWinEventHook)
//         UnhookWinEvent(hWinEventHook);
//     return 0;
// }

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
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
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

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    // WS_EX_PALETTEWINDOW

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_PALETTEWINDOW,
        g_szClassName,
        L"The title of my window",
        WS_OVERLAPPEDWINDOW,
        10, 10, 200, 700,
        NULL, NULL, hInstance, NULL);

    // -10, 0, 200, 1032,

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
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }



    return Msg.wParam;
}

    // // work area reduce
    // RECT workarea;

    // // Get the current work area
    // SystemParametersInfo(SPI_GETWORKAREA, 0, &workarea, 0);

    // // modify 'workarea' here: either subtract your application's
    // // space (after starting up) or add it back in (before terminating)
    // workarea.left -= 1000;

    // // Set the new work area and broadcast the change to all running applications
    // SystemParametersInfo(SPI_SETWORKAREA, 0, &workarea, SPIF_SENDCHANGE);