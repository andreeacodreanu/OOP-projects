/*Aplicatie pentru gestionarea zborurilor unei comparii*/
#include <iostream>
#include <string.h>

using namespace std;

class Zbor
{
protected:
    char ID[256];
    char oras[256];
    int zi;
    char dest[256];
    int d;  ///durata
    int pret;
public:
    Zbor()
    {

    }
    Zbor(char a[256], char b[25] = "", int c = 0, char dd[256] = "",
          int e = 0, int f = 0)
    {
        strcpy(ID, a);
        strcpy(oras, b);
        zi = c;
        strcpy(dest, dd);
        d = e;
        pret = f;
    }
    Zbor(const Zbor &a)
    {
        strcpy(ID, a.ID);
        strcpy(oras, a.oras);
        zi = a.zi;
        strcpy(dest, a.dest);
        d = a.d;
        pret = a.pret;
    }
    ~Zbor()
    {

    }
    Zbor &operator = (const Zbor &a)
    {
        if (this != &a)
        {
            strcpy(ID, a.ID);
            strcpy(oras, a.oras);
            zi = a.zi;
            strcpy(dest, a.dest);
            d = a.d;
            pret = a.pret;
        }
        return *this;
    }
    friend istream &operator >> (istream &i, Zbor &a);
    friend ostream &operator >> (ostream &o, Zbor &a);
    virtual void Afisare()
    {
        cout << ID << " " << zi << " " << oras << " " << dest;
        cout << " " << d << " " << pret << " ";
    }
    virtual void Citire()
    {
        cin >> *this;
    }
};

istream &operator >> (istream &i, Zbor &a)
{
    cout << "ID = ";
    i >> a.ID;
    cout << "Ziua = ";
    i >> a.zi;
    cout << "Oras = ";
    i >> a.oras;
    cout << "Destinatie = ";
    i >> a.dest;
    cout << "Durata zborului = ";
    i >> a.d;
    cout << "Pretul zborului = ";
    i >> a.pret;
    return i;
}

ostream &operator >> (ostream &o, Zbor &a)
{
    o << a.ID << " " << a.zi << " " << a.oras << " ";
    o << a.dest << " " << a.d << " " << a.pret;
    o << endl;
    return o;
}

class Zbor_Temp : public virtual Zbor
{
protected:
    int pa;
public:
    Zbor_Temp() : Zbor()
    {

    }
    Zbor_Temp(char a[256], char b[25] = "", int c = 0, char dd[256] = "",
              int e = 0, int f = 0, int g = 0) : Zbor(a, b, c, dd, e, f)
    {
        pa = g;
    }
    Zbor_Temp(const Zbor_Temp& a) : Zbor(a)
    {
        pa = a.pa;
    }
    ~Zbor_Temp() { }
    Zbor_Temp &operator = (const Zbor_Temp &a)
    {
        if (this != &a)
        {
            Zbor :: operator = (a);
            pa = a.pa;
        }
        return *this;
    }
    friend istream &operator >> (istream &i, Zbor_Temp &a);
    void Afisare()
    {
        Zbor :: Afisare();
        cout << pa;
    }
    void Citire()
    {
        cin >> *this;
    }
};

istream &operator >> (istream &i, Zbor_Temp &a)
{
    Zbor &aux = static_cast <Zbor &> (a);
    i >> aux;
    cout << "Zi expirare zbor temporar = ";
    i >> a.pa;
    return i;
}

class Zbor_Disc : public virtual Zbor
{
protected:
    int disc;
public:
    Zbor_Disc() : Zbor()
    {

    }
    Zbor_Disc(char a[256], char b[25] = "", int c = 0, char dd[256] = "",
               int e = 0, int f = 0, int g = 0) : Zbor(a, b, c, dd, e, f)
    {
        disc = g;
    }
    Zbor_Disc(const Zbor_Disc& a) : Zbor(a)
    {
        disc = a.disc;
    }
    ~Zbor_Disc() { }
    Zbor_Disc &operator = (const Zbor_Disc &a)
    {
        if (this != &a)
        {
            Zbor :: operator = (a);
            disc = a.disc;
        }
        return *this;
    }
    friend istream &operator >> (istream &i, Zbor_Disc &a);
    void Afisare()
    {
        Zbor :: Afisare();
        cout << disc;
    }
    void Citire()
    {
        cin >> *this;
    }
};

istream &operator >> (istream &i, Zbor_Disc &a)
{
    Zbor &aux = static_cast <Zbor &> (a);
    i >> aux;
    cout << "Discount = ";
    i >> a.disc;
    return i;
}

class Zbor_TD : public Zbor_Temp, public Zbor_Disc
{
public:
    Zbor_TD() : Zbor_Disc(), Zbor_Temp()
    {

    }
    Zbor_TD(char a[256], char b[25] = "", int c = 0, char dd[256] = "",
            int e = 0, int f = 0, int g = 0, int h = 0) :
            Zbor_Temp(a, b, c, dd, e, f, g), Zbor_Disc(a, b, c, dd, e, f, h)
    {

    }
    Zbor_TD(const Zbor_TD &a) : Zbor_Disc(a), Zbor_Temp(a)
    {

    }
    Zbor_TD &operator = (const Zbor_TD &a)
    {
        if (this != &a)
        {
            Zbor_Disc :: operator = (a);
            Zbor_Temp :: operator = (a);
        }
        return *this;
    }
    friend istream &operator >> (istream &i, Zbor_TD &a);

    void Afisare()
    {
        cout << ID << " " << zi << " " << oras << " " << dest;
        cout << " " << d << " " << pret << " ";
        cout << disc << " " << pa;
    }
    void Citire()
    {
        cin >> *this;
    }
};
istream &operator >> (istream &i, Zbor_TD &a)
{
    Zbor &aux = static_cast <Zbor &> (a);
    i >> aux;
    cout << "Zi expirare zbor temporar = ";
    i >> a.pa;
    cout << "Discount = ";
    i >> a.disc;
}

int main()
{
    Zbor **v;
    int n;
    cout << "numarul de zboruri = ";
    cin >> n;
    v = new Zbor*[n+1];
    cout << "1 -- Zbor" << endl <<  "2 -- Zbor cu discount" << endl;
    cout << "3 -- Zbor temporar" << endl << "4 -- Zbor temporar cu discount";

    for (int i = 1; i<=n; i++)
    {
        int tip;
        cout << endl << "tipul zborului = ";
        cin >> tip;
        if (tip == 1)
        {
            v[i] = new Zbor;
            v[i]->Citire();
        }
        else if (tip == 2)
        {
            v[i] = new Zbor_Disc;
            Zbor_Disc *a = dynamic_cast <Zbor_Disc*> (v[i]);
            v[i]->Citire();
        }
        else if (tip == 3)
        {
            v[i] = new Zbor_Temp;
            Zbor_Temp *a = dynamic_cast <Zbor_Temp*> (v[i]);
            v[i]->Citire();
        }
        else if (tip == 4)
        {
            v[i] = new Zbor_TD;
            Zbor_TD *a = dynamic_cast <Zbor_TD*> (v[i]);
            v[i]->Citire();
        }
        else
        {
            cout << endl << "Nu exista tipul de zbor ales." << endl;
            return 0;
        }
    }
    cout << endl << "Datele zborurilor inregistrate" << endl;
    for (int i = 1; i<= n; i++)
    {
        v[i]->Afisare();
        cout << endl;
    }
    return 0;
}
