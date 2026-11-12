#include <iostream>
#include <string>
#include <limits>
#include <cstdint> // Udostępnia typy liczb całkowitych o określonej liczbie bitów, np. uint64_t (64 bity bez znaku).
// API zestaw funkcji i zasad pozwalających naszemu programowi korzystać z usług systemu operacyjnego.
#include <sys/sysctl.h> // nagłówek systemowy udostępniający deklarację funkcji sysctlbyname().

using namespace std;

// Klasa Computer
class Computer
{
private:
    // Pola obiektu klasy Computer. Przechowuje w sekcji private, aby nie było mozliwosci, ze ktos będzie w stanie zmienic te dane
    string name;
    // wycofuje:
    // int ramGB;
    uint64_t ramBytes;
    string operatingSystem;
    int diskGB;

public:
    // Konstruktor:
    Computer(string newName, uint64_t newRamBytes, string newOS, int newDiskGB);
    // Metody klasy Computer. Udostępnione w sekcji public. Do tych metod chce mieć dostęp.
    void ramStatus();
    void showInformation()
    {
        cout << "Nazwa Komputera: " << name << endl
             << "System: " << operatingSystem << endl
             << "Pojemnosc RAM: " << ramBytes / (1024 * 1024 * 1024) << "GiB" << endl
             << "Pojemnosc dysku: " << diskGB << endl;
    }
    // Metoda pobieram rzeczywistą ilość RAM z sysemu MacOS
    // Aktualizacja zmieniam typ metody z void na bool, tak aby main()
    // dostał informację o powdzeniu odczytu
    // void updateRamInfo();
    bool updateRamInfo();
};

// Definicja konstruktora obiektu Computer, z przekazanymi parametrami
Computer::Computer(string newName, uint64_t newRamBytes, string newOS, int newDiskGB)
{
    name = newName;
    ramBytes = newRamBytes;
    operatingSystem = newOS;
    diskGB = newDiskGB;
}
// Zmieniam typ definicji metody updateRamInfo z void na bool. Typ musi być zgodny z metodą w klasie
bool Computer::updateRamInfo()
{
    // odczyt RAM do lokalnej zmiennej pomocniczej
    // Nie chcę odrazu przekazywać wyniku do ramBytes, poniewaz jak zwroci -1
    // to nie mam gwarancji, ze pole ramBytes zawiera prawidlowa wartosc.
    // Dlatego do walidacji uzywam zmiennej pomocniczej. Jesli wynik jest 0 to dane ze zmiennej pomocniczej przekazuje do glownej zmiennej ramBytes
    uint64_t detectedRamBytes = 0;

    // Nie deklaruje ponownie ramBytes,
    // ramBytes jest juz polem prywatnym klasy Computer.
    // Metoda updateRamInfo() ma do niego bezposredni dostep.

    // zmiena określająca rozmiar miejsca do ktorego system zapisze wynik (rozmiar bufora)
    // dodatkowo jest to zmienna lokalna updateRamInfo()
    // # ZMIANA nie do ramBytes tylko do detectedRamBytes!
    // Chcę sprawdzić czy API mac przekazał prawidłowe dane. Wyjaśnienie pod int result
    size_t dataSize = sizeof(detectedRamBytes);

    // Wywolujemy funkcje API macOS, aby pobrac fizyczna ilosc RAM w bajtach.
    // Funkcja zapisuje wynik w detectedRamBytes, a do result zwraca status operacji:
    // 0 - sukces, -1 - blad.
    int result = sysctlbyname(
        "hw.memsize",
        &detectedRamBytes,
        &dataSize,
        nullptr,
        0);

    // Zmiana walidacji
    // if (result == -1)
    // {
    //     cout << "Wystąpił błąd!" << endl;
    // }
    // Sprawdzenie przekazanych danych z API MacOS. Weryfikacja 3 elementow:
    // result — sprawdzam, czy funkcja sysctlbyname() zakończyła się sukcesem (0), czy błędem (-1).
    // dataSize — sprawdzam, czy system zwrócił dokładnie tyle bajtów, ile oczekuje, czyli 8.
    // detectedRamBytes — sprawdzam, czy odczytana pojemność RAM jest większa od 0.
    if (result == 0 && dataSize == sizeof(detectedRamBytes) && detectedRamBytes > 0)
    {
        ramBytes = detectedRamBytes;
        return true;
    }
    else
    {
        cout << "Blad odczytu pamieci RAM" << endl;
        return false;
    }
}

int main()
{
    // zmienna do przechowania wyboru uzytkownika z menu
    int userChoice;
    // MENU - wdrozenie
    do
    {
        cout << "\n====== IT SYSTEM MONITOR ======" << endl;
        cout << "1. Monitoring Live" << endl;
        cout << "2. Historia Monitoringu" << endl;
        cout << "3. Informacje o urządzeniu" << endl;
        cout << "0. Zakoncz program" << endl;

        cout << "Wybierz opcje: ";

        // Walidacja danych wejsciowych
        // NOTE: Gdy uzytkownik wpisze dane typu "abc"
        // cin >> userChoice probuje odczytac liczbe. Operacja konczy sie bledem
        // ! odwraca wynik sprawdzenia i wchodzi do if'a
        // cin.clear() - usuwa stan bledu strumienia
        // cin.ignore() - odrzuca nieprawidlowe dane z biezacej linii

        if (!(cin >> userChoice))
        {
            cout << "Blad! Podaj prawidlowa liczbe z menu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Bez ustawienia zmiennej, program przechodzi do zakonczenia dzialania programu
            userChoice = -1;
            continue;
        }

        switch (userChoice)
        {
        case 1:
        {
            cout << "Monitoring live" << endl;
            break;
        }
        case 2:
        {
            cout << "Historia Monitoringu" << endl;
            break;
        }
        case 3:
        {
            // MODYFIKACJA, aktualnie konstruktor dostaje wartosc na sztywno 8589934592ULL
            // Sprawdzam czy metoda updateRamInfo() jest w stanie ja zastapic
            Computer myComputer("MacBook", 0, "MacOS", 256);
            if (myComputer.updateRamInfo())
            {
                myComputer.showInformation();
            }
            break;
        }
        case 0:
        {
            cout << "Program konczy dzialanie" << endl;
            break;
        }
        default:
        {
            cout << "Opcja z menu nie zostala prawidlowo wybrana" << endl;
            break;
        }
        }

    } while (userChoice != 0);

    return 0;
}