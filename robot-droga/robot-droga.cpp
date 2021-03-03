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
    return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
