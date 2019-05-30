#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;
struct object
{
    static const int N = 20;
    static const int A = 30;

    char info; 
    int operator == (const object& p) const;// ........
    friend ostream& operator << (ostream& out, const object& a);

    object(const char n[], const char a[]);
    object();
};

namespace mapping_linkedlist
{
    struct node;
    typedef node* position; 
    
    struct node
    {
        object o;
        node*next;
        node();
        int operator == (const node& p)const;
    };
    
    node:: node() // для фиктивного элемента
    {
       // o.name[0] = '\0';       //d
        //o.address[0] = '\0';    //r
        o.info = '\0';
        next = NULL;
    }


    class tree
    {
    public:
        node* Parent(node* p);
        node* LeftMostChild(node* n);
        node* RightSibling(node* n);
        char Label(node* n);
        node* Create(char v);
        node* Create(char v, node*t1);
        node* Create(char v, node*t1, node*t2);

        node* Root();
        void Makenull();
    private:
        node* root;
        static const int N = 20;
        static node m[N];
        static const int space = -1;
        node* lfprn(node* root);
    };
    node tree:: m[N];
    node* lfprn(node* root) // прямой обход (слева на право)
    {
        node* q = root;
        return q;
    }
    node* search_parent(node* root,node* n) // прямой обход (слева на право)
    // находит родителя узла n
    {
        node* q = root;
        while () // в стеке не останется 1 элемент
        {
            if (q != NULL)
            {
                // добавить в стек
                q = leftmostchild();
            }
                
        }
        return q;
    }
    node* tree:: Parent(node* p)
    {
        //поиск родителя узла
        return p;

    }

    node* tree:: LeftMostChild(node* n)
    {
        return n->next;
    }
    node* tree:: RightSibling(node* n)
    {
        //найти родителя узла
        // найти правого брата (следующий после узла n)
    }
    char tree:: Label(node* n)
    {
        // поиск узла(по метке в массиве?)
        return 'c';

    }
    node* tree:: Create(char v)
    {
        node* r = new node; //  создание элемента (ф-я?)
        r->o.info = v;
        return r;
    }
    node* tree:: Create(char v,node* t1)
    {
        node* r = new node; //  создание элемента (ф-я?)
        r->o.info = v;

        r->next = t1;

        



        return r;
    }
    node* tree:: Root()
    {

    }
    void tree:: Makenull()
    {

    }
}