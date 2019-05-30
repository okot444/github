/* Список адресов и имен. Из этого списка необходимо убрать дубликаты.
АТД - список
l - список
p - позиция 
x - объект
1. End(l) - позиция после последнего эл-та списка
2. Insert(x,p,l) - вставка объекта в позицию a(1) ... a(p-1),x,a(p+1)... a(n) 
    (позиции после x сдвигаются)
    вставка в End(l): a(1) ... a(n), x
    если позиции p нет, то результат неопределён
3. Locate(x,l) - возвращает позицию p объекта x в списке l
    если нет, то воз-ся  p = End(l)
    если несколько, то воз-ся p = первый найденный 
4. Retrieve (p,l) - возращает объект по позиции в списке
    если p = End(l)  или p нет в списке , то результат неопределён
5. Delete (p,l) - удалить элемент в позиции p в списке l
    a(1), a(2), ... a(p-1), a(p+1), ... a(n)
6. Next(p,l) - возвращает позицию следующего 
7. Previous(p,l) -  возвращает позицию предыдущего 
    если p - последний, то Next(p,l) = End(l)
    если p - первый, то Previous(p,l) результат неопределён
    если p = End(l) или нет в списке, то неопределено ничего
8. Makenull (l) - делает список пустым
9. First(l) - возвращает первую позицию в списке l
    если l - пустой, то возвращается позиция End(l)
10. Print(l) - выводит элементы в порядке их расположения в списке

*/



// ������
//#define N 20
//#define A 30 
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

ostream& operator << (ostream& out, const object& a)
{
    //cout<< "<<"<<endl;
    //for (int i=0; i<a.N; i++){
        cout<<a.name <<' '<< a.address<<endl;
  //  }
    return out;
}
int object:: operator == (const object& p) const
{
    if (strcmp(p.name,name) && strcmp(p.address,address) )
        return 0;
    return 1;
}
object::object()
{
    name[0] = '\0';
    address[0] = '\0';
}
object:: object(const char n[], const char a[])
{
    strcpy(name,n);
    strcpy(address, a);

}

namespace array
{
    typedef int position; 
    class list
    {
    public:
        list (): last(0){}
        position End() const;
        
