///////////////////////////////////////////////////////////////////
//     DDDDDDD  RRRRRRRR IIIIIIII VV    VV EEEEEEEE RRRRRRRR     //
//     DDDDDDDD RRRRRRRR    II    VV    VV EEEEEEEE RRRRRRRR     //
//     DD    DD RR    RR    II    VV    VV EE       RR    RR     //
//     DD    DD RR   RR     II    VV    VV EE       RR   RR      //
//     DD    DD RR  RR      II    VV    VV EE       RR  RR       //
//     DD    DD RRRR        II    VV    VV EEEEEE   RRRR         //
//     DD    DD RR  RR      II    VV    VV EEEEEE   RR  RR       //
//     DD    DD RR   RR     II    VV    VV EE       RR   RR      //
//     DD    DD RR    RR    II    VV    VV EE       RR    RR     //
//     DD    DD RR    RR    II    VV    VV EE       RR    RR     //
//     DDDDDDDD RR    RR    II     VV  VV  EEEEEEEE RR    RR     //
//     DDDDDDD  RR    RR IIIIIIII    VV    EEEEEEEE RR    RR     //
///////////////////////////////////////////////////////////////////
//   jd303484   //
//////////////////


////////////////
// Biblioteki //
////////////////
#include<iostream>
#include<windows.h> //! kursor; okno konsoli
#include<conio.h> //! getch; _kbhit
#include<cstdlib> //! srand; rand
#include<ctime> //! time
using namespace std;

//////////////////////////////
// Definicja klawiszy (224) //
//////////////////////////////
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESCAPE 27
#define ENTER 13

///////////////////////
// Definicja stalych //
///////////////////////
#define HEIGHT 13
#define WIDTH 80

///////////////////////
// obiekty windows.h //
///////////////////////
CONSOLE_FONT_INFOEX font{ sizeof(CONSOLE_FONT_INFOEX) };
CONSOLE_CURSOR_INFO info;
COORD Position;

HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

HWND console = GetConsoleWindow();
RECT r;

////////////////////////////////
// zmienne i tablice globalne //
////////////////////////////////
bool gameOver{};
char level[HEIGHT][WIDTH]{};
short positionX;
short positionY;
short pzT = 2;
short color{};
short kr{};
short i{};
int random{};
unsigned long long wynik;

////////////////////////////////////
// funkcje sterujace (deklaracja) //
////////////////////////////////////
void menu();
void rysowanieM();
void klawiszM();
void opcje1();
void rysowanieO1();
void klawiszO1();
void opcje2();
void rysowanieO2();
void klawiszO2();
void gra();
void rysowanieG();
void klawiszG();
void przeszkody();
void sterD();
void sterSleep();
void kursor();
void kolor(short color);
void planszaDek();
void planszaRys();

//////////
// MAIN //
//////////
int main()
{
    // latwa podmiana funkcji
    system("cls");

    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX & ~WS_VSCROLL & ~WS_HSCROLL);
    font.FontWeight = 400;
    font.dwFontSize.X = 8;
    font.dwFontSize.Y = 16;
    SetCurrentConsoleFontEx(consoleHandle, false, &font);
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 400, TRUE);


    menu();
    system("cls");
    return wynik;
}

