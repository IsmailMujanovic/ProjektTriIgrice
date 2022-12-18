#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include <cmath>

using namespace std;

struct xox
{
    //sve varijable su smjestene u private dijelu i koriste se samo u klasi
private:
    char n[10] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57}; //char niz radi lakseg rada jer ima mnogo upotrebe petlji
    int P1;                                                //brojevi od 48 do 57 u ascii tabeli su char znakovi za cifre
    int P2;                                                //88 == X
    int victory1=0;                                        //79 == O
    int victory2=0;
    int br=0;

public:
    void ispis() //ispisuje/updatea tabelu
    {
        br++;
        system("CLS");
        cout << "IGRAC 1: X     IGRAC 2: O" << endl << endl;

        cout << "       " << "   |   |   " << endl;
        cout << "       " << " " << n[1] << " | " << n[2] << " | " << n[3] << " " << endl;
        cout << "       " << "___|___|___" << endl;
        cout << "       " << "   |   |   " << endl;
        cout << "       " << " " << n[4] << " | " << n[5] << " | " << n[6] << " " << endl;
        cout << "       " << "___|___|___" << endl;
        cout << "       " << "   |   |   " << endl;
        cout << "       " << " " << n[7] << " | " << n[8] << " | " << n[9] << " " << endl;
        cout << "       " << "   |   |   " << endl << endl;
    }

    void player1() //igrac 1 unosi broj koji ce na tabeli biti zamijenjen s znakom X
    {
        do
        {
            cout << "Igrac 1: ";
            cin >> P1;
        }
        while(P1<1 || P1>9 || n[P1]==79 || n[P1]==88);

        n[P1]=88;

        ispis();
    }

    void player2() //igrac 2 unosi broj koji ce na tabeli biti zamijenjen s znakom O
    {
        do
        {
            cout << "Igrac 2: ";
            cin >> P2;
        }
        while(P2<1 || P2>9 || n[P2]==88 || n[P2]==79);

        n[P2]=79;

        ispis();
    }

    int win_check1() //provjerava da li je igrac 1 pobijedio
    {
        for(int i=1; i<=9; i+=3)
        {                                               //provjerava redove (vodoravno)
            if(n[i]==88 && n[i+1]==88 && n[i+2]==88)
                victory1++;
        }
        for(int i=1; i<=9; i++)
        {                                               //provjerava kolone (uspravno)
            if(n[i]==88 && n[i+3]==88 && n[i+6]==88)
                victory1++;
        }
        if(n[1]==88 && n[5]==88 && n[9]==88)
            victory1++;                                 //provjerava dijagonale
        if(n[3]==88 && n[5]==88 && n[7]==88)
            victory1++;

        return victory1;
    }

    int win_check2() //provjerava da li je igrac 2 pobijedio
    {
        for(int i=1; i<=9; i+=3)
        {                                               //provjerava redove (vodoravno)
            if(n[i]==79 && n[i+1]==79 && n[i+2]==79)
                victory2++;
        }
        for(int i=1; i<=9; i++)
        {                                               //provjerava kolone (uspravno)
            if(n[i]==79 && n[i+3]==79 && n[i+6]==79)
                victory2++;
        }
        if(n[1]==79 && n[5]==79 && n[9]==79)
            victory2++;                                 //provjerava dijagonale
        if(n[3]==79 && n[5]==79 && n[7]==79)
            victory2++;

        return victory2;
    }

    void kraj() //unos poteza se ponavlja sve dok neko ne pobijedi, ili bude nerjeseno
    {
        do
        {
            player1();
            if(win_check1()<1 && br<=9)        //ovaj if nam treba da ako prvi igrac pobijedi, drugi igrac ne mogne igrati
                player2();                     //brojac nam je potreban da zaustavi drugog igraca pri unosu zadnjeg poteza kad je nerjeseno
        }
        while(win_check1()<1 && win_check2()<1 && br<=9);     //brojac zaustavlja petlju u slucaju kad je nerjeseno

        if(win_check1()>=1)
        {
            for(int i=1; i<=9; i++)
            {
                if(n[i]!=88 && n[i]!=79)    //na kraju zamjenjuje preostale brojeve s razmakom
                    n[i]=32;                //32 je razmak
            }
            ispis();
            cout << "        KRAJ IGRE" << endl;
            cout << "   IGRAC 1 JE POBJEDNIK" << endl;
        }
        else if(win_check2()>=1)
        {
            for(int i=1; i<=9; i++)
            {
                if(n[i]!=88 && n[i]!=79)    //na kraju zamjenjuje preostale brojeve s razmakom
                    n[i]=32;                //32 je razmak
            }
            ispis();
            cout << "        KRAJ IGRE" << endl;
            cout << "   IGRAC 2 JE POBJEDNIK" << endl;
        }
        else
        {
            ispis();
            cout << "        KRAJ IGRE" << endl;
            cout << "        NERJESENO" << endl;
        }
        cout << endl;
        system("pause");
    }
};