        void Insert( object x, position p);
        position Locate( object x ) const;
        object Retrieve( position p ) const; // 
        position Deletex( position p );
        position Next( position p ) const;
        position Previous( position p ) const;
        void Makenull(); // ? 
        position First() const;
        void Print();
    private:
        position last; // первый свободный
        static const int size = 3;
        object m [size];
    };
    object a;// фиктивный, //////// позиция (?)
    position list:: End() const
    {
        return last;
    }
    void list:: Insert( object x, position p ) //////
    {
        if (p > last || p < 0 || p>=size){  // проверить существует ли позиция
            cout<< "position is missing"<<endl;
            return ;
        }
        if (last == size+1) //???????? вставка в заполненный массив, last
            return;
        for ( int i=last; i>p; i--)  // вставка, все элементы после позиции p сдвигаются
            m[i] = m[i-1];
        m[p] = x;
        last++;
    }
    position list:: Locate( object x ) const
    {
        int i = 0;
        while ( i < last){
            if (m[i] == x)
                return i;
            i++;
        }
        return last;  // если нет в списке
    }
    object list:: Retrieve(position p) const
    {
        if (p >= last || p<0)
            return a;
        return m[p];
    }
    position list:: Deletex( position p )
    {
        if (p >= last || p<0)
            return p ;
        for (int i=p; i<last-1; i++)
            m[i] = m[i+1];
        last--;
        return p;
    }
    position list:: Next( position p ) const
    {
        if (p >= last || p<0)
            return -1;
        /*if (p == size)  
            return last;*/
        return p+1;
    }
    position list:: Previous( position p ) const
    {
        if (p >= last || p<=0)
            return -1;
        return p-1;
    }
    void list:: Makenull()
    {
        last=0;
    }
    position list:: First() const
    {
        return 0;
    }
    void list:: Print()
    {
        cout<<"print"<<endl;
        if (last == 0)
            cout<<"empty"<<endl;
        for ( int i=0; i<last; i++)
            cout<<i<< ": "<< m[i] <<endl;
    }

    
}
// связный список
namespace linkedlist
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
        o.name[0] = '\0';
        o.address[0] = '\0';
        next = this;
    }
    class list
    {
    public:
        list():head(NULL) {}
        ~list() { release(); }
        position End() const;
        void Insert(object x, position p);
        position Locate(object x) const;
        object& Retrieve (position p) const; // ?
        position Deletex (position p);
        position Next (position p) const;
        position Previous (position p)  const;
        void Makenull (); // ? 
        void Print() const;
        
        position First () const;
        
        void set (char const *tname, char const *taddress);
    private:
    	void release();
		elem* head;
		elem* delhead();
		elem* deltail();
		position search(position p) const;// поиск позиции
      position search_pred(position p) const; // поиск предыдущего

    };
    elem a;// фиктивный элемент
    int elem:: operator == (const elem& p) const
    {
        if (strcmp(p.o.name,o.name) && strcmp(p.o.address,o.address) )
            return 0;
        return 1;
    }
    position list::search_pred(position p) const
    {
        position temp;
        while (temp->next != p)// находим предыдущий
            temp = temp->next;
        return temp;
    }
    position list::search(position p) const // поиск позиции
    //возвращает NULL, если позиции нет
    {
        position q=head;
        while ( q!=NULL && q!=p){// ????
            q=q->next;
        }
        return q;
    }
    elem* list:: delhead()// 
    {
        elem*temp=head;
        head = head->next;
        delete temp;
        return head;
    }
    elem* list:: deltail()//
    {
        elem*temp=head;
        head = head->next;
        delete temp;
        return head;
    }
    void list::release()
    {
        while(head)
            delhead();
    }
    position list:: End() const
    {
        return NULL;
       /* position temp = head;
        while (temp->next != NULL)
            temp = temp->next;
            cout<<"NULL"<<endl;
        return temp->next;*/
    }
    
    void list:: Insert(object x,position p) // изменение позиции? //
    {
        position q = search(p); // существует ли позиция
        if (q != p ) // позиции нет в списке и позиция не после последнего ????
        {
            cout << "position doesn't exist"<<endl;
            return;
        }
       // создание элемента 
        elem* el = new elem;      
        el->o = x;
        el->next = NULL;

        if (p == NULL) // позиция End, 
        {
            if (head == NULL){ //добавление первого, изменение  head
                head = el;
                return ;
            }
            q = head;
            //q = search_pred(NULL); // проходим до хвоста
            while (q->next != NULL) // 
                q=q->next;
            q->next = el;
            return;
            
        }
       // вставить на место позиции, (не endl)
        // q- позиция в списке
        if (p == head){ // вставка в голову
            el->next = head;
            head = el;
            return;
        }
        q = head;
        //q = search_pred(p); // проходим до предыдущей позиции
        while (q->next != p)
            q=q->next;
        el->next = p;
        q->next = el;
    }
    position list::  Locate(object x) const 
    // возвратить позицию объекта x
    {
        position h = head;
        while (h ){ //поиск до конца
            if ( h->o == x)
                return h;
            h=h->next;
        }
        return NULL; // если нет, то возвращаем конец end(l)
    }
    object& list:: Retrieve (position p) const // ?
    // возращает объект по позиции в списке
    {
        position q = search(p); // существует ли позиция
        if (q != p || q == NULL){ // позиции нет
            return a.o; // возвращаем фиктивный объект
        }
        return q->o;
    }
    position list::  Deletex (position p)  // void изменение позиции
    {
        

        position q=head;
        while ( q!=NULL && q!=p)// ????  существует ли позиция
            q=q->next;
        //position q = search(p);
        if (q == NULL) // позиции нет - возвращается та же позиция
            return p;
        
        if (p == head){ // удаление головы
            head = delhead();
            return head; //(p->next)
        }
        //position temp =  search_pred(p);
        position temp = head;
        while (temp->next != p) // нахождение предыдущего
            temp = temp->next;

        if (p->next == NULL)// удаление хвоста
        {
            temp->next = NULL;
            delete p;
            return NULL;//temp->next; // 
            //return p = deltail();
        }
       // удаление в середине
        temp->next = p->next;
        delete p;
        return temp->next; // позиция p 
    }
    position list:: Next(position p) const
    {
        position q = search (p);
        if (q != p) /// позиции нет
            return a.next;
        if (p->next == NULL) // если p-последний
            return NULL;
        return p->next;
    }
    position list:: Previous(position p) const // возвращает позицию предыдущего (q)
    {
        position q = search (p);
        if (q != p) // позиции нет
            return a.next;
        if ( p == head) // если p - голова , то возвращаем позицию фиктивного объекта
            return a.next;
        q = search_pred(p);// создаем позицию и проходим до предыдущего
        return q;
    }
    void list:: Makenull ()
    {
        position p=head;
        while (head != NULL){
            head=head->next;
            delete p;
            p = head;
        }
    } 
    position list:: First () const
    {
        if (head)
            return head;
        return NULL;

    }
    void list:: Print() const
    {
        cout<<"print"<<endl;
        position p = head;
        if (p == NULL){
            cout<< "empty" <<endl;
            return;
        }
        while (p){
           cout<< p->o.name<<' '<<p->o.address<<endl;
           cout<<endl;
           p=p->next;
        }
    }
}

