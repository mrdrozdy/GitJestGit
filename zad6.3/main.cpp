#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <locale.h>

using namespace std;

struct student
{
    string imie;
    string nazwisko;
    int punkty;
};

void sortuj(int *&tabs, int n);
int wczytajStudentow(student*&tab);
void usunTabliceStudentow(student *&tab);
void wyswietlStudentow(student* tab, int n, int poczatek);
int wyszukiwanieLiniowe(student *&tab, int *&tabs, int n, int wartosc);
void sortowanieQuickSort(student* tab, int lewy, int prawy, int tryb);
int wyszukiwanieBisekcyjne(student *&tab, int *&tabs, int n, int wartosc);


int main()
{
    setlocale(LC_CTYPE, "Polish");
    int tryb=0, ldd=0, p=0, nmb=0, *tabs, studenci;
    student* tab;
    while(tryb!=-1)
    {
        cout<<"..............................."<<endl;
        cout<<" Prosze wybrac zadanie:\n 1: zadanie 7.1\n 2: zadanie 7.2\n 3: zadanie 7.3\n\n -1: opusc program"<<endl;
        cout<<"\n Tryb: ";
        cin>>tryb;
        cout<<"..............................."<<endl<<endl;
        if(tryb==-1)
        {
            cout<<"Opuszczono program :(.\n"<<endl;
            if(p!=0)
            {
                usunTabliceStudentow(tab);
            }
            return 0;
        }
        else if(tryb==1)
        {
            nmb=wczytajStudentow(tab);
            cout<<"Wczytano dokument studenci.csv.\n"<<endl;
            ldd=1, p=1;
        }
        else if(tryb==2 && ldd==1)
        {
            wyswietlStudentow(tab, nmb, 0);
            int pkt=0;
            cout<<"\nProszê podaæ próg punktowy: ";
            cin>>pkt;
            studenci=wyszukiwanieLiniowe(tab, tabs, nmb, pkt);
            if(studenci==-1)
            {
                cout<<"Brak studentów o podanej liczbie punktów.\n"<<endl;
            }
            else
            {
                cout<<"Studenci posiadaj¹cy liczbê punktów równ¹ "<<pkt<<":\n"<<endl;
                cout<<"|-----------|---------------|"<<endl;
                cout<<"|Imie       |Nazwisko       |"<<endl;
                cout<<"|-----------|---------------|"<<endl;
                for(int i=0; i<studenci; i++)
                {
                    cout<<"|";
                    cout<<tab[tabs[i]].imie;
                    for(int j=0; j<11-tab[tabs[i]].imie.length(); j++)
                    {
                        cout<<" ";
                    }
                    cout<<"|";
                    cout<<tab[tabs[i]].nazwisko;
                    for(int j=0; j<15-tab[tabs[i]].nazwisko.length(); j++)
                    {
                        cout<<" ";
                    }
                    cout<<"|";
                    cout<<endl;
                }
                cout<<"|-----------|---------------|"<<endl;
            }
            delete[] tabs;
            tabs = nullptr;
        }
        else if(tryb==3 && ldd==1)
        {
            sortowanieQuickSort(tab, 0, nmb-1, 0);
            wyswietlStudentow(tab, nmb, 0);
            int pkt=0;
            cout<<"\nProszê podaæ próg punktowy: ";
            cin>>pkt;
            studenci=wyszukiwanieBisekcyjne(tab, tabs, nmb, pkt);
            //studenci = wyszukiwanieBisekcyjne(tab, tabs, 0, nmb-1, pkt);
            if(studenci==-1)
            {
                cout<<"Brak studentów o podanej liczbie punktów.\n"<<endl;
            }
            else
            {
                sortuj(tabs, studenci);
                cout<<"Studenci posiadaj¹cy liczbê punktów równ¹ "<<pkt<<":\n"<<endl;
                cout<<"|-----------|---------------|"<<endl;
                cout<<"|Imie       |Nazwisko       |"<<endl;
                cout<<"|-----------|---------------|"<<endl;
                for(int i=0; i<studenci; i++)
                {
                    cout<<"|";
                    cout<<tab[tabs[i]].imie;
                    for(int j=0; j<11-tab[tabs[i]].imie.length(); j++)
                    {
                        cout<<" ";
                    }
                    cout<<"|";
                    cout<<tab[tabs[i]].nazwisko;
                    for(int j=0; j<15-tab[tabs[i]].nazwisko.length(); j++)
                    {
                        cout<<" ";
                    }
                    cout<<"|";
                    cout<<endl;
                }
                cout<<"|-----------|---------------|"<<endl;
                ofstream zapis;
                string sciezkaDoZapisu="wyniki.csv";
                zapis.open(sciezkaDoZapisu);

                zapis<<studenci<<endl;
                for(int i=0; i<studenci; i++)
                {
                    zapis<<tab[tabs[i]].imie<<";"<<tab[tabs[i]].nazwisko<<";";
                    zapis<<tab[tabs[i]].punkty<<endl;
                }
                zapis.close();
                cout<<"Zapisano rekordy do pliku wyniki.csv"<<endl;
                //cout<<tab[tabs[i]].imie<<" "<<tab[tabs[i]].nazwisko<<endl;
            }
            delete[] tabs;
            tabs = nullptr;
        }
        else if(ldd==1)
        {
            cout<<"Brak zadania o podanej cyfrze.\n"<<endl;
            continue;
        }
        else if(ldd==0)
        {
            cout<<"Nie wczytano dokumentu.\n"<<endl;
        }
    }
    wczytajStudentow(tab);
    usunTabliceStudentow(tab);
    return 0;
}

