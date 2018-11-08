#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <commctrl.h>
#include <iostream>
#include <fstream>
//#include "gnuplot.h"

#define DANE_MENU_DODAJ 1
#define GRAMY_PIWO_500 2
#define DANE_MENU_ZAMKNIJ 3
#define WYCZYSC_B 4
#define GRAMY_WODKA 5
#define PROMILE_PIWO 6
#define PROMILE_WHISKEY 7
#define GRAMY_PIWO_330 8
#define GRAMY_WINO 9
#define OBLICZ 10
#define WCZYTAJ 11

using namespace std;

LRESULT CALLBACK ProceduraOkna(HWND, UINT, WPARAM, LPARAM);

void DodajMenu(HWND);
void DodajKontrole(HWND);
void WczytajObrazy();
void ComboBoxy(HWND);
double Zapisz(int,double);
void Skrypty();

char gramy_alk[20] = {0};
int gramy_alk_int = 0;


HWND hGrAlk,hGraf,hTekst,hCzas,hWaga,hWynik;
HMENU hMenu;
HBITMAP hGrafObr;
HWND hWndComboBox;

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
        case GRAMY_WODKA:
            gramy_alk_int += 16;
            sprintf(gramy_alk,"%d[g]",gramy_alk_int);
            SetWindowText(hGrAlk,gramy_alk);
            break;
        case GRAMY_PIWO_500:
            gramy_alk_int += 18;
            sprintf(gramy_alk,"%d[g]",gramy_alk_int);
            SetWindowText(hGrAlk,gramy_alk);
            break;
        case GRAMY_PIWO_330:
            gramy_alk_int += 12;
            sprintf(gramy_alk,"%d[g]",gramy_alk_int);
            SetWindowText(hGrAlk,gramy_alk);
            break;
        case GRAMY_WINO:
            gramy_alk_int += 17;
            sprintf(gramy_alk,"%d[g]",gramy_alk_int);
            SetWindowText(hGrAlk,gramy_alk);
            break;
        case WYCZYSC_B:

            gramy_alk_int = 0;
            sprintf(gramy_alk,"%d[g]",gramy_alk_int);
            SetWindowText(hGrAlk,gramy_alk);
            SetWindowText(hWynik,"");

            hGrafObr = (HBITMAP)LoadImageW(NULL,L"blank.bmp",IMAGE_BITMAP,350,250,LR_LOADFROMFILE);


            SendMessageW(hGraf,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hGrafObr);

            break;
        case OBLICZ:
            {

            int waga,godziny;
            char ile_promili_ch[20],waga_ch[5],godz_ch[5];
            double ile_pormili,wynik;

            GetWindowText(hWaga,waga_ch,5);
            GetWindowText(hCzas,godz_ch,5);

            godziny = atoi(godz_ch);
            waga = atoi(waga_ch);

            double temp = 0.6 * waga;
            wynik = gramy_alk_int/temp;


//            for(int i = godziny;i>0;i--)
//            {
//                wynik -= 0.12;
//                if(wynik<=0)
//                {
//                    wynik = 0;
//                    break;
//                }
//            }

            ile_pormili = Zapisz(godziny,wynik);
            sprintf(ile_promili_ch,"Po czasie %dh, we krwi pozostanie %.3f promili",godziny,ile_pormili);
            SetWindowText(hWynik,ile_promili_ch);
            Skrypty();

            hGrafObr = (HBITMAP)LoadImageW(NULL,L"PNGtoBMP\\graf.bmp",IMAGE_BITMAP,350,250,LR_LOADFROMFILE);
            SendMessageW(hGraf,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hGrafObr);

            break;

            }
            break;



        }
        break;
    case WM_CREATE: //Tutaj tworze elementy okienka
        WczytajObrazy();
        DodajMenu(hWnd);
        DodajKontrole(hWnd);
        //ComboBoxy(hWnd);
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
    CreateWindowW(L"Static",L"Alkohole:",WS_VISIBLE |WS_CHILD | SS_CENTER,20,20,120,40,hWnd,NULL,NULL,NULL);

    CreateWindowW(L"Button",L"50ml Wodki 40%",WS_VISIBLE|WS_CHILD|WS_BORDER,20,66,140,40,hWnd,(HMENU)GRAMY_WODKA,NULL,NULL);
    CreateWindowW(L"Button",L"500ml Piwa 4.5%",WS_VISIBLE|WS_CHILD|WS_BORDER,20,112,140,40,hWnd,(HMENU)GRAMY_PIWO_500,NULL,NULL);
    CreateWindowW(L"Button",L"330ml Piwa 4.5%",WS_VISIBLE|WS_CHILD|WS_BORDER,20,158,140,40,hWnd,(HMENU)GRAMY_PIWO_330,NULL,NULL);
    CreateWindowW(L"Button",L"175ml Wina 12%",WS_VISIBLE|WS_CHILD|WS_BORDER,20,204,140,40,hWnd,(HMENU)GRAMY_WINO,NULL,NULL);

    CreateWindowW(L"Static",NULL,WS_VISIBLE |WS_CHILD | SS_CENTER|SS_ETCHEDHORZ,170,0,10,600,hWnd,NULL,NULL,NULL);

    CreateWindowW(L"Static",L"Spozytego alkoholu:",WS_VISIBLE |WS_CHILD|SS_CENTER,20,280,140,20,hWnd,NULL,NULL,NULL);
    hGrAlk = CreateWindowW(L"Static",L"0[g]",WS_VISIBLE |WS_CHILD|SS_CENTER|WS_BORDER,20,306,140,40,hWnd,NULL,NULL,NULL);

    CreateWindowW(L"Button",L"WYCZYSC",WS_VISIBLE|WS_CHILD|WS_BORDER,20,352,140,40,hWnd,(HMENU)WYCZYSC_B,NULL,NULL);

    CreateWindowW(L"Static",L"Ile godzin minelo od picia:",WS_VISIBLE|WS_CHILD|ES_NUMBER,180,20,140,40,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static",L"Twoja waga w kg:",WS_VISIBLE|WS_CHILD|ES_NUMBER,180,70,140,40,hWnd,NULL,NULL,NULL);
    hCzas = CreateWindowW(L"Edit",L"",WS_VISIBLE|WS_CHILD|ES_NUMBER|WS_BORDER,340,20,80,40,hWnd,NULL,NULL,NULL);
    hWaga = CreateWindowW(L"Edit",L"",WS_VISIBLE|WS_CHILD|ES_NUMBER|WS_BORDER,340,70,80,40,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Button",L"OBLICZ",WS_VISIBLE|WS_CHILD|WS_BORDER,450,45,80,40,hWnd,(HMENU)OBLICZ,NULL,NULL);
    hWynik = CreateWindowW(L"Static",L"",WS_VISIBLE | WS_CHILD | WS_BORDER,180,120,350,40,hWnd,NULL,NULL,NULL);



    hGraf = CreateWindowW(L"Static",NULL,WS_VISIBLE|WS_CHILD|SS_BITMAP, 180,170,100,100,hWnd,NULL,NULL,NULL);
    SendMessageW(hGraf,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hGrafObr);
}

void ComboBoxy(HWND hWnd)
{
    hWndComboBox = CreateWindowW(L"Combobox",L"",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE ,400,400 , 100, 100, hWnd, NULL, NULL,NULL);
    SendMessage( hWndComboBox, CB_ADDSTRING, 0,( LPARAM ) "Lech" );
}

void WczytajObrazy()
{
    hGrafObr = (HBITMAP)LoadImageW(NULL,L"blank.bmp",IMAGE_BITMAP,350,250,LR_LOADFROMFILE);
}

double Zapisz(int godziny,double wynik)
{
    fstream plik;
    plik.open("dane.dat",ios::out);
    for(int i = 0;i<=godziny;i++)
    {
        wynik -= 0.12;
        plik<<i<<"\t"<<wynik<<endl;
        if(wynik<=0)
        {
        wynik = 0;
        plik<<i<<"\t"<<wynik<<endl;
        break;
        }
    }
    plik.close();
    return wynik;
}

void Skrypty()
{
    system("skrypt.bat");
    system("skrypt2.bat");
}



