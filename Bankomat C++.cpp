#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <cmath>
#include <time.h>

using namespace std;

//liczby cykli zegara
clock_t start, stop;
int czas;

//Struktura dane_logowania z parametrami domyślnymi
struct dane_logowania
{
    string log = "admin", pass = "1234";
    float stan_konta = 35000;
};

struct kredyt
{
    float oprocentowanie_kredytu = 0.179;
};

struct lokata
{
    float oprocentowanie=1.8;
    int kapitalizacja=4;
};

void logowanie(dane_logowania *uzytkownik);
void menu(dane_logowania *uzytkownik, kredyt *promocyjny, lokata *rodzaj);
void pokaz_stan_konta(const dane_logowania *uzytkownik);
void wyslij_przelew(dane_logowania *uzytkownik);
void wez_kredyt(const kredyt *promocyjny);
void zaloz_lokate (const lokata *rodzaj);
void zaplac_blikiem ();
void zmien_haslo(dane_logowania *uzytkownik);
void wyloguj();
void wplata(dane_logowania * uzytkownik);

int main()
{
    //Deklaracja instatncji struktur
    dane_logowania uzytkownik;
    kredyt promocyjny;
    lokata letnia;

    logowanie(&uzytkownik);
    menu(&uzytkownik, &promocyjny, &letnia);

 return 0;
}

void logowanie(dane_logowania *uzytkownik)
{
    string login;
    string haslo;
    cout << "Witamy w naszym Banku!" << endl;
    cout << "-----------------------" << endl;
    cout << "Zaloguj sie do bankowosci " << endl;
    cout << "Login: ";
    cin >> login;
    cout << "Haslo: ";
    cin >> haslo;

    int proba = 0;

    while (login != (*uzytkownik).log || haslo != (*uzytkownik).pass)
    {
           while (proba >= 4);
           {
               proba++;
               system("cls");
               cout << "LOGOWANIE NIEUDANE | BLEDNY LOGIN LUB HASLO" << endl;
               cout << "Login: ";
               cin >> login;
               cout << "Haslo: ";
               cin >> haslo;

               if (proba == 4 && (login != uzytkownik->log || haslo != uzytkownik->pass))
               {
                  cout << "LOGOWANIE NIEUDANE | BLEDNY LOGIN LUB HASLO" << endl;
                  cout << "Wykonano 5 razy bledne logowanie. Dostep do konta zostaje ZABLOKOWANY";
                  Sleep(1500);
                  exit(0);
               }
           }
    }
    cout << "ZALOGOWANO POMYSLENIE";
    Sleep(1000);
    start = clock();
    system("cls");
}

void pokaz_stan_konta(const dane_logowania *uzytkownik)
{
    cout << "Twoj stan konta wynosi: " << uzytkownik->stan_konta << "zl"<< endl;
}

void wyslij_przelew(dane_logowania * uzytkownik)
{
    float kwota ;
    cout << "Aktualny stan konta wynosi: " << uzytkownik->stan_konta << "zl"<< endl;
    cout << "Wpisz kwote jaka chcesz przelac: ";
    cin >> kwota;
    if (kwota>uzytkownik->stan_konta) cout <<"Niewystarczajace srodki na koncie!" << endl;
    else if (kwota<=0) cout <<"Wpisano nieprawidlowa wartosc!" <<endl;
    else
    {
        long int numer_konta;
        cout << "Wpisz numer konta: ";
        cin >> numer_konta;
        uzytkownik->stan_konta -= kwota;
        cout << "Przelew zrealizowano poprawnie" << endl;
    }
}

void wez_kredyt(const kredyt *promocyjny)
{
    float kwota_kredytu;
    int ile_lat;
    float rata,q;

    cout << "Wpisz kwote kredytu: ";
    cin >> kwota_kredytu;
    cout << "Na jaki okres chcesz wziac kredyt (w latach): ";
    cin >> ile_lat;

    if (ile_lat>0 && kwota_kredytu>0)
    {
        q =(1+((promocyjny->oprocentowanie_kredytu)/12));
        rata = (kwota_kredytu*pow(q,(12*ile_lat)))*((q-1)/(pow(q,(12*ile_lat))-1));

        cout << "Twoja stala miesieczna rata bedzie wynosila: " ;
        printf("%.2f",rata);
        cout << " zl" << endl;
    }
    else cout << "Wpisano nie poprawna wartosc w co najmniej jednym polu!" << endl;
}

void zaloz_lokate (const lokata *rodzaj)
{
    long double zysk;
    double kw_wplacona;
    int ile_lat;
    cout << "Wpisz kwote jaka planujesz wplacic na lokate: ";
    cin >> kw_wplacona;
    cout << "Na jaki okres chcesz otworzyc lokate (w latach): ";
    cin >> ile_lat;
    if (ile_lat>0 && kw_wplacona>0)
    {
      zysk = kw_wplacona * pow((1+(rodzaj->oprocentowanie/(rodzaj->kapitalizacja*100))),rodzaj->kapitalizacja*ile_lat);

      cout << "Twoj zysk po " << ile_lat << " latach bedzie wynosil " << zysk-kw_wplacona << " zl\n";

    }
    else cout << "Wpisano nie poprawna wartosc w co najmniej jednym polu!" << endl;
}

