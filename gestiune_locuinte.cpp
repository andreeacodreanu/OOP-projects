/*Se doreste implementarea unei aplicatii care sa permita gestionarea clientilor 
si a proprietatilor imobiliare in cadrul unei agentii imobiliare nou infiintate.*/
#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>

using namespace std;

ifstream f("date.in");

class Locuinta
{
protected:
    char *numeClient;
    int suprafataUtila;
    float discount;
public:
    Locuinta()
    {
        numeClient = NULL;
        suprafataUtila = 0;
        discount = 0;
    }
    Locuinta(char *a, int b, float c)
    {
        numeClient = new char[strlen(a)+1];
        strcpy (numeClient, a);
        suprafataUtila = b;
        discount = c;
        try
        {
            if (b < 0)
                throw b;
        }
        catch (int b)
        {
            cout << "Suprafata utila trebuie sa fie pozitia." << endl;
        }
    }
    Locuinta(const Locuinta& a)
    {
        numeClient = new char[strlen(a.numeClient)+1];
        strcpy (numeClient, a.numeClient);
        suprafataUtila = a.suprafataUtila;
        discount = a.discount;
    }
    virtual ~Locuinta()
    {
        delete numeClient;
        suprafataUtila = 0;
        discount = 0;
    }
    Locuinta &operator = (Locuinta &a)
    {
        numeClient = new char[strlen(a.numeClient)+1];
        strcpy (numeClient, a.numeClient);
        suprafataUtila = a.suprafataUtila;
        discount = a.discount;
        return *this;
    }

    virtual void Afisare()
    {
        cout << numeClient << "    " << suprafataUtila << "    " << discount;
        cout << endl;
    }
    friend ifstream& operator >> (ifstream& i, Locuinta& a);

    virtual float CalculChirie(int X, int Y)
    {
        return 0;
    }

    operator int() const
    {
        return discount;
    }

    virtual void Citire()
    {
        f >> *this;
    }
    virtual void Tip() = 0;

};

ifstream& operator >> (ifstream& i, Locuinta& a)
{
    char aux[100];
    i >> aux;
    a.numeClient = new char[strlen(aux)+1];
    strcpy(a.numeClient, aux);
    i >> a.suprafataUtila;
    i >> a.discount;

    return i;
}

class Apartament : public Locuinta
{
    int etaj;
public:
    Apartament(int a = 0) : Locuinta()
    {
        etaj = a;
        try
        {
            if (a < 0)
                throw a;
        }
        catch (int a)
        {
            cout << "Etajul trebuie sa fie pozotiv." << endl;
        }
    }
    Apartament(char* a, int b, float c, int d) : Locuinta(a, b, c)
    {
        etaj = d;
        try
        {
            if (d < 0)
                throw d;
        }
        catch (int d)
        {
            cout << "Etajul trebuie sa fie pozotiv." << endl;
        }
    }
    Apartament(const Apartament& a)
    {
        numeClient = new char[strlen(a.numeClient)+1];
        strcpy (numeClient, a.numeClient);
        suprafataUtila = a.suprafataUtila;
        discount = a.discount;
        etaj = a.etaj;
    }
    ~Apartament()
    {
        etaj = 0;
    }
    Apartament &operator = (Apartament &a)
    {
        numeClient = new char[strlen(a.numeClient)+1];
        strcpy (numeClient, a.numeClient);
        suprafataUtila = a.suprafataUtila;
        discount = a.discount;
        etaj = a.etaj;
        return *this;
    }

    void Afisare()
    {
        cout << numeClient << "    " << suprafataUtila << "    " << discount;
        cout << "    " << etaj << endl;
    }

    friend ifstream& operator >> (ifstream& i, Apartament& a);

    float CalculChirie(int X, int Y)
    {
        return X * suprafataUtila * (1- Y * discount/100.0);
    }
    void Citire()
    {
        f >> *this;
    }
    void Tip()
    {
        cout << "Apartament" << endl;
    }
};