struct hangman
{
    //sve varijable su smjestene u private dijelu i koriste se samo u klasi
private:
    char slovo='/';                 //spasava slova koje unosi igrac 2
    string unos;                    //spasava rijec koju unosi igrac 1

    int n;                          //velicina rijeci
    char rijec[99];                 //rijec koja se ispisuje umjesto praznih polja
    char iskor_slova[99];           //niz za iskoristena slova

    int sl=0;                       //poveca se kada igrac 2 unese slovo
    int br=0;
    int broj=0;                     //cetiri razlicita brojaca
    int brojac=0;

    char head = 'O';
    char body = '|';
    char l_arm = '/';               //dijelovi tijela
    char r_arm = '\\';
    char l_leg = '/';
    char r_leg = '\\';

    int tc=0;

public:
    hangman() //konstruktor
    {
        head = ' ';
        body = ' ';
        l_arm = ' ';
        r_arm = ' ';                //dijelovi tijela se brisu na pocetku svake igre
        l_leg = ' ';
        r_leg = ' ';
        for(int i=0; i<99; i++)
            iskor_slova[i] = ' ';

        system("CLS");
        cout << "   IGRAC 1" << endl;
        cout << "Unesite rijec: " << endl;          //igrac 1 unosi rijec
        cin >> unos;
        n = unos.size();

        system("CLS");
        cout << "     _____" << endl;
        cout << "    |     |" << endl;
        cout << "    |     |" << endl;
        cout << "    |     " << head << endl;
        cout << "    |    " << l_arm << body << r_arm << endl;          //ispisuje tabelu po prvi put
        cout << "    |    " << l_leg << " " << r_leg << endl;
        cout << "    |" << endl;
        cout << " ___|___       ";

        for(int i=0; i<n; i++)
            rijec[i] = '_';            //clanovi niza postaju prazna polja

        for(int i=0; i<n; i++)
            cout << " " << rijec[i] << " ";                  //ispisuje polja za rijec
        cout << endl;
    }

    void ispis() //updejta tabelu, rijec, iskoristena slova
    {
        system("CLS");
        cout << "     _____" << endl;
        cout << "    |     |" << endl;
        cout << "    |     |" << endl;
        cout << "    |     " << head << endl;
        cout << "    |    " << l_arm << body << r_arm << endl;
        cout << "    |    " << l_leg << " " << r_leg << endl;
        cout << "    |" << endl;
        cout << " ___|___       ";

        for(int i=0; i<n; i++)
            cout << " " << rijec[i] << " ";
        cout << endl << endl;

        cout << "Iskoristena slova: ";
        for(int i=0; i<n+brojac; i++)
            cout << iskor_slova[i] << " ";
        cout << endl;
    }

    void tacnost() //nakon sto igrac 2 unese slovo, ispituje tacnost
    {
        cout << endl << "Unesite slovo: " << endl;
        cin >> slovo;

        for(int i=0; i<=sl; i++)
        {
            while(slovo == iskor_slova[i])          //ponavlja se unos ako je slovo iskoristeno
            {
                cin >> slovo;
            }
        }

        iskor_slova[sl] = slovo;    //stavlja uneseno slovo u niz iskoristena slova
        sl++;                       //prvi put kada igrac 2 unese slovo, brojac "sl" postaje 0, prvobitno -1


        broj=0;
        for(int i=0; i<n; i++)
        {
            if(slovo == unos[i])
            {
                rijec[i] = slovo;       //ako igrac 2 pogodi, ispisuje se slovo na polje
                br++;
            }
            else if(slovo != unos[i])
            {
                broj++;
                if(broj == n)           //ako pogrijesi, brojac se povecava
                    brojac++;
            }
        }

        if(brojac==1)
            head = 'O';
        else if(brojac==2)
            body = '|';
        else if(brojac==3)
            l_arm = '/';
        else if(brojac==4)
            r_arm = '\\';               //6 gresaka je kraj igre
        else if(brojac==5)
            l_leg = '/';
        else if(brojac==6)
            r_leg = '\\';

        ispis();
    }

