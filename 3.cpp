/* ������ ������� � ����. �� ����� ������ ���������� ������ ���������.
��� - ������
l - ������
p - ������� 
x - ������
1. End(l) - ������� ����� ���������� ��-�� ������
2. Insert(x,p,l) - ������� ������� � ������� a(1) ... a(p-1),x,a(p+1)... a(n) 
    (������� ����� x ����������)
    ������� � End(l): a(1) ... a(n), x
    ���� ������� p ���, �� ��������� ����������
3. Locate(x,l) - ���������� ������� p ������� x � ������ l
    ���� ���, �� ���-��  p = End(l)
    ���� ���������, �� ���-�� p = ������ ��������� 
4. Retrieve (p,l) - ��������� ������ �� ������� � ������
    ���� p = End(l)  ��� p ��� � ������ , �� ��������� ����������
5. Delete (p,l) - ������� ������� � ������� p � ������ l
    a(1), a(2), ... a(p-1), a(p+1), ... a(n)
6. Next(p,l) - ���������� ������� ���������� 
7. Previous(p,l) -  ���������� ������� ����������� 
    ���� p - ���������, �� Next(p,l) = End(l)
    ���� p - ������, �� Previous(p,l) ��������� ����������
    ���� p = End(l) ��� ��� � ������, �� ������������ ������
8. Makenull (l) - ������ ������ ������
9. First(l) - ���������� ������ ������� � ������ l
    ���� l - ������, �� ������������ ������� End(l)
10. Print(l) - ������� �������� � ������� �� ������������ � ������

*/