void sortuj(int *&tabs, int n)
{
    for(int i = 0; i < n; i++)
            {
                for(int j = 1; j < n - i; j++)
                {
                    if(tabs[j-1] > tabs[j])
                    {
                        swap(tabs[j-1], tabs[j]);
                    }
                }
            }
}
int wczytajStudentow(student*&tab)
{
    string sciezka,linia,pomoc;
    int liczbaStudentow;
    ifstream plik;
    char sredniki;
    sciezka="studenci.csv";
    plik.open(sciezka);
    plik >> liczbaStudentow;
    tab = new struct student[liczbaStudentow];
    for(int i = 0; i < 2; i++)
    plik >> sredniki;

    for(int i=0; i<liczbaStudentow; i++)
    {
        plik>>linia;
        stringstream ss(linia);
        getline(ss, tab[i].imie, ';');
        getline(ss, tab[i].nazwisko, ';');
        getline(ss, pomoc);
        tab[i].punkty=atoi(pomoc.c_str());
    }

    plik.close();
    return liczbaStudentow;
}

void usunTabliceStudentow(student *&tab)
{
    delete[] tab;
    tab = nullptr;
}

void wyswietlStudentow(student* tab, int n, int poczatek)
{
    cout<<"|-----------|---------------|-------------|"<<endl;
    cout<<"|Imie       |Nazwisko       |Punkty       |"<<endl;
    cout<<"|-----------|---------------|-------------|"<<endl;
    for(int i=poczatek; i<n; i++)
    {
        cout<<"|";
        cout<<tab[i].imie;
        for(int j=0; j<11-tab[i].imie.length(); j++)
        {
            cout<<" ";
        }
        cout<<"|";
        cout<<tab[i].nazwisko;
        for(int j=0; j<15-tab[i].nazwisko.length(); j++)
        {
            cout<<" ";
        }
        cout<<"|";
        cout<<tab[i].punkty;
        for(int j=0; j<13-to_string(tab[i].punkty).length(); j++)
        {
            cout<<" ";
        }
        cout<<"|";
        cout<<endl;
    }
    cout<<"|-----------|---------------|-------------|"<<endl;
}

int wyszukiwanieLiniowe(student *&tab, int *&tabs, int n, int wartosc)
{
    int licz=0, i=0;
    tabs = new int[n];
    while(i<n)
    {
        if(tab[i].punkty==wartosc)
        {
            tabs[licz]=i;
            licz++;
        }
        i=i+1;
    }
    if(licz==0)
    {
        return -1;
    }
    else
    {
        return licz;
    }
}

void sortowanieQuickSort(student* tab, int lewy, int prawy, int tryb)
{
    int srodek;
    struct student piwot;
    int granica;
    int i;
    srodek=(int)(lewy+prawy)/2;
    piwot=tab[srodek];
    tab[srodek]=tab[prawy];
    granica=lewy;
    i=lewy;
    while(i<prawy)
    {
        if(tryb==0)
        {
                if(tab[i].punkty<piwot.punkty)
                {
                    swap(tab[granica], tab[i]);
                    granica=granica+1;
                }
                i=i+1;
        }
        else if(tryb==1)
        {
                if(tab[i].punkty>piwot.punkty)
                {
                    swap(tab[granica], tab[i]);
                    granica=granica+1;
                }
                i=i+1;
        }
    }
    tab[prawy]=tab[granica];
    tab[granica]=piwot;
    if(lewy<granica-1)
    {
        sortowanieQuickSort(tab, lewy, granica-1, tryb);
    }
    if(granica+1<prawy)
    {
        sortowanieQuickSort(tab, granica+1, prawy, tryb);
    }
}


int wyszukiwanieBisekcyjne(student *&tab, int *&tabs, int n, int wartosc)
{
    tabs = new int[n];
    int licz = 0, lewy = 0, srodek, g;
    int prawy = n-1;
    while(lewy <= prawy)
    {
        srodek = (int)(lewy+prawy)/2;
        if(tab[srodek].punkty == wartosc)
        {
            g = 0;
            while(tab[srodek - g].punkty == wartosc)
            {
                tabs[licz] = srodek - g, licz++, g++;
            }
            g = 1;
            while(tab[srodek + g].punkty == wartosc)
            {
                tabs[licz] = srodek + g, licz++, g++;
            }
            break;
        }
        else
        {
            if(wartosc < tab[srodek].punkty)
            {
                prawy = srodek-1;
            }
            else
            {
                lewy = srodek+1;
            }
        }
    }
    if(licz==0)
    {
        return -1;
    }
    else
    {
        return licz;
    }
}