namespace doublelinkedlist
{
    struct elem;
    typedef elem* position; 
    struct elem
    {
        object o;
        position next;
        position prev;
        elem();
        int operator == (const elem& p)const;
    };
    
    elem:: elem() // для фиктивного элемента
    {
        o.name[0] = '\0';
        o.address[0] = '\0';
        next = this;
        prev = this;
    }
    class list
    {
    public:
        list() : begin(NULL), end(NULL) {}
        ~list() { release(); }
        position End() const;
        void Insert(object x, position p);
        position Locate(object x) const;
        object& Retrieve (position p) const; // ?
        position Deletex (position p);
        position Next (position p) const;
        position Previous (position p)  const;
        void Makenull (); //
        position First () const;
        void Print() const;
        
        void set (char const *tname, char const *taddress);
        
        
        
    private:
    	position search(position p) const ;
    	void release();
    	position begin;
    	position end;


    };
    elem a;// фиктивный элемент
    void list:: release()
    {
        if (begin){
            while(begin->next){
                 begin = begin->next;
                 delete begin->prev;
                 begin->prev = NULL;
            }
            delete begin;
        }
    }
    position list:: search(position p) const// поиск позиции
    //возвращает NULL, если позиции нет
    {
        position q=begin;
        //while ( q->next!=NULL || q!=p){ // ?
        while (q!= NULL && q!=p){
            q=q->next;
        }
        return q;
    }
    position list:: End() const
    {
        return NULL;
    }
     void list:: Insert(object x,position p) // изменение позиции? //
    {
        position q = search(p); // существует ли позиция
        //if (q != p && q!=NULL) // позиции нет в списке и позиция не после последнего ????
        if (q != p)
        {
            cout << "position doesn't exist"<<endl;
            return;
        }
        // создание элемента 
        elem* el = new elem;      
        el->o = x;
        el->next = NULL;
        el->prev = NULL;

        if (p == NULL) // позиция End, 
        {
            if (begin == NULL){  //добавление первого (пустой список) , изменение  begin
                begin = end = el;
                return ;
            }
              // непустой список
            end->next = el;
            el->prev = end;
            end = el;
            return;
        }
        // вставить на место позиции p
        // q- позиция в списке
        if (p == begin){ // вставка в голову
            begin->prev = el;
            el->next = begin;
            begin = el;
            return;
        }
        // вставка в середине
        el->prev = p->prev; // addbefore p
        el->prev->next = el;
        p->prev = el;
        el->next = p;
    }
    position list::  Locate(object x) const 
    // возвратить позицию объекта x
    {
        elem* h = begin;
        while (h ){ //поиск до конца
            if ( h->o == x)
                return h;
            h=h->next;
        }
        return NULL; // если нет, то возвращаем конец end(l)
    }
    object& list:: Retrieve (position p) const // ?
   // возращает объект по позиции в списке
    {
        position q = search(p); // существует ли позиция
        if (q != p || q == NULL){ // позиции нет
            return a.o; // возвращаем фиктивный объект
        }
        return q->o;
    }
    position list::  Deletex (position p) // void изменение позиции
    {
        // удаление последнего и 
        //существует ли позиция
        position q = search(p); // существует ли позиция
        if (q != p ) // позиции нет в списке 
        {
            cout << "position doesn't exist"<<endl;
            return p;
        }
        
        if (p == begin){  // удаление головы ???
            begin=p->next;
            p->next->prev=NULL;
            delete p;
            return begin; //(p->next)
        }
        position temp = p->prev; 
        if (p->next == NULL)// удаление хвоста
        {
            temp->next = NULL;
            end = temp;
            delete p;
            return temp->next; // 
        }
        // удаление в середине
        temp->next = p->next;
        p->next->prev = temp;
        delete p;
        return temp->next; // позиция p 
    }
    position list:: Next(position p) const
    {
        position q = search (p);
        if (q != p) // позиции нет
            return a.next;
        if (p->next == NULL) // если p-последний
            return NULL;
        return p->next;
    }
    position list:: Previous(position p) const // возвращает позицию предыдущего (q)
    {
        position q = search (p);
        if (q != p) // позиции нет
            return a.next;
        if ( p == begin) // если p - голова , то возвращаем позицию фиктивного объекта
            return a.next;
        return q->prev;
    }
    void list:: Makenull ()
    {
        position p = begin;
        while (begin){
            begin = begin->next;
            delete p;
            p = begin;
        }
    } 
    position list:: First () const
    {
        if (begin){
            return begin;
        }
        return NULL;

    }
    void list:: Print() const
    {
        cout<<"print"<<endl;
        position p = begin;
        if (p == NULL){
            cout<< "empty" <<endl;
            return;
        }
        while (p){
           // ������ �������
           cout<< p->o.name<<' '<<p->o.address<<endl;
           cout<<endl;
           p=p->next;
        }
    }
}


