#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

//deklaracja podstawowego typu danych przechowywanego w elemencie struktury
struct ListElement
{
    ListElement * next, * prev;
    int klucz;
};

//deklaracja typu klasy listy
class DList
{
    private:
        //front to adres pierwszego elementu listy
        //back natomiast jest adresem ostatniego elemntu listy
        ListElement * front, * back;
        //licznik elementów na liscie
        unsigned licz;

    public:

        //konstruktor inicjujacy pola prywatne
        DList()
        {
            front = back = NULL;
            licz = 0;
        }

        //destruktor usuwajacy elementy listy
        ~DList()
        {
            ListElement * p;
            while(front)
            {
                p = front -> next;
                delete front;
                front = p;
            }
        }

        //funkcja zwracajaca rozmiar listy
        unsigned size()
        {
            return licz;
        }

        //funkcja umieszczajaca element na poczatku listy
        ListElement * push_front(ListElement * p)
        {
            p -> next = front;
            p -> prev = NULL;
            if(front)
            {
                front -> prev = p;
            }
            front = p;
            if(!back)
            {
                back = front;
            }
            licz++;
            return front;
        }

        //funkcja umieszczajaca element na koncu listy
        ListElement * push_back(ListElement * p)
        {
            if(back)
            {
                back -> next = p;
            }
            p -> next = NULL;
            p -> prev = back;
            back = p;
            if(!front)
            {
                front = back;
            }
            licz++;
            return back;
        }

        //funkcja umieszczajaca na liscie emelent p1 za elementem p2
        ListElement * insert(ListElement * p1, ListElement * p2)
        {
            p1 -> next = p2 -> next;
            p1 -> prev = p2;
            p2 -> next = p1;
            if(p1 -> next)
            {
                p1 -> next -> prev = p1;
            }
            else
            {
                back = p1;
            }
            licz++;
            return p1;
        }

        //funkcja pobierajaca element z poczatku listy
        ListElement * pop_front()
        {
            ListElement * p;
            if(front)
            {
                p = front;
                front = front -> next;
                if(!front)
                {
                    back = NULL;
                }
                else
                {
                    front -> prev = NULL;
                }
                licz--;
                return p;
            }
            else return NULL;
        }

        //funkcja pobierajaca element z konca listy
        ListElement * pop_back()
        {
            ListElement * p;
            if(back)
            {
                p = back;
                back = back -> prev;
                if(!back)
                {
                    front = NULL;
                }
                else
                {
                    back -> next = NULL;
                }
                licz--;
                return p;
            }
            else return NULL;
        }

        //funkcja usuwajaca element z listy
        ListElement * erase(ListElement * p)
        {
            if(p -> prev)
                p -> prev -> next = p -> next;
            else
            {
                front = p -> next;
            }
            if(p -> next)
                p -> next -> prev = p -> prev;
            else
            {
                back = p -> prev;
            }
            licz--;
            return p;
        }

        //funkcja wyszukujaca n-ty element
        ListElement * index(unsigned n)
        {
            ListElement * p;
            if((!n) || (n > licz))
            {
                return NULL;
            }
            else if(n == licz)
            {
                return back;
            }
            else if(n < licz / 2)
            {
                p = front;
                while(--n)
                {
                    p = p -> next;
                }
                return p;
            }
            else
            {
                p = back;
                while(licz > n++)
                {
                    p = p -> prev;
                }
                return p;
            }
        }

        //funkcja wyszukujaca n-ty element
        void szukaj(unsigned n)
        {
            ListElement * p;
            if(!n || n > licz)
            {
                cout << "Podany element nie istnieje!" << endl;
            }
            else if(n == licz)
            {
                cout << back -> klucz << endl;
            }
            else if(n < licz / 2)
            {
                p = front;
                while(--n)
                {
                    p = p -> next;
                }
                cout << p -> klucz << endl;
            }
            else
            {
                p = back;
                while(licz > n++)
                {
                    p = p -> prev;
                }
                cout << p -> klucz << endl;
            }
        }

