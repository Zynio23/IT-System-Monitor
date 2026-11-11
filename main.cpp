#include <iostream>
#include <string>
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
    // Wywołanie obiektu z poziomu funkcji main.
    Computer myComputer("MacBook", 8, "MacOS", 256);
    // Wywołanie metody obiektu Computer. Pokazuje dane dotyczące komputera - na razie na sztywno.
    myComputer.showInformation();

    cout << "IT System Monitor - test" << endl;
    return 0;
}