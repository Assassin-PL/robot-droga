// robot-droga.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "stdafx.h"

using namespace std;

#define segSize 5
#define segIl 6
const int MAX_ROWS = 8;
const int MAX_COLUMS = 4;

int algorytm_losujacy(int beg, int end);
void losuj_plansze(int wyloswane_segmenty[MAX_ROWS][MAX_COLUMS]);
void poka_plansze(int wyloswane_segmenty[MAX_ROWS][MAX_COLUMS]);
void inicjalizuj_plansze(bool plansza[8 * segSize][4 * segSize], int wylosowane_segmenty[MAX_ROWS][MAX_COLUMS], bool segmenty[segIl][segSize][segSize]);
void rob_mikrotablice(bool plansza[8 * segSize][4 * segSize], int numer_segmentu, bool segmenty[segIl][segSize][segSize], int numer_wiersza, int numer_kolumny);
void prezentuj_plansze(bool plansza[8 * segSize][4 * segSize]);

int main()
{
    bool rzad1[segIl][segSize] = { {1,1,0,1,1},{1,1,0,0,1},{0,0,0,0,0},{1,1,0,0,0},{0,0,0,1,1},{1,1,0,1,1} };
    bool rzad2[segIl][segSize] = { {1,0,0,1,1},{0,1,1,0,1},{0,0,1,0,0},{1,0,0,1,0},{1,0,0,0,1},{1,1,0,1,1} }; // na czarno 1, na biało 0, jak dla mnie bardziej intuicyjne
    bool rzad3[segIl][segSize] = { {0,0,1,0,0},{0,0,0,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,0} };
    bool rzad4[segIl][segSize] = { {1,0,0,0,1},{1,0,0,0,1},{1,0,1,1,1},{0,1,0,0,1},{0,0,1,0,0},{1,1,0,1,1} };
    bool rzad5[segIl][segSize] = { {1,1,0,1,1},{1,1,0,0,1},{1,0,0,0,0},{1,0,0,1,1},{0,0,0,0,1},{1,1,0,1,1} };
    bool plansza[8 * segSize][4 * segSize];
    bool segmenty[segIl][segSize][segSize] = {
        { {1,1,0,1,1}, {1,0,0,1,1}, {0,0,1,0,0}, {1,0,0,0,1}, {1,1,0,1,1}
        },
        { {1,1,0,0,1}, {0,1,1,0,1}, {0,0,0,0,0}, {1,0,0,0,1}, {1,1,0,0,1}
        },
        { {0,0,0,0,0}, {0,0,1,0,0}, {0,0,1,1,0}, {1,0,1,1,1}, {1,0,0,0,0}
        },
        { {1,1,0,0,0}, {1,0,0,1,0}, {0,0,1,0,0}, {0,1,0,0,1}, {1,0,0,1,1}
        },
        { {0,0,0,1,1}, {1,0,0,0,1}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,0,0,1}
        },
        { {1,1,0,1,1}, {1,1,0,1,1}, {0,0,0,0,0}, {1,1,0,1,1}, {1,1,0,1,1}
        }
    };
    //wylosować 8x4 sekwencji, na podstawie ich indeksu budujemy wielką planszę od góry do dołu
    int wyloswane_segmenty[MAX_ROWS][MAX_COLUMS];
    losuj_plansze(wyloswane_segmenty);
    poka_plansze(wyloswane_segmenty);
    cout << endl;
    inicjalizuj_plansze(plansza, wyloswane_segmenty, segmenty);
    prezentuj_plansze(plansza);
    return 0;
}

int algorytm_losujacy(int beg, int end)
{
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(beg, end); // define the range

    return distr(gen);
}

void losuj_plansze(int wyloswane_segmenty[MAX_ROWS][MAX_COLUMS])
{
    int numer_segmentu = 0;
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMS; j++)
        {
            numer_segmentu = algorytm_losujacy(0, 5);
            wyloswane_segmenty[i][j] = numer_segmentu;
        }
    }
}

void poka_plansze(int wyloswane_segmenty[MAX_ROWS][MAX_COLUMS])
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        cout << endl;
        for (int j = 0; j < MAX_COLUMS; j++)
        {
            cout << wyloswane_segmenty[i][j] <<" ";
        }
    }
}
void inicjalizuj_plansze(bool plansza[8 * segSize][4 * segSize],int wylosowane_segmenty[MAX_ROWS][MAX_COLUMS], bool segmenty[segIl][segSize][segSize])
{
    int numer_segmentu = 0;
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMS; j++)
        {
            numer_segmentu = wylosowane_segmenty[i][j];
            rob_mikrotablice(plansza, numer_segmentu, segmenty, i, j);
        }
    }
}
void rob_mikrotablice(bool plansza[8 * segSize][4 * segSize], int numer_segmentu, bool segmenty[segIl][segSize][segSize], int numer_wiersza, int numer_kolumny)
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < segSize; i++)
    {
        for (int j = 0; j < segSize; j++)
        {
            x = segSize * numer_wiersza + i;
            y = segSize * numer_kolumny + j;
            plansza[x][y] = segmenty[numer_segmentu][i][j];
        }
    }
}

void prezentuj_plansze(bool plansza[8 * segSize][4 * segSize])
{
    for (int i = 0; i < (8 * segSize); i++)
    {
        cout << endl;
        for (int j = 0; j < (4 * segSize); j++)
        {
            if (plansza[i][j])
            {
                cout << "X";
            }
            else
            {
                cout << "O";
            }
        }
    }
}