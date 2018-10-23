#include <windows.h>
#include <stdlib.h>


#define DANE_MENU_DODAJ 1
#define DANE_MENU_ZAMKNIJ 3
#define ZMIEN_TYTUL 4
#define PROMILE_WODKA 5
#define PROMILE_PIWO 6
#define PROMILE_WHISKEY 7

using namespace std;

LRESULT CALLBACK ProceduraOkna(HWND, UINT, WPARAM, LPARAM);

void DodajMenu(HWND);
void DodajKontrole(HWND);

int prom = 0;

HWND hGrAlk;
HMENU hMenu;
HWND hTekst;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    //KLASA OKNA
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"MojaKlasaOkna";
    wc.lpfnWndProc = ProceduraOkna;

    if(!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"MojaKlasaOkna", L"Alkomat", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 600, 600, NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while(GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK ProceduraOkna(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
    case WM_COMMAND: //Wiadomosc jest dostarczana po kazdej akcji
        switch(wp)
        {
        case DANE_MENU_ZAMKNIJ:
            DestroyWindow(hWnd);
            break;
        case DANE_MENU_DODAJ:
            MessageBeep(MB_ICONINFORMATION);
            break;
        case ZMIEN_TYTUL:
            wchar_t tekst[100];
            GetWindowTextW(hTekst,tekst,100);
            SetWindowTextW(hWnd,tekst);
            break;
        case PROMILE_WODKA:
            break;

        }
        break;
    case WM_CREATE: //Tutaj tworze elementy okienka
        DodajMenu(hWnd);
        DodajKontrole(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void DodajMenu(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hMenuDane = CreateMenu();
    HMENU hMenuDaneDodaj = CreateMenu();

    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenuDane,"Dane");
        AppendMenu(hMenuDane, MF_POPUP, (UINT_PTR)hMenuDaneDodaj, "Dodaj");
            AppendMenu(hMenuDaneDodaj, MF_STRING, DANE_MENU_DODAJ, "Vodka");

        AppendMenu(hMenuDane, MF_STRING, NULL, "Placeholder");

        AppendMenu(hMenuDane, MF_SEPARATOR, NULL, NULL);

        AppendMenu(hMenuDane, MF_STRING, DANE_MENU_ZAMKNIJ, "Zamknij");

    AppendMenu(hMenu,MF_STRING,NULL,"Pomoc");








    SetMenu(hWnd,hMenu);
}

void DodajKontrole(HWND hWnd)
{
    CreateWindowW(L"Static",L"Alkohole:",WS_VISIBLE | WS_CHILD | SS_CENTER,20,20,80,40,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static",L"Ilosc spozytego alkoholu [g]:",WS_VISIBLE | WS_CHILD | SS_CENTER,120,20,120,40,hWnd,NULL,NULL,NULL);
    hGrAlk = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER,240,20,120,40,hWnd,NULL,NULL,NULL);
    //hTekst = CreateWindowW(L"Edit",L"...",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,200,154,100,50,hWnd,NULL,NULL,NULL);

    CreateWindowW(L"Button",L"Wodka",WS_VISIBLE|WS_CHILD|WS_BORDER,20,66,80,40,hWnd,(HMENU)PROMILE_WODKA,NULL,NULL);
    CreateWindowW(L"Button",L"Piffko",WS_VISIBLE|WS_CHILD|WS_BORDER,20,112,80,40,hWnd,(HMENU)ZMIEN_TYTUL,NULL,NULL);
    CreateWindowW(L"Button",L"Whiskey",WS_VISIBLE|WS_CHILD|WS_BORDER,20,158,80,40,hWnd,(HMENU)ZMIEN_TYTUL,NULL,NULL);
}
