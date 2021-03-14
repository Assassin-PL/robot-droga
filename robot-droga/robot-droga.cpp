// robot-droga.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "stdafx.h"

using namespace std;

class List {
    struct Node {
        int x = 0; //koordynaty naszego punktu z planszy
        int y = 0;
        bool is_visited = false; // wartosc kazdego wierzcholku mowiaca o tym czy nie zostal odwiedzony
        Node* next;
    };

    Node* head;

public:
    List() {
        head = NULL;
    }

    ~List() {
        while (head != NULL) {
            Node* n = head->next;
            delete head;
            head = n;
        }
    }

    void add(int value, int value_sec) { //dodawanie wierzcholka
        Node* n = new Node;
        n->x = value;
        n->y = value_sec;
        n->next = head;
        head = n;
    }

    void get_number(int number) { //debugowa funkcja
        cout << " x = " << test(number)->x << " y = " << test(number)->y << endl;
        cout << " Is visited??? : " << test(number)->is_visited << endl;
    }

    Node* test(int ile_razy) //!!wazna funkcja, pozwala nam na dostep do wskaznika do ostatniej komorki listy ()
    {
        Node* n = head;
        for (int i = 0; i < ile_razy; i++)
        {
            n = n->next;
        }
        return n;
    }

    void make_visited(int number) { //funkcaj zmieniajaca wezel na odwiedzony
        test(number)->is_visited = true;
    }

    int get_x(int number) { //funkcja zwracajoca kordy po x
        return test(number)->x;
    }

    int get_y(int number) { //funkcja zwracajoca kordy po y
        return test(number)->y;
    }

