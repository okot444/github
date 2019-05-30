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
    char c;
    int operator == (const object& p) const;// ........
    friend ostream& operator << (ostream& out, const object& a);

    object(char ch);
    object();
};

ostream& operator << (ostream& out, const object& a)
{
    cout<<a.c <<' '<<endl;
    return out;
}
int object:: operator == (const object& p) const
{
    if ( c == p.c )
        return 0;
    return 1;
}
object::object()
{
    c = '\0';
}
object:: object(const char ch)
{
    c = ch;

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
        position last; // ������ ���������
        static const int size = 3;
        object m [size];
    };
    object a;// ���������, //////// ������� (?)
    position list:: End() const
    {
        return last;
    }
    void list:: Insert( object x, position p ) //////
    {
        if (p > last || p < 0 || p>=size){  // ��������� ���������� �� �������  //??
            cout<< "position is missing"<<endl;
            return ;
        }
        if (last == size+1) //???????? ������� � ����������� ������, last
            return;
        for ( int i=last; i>p; i--)  // �������, ��� �������� ����� ������� p ����������
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
        return last; // ���� ��� � ������
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
// ������� ������
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
    
    elem:: elem() // ��� ���������� ��������
    {
        o.c = '\0';
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
		position search(position p) const; // ����� �������
		position search_pred(position p) const; // ����� �����������

    };
    elem a;// ��������� �������
    int elem:: operator == (const elem& p) const
    {
        if (p.o.c ==  o.c )
            return 0;
        return 1;
    }
    position list::search_pred(position p) const
    {
        position temp;
        while (temp->next != p) // ������� ����������
            temp = temp->next;
        return temp;
    }
    position list::search(position p) const // ����� �������
    //���������� NULL, ���� ������� ���
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
    
    void list:: Insert(object x,position p) // ��������� �������? //
    {
        position q = search(p); // ���������� �� �������
        if (q != p ) // ������� ��� � ������ � ������� �� ����� ���������� ????
        {
            cout << "position doesn't exist"<<endl;
            return;
        }
        // �������� �������� 
        elem* el = new elem;      
        el->o = x;
        el->next = NULL;

        if (p == NULL) // ������� End, 
        {
            if (head == NULL){ //���������� �������, ���������  head
                head = el;
                return ;
            }
            q = head;
            //q = search_pred(NULL); // �������� �� ������
            while (q->next != NULL) // 
                q=q->next;
            q->next = el;
            return;
            
        }
       // �������� �� ����� �������, (�� endl)
        // q- ������� � ������
        if (p == head){ // ������� � ������
            el->next = head;
            head = el;
            return;
        }
        q = head;
        //q = search_pred(p); // �������� �� ���������� �������
        while (q->next != p)
            q=q->next;
        el->next = p;
        q->next = el;
    }
    position list::  Locate(object x) const 
    // ���������� ������� ������� x
    {
        position h = head;
        while (h ){ //����� �� �����
            if ( h->o == x)
                return h;
            h=h->next;
        }
        return NULL; // ���� ���, �� ���������� ����� end(l)
    }
    object& list:: Retrieve (position p) const // ?
   // ��������� ������ �� ������� � ������
    {
        position q = search(p); // ���������� �� �������
        if (q != p || q == NULL){ // ������� ���
            return a.o; // ���������� ��������� ������
        }
        return q->o;
    }
    position list::  Deletex (position p) // void ��������� �������
    {
        // �������� ���������� � 
        //���������� �� �������
       // cout<<"!"<<endl;
        position q=head;
        while ( q!=NULL && q!=p)// ????
            q=q->next;
        //position q = search(p); // ���������� �� �������
        if (q == NULL) // ������� ��� � ������ 
            return p;
        
        if (p == head){ // �������� ������
            head = delhead();
            return head; //(p->next)
        }
        //position temp =  search_pred(p);// ����� ����������
        position temp = head;
        while (temp->next != p) // ������� ����������
            temp = temp->next;

        if (p->next == NULL)// �������� ������
        {
            temp->next = NULL;
            delete p;
            return NULL;//temp->next; // 
            //return p = deltail();
        }
        // �������� � ��������
        temp->next = p->next;
        delete p;
        return temp->next; // ������� p 
    }
    position list:: Next(position p) const
    {
        position q = search (p);
        if (q != p) // ������� ���
            return a.next;
        if (p->next == NULL) // ���� p-���������
            return NULL;
        return p->next;
    }
    position list:: Previous(position p) const // ���������� ������� ����������� (q)
    {
        position q = search (p);
        if (q != p) // ������� ���
            return a.next;
        if ( p == head) // ���� p - ������ , �� ���������� ������� ���������� �������
            return a.next;
        q = search_pred(p);// ������� ������� � �������� �� �����������
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
           // ������ �������
           cout<< p->o.c<<' '<<endl;
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
    
    elem:: elem() // ��� ���������� ��������
    {
        o.c = '\0';
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
    elem a;// ��������� �������
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
    position list:: search(position p) const // ����� �������
    //���������� NULL, ���� ������� ���
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
    void list:: Insert(object x,position p) // ��������� �������? //
    {
        position q = search(p); // ���������� �� �������
        //if (q != p && q!=NULL) // ������� ��� � ������ � ������� �� ����� ���������� ????
        if (q != p)
        {
            cout << "position doesn't exist"<<endl;
            return;
        }
        // �������� �������� 
        elem* el = new elem;      
        el->o = x;
        el->next = NULL;
        el->prev = NULL;

        if (p == NULL) // ������� End, 
        {
            if (begin == NULL){ //���������� ������� (������ ������) , ���������  begin
                begin = end = el;
                return ;
            }
            // �������� ������
            end->next = el;
            el->prev = end;
            end = el;
            return;
        }
       // �������� �� ����� ������� p
        // q - ������� � ������
        if (p == begin){ // ������� � ������
            begin->prev = el;
            el->next = begin;
            begin = el;
            return;
        }
        // ������� � ��������
        el->prev = p->prev; // addbefore p
        el->prev->next = el;
        p->prev = el;
        el->next = p;
    }
    position list::  Locate(object x) const 
    // ���������� ������� ������� x
    {
        elem* h = begin;
        while (h ){ //����� �� �����
            if ( h->o == x)
                return h;
            h=h->next;
        }
        return NULL; // ���� ���, �� ���������� ����� end(l)
    }
    object& list:: Retrieve (position p) const // ?
   // ��������� ������ �� ������� � ������
    {
        position q = search(p); // ���������� �� �������
        if (q != p || q == NULL){ // ������� ���
            return a.o; // ���������� ��������� ������
        }
        return q->o;
    }
    position list::  Deletex (position p) // void ��������� �������
    {
        // �������� ���������� � 
        //���������� �� �������
        position q = search(p); // ���������� �� �������
        if (q != p ) // ������� ��� � ������ 
        {
            cout << "position doesn't exist"<<endl;
            return p;
        }
        
        if (p == begin){ // �������� ������ ???
            begin=p->next;
            p->next->prev=NULL;
            delete p;
            return begin; //(p->next)
        }
        position temp = p->prev; // ������� ����������
        if (p->next == NULL)// �������� ������
        {
            temp->next = NULL;
            end = temp;
            delete p;
            return temp->next; // 
        }
        // �������� � ��������
        temp->next = p->next;
        p->next->prev = temp;
        delete p;
        return temp->next; // ������� p 
    }
    position list:: Next(position p) const
    {
        position q = search (p);
        if (q != p) // ������� ���
            return a.next;
        if (p->next == NULL) // ���� p-���������
            return NULL;
        return p->next;
    }
    position list:: Previous(position p) const // ���������� ������� ����������� (q)
    {
        position q = search (p);
        if (q != p) // ������� ���
            return a.next;
        if ( p == begin) // ���� p - ������ , �� ���������� ������� ���������� �������
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
           cout<< p->o.c<<endl;
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
        o.c= '\0';
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
    elem a;//��������� �������
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
    void list:: move (position &h1, position &h2, position &pred)//����������� �������� �� ������� ������ �� ������
    // � - ������� �������� � ������ ������, pred - ������� ����� p
    // q ������� �� ������ ������
    {
        position temp = m[h1].next; 
        m[h1].next = h2;
        h2 = h1;
        pred = temp;
    }
    position list:: search(position p) const  // ����� ������� � ������
    // ���������� -1, ���� ������� ���
    {
        int i = head;
        while ( i != -1 && i != p ){ // ?
            i = m[i].next;
        }
        return i;
    }
    position list:: search_pred(position p) const  // ����� ���������� ������� � ������
    // ��� �������� �� ������������� �������
    {
        int i = head;
        while (m[i].next != p) // ������ �� ������
           i = m[i].next;
        return i;
    }
    position list:: End() const
    {
        return -1;//space
    }
    void list:: Insert(object x, position p) // -1 ?? �������
    {
        position i = search(p);
        //if ( i == -1 && p != space) // ������� ��� � ������ ????
        if (i!=p)
            return ;
            
        if (space == -1) //?? -1
            return;
        // ����������� �� ������ ������ � ������ 
        if (p == -1) // ������� endl
            {
                if (head == -1) { // ������� ������� �������� � ������ ������
                    move(space,head,space); 
                    m[head].o = x;
                    return;
                }
                // ������ ��������, ���������� � �����
                position temp = search_pred(-1); // ����� �����������
                move(space,m[temp].next,space); 
                m[m[temp].next].o = x;
                return;
            }
        // ������� � ������� (�� end)
        if (p == head) { // � ������
            move(space,head,space);
            m[head].o = x;
            return;
        }
        // � ��������
        move(space,head,space);
        m[p].o = x;
        return;
    }

    position list:: Locate(object x) const
    {
        position temp = head;
        while (temp != -1 ){ //����� �� �����
            if ( m[temp].o == x)
                return temp;
            temp = m[temp].next;
        }
        return -1; // ���� ���, �� ���������� ����� end(l)
    }
    object& list:: Retrieve (position p) const
    {
        position temp = head;
        while (temp != -1){ // ������ �� ������
            if (temp == p)
                return m[temp].o;
            temp = m[temp].next;
        }
        return a.o;

    }
    position list::  Deletex (position q) // void ��������� �������
    {
        // �������� ���������� � 
        //���������� �� �������
        position p = search(q); // ���������� �� �������
        if (p != q ){ // ������� ��� � ������ 
            cout << "position is missing"<<endl;
            return q;
        }
        
        if (q == head){ // �������� ������
            move(head,space,head);
            return head; //(p->next)
        }
        position pred =  search_pred(q);// ����� ����������
        if (m[q].next == -1){// �������� ������
            move(q,space,m[pred].next);
            return -1;
        }
        // �������� � ��������
        move(q,space,m[pred].next);
        return m[pred].next; // ������� p
    }
    position list:: Next (position p) const
    {
        position q = search(p);
        if (q == -1 || m[q].next == -1) // ��� � ������ ��� ��������� (temp == -1 �� ���������� (?))
            return -1; // endl
        return m[p].next;
    }
    position list:: Previous (position p)  const
    {
        position q = search (p);
        if (q != p) // ������� ���
            return a.next;
        if ( p == head) // ���� p - ������ , �� ���������� ������� ���������� �������
            return a.next;
        q = search_pred(p);// ������� ������� � �������� �� �����������
        return q;
    }
    void list:: Makenull ()
    {
        position temp = search_pred(-1); // ������ �� ������
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
           cout<< m[p].o.c; // ������ �������
           cout<<endl;
           p=m[p].next;
        }
        cout<<endl;
    }

}
using namespace linkedlist;
namespace lifo
{
    class stack
    { 
    public:
        //stack();
        void Makenull();
        void Push(object c);
        object Pop();
        object Top();
        int Empty();
        int Full();
    private:
        //elem* head;
        linkedlist:: list l;
    };
    void stack:: Makenull()
    {
        l.Makenull();
    }
    void stack:: Push(object c)
    {
        // вставка в пустой (добавление первого) или вставка в голову
        if (l.First() == l.End()) 
            l.Insert(c,l.First());
        else 
            l.Insert(c,l.First());
    }
    object stack:: Pop()
    {
        object p = l.Retrieve (l.First());
        l.Deletex(l.First());
        return p;
    }
    object stack:: Top()
    {
        return l.Retrieve (l.First());
    }
    int stack:: Empty()
    {
        if (l.First() == l.End()) //??????
            return 1;
        return 0;
    }
    int stack::Full()
    {
        return 0; //???
    }
    

}
namespace fifo_array
{
    typedef int position; 
    class queue
    {
    public:
        void Makenull();
        void Enqueue(object c);
        object Dequeue();
        object Front();
        int Full();
        int Empty();
    private:
        static const int LEN  = 6; 
        position next(position v) {return (v+1)%(LEN+1);}// �-� ���������� ������� ����������
        object s[LEN+1]; // LEN - ���-�� ���������
        position r, t; // t- хвост r- голова
    };
    void queue:: Makenull() // подготовка к работе
    {
        r = 1,t = 0;
    }
    void queue:: Enqueue(object c) // поместить в голову
    {
        t = next(t);
        s[t] = c;
    }
    object queue:: Dequeue() // извлечение из головы
    {
        position temp=r;
        r = next(r);
        return  s[temp]; // возвращаем извлечённое значение
    }
    object queue:: Front() // ф-я возвращает элемент в голове
    {
        return s[r];
    }
    int queue:: Empty() // проверка на пустоту
    {
        return next(t) == r ;
    }
    int queue:: Full()//проверка на полноту
    {
        return  next(next(t)) == r;
    }
}

namespace fifo_ringlist

{
    struct elem;
    typedef elem* position; 
    
    struct elem
    {
        char info;
        position next;
        elem();
        int operator == (const elem& p)const;
    };
    
    elem:: elem() // ��� ���������� ��������
    {
        info = '\0';
        next = this;
    } 
    class queue
    {
    public:
        queue(): tail(NULL){}
        void Makenull();
        void Enqueue(char c);
        char Dequeue();
        char Front();
        int Full();
        int Empty();
    private:
        elem* o_dellist(elem*t);
        elem* o_addfirst(int i);
        elem* o_addtail(elem*t,int i) ;
        void  o_delhead(elem*t);
        void o_addhead(elem*t,int i);
        position tail;
    };

    elem* queue:: o_dellist(elem*t)//(кольц.список) удаление списка
    {
        if (t!=0){ // проверка на непустоту списка
            elem*q=t->next; // сохран€ем голову
            while (q!=t) {
                t->next=q->next;
                free(q);
                q=t->next;
            }
            free(q);
        }
        return 0;
    }
    void queue:: o_addhead(elem*t,int i) //(кольц.список) вставка в голову  , ф-я используется в непустых списках
    {
        elem*p=(elem*)malloc(sizeof(elem)); // выдел€ем пам€ть
        p->info=i; // записываем значение
        p->next=t->next;
        t->next=p;
    }
    elem* queue:: o_addfirst(int i) //(кольц.список)  добавление первого элемента (возвращает указатель на хвост) ф-я используется в пустых списках
    {
        elem*t=(elem*)malloc(sizeof(elem));
        t->info=i;
        t->next=t;
        return t;
    }
    elem* queue:: o_addtail(elem*t,int i) //(кольц.список) вставка в хвост , ф-я используется в непустых списках
    {
        o_addhead(tail,i);
        return t->next;
    }
    void queue:: o_delhead(elem*t) // (кольц.список) удаление головы , ф-я используется в списках с 2 и более элементами
    {
        elem*q=t->next;
        t->next=q->next;// изменяем голову на новую
        free(q);// удаляем старую голову
    }
    void queue:: Makenull()
    {
        tail = o_dellist(tail);
    }
    void queue:: Enqueue(char c)
    {
        if (tail != NULL)
            tail = o_addtail(tail,c);
        else
            tail = o_addfirst(c);
    }
    char queue:: Dequeue()
    {
        char h = tail->next->info;
        o_delhead(tail);
        return h;

    }
    char queue:: Front()
    {
        return tail->next->info;
    }
    int queue:: Full()
    {
        return tail->next->next == tail->next;
    }
    int queue:: Empty()
    {
        return tail == tail->next;

    }
}

namespace fifo_atd_list
{
    using namespace linkedlist;
    class queue
    {
    public:
        void Makenull();
        void Enqueue(object c);
        object Dequeue();
        object Front();
        int Full();
        int Empty();
    private:
        list l;
    };
    void queue:: Makenull()
    {
        l.Makenull();
    }
    void queue:: Enqueue(object c)
    {
        l.Insert (c,l.End());
    }
    object queue:: Dequeue()
    {
        object p = l.Retrieve(l.First());
        l.Deletex (l.First());
        return p;
    }
    object queue:: Front()
    {
        return l.Retrieve(l.First());
    }
    int queue:: Full()
    {
        return 0; //?
    }
    int queue:: Empty()
    {
        if (l.First() == l.End()) 
            return 1;
        return 0;
    }
}

namespace mapping_atd_list
{
    //struct elem;
    typedef char* domaintype;
    typedef char** rangetype;
    class mapping
    {
    public:
        void Makenull();
        void Assign (domaintype d, rangetype r); // делает d = r
        int Compute (domaintype d ,rangetype r); // делает r = d
    private:
        list l;
    };
    void mapping:: Makenull()
    {
        l.Makenull();
    }
    void mapping:: Assign (domaintype d, rangetype r)
    {
         // поиск d
       // domaintype p = l.First();
       // while (p!=l.End() && p!= l.Retrieve(d))


    }
    int mapping:: Compute (domaintype d, rangetype r)
    {
        return 1;
    }
}

using namespace cursor;
int main()
{
    /*queue s;
    s.Makenull();
    s.Enqueue('a');
    s.Enqueue('b');
    object c= s.Front();
    cout<<c.c<<endl;*/
    linkedlist:: list l;
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
