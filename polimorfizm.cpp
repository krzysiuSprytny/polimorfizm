#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Flota {
protected:
    string kod;
    string typ;

public:
    static int liczbaPojazdow;
    static int liczbaTIRow;
    static int liczbaOsobowych;

    Flota(string kod, string typ) : kod(kod), typ(typ) {
        liczbaPojazdow++;
        if (typ == "TIR") liczbaTIRow++;
        else if (typ == "Osobowy") liczbaOsobowych++;
    }

    virtual void tankuj() = 0;

    string getKod() { return kod; }
    string getTyp() { return typ; }
};

int Flota::liczbaPojazdow = 0;
int Flota::liczbaTIRow = 0;
int Flota::liczbaOsobowych = 0;

class TIR : public Flota {
public:
    TIR(string kod) : Flota(kod, "TIR") {}

    void tankuj() override {
        cout << "Pojazd " << kod << " zatankowany: Diesel" << endl;
    }
};

class Osobowy : public Flota {
public:
    Osobowy(string kod) : Flota(kod, "Osobowy") {}

    void tankuj() override {
        cout << "Pojazd " << kod << " zatankowany: LPG" << endl;
    }
};

int main() {
    vector<Flota*> flota;
    int wybor;

    do {
        cout << "\nMenu:\n";
        cout << "1. Dodaj pojazd do floty\n";
        cout << "2. Zatankuj flotę\n";
        cout << "3. Wypisz listę pojazdów\n";
        cout << "4. Wyjście\n";
        cout << "Wybierz opcję: ";
        cin >> wybor;

        if (wybor == 1) {
            string kod, typ;
            cout << "Podaj kod identyfikacyjny pojazdu: ";
            cin >> kod;
            cout << "Podaj typ pojazdu (TIR/Osobowy): ";
            cin >> typ;

            if (typ == "TIR") {
                flota.push_back(new TIR(kod));
                cout << "Dodano TIR o kodzie " << kod << "." << endl;
            } else if (typ == "Osobowy") {
                flota.push_back(new Osobowy(kod));
                cout << "Dodano Osobowy o kodzie " << kod << "." << endl;
            } else {
                cout << "Nieznany typ pojazdu!" << endl;
            }

        } else if (wybor == 2) {
            if (flota.empty()) {
                cout << "Flota jest pusta!" << endl;
            } else {
                for (auto pojazd : flota) {
                    pojazd->tankuj();
                }
            }

        } else if (wybor == 3) {
            if (flota.empty()) {
                cout << "Flota jest pusta!" << endl;
            } else {
                cout << "Lista pojazdów we flocie:\n";
                for (auto pojazd : flota) {
                    cout << "- " << pojazd->getTyp() << " o kodzie " << pojazd->getKod() << endl;
                }
                cout << "Liczba wszystkich pojazdów: " << Flota::liczbaPojazdow << endl;
                cout << "Liczba TIRów: " << Flota::liczbaTIRow << endl;
                cout << "Liczba osobowych: " << Flota::liczbaOsobowych << endl;
            }

        } else if (wybor != 4) {
            cout << "Nieprawidłowa opcja!" << endl;
        }

    } while (wybor != 4);

    // Czyszczenie pamięci
    for (auto pojazd : flota) {
        delete pojazd;
    }

    cout << "Do widzenia!" << endl;
    return 0;
}