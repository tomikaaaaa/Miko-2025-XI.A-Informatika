#include <iostream>
#include <cstdlib>

using namespace std;

struct Lista
{
    int adat;
    Lista *next;
    Lista(int adat)
    {
        this->adat = adat;
        this->next = NULL;
    }
    ~Lista()
    {
        if(this->next) delete this->next;
    }
    void felfuz(int adat)
    {
        if(this->next) this->next->felfuz(adat);
        else this->next = new Lista(adat);
    }
    void kiir()
    {
        cout << this->adat << " ";
        if(this->next) this->next->kiir();
    }
};

class Queue
{
    Lista *first;
    Lista *last;

public:
    Queue()
    {
        first = NULL;
        last = NULL;
    }

    ~Queue()
    {
        if(first) delete first;
        first = NULL;
        last = NULL;
    }

    void push(int adat)
    {
        if(first)
        {
            last->next = new Lista(adat);
            last = last->next;
        }
        else
        {
            first = new Lista(adat);
            last = first;
        }
    }

    int elso()
    {
        return first ? first->adat : NULL;
    }

    int utolso()
    {
        return last ? last->adat : NULL;
    }

    int pop()
    {
        if(first)
        {
            int adat = first->adat;
            Lista *tmp = first;
            first = first->next;
            tmp->next = NULL;
            delete tmp;
            return adat;
        }
        return NULL;
    }

    bool isEmpty()
    {
        return first == NULL;
    }
};

class Stack
{
    Lista *first;
    Lista *last;

public:
    Stack()
    {
        first = NULL;
        last = NULL;
    }
    ~Stack()
    {
        if(first) delete first;
        first = NULL;
        last = NULL;
    }
    void push(int adat)
    {
        if(first)
        {
            Lista* tmp = new Lista(adat);
            tmp->next = first;
            first = tmp;
        }
        else
        {
            first = new Lista(adat);
            last = first;
        }
    }

    int elso()
    {
        return first ? first->adat : NULL;
    }

    int utolso()
    {
        return last ? last->adat : NULL;
    }

    int pop()
    {
        if(first)
        {
            int adat = first->adat;
            Lista *tmp = first;
            first = first->next;
            tmp->next = NULL;
            delete tmp;
            return adat;
        }
        return NULL;
    }
    bool isEmpty()
    {
        return first == NULL;
    }
};

int main()
{
    cout << "Hatulrol lancolt lista:" << endl
    Lista *l = new Lista(5);
    for(int i = 0; i < 10; i++)
    {
        l->felfuz(rand()%101);
    }
    l->kiir();

    Queue sor;
    Stack verem;
    for(int i = 0; i < 10; i++)
    {
        int tmp = rand()%100 + 1;
        sor.push(tmp);
        verem.push(tmp);
        cout << tmp << " ";
    }
    cout <<"Sor elemei:" << endl;
    while(!sor.isEmpty())
    {
        cout << sor.pop() << " ";
    }
    cout << "Verem elemei:"<< endl;
    while(!verem.isEmpty())
    {
        cout << verem.pop() << " ";
    }
    return 0;
}
