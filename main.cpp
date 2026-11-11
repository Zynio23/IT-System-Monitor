#include <iostream>
#include <string>
using namespace std;

class Computer
{
private:
    string name;
    int ramGB;
    string operatingSystem;
    int diskGB;

public:
    // Konstruktor:
    Computer(string newName, int newRamGB, string newOS, int newDiskGB);
    void ramStatus();
    void showInformation()
    {
        cout << "Nazwa Komputera: " << name << endl
             << "System: " << operatingSystem << endl
             << "Pojemnosc RAM: " << ramGB << endl
             << "Pojemnosc dysku: " << diskGB << endl;
    }
};

Computer::Computer(string newName, int newRamGB, string newOS, int newDiskGB)
{
    name = newName;
    ramGB = newRamGB;
    operatingSystem = newOS;
    diskGB = newDiskGB;
}

int main()
{
    Computer myComputer("MacBook", 8, "MacOS", 256);
    myComputer.showInformation();

    cout << "IT System Monitor - test" << endl;
    return 0;
}