    void kraj() //unos slova se ponavlja sve dok igrac 2 ne pogrjesi 6 puta, ili pogodi rijec
    {
        do
        {
            tacnost();
        }
        while(br<n && brojac<6);

        if(br==n)   //ako pogodi sva slova zavrsava se igra
        {
            cout << endl;
            cout << "        KRAJ IGRE" << endl;
            cout << "   IGRAC 2 JE POBJEDNIK" << endl;
        }
        if(brojac>=6)   //ako pogrijesi 6 puta zavrsava se igra
        {
            cout << endl;
            cout << "        KRAJ IGRE" << endl;
            cout << "   IGRAC 1 JE POBJEDNIK" << endl;
            cout << endl << "   Zeljena rijec je bila: " << unos << endl;
        }
        cout << endl;
        system("pause");
    }
};

struct memory_test
{
    //sve varijable su smjestene u private dijelu i koriste se samo u klasi
private:
    int n=4;                //broj cifri random broja

    int brojac=0;           //brojac za vrijeme/sekunde
    int br=0;               //brojac za tacan/netacan odgovor

    int niz[99];                      //niz u koji se smjestaju random cifre, te postaje random broj
    long long int korisnikov_broj;    //varijabla za unos, long long int je potreban ako ima vise cifri(14,15)
    int netacno=0;                    //ako je vece od nula, prekida se petlja

public:
    void random_number() //stvara random broj sa onoliko cifara koliki je n
    {
        srand(time(0));            // srand - postavlja seed komandi rand, bez postavljenog seeda, random broj ce uvijek biti isti
        for(int i=0; i<n; i++)     // time(0) - osigurava da seed uvijek bude u potpunosti random, biblioteka: ctime
        {
            niz[i] = rand()%10;
            cout << niz[i];        // n je broj cifri, a svaka cifra se tvori random od 0 do 9, cemu sluzi %10
        }
        cout << endl;
    }

    void ten_sec() //odbrojava 10 sekundi
    {
        for(brojac=10; brojac>=0; brojac--)
        {
            cout << "\rVrijeme: " << setw(2) << brojac;         // "\r" - brise postojecu liniju
            Sleep(1000);                                        // sleep(1000) - zaustavi program na 1000 milisekundi
        }                                                       // biblioteka za sleep(): windows.h
        cout << endl;
    }

    void unos() //korisnik unosi njegov broj
    {
        korisnikov_broj=0;
        system("cls");
        cout << "           MEMORY TEST         score: " << n << "/15" << endl;
        cout << endl << "Unesite broj: ";
        cin >> korisnikov_broj;
    }

    void provjera() //provjerava tacnost odgovora
    {
        for(int i=0; i<n; i++)
        {
            if((long long int)(korisnikov_broj / pow(10,n-1-i)) % 10 == niz[i])    //uzima svaku cifru unesenog broja i poredi je sa cifrom random broja
                br++;
        }

        if(br==n) //ako su sve cifre iste, odgovor je tacan
        {
            cout << "Unijeli ste tacan broj." << endl;
            if(n<15)
            {
                cout << endl;
                system("pause");
            }
        }
        else if(br<n) //a ako nisu, netacan
        {
            netacno=0;
            cout << "Unijeli ste netacan broj." << endl;
            cout << "Tacan broj je bio: ";
            for(int i=0; i<n; i++)
                cout << niz[i];
            cout << endl;
            netacno++;
        }
    }

    void zavrsetak() //vrti sve metode u petlji dok korisnik ne pogrjesi ili ne dodje do score-a 15
    {
        do
        {
            system("cls");
            cout << "           MEMORY TEST         score: " << n << "/15" << endl;
            cout << endl << "Imate 10 sekundi da zapamtite ovaj broj: ";
            random_number();
            ten_sec();
            unos();
            provjera();
            if(netacno>0)
                break;
            n++;        //score se povecava nakon svakog tacnog odgovora
            br=0;       //brojac za tacnost se resetuje
            brojac=10;  //brojac za vrijeme se resetuje
        }
        while(n!=16);
        if(n>15)
        {
            cout << endl;
            cout << "            KRAJ IGRE" << endl;
            cout << "          POBJEDILI STE" << endl;
        }
        else
        {
            cout << endl;
            cout << "            KRAJ IGRE" << endl;
            cout << "          IZGUBILI STE!" << endl;
        }
        cout << endl;
        system("pause");
    }
};

int main()
{
    system("color f0");
    int izbor;

    cout << "      MAIN MENU " << endl << endl;
    cout << "   1 - TIC TAC TOE" << endl;
    cout << "   2 - HANGMAN" << endl;
    cout << "   3 - MEMORY TEST" << endl << endl;
    do
    {
        cin >> izbor;
    }
    while(izbor<1 || izbor>3);

    if(izbor == 1)
    {
        xox player;
        player.ispis();
        player.kraj();
    }
    else if(izbor == 2)
    {
        hangman player;
        player.kraj();
    }
    else
    {
        memory_test player;
        player.zavrsetak();
    }
    return 0;
}