void zaplac_blikiem ()
{
    unsigned int blik, num1, num2;
    cout << "Nacisnij ENTER aby wygnerowac kod blik";
    cin.sync(); //w celu oproznienia bufora strumienia z pozostalosci
    cin.get();
    //ze wzgledu na ograniczony zakres fukcji rand() uzywam dwoch zmiennych
    num1 = rand()%899+100;
    num2 = rand()%1000;
    blik = 1000 * num1 + num2;
    cout << "Twoj kod blik to: " <<blik << endl;
}

void zmien_haslo(dane_logowania * uzytkownik)
{
    string haslo_wpisane;
    cout <<"W celu zmiany hasla wpisz dotychczas uzywane: ";
    cin >> haslo_wpisane;
    if (haslo_wpisane==uzytkownik->pass)
    {
        string nowe_haslo, nowe_haslo_potwierdzenie;
        cout << "Wpisz nowe haslo: ";
        cin >> nowe_haslo;
        cout << "Wpisz ponownie nowe haslo: ";
        cin >> nowe_haslo_potwierdzenie;
        cout << endl;

        while (nowe_haslo != nowe_haslo_potwierdzenie)
        {
            cout << "Wpisane hasla roznia sie sie od siebie! \nSprobuj ponownie" << endl;
            cout << "Wpisz nowe haslo: ";
            cin >> nowe_haslo;
            cout << "Wpisz ponownie nowe haslo: ";
            cin >> nowe_haslo_potwierdzenie;
            cout << endl;
        }

    uzytkownik->pass = nowe_haslo;
    cout << "Haslo zmienione poprawnie, zaloguj sie uzywajac nowego hasla" << endl;
    cout << "Wcisnij ENTER, aby przejsc do ekranu logowania" ;
    cin.sync();
    cin.get();
    system("cls");
    logowanie(uzytkownik);
    }

    else
    {
        cout << "Wpisano nieporawne haslo!" << endl;
        Sleep(1500);
    }
}

void wyloguj()
{
    cout << "Wylogowano pomyslnie. \nZAPRASZAMY PONOWNIE DO BANKU C++\n";
    stop = clock();
    czas = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Czas trwania sesji: " <<czas/60<<" min i "<< czas%60 << " sek" <<endl;
    Sleep(2000);
    exit (0);
}

void menu(dane_logowania *uzytkownik, kredyt *promocyjny, lokata *rodzaj)
{
    char wybor;

    while (true)
    {
        cout << "  Bank C++" << endl;
        cout << "------------" << endl;
        cout << "WYBIERZ OPCJE: " << endl;
        cout << "1.POKAZ STAN KONTA" << endl;
        cout << "2.WYSLIJ PRZELEW" << endl;
        cout << "3.WEZ KREDYT" << endl;
        cout << "4.ZALOZ LOKATE OSZCZEDNOSCIOWA" << endl;
        cout << "5.ZAPLAC BLIKIEM" << endl;
        cout << "6.ZMIEN HASLO" << endl;
        cout << "7.WYLOGUJ" << endl;
        cout << "8.WPLAC" << endl;

        srand(time(NULL));
        wybor=getch();
        system("cls");

        switch (wybor)
        {
            case '1':
                pokaz_stan_konta(uzytkownik);
            break;

            case '2':
                wyslij_przelew(uzytkownik);
            break;

            case '3':
                wez_kredyt(promocyjny);
            break;

            case '4':
                zaloz_lokate(rodzaj);
            break;

            case '5':
                zaplac_blikiem();
            break;

            case '6':
                 zmien_haslo(uzytkownik);
            break;

            case '7':
                 wyloguj();
            break;

            case '8':
                 wplata(uzytkownik);
            break;

            default:
                cout <<"Wybrano niepoprawny numer opcji, sprobuj ponownie" << endl;
        }

        if (wybor!='6')
        {
            cout << "Wcisnij ENTER aby KONTYNUOWAC";
            cin.sync();
            cin.get();
            system("cls");
        }
        else system("cls");
    }
}

void wplata(dane_logowania * uzytkownik)
{
    float wplata ;
    cout << "Aktualny stan konta wynosi: " << uzytkownik->stan_konta << "zl"<< endl;
    cout << "Wpisz kwote jaka chcesz wplacic: ";
    cin >> wplata;
    if (wplata<=0) cout <<"Wpisano nieprawidlowa wartosc!" <<endl;
    else
    {
        uzytkownik->stan_konta += wplata;
        cout << "Wplata zrealizowana poprawnie" << endl;
    }
}