namespace cursor
{
    struct elem;
    class list;
    typedef int position; 
    struct elem
    {
        object o;
        int next;
        elem();
    };
    elem:: elem() // ��� ���������� ��������
    {
        o.name[0] = '\0';
        o.address[0] = '\0';
        next  = -1;
    }
    class list
    {
    public:
        list() ;
        //~list() ;
        position End() const;
        void Insert(object x, position p);
        position Locate(object x) const;
        object& Retrieve (position p) const; 
        position Deletex (position p);
        position Next (position p) const;
        position Previous (position p)  const;
        void Makenull (); //
        position First () const;
        void Print() const;
        void set (char const *tname, char const *taddress);
    private:
        void move (position &h1, position &h2, position &pred);
        position search(position p) const ;
        position search_pred(position p) const ;
        void release();
        static const int size =20;
        static position space ;
        static elem m[size];
        //static elem m[];
        position head;
        

    };
    elem a;// фиктивный элемент
    elem list:: m[size];// = {a,a,a,a,a};
    position list:: space = 0;
    list:: list() 
    {
        int i=0;
        head = -1; //?

        for (; i<size-1; i++)
            m[i].next = i+1;
        m[i].next = -1;
    }
    void list:: move (position &h1, position &h2, position &pred)
    // перемещение элемента  h1 в h2
    // 
    {
        position temp = m[h1].next; 
        m[h1].next = h2;
        h2 = h1;
        pred = temp;
    }
    position list:: search(position p) const   // поиск позиции в списке
    // возвращает -1, если позиции нет
    {
        int i = head;
        while ( i != -1 && i != p ){ // ?
            i = m[i].next;
        }
        return i;
    }
    position list:: search_pred(position p) const  // поиск предыдущей позиции в списке
    // нет проверки на существование позиции
    {
        int i = head;
        while (m[i].next != p) // проход до хвоста
           i = m[i].next;
        return i;
    }
    position list:: End() const
    {
        return -1;//space
    }
    void list:: Insert(object x, position p)
    {
        position i = search(p);
        //if ( i == -1 && p != space) // позиции нет в списке ????
        if (i!=p)
            return ;
            
        if (space == -1) //?? -1
            return;
         // перемещение из пустого списка в другой 
        if (p == -1) // позиция endl
            {
                if (head == -1) { // вставка первого элемента в пустой список
                    move(space,head,space); 
                    m[head].o = x;
                    return;
                }
                // список непустой, добавление в конец
                position temp = search_pred(-1); // поиск предыдущего (хвоста)
                move(space,m[temp].next,space); 
                m[m[temp].next].o = x;
                return;
            }
        // вставка в позицию (не end)
        if (p == head) { // в голову
            move(space,head,space);
            m[head].o = x;
            return;
        }
        // в середине
        move(space,head,space);
        m[p].o = x;
        return;
    }