ifstream& operator >> (ifstream& i, Apartament& a)
{
    char aux[100];
    i >> aux;
    a.numeClient = new char[strlen(aux)+1];
    strcpy(a.numeClient, aux);
    i >> a.suprafataUtila;
    i >> a.discount;
    i >> a.etaj;

    return i;
}

class Casa : public Locuinta
{
    int suprafataCurte;
    int nrEtaje;
    float suprafataEtaje;
public:
    Casa(int a = 0, int b = 0, float c = 0) : Locuinta()
    {
        suprafataCurte = a;
        nrEtaje = b;
        suprafataEtaje = c;
    }
    Casa(char* a, int b = 0, float c = 0, int d = 0, int e = 0, float f = 0) : Locuinta(a, b, c)
    {
        suprafataCurte = d;
        nrEtaje = e;
        suprafataEtaje = f;
        try
        {
            if (d < 0)
                throw d;
            if (e < 0)
                throw e;
            if (f < 0)
                throw f;
        }
        catch (int d)
        {
            cout << "Suprafata curtii trebuie sa fie pozotiva." << endl;
        }
        catch (int e)
        {
            cout << "Numarul etajelor trebuie sa fie pozitiv." << endl;
        }
        catch (int f)
        {
            cout << "Suprafata etajelor trebuie sa fie pozitiva." << endl;
        }
    }
    Casa(const Casa& a)
    {
        numeClient = new char[strlen(a.numeClient)+1];
        strcpy (numeClient, a.numeClient);
        suprafataUtila = a.suprafataUtila;
        discount = a.discount;
        suprafataCurte = a.suprafataCurte;
        nrEtaje = a.nrEtaje;
        suprafataEtaje = a.suprafataEtaje;
    }
    ~Casa()
    {
        suprafataCurte = 0;
        nrEtaje = 0;
        suprafataEtaje = 0;
    }
    Casa &operator = (Casa &a)
    {
        numeClient = new char[strlen(a.numeClient)+1];
        strcpy (numeClient, a.numeClient);
        suprafataUtila = a.suprafataUtila;
        discount = a.discount;
        suprafataCurte = a.suprafataCurte;
        nrEtaje = a.nrEtaje;
        suprafataEtaje = a.suprafataEtaje;
        return *this;
    }

    void Afisare()
    {
        cout << numeClient << "    " << suprafataUtila << "    " << discount;
        cout << "    " << suprafataCurte << "    " << nrEtaje << "    ";
        cout << suprafataEtaje << endl;
    }

    friend ifstream& operator >> (ifstream& i, Casa& a);

    float CalculChirie(int X, int Y)
    {
        return X * (suprafataUtila + 0.2 * suprafataCurte) * (1 - Y * discount/100.0);
    }
    void Citire()
    {
        f >> *this;
    }
    void Tip()
    {
        cout << "Casa " << endl;
    }
};

ifstream& operator >> (ifstream& i, Casa& a)
{
    char aux[100];
    i >> aux;
    a.numeClient = new char[strlen(aux)+1];
    strcpy(a.numeClient, aux);
    i >> a.suprafataUtila;
    i >> a.discount;
    i >> a.suprafataCurte;
    i >> a.nrEtaje;
    i >> a.suprafataEtaje;

    return i;
}