///////////////////////////////////
// funkcje sterujace (definicja) //
///////////////////////////////////
void menu() //! wszystko zw z menu
{
    i = 0;
    kr = 0;
    system("cls");
    system("color 4f");
    while (1)
    {
        rysowanieM();
        klawiszM();
        kursor();
        if (kr == ENTER) break;
        Sleep(25);
    }
    if (i == 0) gra();
    else if (i == 1) opcje1();
}
void rysowanieM() //! przeniesienie rysowania menu
{
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(consoleHandle, Position);
    SetConsoleTextAttribute(consoleHandle, 79);
    cout << "\t\t                                                            " << endl;
    cout << "\t\t    DDDDDDD  RRRRRRRR IIIIIIII VV    VV EEEEEEEE RRRRRRRR   " << endl;
    cout << "\t\t    DDDDDDDD RRRRRRRR    II    VV    VV EEEEEEEE RRRRRRRR   " << endl;
    cout << "\t\t    DD    DD RR    RR    II    VV    VV EE       RR    RR   " << endl;
    cout << "\t\t    DD    DD RR   RR     II    VV    VV EE       RR   RR    " << endl;
    cout << "\t\t    DD    DD RR  RR      II    VV    VV EE       RR  RR     " << endl;
    cout << "\t\t    DD    DD RRRR        II    VV    VV EEEEEE   RRRR       " << endl;
    cout << "\t\t    DD    DD RR  RR      II    VV    VV EEEEEE   RR  RR     " << endl;
    cout << "\t\t    DD    DD RR   RR     II    VV    VV EE       RR   RR    " << endl;
    cout << "\t\t    DD    DD RR    RR    II    VV    VV EE       RR    RR   " << endl;
    cout << "\t\t    DD    DD RR    RR    II    VV    VV EE       RR    RR   " << endl;
    cout << "\t\t    DDDDDDDD RR    RR    II     VV  VV  EEEEEEEE RR    RR   " << endl;
    cout << "\t\t    DDDDDDD  RR    RR IIIIIIII    VV    EEEEEEEE RR    RR   " << endl;
    cout << "\t\t                                                            " << endl;
    SetConsoleTextAttribute(consoleHandle, 244);
    cout << "\t\t                                                             " << endl;
    cout << "\t\t                          ";
    if (i == 0) SetConsoleTextAttribute(consoleHandle, 79);
    cout << " NOWA GRA ";
    SetConsoleTextAttribute(consoleHandle, 244);
    cout << "                         " << endl;
    cout << "\t\t                          ";
    if (i == 1) SetConsoleTextAttribute(consoleHandle, 79);
    cout << " OPCJE    ";
    SetConsoleTextAttribute(consoleHandle, 244);
    cout << "                         " << endl;
    cout << "\t\t                          ";
    if (i == 2) SetConsoleTextAttribute(consoleHandle, 79);
    cout << " WYJSCIE  ";
    SetConsoleTextAttribute(consoleHandle, 244);
    cout << "                         " << endl;
    cout << "\t\t                                                             " << endl;
    cout << "\t\t         STEROWANIE - GORA/DOL     ZATWIERDZ - ENTER         " << endl;
    cout << "\t\t                                                             " << endl;
    SetConsoleTextAttribute(consoleHandle, 15);
}
void klawiszM() //! Wykrywanie klawiszy dla menu
{

    if (_kbhit())
    {
        switch (kr = _getch())
        {
        case KEY_DOWN:
        {
            if (i < 2)i++;
            break;
        }
        case KEY_UP:
        {
            if (i > 0)i--;
            break;
        }
        case ENTER:
        {
            break;
        }
        default: break;
        }
    }
}



void opcje1() //! wszystko zw z menu opcji (Poziom trudnosci)
{
    kr = 0;
    system("cls");
    while (1)
    {
        rysowanieO1();
        klawiszO1();
        kursor();
        Sleep(25);
        if (kr == ENTER || kr == KEY_RIGHT) break;
    }
    if (kr == ENTER) menu();
    else if (kr == KEY_RIGHT) opcje2();
}
void rysowanieO1() //! przeniesienie rysowania opcji
{
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(consoleHandle, Position);
    SetConsoleTextAttribute(consoleHandle, 4);
    cout << "\n WYBIERZ POZIOM TRUDNOSCI";
    SetConsoleTextAttribute(consoleHandle, 15);
    cout << " | ";
    SetConsoleTextAttribute(consoleHandle, 8);
    cout << "WYBIERZ STYL" << endl;
    SetConsoleTextAttribute(consoleHandle, 4);
    if (pzT == 1)
    {
        SetConsoleTextAttribute(consoleHandle, 15),
            cout << "   [X] - LATWY" << endl;
    }
    else cout << "   [ ] - LATWY" << endl;
    SetConsoleTextAttribute(consoleHandle, 4);
    if (pzT == 2)
    {
        SetConsoleTextAttribute(consoleHandle, 15);
        cout << "   [X] - SREDNI" << endl;
    }
    else cout << "   [ ] - SREDNI" << endl;
    SetConsoleTextAttribute(consoleHandle, 4);
    if (pzT == 3)
    {
        SetConsoleTextAttribute(consoleHandle, 15);
        cout << "   [X] - TRUDNY" << endl;
    }
    else cout << "   [ ] - TRUDNY" << endl;
    SetConsoleTextAttribute(consoleHandle, 15);
}
void klawiszO1() //! Wykrywanie klawiszy dla menu opcji
{
    if (_kbhit())
    {
        switch (kr = _getch())
        {
        case KEY_DOWN:
        {
            if (pzT < 3)pzT++;
            break;
        }
        case KEY_UP:
        {
            if (pzT > 1)pzT--;
            break;
        }
        default: break;
        }
    }
}




