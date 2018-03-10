#include <iostream>
#include <string.h>

using namespace std;

class Angajat
{
protected:
    char nume[256];
    char prenume[256];
    int tip_contract;
    static int prima;
public:
    Angajat() { }
    Angajat(char a[256], char b[256] = "", int c = 0)
    {
        strcpy(nume, a);
        strcpy(prenume, b);
        tip_contract = c;
    }
    ~Angajat() { }
    Angajat(const Angajat &a)
    {
        strcpy(nume, a.nume);
        strcpy(prenume, a.prenume);
        tip_contract = a.tip_contract;
    }
    Angajat &operator = (const Angajat &a)
    {
        if (this != &a)
        {
            strcpy(nume, a.nume);
            strcpy(prenume, a.prenume);
            tip_contract = a.tip_contract;
        }
        return *this;
    }
    friend istream &operator >> (istream &i, Angajat &a);
    virtual void Afisare()
    {
        cout << nume << " " << prenume << " ";
        if (tip_contract == 1)
            cout << "contract permanent ";
        else
            cout << "plata cu ora ";
    }
    virtual int calcul_prima() = 0;
    virtual void Citire()
    {
        cin >> *this;
    }
};
istream &operator >> (istream &i, Angajat &a)
{
    cout << "Nume = ";
    i >> a.nume;
    cout << "Prenume = ";
    i >> a.prenume;
    cout << "Tip contract = ";
    i >> a.tip_contract;
    return i;
}

int Angajat :: prima = 400;

class Tesa : public Angajat
{
protected:
    char prima_zi[256];
    char ultima_zi[256];
public:
    Tesa() { }
    Tesa(char a[256], char b[256] = "", int c = 0, char d[256] = "", char e[256] = "") : Angajat(a, b, c)
    {
        strcpy(prima_zi, d);
        strcpy(ultima_zi, e);
    }
    Tesa(const Tesa &a) : Angajat(a)
    {
        strcpy(prima_zi, a.prima_zi);
        strcpy(ultima_zi, a.ultima_zi);
    }
    Tesa &operator = (const Tesa &a)
    {
        if (this != &a)
        {
            strcpy(prima_zi, a.prima_zi);
            strcpy(ultima_zi, a.ultima_zi);
        }
        return *this;
    }
    ~Tesa() { }
    friend istream &operator >> (istream &i, Tesa &a);
    void Afisare()
    {
        Angajat :: Afisare();
        cout << prima_zi << " " << ultima_zi;
    }
    int calcul_prima()
    {

    }
    void Citire()
    {
        cin >> *this;
    }
};

class Muncitor : public Angajat
{
protected:
    int varsta;
    char data_angajare[256];

public:
    Muncitor() { }
    Muncitor(char a[256], char b[256] = "", int c = 0, int d = 0, char e[256] = "") : Angajat(a, b, c)
    {
        varsta = d;
        strcpy(data_angajare, e);
    }
    Muncitor(const Muncitor &a) : Angajat(a)
    {
        varsta = a.varsta;
        strcpy(data_angajare, a.data_angajare);
    }
    Muncitor &operator = (const Muncitor &a)
    {
        if (this != &a)
        {
            varsta = a.varsta;
            strcpy(data_angajare, a.data_angajare);
        }
        return *this;
    }
    ~Muncitor() { }
    friend istream &operator >> (istream &i, Muncitor &a);
    void Afisare()
    {
        Angajat :: Afisare();
        cout << varsta << " " << data_angajare;
    }
    int calcul_prima()
    {

    }
    void Citire()
    {
        cin >> *this;
    }

};

istream &operator >> (istream &i, Muncitor &a)
{
    Angajat &aux = static_cast<Angajat&> (a);
    i >> aux;
    cout << "Varsta = ";
    i >> a.varsta;
    cout << "Data angajare = ";
    i >> a.data_angajare;
    return i;
}

istream &operator >> (istream &i, Tesa &a)
{
    Angajat &aux = static_cast<Angajat&> (a);
    i >> aux;
    cout << "Prima zi = ";
    i >> a.prima_zi;
    cout << "Ultima zi = ";
    i >> a.ultima_zi;
    return i;
}

int main()
{
    Angajat **v;
    int n;
    cout << "numarul de angajati = ";
    cin >> n;
    v = new Angajat*[n+1];

    cout << "1 -- muncitor" << endl;
    cout << "2 -- tesa" << endl;

    for (int i = 1; i<=n; i++)
    {
        int tip;
        cout << endl << "tipul angajatului = ";
        cin >> tip;
        if (tip == 1)
        {
            v[i] = new Muncitor;
            Tesa *a = dynamic_cast <Tesa*> (v[i]);
            v[i]->Citire();
        }
        else if (tip == 2)
        {
            v[i] = new Tesa;
            Tesa *a = dynamic_cast <Tesa*> (v[i]);
            v[i]->Citire();
        }
        else
        {
            cout << endl << "Nu exista tipul de angajat ales." << endl;
            return 0;
        }
    }
    return 0;
}