        //funkcja wyswietlajaca liste
        void showEl()
        {
            ListElement * p;
            if(!front)
            {
                cout << "The list is empty!" << endl;
            }
            else
            {
                p = front;
                while(p){
                    cout << p -> klucz << " ";
                    p = p -> next;
                }
                cout << endl;
            }
        }

        //funkcja wyswietlajaca rozmiar listy
        void rozmiar()
        {
            cout << "Aktualny rozmiar listy to: " << licz << endl;
        }
};

int main()
{
    setlocale(0, "");
    DList dl;
    ListElement * p;
    int i;
    srand( time( NULL ) );

    cout << "1) : ";    dl.showEl();

    //program losuje ile elementow doda na poczatku listy (2-12), nastepnie wypelnia liste losowymi numerami (1-20)
    int N = 2 + rand()%11;
    for(i = 1; i <= N; i++)
    {
        p = new ListElement;
        p -> klucz = 1 + rand()%21;;
        dl.push_front(p);
    }

    cout << "2) : ";    dl.showEl();

    //program losuje ile elementow doda na koniec listy (2-12), nastepnie wypelnia liste losowymi numerami (1-20)
    int N1 = 2 + rand()%11;
    for(i = 1; i <= N1; i++)
    {
        p = new ListElement;
        p -> klucz = 1 + rand()%21;
        dl.push_back(p);
    }

    cout << "3) : ";    dl.showEl();

    //program usunie pierwszy element z listy
    dl.pop_front();

    cout << "4) : ";    dl.showEl();

    //program usunie ostatni element z listy
    dl.pop_back();

    cout << "5) : ";    dl.showEl();

    //program doda nowy element za wybranym elementem
    p = new ListElement;
    int N2;
    cout << "Podaj liczbe, ktora chcesz dopisac:";
    cin >> p -> klucz;
    cout << "Podaj, za ktorym elementem listy chcesz go umiescic:";
    cin >> N2;
    while(N2 <0)
    {
        cout << "Podano nieprawidlowa wartosc! Sprobuj ponownie:";
        cin >> N2;
    }
    dl.insert(p, dl.index(N2));

    cout << "6) : ";    dl.showEl();

    //program usunie wybrany element z listy
    int N3;
    cout << "Podaj ktory element chcesz usunac:";
    cin >> N3;
    while(N3 <= 0)
    {
        cout << "Podano niepoprawna wartosc! Sprobuj ponownie:";
        cin >> N3;
    }
    delete dl.erase(dl.index(N3));

    cout << "7) : ";    dl.showEl();

    //wyszukujemy element listy i wyswietlamy jego zawartosc
    int N4;
    cout << "Podaj element listy ktory chcesz wyszukac:";
    cin >> N4;

    cout << "8) : ";    dl.szukaj(N4);

    //program ususnie przedostatni element z listy
    delete dl.erase(dl.index(dl.size() - 1));

    cout << "9) : ";    dl.showEl();

    //w zaleznosci od odpowiedzi na pytanie program wyswietli rozmiar listy lub nie
    char odp;
    cout << "Czy program ma wyswietlic rozmiar listy?(T|t/N|n):";
    cin >> odp;
    int znak = int(odp);

    while(znak != 78 && znak != 84 && znak != 110 && znak != 116)
    {
        cout << "Podano nieprawidlowy znak! Sprobuj ponownie:";
        cin >> odp;
        znak = int(odp);
    }
    if(znak == 84 || znak == 116)
    {
        cout << "10) : ";    dl.rozmiar();
    }
    else if(znak == 78 || znak == 110)
    {
        cout << "10) : ////////////////////" << endl;
    }

    //program wyczysci cala liste (usunie jej wszystkie elementy)
    while(dl.size())
    {
        dl.pop_front();
    }
    cout << "11) : ";   dl.showEl();

    system("PAUSE");
}