void opcje2() //! wszystko zw z menu opcji (Kolor gry)
{
    kr = 0;
    system("cls");
    while (1)
    {
        rysowanieO2();
        klawiszO2();
        if (kr == ENTER || kr == KEY_LEFT) break;
        kursor();
        Sleep(25);
    }
    if (kr == ENTER) menu();
    else if (kr == KEY_LEFT) opcje1();
}
void rysowanieO2() //! przeniesienie rysowania opcji
{
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(consoleHandle, Position);
    SetConsoleTextAttribute(consoleHandle, 8);
    cout << "\n WYBIERZ POZIOM TRUDNOSCI";
    SetConsoleTextAttribute(consoleHandle, 15);
    cout << " | ";
    kolor(color);
    cout << "WYBIERZ STYL" << endl;
    if (color == 0)
    {
        kolor(color);
        cout << "   [X] - BIALY" << endl;
    }
    else {
        SetConsoleTextAttribute(consoleHandle, 8);
        cout << "   [ ] - BIALY" << endl;
    }
    if (color == 1)
    {
        kolor(color);
        cout << "   [X] - CZERWONY" << endl;
    }

    else {
        SetConsoleTextAttribute(consoleHandle, 8);
        cout << "   [ ] - CZERWONY" << endl;
    }
    if (color == 2)
    {
        kolor(color);
        cout << "   [X] - ZIELONY" << endl;
    }

    else {
        SetConsoleTextAttribute(consoleHandle, 8);
        cout << "   [ ] - ZIELONY" << endl;
    }
    if (color == 3)
    {
        kolor(color);
        cout << "   [X] - NIEBIESKI" << endl;
    }

    else {
        SetConsoleTextAttribute(consoleHandle, 8);
        cout << "   [ ] - NIEBIESKI" << endl;
    }
    if (color == 4)
    {
        kolor(color);
        cout << "   [X] - FIOLETOWY" << endl;
    }

    else {
        SetConsoleTextAttribute(consoleHandle, 8);
        cout << "   [ ] - FIOLETOWY" << endl;
    }
}
void klawiszO2() //! Wykrywanie klawiszy dla menu opcji
{
    if (_kbhit())
    {
        switch (kr = _getch())
        {
        case KEY_DOWN:
        {
            if (color < 4)color++;
            break;
        }
        case KEY_UP:
        {
            if (color > 0)color--;
            break;
        }
        default: break;
        }
    }
}



void gra() //! tutaj wszystko zw z gra
{
    positionX = 1;
    positionY = 7;
    wynik = 0;
    kr = 0;
    gameOver = 0;

    system("cls");
    kolor(color);

    kursor();
    planszaDek();
    planszaRys();
    srand(time(NULL));

    while (!gameOver) //! petla gry
    {
        klawiszG();
        przeszkody();
        level[positionY][positionX] = 0xAF; //! Aktualizacja gracza na mapie

        wynik += pzT * 10 + positionX / 5;
        kursor();
        sterD();
        rysowanieG();

        sterSleep();

        if (kr == ESCAPE) break; //! wyjscie ESC
    }
    if (kr != ESCAPE)
    {
        cout << endl << "\n\t | GAME OVER! | ESC, aby wyjsc do menu |";
        while (_getch() != ESCAPE) Sleep(50);
    }
    system("cls");
    menu();
}
void rysowanieG() //! przesuniecie rysowania gry (aktualizacja tylko wierszy potrzebnych)
{
    Position.X = 9;
    Position.Y = 1;
    SetConsoleCursorPosition(consoleHandle, Position);
    cout << "WYNIK: " << wynik << " | POZIOM TRUDNOSCI: " << pzT << "\n";
    for (int i = 1; i < HEIGHT - 1; i += 2)
    {
        Position.X = 9;
        Position.Y = i + 2;
        SetConsoleCursorPosition(consoleHandle, Position);
        for (int j = 1; j < WIDTH - 1; j++)
        {
            cout << level[i][j];
        }
        cout << endl;
    }
}
void klawiszG() //! Wykrywanie klawiszy dla gry
{
    //! Wchodzi po wcisnieciu klawisza
    if (_kbhit())
    {
        //! Rozpoznanie z listy klawiszy
        switch (kr = _getch())
        {
        case KEY_UP:
        {
            level[positionY][positionX] = ' ';
            if (positionY > 3)positionY -= 2;
            break;
        }
        case KEY_DOWN:
        {
            level[positionY][positionX] = ' ';
            if (positionY < 9)positionY += 2;
            break;
        }
        case KEY_LEFT:
        {
            level[positionY][positionX] = ' ';
            if (positionX > 1)positionX -= 1;
            break;
        }
        case KEY_RIGHT:
        {
            level[positionY][positionX] = ' ';
            if (positionX < WIDTH - 3)positionX += 1;
            break;
        }
        case 112: //! "P"
        {
            system("cls");
            cout << "\n\t PAUZA - KLIKNIJ DOWOLNY PRZYCISK ABY KONTYNUOWAC";
            _getch();
            kolor(color);
            system("cls");
            planszaRys();
            break;
        }
        default: break;
        }
    }
}



