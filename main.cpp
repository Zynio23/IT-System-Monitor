#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Klasa Computer
class Computer
{
private:
    // Pola obiektu klasy Computer. Przechowuje w sekcji private, aby nie było mozliwosci, ze ktos będzie w stanie zmienic te dane
    string name;
    int ramGB;
    string operatingSystem;
    int diskGB;

public:
    // Konstruktor:
    Computer(string newName, int newRamGB, string newOS, int newDiskGB);
    // Metody klasy Computer. Udostępnione w sekcji public. Do tych metod chce mieć dostęp.
    void ramStatus();
    void showInformation()
    {
        cout << "Nazwa Komputera: " << name << endl
             << "System: " << operatingSystem << endl
             << "Pojemnosc RAM: " << ramGB << endl
             << "Pojemnosc dysku: " << diskGB << endl;
    }
};

// Definicja konstruktora obiektu Computer, z przekazanymi parametrami
Computer::Computer(string newName, int newRamGB, string newOS, int newDiskGB)
{
    name = newName;
    ramGB = newRamGB;
    operatingSystem = newOS;
    diskGB = newDiskGB;
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
            Computer myComputer("MacBook", 8, "MacOS", 256);
            myComputer.showInformation();
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