// Dynamic Link Library.cpp :

#include "framework.h"
#include "resource.h"
#include <string>

#define MAX_LOADSTRING          100
#define CMD_BUTTON_1            1001
#define CMD_BUTTON_2            1002
#define CMD_BUTTON_3            1003
#define CMD_BUTTON_DEC          1004

typedef long (*sqr_type)(long);   // sqr_type ~~ long (*)(long)  

sqr_type sqr_fun; // sqr_type sqr_fun == long (*sqr_fun)(long)
sqr_type cube_fun;
sqr_type hex_fun;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND static2;
HWND edit;
HWND list;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void button1Click();
void button2Click();
void button3Click();
void button4Click();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DYNAMICLINKLIBRARY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DYNAMICLINKLIBRARY));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DYNAMICLINKLIBRARY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(250,128,114));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DYNAMICLINKLIBRARY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CreateWindowW(L"Button", L"Sqr", WS_CHILD | WS_VISIBLE, 10, 10, 75, 23, hWnd, (HMENU)CMD_BUTTON_1, hInst, NULL);
        CreateWindowW(L"Button", L"Cube", WS_CHILD | WS_VISIBLE, 95, 40, 75, 23, hWnd, (HMENU)CMD_BUTTON_2, hInst, NULL);
        CreateWindowW(L"Button", L"Hex", WS_CHILD | WS_VISIBLE, 10, 180, 75, 23, hWnd, (HMENU)CMD_BUTTON_3, hInst, NULL);
        CreateWindowW(L"Button", L"Dec", WS_CHILD | WS_VISIBLE, 10, 210, 75, 23, hWnd, (HMENU)CMD_BUTTON_DEC, hInst, NULL);

        edit = CreateWindowW(L"EDIT", L"5", WS_CHILD | WS_VISIBLE, 10, 40, 75, 23, hWnd, NULL, hInst, NULL); 
        list = CreateWindowW(L"Listbox", L"5", WS_CHILD | WS_VISIBLE, 10, 80, 400, 100, hWnd, NULL, hInst, NULL); 
        static2 = CreateWindowW(L"Static", L"Sqr", WS_CHILD | WS_VISIBLE, 180, 40, 150, 23, hWnd, 0, hInst, NULL);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case CMD_BUTTON_1:
                button1Click();
                break;
            case CMD_BUTTON_2:
                button2Click();
                break;
            case CMD_BUTTON_3:
                button3Click();
                break;
            case CMD_BUTTON_DEC:
                button4Click();
                break;

            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void button1Click() {
    HMODULE dll = LoadLibraryW(L"DLLCreate.dll");
    if (dll == NULL) {
        MessageBoxW(NULL, L"ERROR", L"DLL", MB_OK | MB_ICONERROR);
    }
    else {
        sqr_fun = (sqr_type)GetProcAddress(dll, "Sqr");
        if (sqr_fun == NULL) {
            MessageBoxW(NULL, L"ERROR", L"FUN", MB_OK | MB_ICONERROR);
        }
        else {
            WCHAR str[50];
            long x = 2;
            _snwprintf_s(str, 50, L"%d ^ 2 = %d", x, sqr_fun(x));
            MessageBoxW(NULL, str, L"FUNC", MB_OK | MB_OK);
        }
    }
}
void button2Click() {

    HMODULE dll = LoadLibraryW(L"DLLCreate.dll");
    if (dll == NULL) {
        MessageBoxW(NULL, L"ERROR", L"DLL", MB_OK | MB_ICONERROR);
    }
    else {
        cube_fun = (sqr_type)GetProcAddress(dll, "Cube");
        if (cube_fun == NULL) {
            MessageBoxW(NULL, L"ERROR", L"FUN", MB_OK | MB_ICONERROR);
        }
        else {
            WCHAR str[100];
            int x = 0;
            SendMessageW(edit, WM_GETTEXT, 100, (LPARAM)str);
            x = _wtoi(str);
           // _itow_s(cube_fun(x), str, 10);
            _snwprintf_s(str, 50, L"%d ^ 3 = %d", x, cube_fun(x));
            SendMessageW(static2, WM_SETTEXT, 100, (LPARAM)str);
           
        }
    }
}

void button3Click() {

    HMODULE dll = LoadLibraryW(L"DLLCreate");

    int (*hex2dec)(const char*);
    hex2dec = (int (*)(const char*))GetProcAddress(dll, "hex2dec");

    if (hex2dec) {
        char buff[100];
        SendMessageA(edit, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)buff);

        _snprintf_s(buff, 100, 100, "%s to dec = %d", buff, hex2dec(buff));

        SendMessageA(list, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)buff);
    }
    else {

        MessageBoxW(NULL, L"error", L"hex2dec", MB_OK | MB_ICONERROR);
    }
}

void button4Click() {
    HMODULE dll = LoadLibraryW(L"DLLCreate");

    char* (*dec2hex)(int);
    dec2hex = (char* (*)(int))GetProcAddress(dll, "dec2hex");

    if (dec2hex) {
        char buff[100];
        SendMessageA(edit, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)buff);
        int param = atoi(buff);
        char* res = dec2hex(param);
        _snprintf_s(buff, 100, 100, "%d to hex = %s", param, res);
        delete res;

        SendMessageA(list, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)buff);
    }
    else {

        MessageBoxW(NULL, L"error", L"dec2hex", MB_OK | MB_ICONERROR);
    }
}