    position list:: Locate(object x) const
    {
        position temp = head;
        while (temp != -1 ){ //поиск до конца
            if ( m[temp].o == x)
                return temp;
            temp = m[temp].next;
        }
        return -1; // если нет, то возвращаем конец end(l)
    }
    object& list:: Retrieve (position p) const
    {
        position temp = head;
        while (temp != -1){ // проход по списку
            if (temp == p)
                return m[temp].o;
            temp = m[temp].next;
        }
        return a.o;

    }
    position list::  Deletex (position q)  // void изменение позиции
    {
        // удаление последнего и 
        //существует ли позиция
        position p = search(q);  // существует ли позиция
        if (p != q ){  // позиции нет в списке 
            cout << "position is missing"<<endl;
            return q;
        }
        
        if (q == head){ // удаление головы
            move(head,space,head);
            return head; //(p->next)
        }
        position pred =  search_pred(q);// найти предыдущий
        if (m[q].next == -1){// удаление хвоста
            move(q,space,m[pred].next);
            return -1;
        }
        // удаление в середине
        move(q,space,m[pred].next);
        return m[pred].next; // позиция p
    }
    position list:: Next (position p) const
    {
        position q = search(p);
        if (q == -1 || m[q].next == -1) // нет в списке или последний (temp == -1 не определено (?))
            return -1; // endl
        return m[p].next;
    }
    position list:: Previous (position p)  const
    {
        position q = search (p);
        if (q != p) // позиции нет
            return a.next;
        if ( p == head) // если p - голова , то возвращаем позицию фиктивного объекта
            return a.next;
        q = search_pred(p);// проходим до предыдущего
        return q;
    }
    void list:: Makenull ()
    {
        position temp = search_pred(-1); // проход до хвоста
        m[temp].next = space;
        space = head;
        head = -1;
    }
    position list:: First () const
    {
       // if (head != -1)
            return head;
        //return -1; // endl

    }
    void list:: Print () const
    {
        cout<<"print"<<endl;
        if (head == -1){
            cout<< "empty" <<endl;
            return;
        }
        position p = head;
        while (p != -1){
           cout<< m[p].o.name<<' '<<m[p].o.address; // печать объекта
           cout<<endl;
           p=m[p].next;
        }
        cout<<endl;
    }

}
using namespace linkedlist;
namespace lifo
{
    struct elem
    {
        object o;
        int next;
        elem();
    };
    elem:: elem() 
    {
        o.name[0] = '\0';
        o.address[0] = '\0';
        next  = -1;
    }
    class stack
    { 
    public:
        void Makenull();
        void Push(object c);
        char Pop(){return s[--up];}
        char Top(){return s[up];}
        int Empty(){return up==EMPTY;}
        int Full(){return up==FULL;}
    private:
        //elem* head;
        list l;
    };
    void stack:: Push(char c)
    {
        // вставка в пустой (добавление первого) или вставка в голову
        if (l.Empty())
            l.Insert(c,l.First());
        else 
            l.Insert(c,l.End());
    }
    char stack:: Pop()
    {
        
    }

    

}

namespace fifo 
{
    class queue
    {
    public:
        void Enqueue(char c);
        char Dequeue();
        char Front();
        int Full();
        int Empty();
        void Makenull();
    
    private:
       // int next(int v) {return (v+1)%(LEN+1);}// �-� ���������� ������� ����������
        //char s[LEN+1]; // LEN - ���-�� ���������
        int r, t; // t- ����� r- ������
        
    };
}
using namespace cursor;
void  set (list *l)
{
    
    //char n[]= "John";
    //char a[]="New York";
    //x->name = n;
    object x("John","New York");
    l->Insert(x,l->End());
   // position p = l->First();
    //l->Insert(x,l->End());
    
    strcpy(x.name,"Amy");
    strcpy(x.address, "London");
    l->Insert(x,l->End());
	l->Insert(x,l->End());
	l->Insert(x,l->End());
	
    strcpy(x.name,"Tom");
    strcpy(x.address, "Street");
    l->Insert(x,l->End());
   // l->Insert(x,l->End());
   // l->Insert(x,l->End());
   // position p = l->First();
    //cout<<p->o.name<<endl;
}

int main()
{
    //object x( "Paul","New York" );
    //object y( "Este","Los Angeles" );
    list l;
   // set(&l);
    l.Print();
    
    position p  = l.First(),q;
    while ( p != l.End() ) { 
        q = l.Next(p);
        while( q != l.End() ) {
            if (l.Retrieve(p) == l.Retrieve(q)){ // 
                q = l.Deletex(q);
            }
            else{
                q = l.Next(q);
            }
        }
        p = l.Next(p);
    }

    l.Print();
    l.Makenull();
    l.Print();
    
}
