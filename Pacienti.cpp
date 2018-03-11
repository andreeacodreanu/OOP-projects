#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

class Pacient
{
protected:
    char nume[256];
    int varsta;
    char adresa[256];
    int colesterol;
    int zi_colesterol;
public:
    Pacient(){ }
    Pacient(char a[256], int b, char c[256], int d, int e)
    {
        strcpy(nume, a);
        varsta = b;
        strcpy(adresa, c);
        colesterol = d;
        zi_colesterol = e;
    }
    ~Pacient(){ }
    Pacient(const Pacient &a)
    {
        strcpy(nume, a.nume);
        varsta = a.varsta;
        strcpy(adresa, a.adresa);
        colesterol = a.colesterol;
        zi_colesterol = a.zi_colesterol;
    }
    Pacient &operator = (const Pacient &a)
    {
        if (this != &a)
        {
            strcpy(nume, a.nume);
            varsta = a.varsta;
            strcpy(adresa, a.adresa);
            colesterol = a.colesterol;
            zi_colesterol = a.zi_colesterol;
        }
        return *this;
    }
    friend istream &operator >> (istream &i, Pacient &a);
    virtual void Afisare()
    {
        cout << nume << " " << varsta << " " << adresa << " " <<colesterol << " " << zi_colesterol << " ";
    }
    virtual void Citire() = 0;
    virtual int get_risc_cardio() = 0;
    int get_colesterol()
    {
        return colesterol;
    }
};

istream &operator >> (istream &i, Pacient &a)
{
    cout << "Nume = ";
    i >> a.nume;
    cout << "Varsta = ";
    i >> a.varsta;
    cout << "Adresa = ";
    i >> a.adresa;
    cout << "Colesterol = ";
    i >> a.colesterol;
    cout << "Ziua recolarii analizei = ";
    i >> a.zi_colesterol;
    return i;
}

class Adult_peste40 : public Pacient
{
    char fumator[3];
    char sedentarism[20];
public:
    Adult_peste40(){ }
    Adult_peste40(char a[256], int b, char c[256], int d, int e, char f[3], char g[20]) : Pacient(a, b, c, d, e)
    {
        strcpy(fumator, f);
        strcpy(sedentarism, g);
    }
    ~Adult_peste40(){ }
    Adult_peste40(const Adult_peste40 &a) : Pacient(a)
    {
        strcpy(fumator, a.fumator);
        strcpy(sedentarism, a.sedentarism);
    }
    Adult_peste40 &operator = (const Adult_peste40 &a)
    {
        Pacient :: operator=(a);
        if (this != &a)
        {
            strcpy(fumator, a.fumator);
            strcpy(sedentarism, a.sedentarism);
        }
        return *this;
    }

    friend istream &operator >> (istream &i, Adult_peste40 &a);

    void Citire()
    {
        cin >> *this;
    }

    void Afisare()
    {
        Pacient :: Afisare();
        cout << fumator << " " << sedentarism;
    }

    int get_risc_cardio()
    {
     Pacient &aux = static_cast <Pacient&> (*this);
     int val1 = 1, val2 = 1;
     if (strcmp(fumator, "da") == 1)
        val1 = 2;
    if (strcmp(sedentarism, "mediu") == 1)
        val2 = 2;
    else if (strcmp(sedentarism, "ridicat") == 1)
        val2 = 3;
     return aux.get_colesterol() * val1 * val2;
    }
};

istream &operator >> (istream &i, Adult_peste40 &a)
{
    Pacient &aux = static_cast <Pacient&> (a);
    i >> aux;
    cout << "Fumator (da/nu) = ";
    i >> a.fumator;
    cout << "Sedentarism (scazut/mediu/ridicat) = ";
    i >> a.sedentarism;
    return i;
}

class Adult_sub40 : public Pacient
{
public:
    Adult_sub40(){ }
    Adult_sub40(char a[256], int b, char c[256], int d, int e) : Pacient(a, b, c, d, e)
    { }
    ~Adult_sub40(){ }
    Adult_sub40(const Adult_sub40 &a) : Pacient(a)
    { }
    Adult_sub40 &operator = (const Adult_sub40 &a)
    {
        Pacient :: operator = (a);
        return *this;
    }

    friend istream &operator >> (istream &i, Adult_sub40 &a);

    void Citire()
    {
        cin >> *this;
    }

    void Afisare()
    {
        Pacient :: Afisare();
    }

    int get_risc_cardio()
    {
        Pacient &aux = static_cast <Pacient&> (*this);
        return aux.get_colesterol();
    }
};

istream &operator >> (istream &i, Adult_sub40 &a)
{
    Pacient &aux = static_cast <Pacient&> (a);
    i >> aux;
    return i;
}

class Copil : public Pacient
{
    int proteinaC;
    int zi_proteinaC;
    char antecedente[3];
public:
    Copil() { }
    Copil(char a[256], int b, char c[256], int d, int e, int f, int g, char h[3]) : Pacient(a, b, c, d, e)
    {
        proteinaC = f;
        zi_proteinaC = g;
        strcpy(antecedente, h);
    }
    ~Copil() { }
    Copil(const Copil &a) : Pacient(a)
    {
        proteinaC = a.proteinaC;
        zi_proteinaC = a.zi_proteinaC;
        strcpy(antecedente, a.antecedente);
    }
    Copil &operator = (Copil &a)
    {
        Pacient :: operator = (a);
        if (this != &a)
        {
            proteinaC = a.proteinaC;
            zi_proteinaC = a.zi_proteinaC;
            strcpy(antecedente, a.antecedente);
        }
        return *this;
    }

    friend istream &operator >> (istream &i, Copil &a);

    void Citire()
    {
        cin >> *this;
    }

    void Afisare()
    {
        Pacient :: Afisare();
        cout << proteinaC << " " << zi_proteinaC << " " << antecedente;
    }

    int get_risc_cardio()
    {
        return 0 ;
    }
};

istream &operator >> (istream &i, Copil &a)
{
    Pacient &aux = static_cast <Pacient&> (a);
    i >> aux;
    //i >> a.nume >> a.varsta >> a.adresa >> a.colesterol >> a.zi_colesterol;
    cout << "Proteina C = ";
    i >> a.proteinaC;
    cout << "Zi recoltare proteina C = ";
    i >> a.zi_proteinaC;
    cout << "Antecedente = ";
    i >> a.antecedente;
    return i;
}

int main()
{
    Pacient **P;
    int n;
    cout << "introduceti numarul de pacienti = ";
    cin >> n;
    P = new Pacient*[n+1];

    cout << "1 -- Adult peste 40 de ani" << endl;
    cout << "2 -- Adult sub 40 de ani" << endl;
    cout << "3 -- Copli" << endl;

    for (int i = 1; i <= n; i++)
    {
        int tip;
        cout << "tip = ";
        cin >> tip;
        if (tip == 1)
        {
            P[i] = new Adult_peste40;
            dynamic_cast <Adult_peste40*>(P[i]);
            P[i]->Citire();
            //cout << "risc cardio " << P[i].get_risc_cardio();
        }
        else if (tip == 2)
        {
            P[i] = new Adult_sub40;
            dynamic_cast <Adult_sub40*>(P[i]);
            P[i]->Citire();
        }
        else if (tip == 3)
        {
            P[i] = new Copil;
            dynamic_cast <Copil*>(P[i]);
            P[i]->Citire();
        }
        else exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= n; i++)
    {
        P[i]->Afisare();
        cout << endl;
    }
    return 0;
}
