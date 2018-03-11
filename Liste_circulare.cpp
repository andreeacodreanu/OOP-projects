#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("date.in");

class Nod
{
    int info;
    Nod *urm;

public:
    friend class Lista;
    int get_info()
    {
        return info;
    }
    void set_info(int a)
    {
        info = a;
    }
    Nod* get_urm()
    {
        return urm;
    }
    void set_urm(Nod*a)
    {
        urm = a;
    }
    Nod()
    {
        urm = NULL;
    }
    ~Nod() { }
};

class Lista
{
    Nod *prim;
    Nod *ultim;
    int nr_elem;

public:

    Lista()
    {
        prim = NULL;
    }
    ~Lista() { }
    Nod* get_prim(){return prim;}
    void creare(); //crearea listei
    void inserare(int x); //inserarea elementului x in lista
    void afisare(); //afisarea listei
    void stergere(Nod*p, int k); //stergerea elementului de pe pozitia k
    void eliminare_k(int k); //eliminarea din k in k
    void inversare_leg(); //inversarea legaturilor
};

void Lista :: inserare(int x)
{
    Nod *p;
    p = new Nod;
    p->info = x;
    if (prim == NULL)
    {
        prim = p;
        ultim = p;
    }
    else
    {
        ultim->urm = p;
        ultim = p;
    }
}

void Lista :: creare()
{
    int i, x;
    fin >> nr_elem;
    for (i = 1; i <= nr_elem; i++)
    {
        fin >> x;
        inserare (x);
    }
    ultim->urm = prim;
}

void Lista :: afisare()
{
    Nod *p;
    p = prim;
    int i;
    for (i = 1; i <= nr_elem; i++)
    {
        cout << p->get_info() << " ";
        p = p->urm;
    }
    cout << endl;
}

void Lista :: stergere(Nod* p,int k)
{
    Nod *r;
    r = p;
    if (k > nr_elem)
        return;
    if (k == 1)
    {
        ultim->urm = prim->urm;
        cout << "S-a eliminat nodul cu valoarea " << prim->info << endl;
        delete prim;
        prim = ultim->urm;
    }
    else
    {
        int i = k;
        while (i > 2)
        {
            r = r->urm;
            i--;
        }
        Nod* c;
        c = r->urm;
        r->urm = c->urm;
        cout << "S-a eliminat nodul cu valoarea " << c->info << endl;
        delete c;
        if (k == nr_elem)
        {
            ultim = r;
        }
    }
    nr_elem--;
}

void Lista :: eliminare_k(int k)
{
    stergere(prim, k);
    Nod *r = prim;
    while (nr_elem > 1)
    {
        for (int i = 1; i < k; i++)
            r = r->urm;
        stergere(r, k);
    }
    cout << r->urm->info;
}

void Lista :: inversare_leg()
{
    Nod* r = prim;
    Nod* p = r->urm;
    Nod* q = p->urm;
    for (int i = 1; i < nr_elem; i++)
    {
        p->urm = r;
        r = p;
        p = q;
        q = q->urm;
    }
    r = prim;
    prim = ultim;
    ultim = r;
}

int main()
{
    Lista L;
    L.creare();

    cout << "MENIU" << endl << endl;
    cout << "TASTA 1 - afisare lista" << endl;
    cout << "TASTA 2 - inversare legaturi" << endl;
    cout << "TASTA 3 - stergerea elementului de pe pozitia k" << endl;
    cout << "TASTA 4 - eliminare din k in k" << endl << endl;
    cout << "Introduceti optiunea: ";

    int x, k;
    cin >> x;

    Nod* N = L.get_prim();

    switch (x)
    {
    case 1:
        L.afisare();
        break;

    case 2:
        L.inversare_leg();
        L.afisare();
        break;

    case 3:
        cout << "k = ";
        cin >> k;
        L.stergere(N, k);
        L.afisare();
        break;

    case 4:
        cout << "k = ";
        cin >> k;
        L.eliminare_k(k);
        break;
    default: return 0;
    }
    return 0;
}
