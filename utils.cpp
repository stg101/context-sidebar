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

        std::wcout << hwnd << " || " << getText(hwnd) << " || " << getAppName(hwnd) << std::endl;
        // std::wcout << hwnd << " || " << getText(hwnd) << std::endl;
        // std::wcout << hwnd << std::endl;
    }
}

void resize()
{
    // work area reduce
    RECT workarea;

    // Get the current work area
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workarea, 0);

    // modify 'workarea' here: either subtract your application's
    // space (after starting up) or add it back in (before terminating)
    workarea.left = 0;

    // Set the new work area and broadcast the change to all running applications
    // SystemParametersInfo(SPI_SETWORKAREA, 0, &workarea, SPIF_SENDCHANGE);
    SystemParametersInfo(SPI_SETWORKAREA, 0, &workarea, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
}