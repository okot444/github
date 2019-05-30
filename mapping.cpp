#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;
struct object
{
    static const int N = 20;
    static const int A = 30;

    char name [N]; 
    char address [A]; 
    int operator == (const object& p) const;// ........
    friend ostream& operator << (ostream& out, const object& a);

    object(const char n[], const char a[]);
    object();
};

namespace mapping_linkedlist
{
    struct elem;
    typedef elem* position; 
    
    struct elem
    {
        object o;
        position next;
        elem();
        int operator == (const elem& p)const;
    };
    
    elem:: elem() // для фиктивного элемента
    {
        o.name[0] = '\0';       //d
        o.address[0] = '\0';    //r
        next = this;
    }


    typedef elem* domaintype;
    typedef unsigned char rangetype;
    class mapping
    {
    public:
        mapping():head(NULL){}
        void Makenull();
        void Assign (char* d,char* r); // делает d = r
        int Compute (char* d ,char** r); // делает r = d
    private:
        elem *head;
    };
    void Makenull()
    {
        // delall;
    }
    void mapping:: Assign (char* d,char* r )// делает d = r
    {
        elem* p=head;
        while ( p->next->o.name != d  && p->next ) // поиск d, возвращает предыдущий
            p=p->next;
        if ( p->next ){ // d существует
            strcmp(p->next->o.address, r); // m(d) = r
            return;
        }
        // добавление первого или добавление в конец
        elem* el = new elem;
        strcmp( el->o.address,r );
        el->next = NULL;

        if ( head ){ // добавление в конец
            p->next = el;
            return;
        }
        // добавление первого
        head = el;
    }
    int mapping:: Compute (char* d ,char** r) //    char**
    {
        elem* p=head;
        while ( p->o.name != d  && p ) // поиск d,
            p=p->next;
        if (p){
            strcmp(*r, p->o.address);
            return 1;
        }
        return 0;
    }

}


int main()
{

}