// ??????
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
        if (p > last || p < 0 || p>=size){  // ��������� ���������� �� �������
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
        return last;  // ���� ��� � ������
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
		position search(position p) const;// ����� �������
      	position search_pred(position p) const; // ����� �����������

    };
    elem a;// ��������� �������
    int elem:: operator == (const elem& p) const
    {
        if (strcmp(p.o.name,o.name) && strcmp(p.o.address,o.address) )
            return 0;
        return 1;
    }
    position list::search_pred(position p) const// ����� �������
    // ���������� ������� �����������
    //���������� NULL, ���� ������� ���
    {
        position q=head;
      	while ( q != NULL)
        	if (q->next != p)
            	q=q->next;
            else
            	return q;
        
        return q;
    }
    elem* list:: delhead()// 
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
    }
    
    void list:: Insert(object x,position p) //
    {
        position q;
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
            q = search_pred(NULL); // �������� �� ������
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
        q = search_pred(p); // �������� �� ���������� �������
        if (q == NULL)
        	return ;
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
        position q = search_pred(p); // ���������� �� �������
        
        if (q == NULL){ // ������� ���
            return a.o; // ���������� ��������� ������
        }
        return q->next->o;
    }
    position list::  Deletex (position p)  // void ��������� �������
    {
        

       /* position q=head;
        while ( q!=NULL && q!=p)// ????  ���������� �� �������
            q=q->next;
        //position q = search(p);
        if (q == NULL) // ������� ��� - ������������ �� �� �������
            return p;*/
        if (p == head){ // �������� ������
        cout<<"p=head"<<endl;
            head = delhead();
            return head; //(p->next)
        }
        position temp =  search_pred(p);
        if (temp == NULL)
        {
        	cout<<"temp NULL"<<endl;
        	return p; // ������� ��� - ������������ �� �� �������
        }
        /*position temp = head;
        while (temp->next != p) // ���������� �����������
            temp = temp->next;*/
		cout<<"end"<<endl;
        if (p->next == NULL)// �������� ������
        {
        	cout<<"deltail"<<p->o.name<<endl;
            temp->next = NULL;
            delete p;
            return NULL;//temp->next; // 
            //return p = deltail();
        }
       // �������� � ��������
       cout<<"mid"<<endl;
        temp->next = p->next;
        delete p;
        return temp->next; // ������� p 
    }
    position list:: Next(position p) const
    {
    	if (p == head)
    		return p->next;
    		position q = search_pred (p);
        if (q == NULL) /// ������� ���
        {
        	cout<<"no p"<<endl;
            return a.next;
        }
        if (p->next == NULL) // ���� p-���������
            return NULL;
        return p->next;
    }
    position list:: Previous(position p) const // ���������� ������� ����������� (q)
    {
    	if (p == head)
    		return p->next;
        position q = search_pred (p);
       
        if (q == NULL ) // ������� ��� q!=p
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
    
    elem:: elem() // ��� ���������� ��������
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
        
    private:
    	int search(position p) const ;
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
    int list::search(position p) const// ����� �������
    // ���������� ������� �����������
    //���������� NULL, ���� ������� ���
    {
        position q=begin;
      	while ( q != NULL)
      		if (q!=p)
            	q=q->next;
            else 
            	return 1;
            	
        return 0;
    }
    /*position list:: search(position p) const// ����� �������
    //���������� NULL, ���� ������� ���
    {
        position q=begin;
        //while ( q->next!=NULL || q!=p){ // ?
        while (q!= NULL && q!=p){
            q=q->next;
        }
        return q;
    }*/
    position list:: End() const
    {
        return NULL;
    }
     void list:: Insert(object x,position p) // ��������� �������? //
    {
        
        // �������� �������� 
        elem* el = new elem;      
        el->o = x;
        el->next = NULL;
        el->prev = NULL;

        if (p == NULL) // ������� End, 
        {
            if (begin == NULL){  //���������� ������� (������ ������) , ���������  begin
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
        // q- ������� � ������
        if (p == begin){ // ������� � ������
            begin->prev = el;
            el->next = begin;
            begin = el;
            return;
        }
        // ������� � �����
        if (p == end){
        	
        	el->o = p->o;
        	p->o = x;
        	end = el;
        	end->prev = p;
        	p->next = end;
        	
        	
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
        int q = search(p); // ���������� �� �������
        if (q==0){ // ������� ���
            return a.o; // ���������� ��������� ������
        }
        return p->o;
    }
    position list::  Deletex (position p) // void ��������� �������
    {
        // �������� ���������� � 
        //���������� �� �������
        
        if (p == begin){  // �������� ������ ???
            begin=p->next;
            p->next->prev=NULL;
            delete p;
            return begin; //(p->next)
        }
        position temp = p->prev; 
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
        int q = search (p);
        if (q ==0) // ������� ���
            return a.next;
        if (p->next == NULL) // ���� p-���������
            return NULL;
        return p->next;
    }
    position list:: Previous(position p) const // ���������� ������� ����������� (q)
    {
        int q = search (p);
        if (q == 0) // ������� ���
            return a.next;
        if ( p == begin) // ���� p - ������ , �� ���������� ������� ���������� �������
            return a.next;
        return p->prev;
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
    elem:: elem() // 
    {
        o.name[0] = '\0';
        o.address[0] = '\0';
        next  = -1;
    }
    class list
    {
    public:
        list() ;
        ~list() {Makenull();}
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
    elem a;// ��������� �������
    elem list:: m[size];// = {};
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
    // ����������� ��������  h1 � h2
    // 
    {
        position temp = m[h1].next; 
        m[h1].next = h2;
        h2 = h1;
        pred = temp;
    }
    position list:: search(position p) const   // ����� ������� � ������
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
    void list:: Insert(object x, position p)
    {
        /*position i = search(p);
        //if ( i == -1 && p != space) // ������� ��� � ������ (?)
        if (i!=p)
            return ;
            */
        if (space == -1) //
            return;
         // ����������� �� ������� ������ � ������ 
        if (p == -1) // ������� endl
            {
                if (head == -1) { // ������� ������� �������� � ������ ������
                    move(space,head,space); 
                    m[head].o = x;
                    return;
                }
                // ������ ��������, ���������� � �����
                position temp = search_pred(-1); // ����� ����������� (������)
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
    position list::  Deletex (position q)  // void ��������� �������
    {
        // �������� ���������� � 
        //���������� �� �������
        position p = search(q);  // ���������� �� �������
        if (p != q ){  // ������� ��� � ������ 
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
        q = search_pred(p);// �������� �� �����������
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
           cout<< m[p].o.name<<' '<<m[p].o.address; // ������ �������
           cout<<endl;
           p=m[p].next;
        }
        cout<<endl;
    }

}
using namespace doublelinkedlist;
void  set (list *l)
{
    
    //char n[]= "John";
    //char a[]="New York";
    //x->name = n;
    object x("John","New York");
    l->Insert(x,l->End());
   // position p = l->First();
    l->Insert(x,l->End());
    
    strcpy(x.name,"Amy");
    strcpy(x.address, "London");
    l->Insert(x,l->End());
	l->Insert(x,l->End());
	l->Insert(x,l->End());
	
    strcpy(x.name,"Tom");
    strcpy(x.address, "Street");
    l->Insert(x,l->End());
    l->Insert(x,l->End());
   // l->Insert(x,l->End());
   // position p = l->First();
    //cout<<p->o.name<<endl;
}

int main()
{
    object x( "Paul","New York" );
    //object y( "Este","Los Angeles" );
    list l;
    set(&l);
    l.Print();
    
   // position p=l.Next(l.End());
    //l.Insert(x,p);
    
    position p  = l.First(),q;
    while ( p != l.End() ) { 
        q = l.Next(p);
        while( q != l.End() ) {
            if (l.Retrieve(p) == l.Retrieve(q)){ // 
            	cout<<q->o.name<<endl;
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
