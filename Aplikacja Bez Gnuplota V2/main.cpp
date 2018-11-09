#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <commctrl.h>
#include <iostream>
#include <fstream>
#include <algorithm>

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
#define DODAJ_INNE_PIWO 12
#define DODAJ_INNE 13


using namespace std;

LRESULT CALLBACK ProceduraOkna(HWND, UINT, WPARAM, LPARAM);

void DodajMenu(HWND);
void DodajKontrole(HWND);
void WczytajObrazy();
void ComboBoxy(HWND);
double Zapisz(int,double);
void Skrypty();
void StworzKlaseDialog(HINSTANCE);
void StworzDialog(HWND);

char gramy_alk[20] = {0};
double gramy_alk_f = 0;


HWND hGrAlk,hGraf,hTekst,hCzas,hWaga,hWynik,hObjetosc,hZawartosc;
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

    StworzKlaseDialog(hInst);

    CreateWindowW(L"MojaKlasaOkna", L"Alkomat", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 20, 20, 800, 800, NULL, NULL, NULL, NULL);

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
        case DODAJ_INNE:
            StworzDialog(hWnd);
            break;
        case DODAJ_INNE_PIWO:
            break;
        case DANE_MENU_ZAMKNIJ:
            DestroyWindow(hWnd);
            break;
        case DANE_MENU_DODAJ:
            MessageBeep(MB_ICONINFORMATION);
            break;
        case GRAMY_WODKA:
            gramy_alk_f += 15.60;
            sprintf(gramy_alk,"%.2f[g]",gramy_alk_f);
            SetWindowText(hGrAlk,gramy_alk);
            break;
        case GRAMY_PIWO_500:
            gramy_alk_f += 17.55;
            sprintf(gramy_alk,"%.2f[g]",gramy_alk_f);
            SetWindowText(hGrAlk,gramy_alk);
            break;
        case GRAMY_PIWO_330:
            gramy_alk_f += 11.58;
            sprintf(gramy_alk,"%.2f[g]",gramy_alk_f);
            SetWindowText(hGrAlk,gramy_alk);
            break;
        case GRAMY_WINO:
            gramy_alk_f += 16.38;
            sprintf(gramy_alk,"%.2f[g]",gramy_alk_f);
            SetWindowText(hGrAlk,gramy_alk);
            break;
        case WYCZYSC_B:

            gramy_alk_f = 0;
            sprintf(gramy_alk,"%.2f[g]",gramy_alk_f);
            SetWindowText(hGrAlk,gramy_alk);
            SetWindowText(hWynik,"");

            hGrafObr = (HBITMAP)LoadImageW(NULL,L"blank.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);


            SendMessageW(hGraf,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hGrafObr);

            break;
        case OBLICZ:
            int waga,godziny;
            char ile_promili_ch[20],waga_ch[5],godz_ch[5];
            double ile_pormili,wynik;

            GetWindowText(hWaga,waga_ch,5);
            GetWindowText(hCzas,godz_ch,5);

            godziny = atoi(godz_ch);
            waga = atoi(waga_ch);

            double temp = 0.6 * waga;
            wynik = gramy_alk_f/temp;

            ile_pormili = Zapisz(godziny,wynik);
            sprintf(ile_promili_ch,"Po czasie %dh, we krwi pozostanie %.3f promili",godziny,ile_pormili);
            SetWindowText(hWynik,ile_promili_ch);
            Skrypty();

            if(hGrafObr = (HBITMAP)LoadImageW(NULL,L"PNGtoBMP\\graf.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE))
                SendMessageW(hGraf,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hGrafObr);
            break;
        }
        break;
    case WM_CREATE: //Tutaj tworze elementy okienka
        //StworzDialog(hWnd);
        WczytajObrazy();
        DodajMenu(hWnd);
        DodajKontrole(hWnd);
        ComboBoxy(hWnd);
        break;
    case WM_DESTROY:
        remove("PNGtoBMP//graf.bmp");
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
    CreateWindowW(L"Button",L"INNE",WS_VISIBLE|WS_CHILD|WS_BORDER,20,250,140,40,hWnd,(HMENU)DODAJ_INNE,NULL,NULL);


    CreateWindowW(L"Static",NULL,WS_VISIBLE |WS_CHILD | SS_CENTER|SS_ETCHEDHORZ,170,0,10,2000,hWnd,NULL,NULL,NULL); //SEPARATOR

    CreateWindowW(L"Static",L"Spozytego alkoholu:",WS_VISIBLE |WS_CHILD|SS_CENTER,20,326,140,20,hWnd,NULL,NULL,NULL);
    hGrAlk = CreateWindowW(L"Static",L"0[g]",WS_VISIBLE |WS_CHILD|SS_CENTER|WS_BORDER,20,352,140,40,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Button",L"WYCZYSC",WS_VISIBLE|WS_CHILD|WS_BORDER,20,398,140,40,hWnd,(HMENU)WYCZYSC_B,NULL,NULL);

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
    hWndComboBox = CreateWindowW(L"Combobox",L"",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE ,20,296 , 100, 100, hWnd, NULL, NULL,NULL);
    SendMessage( hWndComboBox, CB_ADDSTRING, 0,( LPARAM ) "Lech" );
    SendMessage( hWndComboBox, CB_ADDSTRING, 1,( LPARAM ) "¯ubr" );
    SendMessage( hWndComboBox, CB_SETCURSEL, 0,0);
    CreateWindowW(L"Button",L"+",WS_VISIBLE|WS_CHILD|WS_BORDER,124,296,23,23,hWnd,(HMENU)DODAJ_INNE_PIWO,NULL,NULL);


}

void WczytajObrazy()
{
    hGrafObr = (HBITMAP)LoadImageW(NULL,L"blank.bmp",IMAGE_BITMAP,400,400,LR_LOADFROMFILE);
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
}

LRESULT CALLBACK DialogProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch(msg)
    {
    case WM_COMMAND:
        switch(wp)
        {
        case 1:
            {
            char objetosc[10];
            char zawartosc[10];
            double obj_f,zaw_f,temp2;

            GetWindowText(hObjetosc,objetosc,10);
            GetWindowText(hZawartosc,zawartosc,10);

            for(int i =0;i<10;i++)
            {
                if(zawartosc[i]==',')
                    zawartosc[i]='.';
            }


            obj_f = atof(objetosc);
            zaw_f = atof(zawartosc);


            temp2 = obj_f*zaw_f;
            double temp3 = temp2*0.0078;


            gramy_alk_f += temp3;


            DestroyWindow(hWnd);

            sprintf(gramy_alk,"%.2f[g]",gramy_alk_f);
            SetWindowText(hGrAlk,gramy_alk);


            }
            break;
        case 2:
            DestroyWindow(hWnd);
            break;
        }
//    case WM_CLOSE:
//        DestroyWindow(hWnd);
//        break;
    default:
        return DefWindowProc(hWnd,msg,wp,lp);
    }
}

void StworzKlaseDialog(HINSTANCE hInst)
{
    WNDCLASSW dialog = {0};
    dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    dialog.hCursor = LoadCursor(NULL, IDC_ARROW);
    dialog.hInstance = hInst;
    dialog.lpszClassName = L"KlasaDialog";
    dialog.lpfnWndProc = DialogProcedure;

    RegisterClassW(&dialog);
}

void StworzDialog(HWND hWnd)
{
    HWND hDlg = CreateWindowW(L"KlasaDialog",L"Inne",WS_VISIBLE|WS_OVERLAPPEDWINDOW,100,200,400,200,hWnd,NULL,NULL,NULL);

    CreateWindowW(L"Static",L"Objetosc[ml]:",WS_VISIBLE|WS_CHILD,10,10,120,20,hDlg,NULL,NULL,NULL);
    hObjetosc = CreateWindowW(L"Edit",L"",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_NUMBER,10,30,140,40,hDlg,NULL,NULL,NULL);
    CreateWindowW(L"Static",L"Zawartosc alk.[%]:",WS_VISIBLE|WS_CHILD,10,80,120,20,hDlg,NULL,NULL,NULL);
    hZawartosc = CreateWindowW(L"Edit",L"",WS_VISIBLE|WS_CHILD|WS_BORDER,10,100,140,40,hDlg,NULL,NULL,NULL);

    CreateWindowW(L"Button",L"Dodaj",WS_VISIBLE|WS_CHILD,200,30,140,40,hDlg,(HMENU)1,NULL,NULL);
    CreateWindowW(L"Button",L"Wyjdz",WS_VISIBLE|WS_CHILD,200,100,140,40,hDlg,(HMENU)2,NULL,NULL);

}


