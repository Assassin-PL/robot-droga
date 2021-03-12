// robot-droga.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "stdafx.h"

using namespace std;

#define segSize 5
#define segIl 6
const int MAX_ROWS = 8;
const int MAX_COLUMS = 4;
const int PLANSZA_WIDTH = MAX_COLUMS * segSize;
const int PLANSZA_HEIGHT = MAX_ROWS * segSize;

int algorytm_losujacy(int beg, int end);
void losuj_plansze(int wyloswane_segmenty[MAX_ROWS][MAX_COLUMS]);
void poka_plansze(int wyloswane_segmenty[MAX_ROWS][MAX_COLUMS]);
void inicjalizuj_plansze(int plansza[8 * segSize][4 * segSize], int wylosowane_segmenty[MAX_ROWS][MAX_COLUMS], bool segmenty[segIl][segSize][segSize]);
void rob_mikrotablice(int plansza[8 * segSize][4 * segSize], int numer_segmentu, bool segmenty[segIl][segSize][segSize], int numer_wiersza, int numer_kolumny);
void prezentuj_plansze(int plansza[8 * segSize][4 * segSize]);
void losuj_punkt(int punkt[], int plansza[8 * segSize][4 * segSize]);
bool is_point_inside_board(int point_x, int point_y, int plansza[PLANSZA_HEIGHT][PLANSZA_WIDTH]);

int main()
{
    int start_point[2];
    int end_point[2];
    bool rzad1[segIl][segSize] = { {1,1,0,1,1},{1,1,0,0,1},{0,0,0,0,0},{1,1,0,0,0},{0,0,0,1,1},{1,1,0,1,1} };
    bool rzad2[segIl][segSize] = { {1,0,0,1,1},{0,1,1,0,1},{0,0,1,0,0},{1,0,0,1,0},{1,0,0,0,1},{1,1,0,1,1} }; // na czarno 1, na biało 0, jak dla mnie bardziej intuicyjne
    bool rzad3[segIl][segSize] = { {0,0,1,0,0},{0,0,0,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,0} };
    bool rzad4[segIl][segSize] = { {1,0,0,0,1},{1,0,0,0,1},{1,0,1,1,1},{0,1,0,0,1},{0,0,1,0,0},{1,1,0,1,1} };
    bool rzad5[segIl][segSize] = { {1,1,0,1,1},{1,1,0,0,1},{1,0,0,0,0},{1,0,0,1,1},{0,0,0,0,1},{1,1,0,1,1} };
    int plansza[8 * segSize][4 * segSize];
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
    losuj_punkt(start_point, plansza);
    losuj_punkt(end_point, plansza);
    cout << " \n A :" << start_point[0] << " , " << start_point[1] << "\n B :  " << end_point[0] << " , " << end_point[1] << endl;
    plansza[start_point[0]][start_point[1]] = 2;
    plansza[end_point[0]][end_point[1]] = 3;
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
void inicjalizuj_plansze(int plansza[8 * segSize][4 * segSize],int wylosowane_segmenty[MAX_ROWS][MAX_COLUMS], bool segmenty[segIl][segSize][segSize])
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
void rob_mikrotablice(int plansza[8 * segSize][4 * segSize], int numer_segmentu, bool segmenty[segIl][segSize][segSize], int numer_wiersza, int numer_kolumny)
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

void prezentuj_plansze(int plansza[8 * segSize][4 * segSize])
{
    for (int i = 0; i < (8 * segSize); i++)
    {
        cout << endl;
        for (int j = 0; j < (4 * segSize); j++)
        {
            if (plansza[i][j] == 1)
            {
                cout << "X";
            }
            else if(plansza[i][j] == 0)
            {
                cout << "O";
            }
            else if (plansza[i][j] == 2)
            {
                cout << "A";
            }
            else if (plansza[i][j] == 3)
            {
                cout << "B";
            }
        }
    }
}

void losuj_punkt(int punkt[], int plansza[8 * segSize][4 * segSize])
{
    int x, y;
    x = algorytm_losujacy(0, PLANSZA_HEIGHT);
    y = algorytm_losujacy(0, PLANSZA_WIDTH);
    while(!is_point_inside_board(x,y,plansza))
    {
        x = algorytm_losujacy(0, PLANSZA_HEIGHT);
        y = algorytm_losujacy(0, PLANSZA_WIDTH);
    }
    punkt[0] = x;
    punkt[1] = y;
}

bool is_point_inside_board(int point_x, int point_y, int plansza[PLANSZA_HEIGHT][PLANSZA_WIDTH])
{
    if (plansza[point_x][point_y])
        return false;
    else
        return true;
}