template <class T>
class Gestiune
{
    Locuinta **L;
    int nr_loc;
    T id;
    static int index;
public:
    Gestiune(int x = 1)
    {
        try
        {
            L = new Locuinta*[x+1];
        }
        catch (bad_alloc t)
        {
            cout << "Nu s-a putut aloca memorie." << endl;
            exit(EXIT_FAILURE);
        }
        try
        {
            if (x < 0)
                throw x;
        }
        catch (int x)
        {
            cout << "Nr loc trebuie sa fie pozitiv." << endl;
        }
        nr_loc = x;
        index++;
    }
    ~Gestiune()
    {
        if (L != NULL)
            delete []L;
        nr_loc = 0;
        index--;
    }
    Gestiune operator += (Locuinta &a)
    {
        nr_loc++;
        L[nr_loc] = &a;
        return *this;

    }
    void citire()
    {
        cout << "Se vor adauga " << nr_loc << " locuinte." << endl;

        for (int i = 1; i <= nr_loc; i++)
        {
            int ac;
            cout << "Tip = ";
            cin >> ac;
            try
            {
                if (ac == 1)
                {
                    L[i] = new Apartament;
                    Apartament *a = dynamic_cast <Apartament*>(L[i]);
                    L[i]->Citire();
                }
                else if (ac == 2)
                {
                    L[i] = new Casa;
                    Casa *d = dynamic_cast <Casa*>(L[i]);
                    L[i]->Citire();
                }
                else throw ac;
            }
            catch (int x)
            {
                cout << "Tip inexistent" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    void afisare()
    {
        for (int i = 1; i <= nr_loc; i++)
        {
            L[i]->Tip();
            L[i]->Afisare();
        }
    }
    static void get_index()
    {
        cout << "index = " << Gestiune :: index << endl;
    }
    int get_nr_loc()
    {
        return nr_loc;
    }
};

template <class T>
int Gestiune <T> :: index = 0;

template <>
class Gestiune <char*>
{
    Locuinta **L;
    int nr_loc;
    int nr_clienti;
    char **nume;
    static int index;
public:
    Gestiune(int x = 1)
    {
        try
        {
            L = new Locuinta*[x+1];
        }
        catch (bad_alloc t)
        {
            cout << "Nu s-a putut aloca memorie" << endl;
            exit(EXIT_FAILURE);
        }
        try
        {
            if (x < 0)
                throw x;
        }
        catch (int x)
        {
            cout << "Nr loc trebuie sa fie pozitiv." << endl;
        }
        nr_loc = x;
        index++;
        nr_clienti = 0;
        nume = new char*[nr_clienti+1];
    }
    ~Gestiune()
    {
        if (L != NULL)
            delete []L;
        if (nume != NULL)
            delete []nume;
        nr_loc = 0;
        nr_clienti = 0;
        index--;
    }
    Gestiune operator += (Locuinta &a)
    {
        nr_loc++;
        L[nr_loc] = &a;
        return *this;

    }
    void citire()
    {
        cout << "Se vor adauga " << nr_loc << " locuinte." << endl;
        for (int i = 1; i <= nr_loc; i++)
        {
            int ac;
            cout << "Tip = ";
            cin >> ac;
            try
            {
                if (ac == 1)
                {
                    L[i] = new Apartament;
                    Apartament *a = dynamic_cast <Apartament*>(L[i]);
                    L[i]->Citire();
                }
                else if (ac == 2)
                {
                    L[i] = new Casa;
                    Casa *a = dynamic_cast <Casa*>(L[i]);
                    L[i]->Citire();
                }
                else throw ac;
            }
            catch (int x)
            {
                cout << "Tip inexistent" << endl;
                exit(EXIT_FAILURE);
            }
        }
        cout << "Numar clienti: ";
        cin >> nr_clienti;
        for (int i = 1; i <= nr_clienti; i++)
        {
            char *s;
            cout << "Dati nume: ";
            cin >> s;
            nume[i] = new char[strlen(s)+1];
            strcpy(nume[i], s);
        }
    }
    void afisare()
    {
        for (int i = 1; i <= nr_loc; i++)
        {
            L[i]->Afisare();
        }
        cout << "Clientii sunt: " << endl;
        for (int i = 1; i <= nr_clienti; i++)
            cout << nume[i] << endl;
    }
    static void get_index()
    {
        cout << "index = " << Gestiune :: index << endl;
    }
};

int Gestiune <char*> :: index = 0;

int main()
{
    cout << "Apartament --> TASTA 1" << endl;
    cout << "Casa --> TASTA 2" << endl;
    cout << "--citirea datelor despre locuinte se va face din fisier--" << endl;
    Gestiune <char*> A;
    Gestiune <int> B(3);

    A.citire();
    A.afisare();

    B.citire();
    B.afisare();

    return 0;
}