    bool get_visited(int number) {
        return test(number)->is_visited;
    }
};

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
void zacznij_ruch(int plansza[8 * segSize][4 * segSize], int start_point[2], int end_point[2]);
void wiedz_do_wezla(List& list, int plansza[8 * segSize][4 * segSize], int number, int& how);
void tworz_sasiedztwa(List& list, int plansza[8 * segSize][4 * segSize], int number, int& how);
void tworz_sasiedztwa_2(List& list, int plansza[8 * segSize][4 * segSize], int number, int& how);
void tworz_sasiedztwa_3(List& list, int plansza[8 * segSize][4 * segSize], int number, int& how);
void tworz_sasiedztwa_4(List& list, int plansza[8 * segSize][4 * segSize], int number, int& how);


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
    cout << endl;
    zacznij_ruch(plansza, start_point, end_point);
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
            cout << wyloswane_segmenty[i][j] << " ";
        }
    }
}
void inicjalizuj_plansze(int plansza[8 * segSize][4 * segSize], int wylosowane_segmenty[MAX_ROWS][MAX_COLUMS], bool segmenty[segIl][segSize][segSize])
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
            else if (plansza[i][j] == 0)
            {
                cout << " ";
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
    while (!is_point_inside_board(x, y, plansza))
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

void zacznij_ruch(int plansza[8 * segSize][4 * segSize], int start_point[2], int end_point[2])
{
    plansza[end_point[0]][end_point[1]] = 0;
    List list; //inicjalizacja listy
    int how = -1; // zmienna informujaca nas o wielkosci listy, jest zawsze inkrementowana jak sie zrobi list.add
    list.add(start_point[0], start_point[1]); // dodanie 1 punktu czyli naszego wylosowanego a jako koordynatow do listy
    list.make_visited(0); // no na poczotku informujemy program ze ten wierzcholek zostal odwieddzony
    how++;
    tworz_sasiedztwa(list, plansza, how, how);
    cout << endl << how << endl;
    for (int i = 0; i <= how; i++)
    {
        cout << "  koordynat x wynosi: " << list.get_x(i) << "  koordynat y wynosi: " << list.get_y(i) << "  czy jest odwiedzone? : " << list.get_visited(i) << endl;
    }
    wiedz_do_wezla(list, plansza, 0, how);
    cout << endl << how << endl;
    for (int i = 0; i <= how; i++)
    {
        cout << "  koordynat x wynosi: " << list.get_x(i) << "  koordynat y wynosi: " << list.get_y(i) << "  czy jest odwiedzone? : " << list.get_visited(i) << endl;
    }
    for (int i = 0; i < 10000; i++)
    {
        wiedz_do_wezla(list, plansza, 0, how);
        if (list.get_x(0) == end_point[0] && list.get_y(0) == end_point[1])
        {
            cout << endl << "Znaleziono B!!" << endl;
            break;
        }
        if (list.get_x(1) == end_point[1] && list.get_y(0) == end_point[1])
        {
            cout <<endl << "Znaleziono B!!"<<endl;
            break;
        }
        if (list.get_x(2) == end_point[2] && list.get_y(0) == end_point[1])
        {
            cout << endl << "Znaleziono B!!" << endl;
            break;
        }
        if (list.get_x(3) == end_point[3] && list.get_y(0) == end_point[1])
        {
            cout << endl << "Znaleziono B!!" << endl;
            break;
        }
    }
    for (int i = 0; i <= 50; i++)
    {
        cout << "  koordynat x wynosi: " << list.get_x(i) << "  koordynat y wynosi: " << list.get_y(i) << "  czy jest odwiedzone? : " << list.get_visited(i) << endl;
    }
    /*while (1)
    {
        wiedz_do_wezla(list, plansza, 0, how);
        if (list.get_x(0) == end_point[0] && list.get_y(0) == end_point[0])
        {
            cout << "znaleziono B!!!!!";
            break;
        }
        if (list.get_x(1) == end_point[0] && list.get_y(1) == end_point[0])
        {
            cout << "znaleziono B!!!!!";
            break;
        }if (list.get_x(2) == end_point[0] && list.get_y(2) == end_point[0])
        {
            cout << "znaleziono B!!!!!";
            break;
        }if (list.get_x(3) == end_point[0] && list.get_y(3) == end_point[0])
        {
            cout << "znaleziono B!!!!!";
            break;
        }if (list.get_x(4) == end_point[0] && list.get_y(4) == end_point[0])
        {
            cout << "znaleziono B!!!!!";
            break;
        }
    }*/
    plansza[end_point[0]][end_point[1]] = 3;
    //while (plansza[list.get_x(how)][list.get_y(how)] != 3)//trzeba mu ogarnac zeby sie nie zapetla to znaczy co bedzie jak dojdzie do koziego rogu trzeba bedzie mu napisac funkcje zeby sie wycofal
    //{
    //    wiedz_do_wezla(list, plansza, how, how);
    //}
}

void tworz_sasiedztwa(List& list, int plansza[8 * segSize][4 * segSize], int number, int& how)// tworzymy liste sasiedztwa, czyli liste miejsc na ktorych robot moze sie poruszac
{
    if (plansza[list.get_x(number)][list.get_y(number) + 1] == 0 && (list.get_y(number) + 1) >= 0 && (list.get_y(number) + 1) < (4 * segSize)) // !trzeba bedzie zrobic ifa informujacego o tym czy koordynat nie wyzedl poza rozmiar tablicy bo jak tak to bedzie blad + trzeba bedzie dodac warunek sprawdzajacy czy ten pole nie jest odwiedzone(czy is_visited przyjmuje true)
    {
        list.add(list.get_x(number), list.get_y(number) + 1);
        how++;
        number++;
    }
    if (plansza[list.get_x(number)][list.get_y(number) - 1] == 0 && (list.get_y(number) - 1) >= 0 && (list.get_y(number) - 1) < (4 * segSize))
    {
        list.add(list.get_x(number), list.get_y(number) - 1);
        how++;
        number++;
    }
    if (plansza[list.get_x(number) + 1][list.get_y(number)] == 0 && (list.get_x(number) + 1) >= 0 && (list.get_x(number) + 1) < (8 * segSize))
    {
        list.add(list.get_x(number) + 1, list.get_y(number));
        how++;
        number++;
    }
    if (plansza[list.get_x(number) - 1][list.get_y(number)] == 0 && (list.get_x(number) - 1) >= 0 && (list.get_x(number) - 1) < (8 * segSize))
    {
        list.add(list.get_x(number) - 1, list.get_y(number));
        how++;
        number++;
    }
}

void wiedz_do_wezla(List& list, int plansza[8 * segSize][4 * segSize], int number, int& how)
{
    int x, y;
    if (list.get_visited(number) == 0)
    {
        x = list.get_x(number);
        y = list.get_y(number);
        list.make_visited(number); // no na poczotku informujemy program ze ten wierzcholek zostal odwieddzony
        plansza[x][y] = 1;
        tworz_sasiedztwa(list, plansza, number, how);
    }
    else
    {
        number++;
        wiedz_do_wezla(list, plansza, number, how);
    }
}

