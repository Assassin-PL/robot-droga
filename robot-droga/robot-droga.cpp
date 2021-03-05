// robot-droga.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "stdafx.h"

using namespace std;

#define segSize 5
#define segIl 6

int main()
{
    cout << "Hello World!\n";
    cout << "Witaj janusz!\n";
    cout << "Witaj!1213\n";
    cout << "Pisze cos"<<endl;
    bool rzad1[segIl][segSize] = { {1,1,0,1,1},{1,1,0,0,1},{0,0,0,0,0},{1,1,0,0,0},{0,0,0,1,1},{1,1,0,1,1} };
    bool rzad2[segIl][segSize] = { {1,0,0,1,1},{0,1,1,0,1},{0,0,1,0,0},{1,0,0,1,0},{1,0,0,0,1},{1,1,0,1,1} }; // na czarno 1, na biało 0, jak dla mnie bardziej intuicyjne
    bool rzad3[segIl][segSize] = { {0,0,1,0,0},{0,0,0,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,0} };
    bool rzad4[segIl][segSize] = { {1,0,0,0,1},{1,0,0,0,1},{1,0,1,1,1},{0,1,0,0,1},{0,0,1,0,0},{1,1,0,1,1} };
    bool rzad5[segIl][segSize] = { {1,1,0,1,1},{1,1,0,0,1},{1,0,0,0,0},{1,0,0,1,1},{0,0,0,0,1},{1,1,0,1,1} };
    bool plansza[8 * segSize][4 * segSize];
     //wylosować 8x4 sekwencji, na podstawie ich indeksu budujemy wielką planszę od góry do dołu
    return 0;
}