void przeszkody() //! wszystko zw z przeszkodami + warunek przegranej
{
    //! Aktualizacja pozycji przeszkod
    for (int i = 3; i < 10; i += 2)
    {
        for (int j = 1; j < WIDTH - 1; j++)
        {
            if (level[i][j] == 'X')
            {
                if ((i == positionY && j == positionX + 1) || (i == positionY && j == positionX)) gameOver = 1;
                level[i][j] = ' ';
                if (j > 1) level[i][j - 1] = 'X';
            }
        }
    }

    //! Tworzenie przeszkod
    random = rand() % 20 + 1;
    if (random == 3 || random == 5 || random == 7 || random == 9) level[random][WIDTH - 2] = 'X';
}



void sterD() //! sterowanie wierszami 1 i 11 z tzw "drzewkami"
{
    static bool tlo{};
    for (int i = 1; i < 12; i += 10)
    {
        for (int j = 1; j < WIDTH - 1; j++)
        {
            if (j % 2 == tlo && (i == 1 || i == 11)) level[i][j] = 0x05;
            else level[i][j] = ' ';
        }
    }
    tlo = !tlo;
}



void sterSleep() //! Sterowanie Sleep
{
    //! warunki w zaleznosci od wyniku (TYLKO 3 ETAPY)
    if (wynik < 10000)Sleep(100 - pzT * 10);
    else if (wynik > 10000 && wynik < 25000)Sleep(100 - pzT * 20);
    else Sleep(100 - pzT * 30);
}



void kursor() //! znikanie kursora konsoli (OSTROZNIE!)
{
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}



void kolor(short color)
{
    if (color == 0) SetConsoleTextAttribute(consoleHandle, 15);
    else if (color == 1) SetConsoleTextAttribute(consoleHandle, 4);
    else if (color == 2) SetConsoleTextAttribute(consoleHandle, 10);
    else if (color == 3) SetConsoleTextAttribute(consoleHandle, 1);
    else if (color == 4) SetConsoleTextAttribute(consoleHandle, 5);
}



void planszaDek() //! wykreowanie terenu planszy (a przynajmniej granic)
{
    for (int i{}; i < HEIGHT; i++)
    {
        for (int j{}; j < WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT - 1) level[i][j] = 0xCD;
            else if (j == 0 || j == WIDTH - 1) level[i][j] = 0xBA;
            else if (i == 6) level[i][j] = '=';
            else if (i == 2 || i == 10) level[i][j] = 0xDB;
            else if (i % 2 == 0) level[i][j] = '-';
            else level[i][j] = ' ';
        }
    }
    level[0][0] = 0xC9;
    level[0][WIDTH - 1] = 0xBB;
    level[HEIGHT - 1][0] = 0xC8;
    level[HEIGHT - 1][WIDTH - 1] = 0xBC;
}



void planszaRys() //! rysowanie planszy
{
    Position.X = 0;
    Position.Y = 1;
    SetConsoleCursorPosition(consoleHandle, Position);
    cout << "\t WYNIK: " << wynik << " | POZIOM TRUDNOSCI: " << pzT << "\n";
    for (int i{}; i < HEIGHT; i++)
    {
        cout << "\t";
        for (int j{}; j < WIDTH; j++)
        {
            cout << level[i][j];
        }
        cout << endl;
    }
    cout << "\t | STRZALKI - RUCH | ESC - WYJSCIE | P - PAUZA |";
}
